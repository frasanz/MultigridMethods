#include <stdio.h>
#include "multigrid_kernel.cu"

#define N_MALLAS 12
#define BLOCK_SIZE 16

void gpu_imprime(Grid g, const char *);
void gpu_muestra(Grid g, const char *);
void multigrid(Grid *u, 
               Grid *f, 
							 Grid *v, 
							 Grid *d, 
							 int m,
							 double *max,
							 double *def,
							 double *host_def); 


int main(){
	int i;
	int dim;
	int size;
	int sizetotal=0;
	double max=1.0;
	double max_ant;

	/* Definition of the Grids */
	Grid u[N_MALLAS];
	Grid f[N_MALLAS];
	Grid v[N_MALLAS];
	Grid d[N_MALLAS];

	/* Double to compute max(defect) of each file */
	double * gpu_def;    //In GPU
	double * host_def;   //In Host

	/* malloc */
	for(i=0; i<N_MALLAS; i++){
		dim  =  (int)pow(2,i+1)+1;
		size =  dim*dim;
		u[i].d = dim;
		f[i].d = dim;
		v[i].d = dim;
		d[i].d = dim;

		u[i].size = size;
		f[i].size = size;
		v[i].size = size;
		d[i].size = size;

		cudaMalloc(&u[i].v, size*sizeof(double));
		cudaMalloc(&v[i].v, size*sizeof(double));
		cudaMalloc(&d[i].v, size*sizeof(double));
		cudaMalloc(&f[i].v, size*sizeof(double));
		sizetotal +=4*size;
	}
	int m = N_MALLAS - 1 ;
	dim = (int)pow(2,m+1)+1;
	size = dim*dim;
	cudaMalloc(&gpu_def, size*sizeof(double));
	sizetotal+=size;
	host_def=(double*)malloc(size*sizeof(double));

	printf("We need about %d Mb in the GPU\n", sizetotal*sizeof(double)/1024/1024);

	/* To call CUDA */
	dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid((dim+BLOCK_SIZE-1)/dimBlock.x, (dim+BLOCK_SIZE-1)/dimBlock.y);

	/* Inicializamos la malla de la función */
	cero<<<dimGrid, dimBlock>>>(f[m]);

	/* Initialize u[m] with random values */
	cero<<<dimGrid, dimBlock>>>(u[m]);
	random<<<dimGrid, dimBlock>>>(u[m]);

	/* main loop */
	for(i=0; i<N_MALLAS; i++){
		max_ant = max;
		max = 0.0;
		multigrid(&u[0],&f[0], &v[0], &d[0], m, &max, gpu_def, host_def);
		printf("[Iteration #%d] nd=%e ratio=%f\n", i, max, max/max_ant);
	}

	/* Free memory */
	for(i=0; i<N_MALLAS; i++){
		cudaFree(u[i].v);
		cudaFree(f[i].v);
		cudaFree(v[i].v);
		cudaFree(d[i].v);
	}
	cudaFree(gpu_def);
	free(host_def);
	
	return 0;
}

void gpu_imprime(Grid g, const char *nombre){
	FILE *f;
	f=fopen(nombre, "w");
	int i,j;
	double *hg;
	hg = (double*)malloc(g.size*sizeof(double));
	cudaMemcpy(hg,g.v, g.size*sizeof(double), cudaMemcpyDeviceToHost);

	for(i=0; i< g.d; i++){
		for(j=0; j< g.d; j++){
			fprintf(f, "%d %d %f\n", i, j, hg[I(g.d,i,j)]);
		}
		fprintf(f,"\n");
	}
	fclose(f);
}

void gpu_muestra(Grid g, const char *nombre){
	int i,j;
	double *hg;
	hg = (double *)malloc(g.size*sizeof(double));
	cudaMemcpy(hg, g.v, g.size*sizeof(double), cudaMemcpyDeviceToHost);

	printf("%s=\n", nombre);
	for( i = 0 ; i<g.d; i++){
		for(j=0; j<g.d; j++){
			printf("%f ",hg[I(g.d,i,j)]);
		}
		printf("\n");
	}
}

void multigrid(Grid *u,
               Grid *f, 
							 Grid *v,
							 Grid *d,
							 int m,
							 double *max,
							 double *def,
							 double *host_def)
{
	int dim;
	int dim_;
	int i;
	
	/* Primer caso, malla 0, solución */
	if(m == 0){
		exacta<<<1,1>>>(u[m],f[m]);
	}
	else{ /* Some definitions to call cuda */
		dim  = (int)pow(2,m+1)+1;
		dim_ = (int)pow(2,m)+1;
		dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
		dim3 dimGrid((dim+BLOCK_SIZE-1)/dimBlock.x, (dim+BLOCK_SIZE-1)/dimBlock.y);
		dim3 dimGrid_((dim_+BLOCK_SIZE-1)/dimBlock.x,(dim_+BLOCK_SIZE-1)/dimBlock.y);

		/* some grids == 0 */
		cero<<<dimGrid , dimBlock>>>(v[m]);
		cero<<<dimGrid , dimBlock>>>(d[m]);
		cero<<<dimGrid_, dimBlock>>>(u[m-1]);
		cero<<<dimGrid_, dimBlock>>>(f[m-1]);

		/* R-N smoothing */
		suaviza_r<<<dimGrid, dimBlock>>>(u[m],f[m]);
		suaviza_n<<<dimGrid, dimBlock>>>(u[m],f[m]);

		/* Compute the defect */
		defecto<<<dimGrid, dimBlock>>>(u[m],f[m],d[m]);

		/* Defect from d[m] to f[m-1] */
		restringe<<<dimGrid_, dimBlock>>>(d[m],f[m-1]);

		/* Call to multigrid */
		multigrid(&u[0],&f[0],&v[0],&d[0],m-1,max, def, host_def);

		/* Interpolate from u[m-1] to v[m] */
		interpola<<<dimGrid_, dimBlock>>>(u[m-1], v[m]);

		/* Sum */
		suma<<<dimGrid, dimBlock>>>(u[m],v[m]);

		/* R-N smoothing */
		suaviza_r<<<dimGrid, dimBlock>>>(u[m],f[m]);
		suaviza_n<<<dimGrid, dimBlock>>>(u[m],f[m]);

		/* If we're in the upper grid, check the defect */
		if(m==N_MALLAS-1){
			defecto<<<dimGrid, dimBlock>>>(u[m],f[m],d[m]);
			dim3 dg((dim+BLOCK_SIZE-1)/dimBlock.x,1);
			dim3 db(BLOCK_SIZE,1);

			/* compute the max or each row */
			maxx<<<dg, db>>>(d[m],def);

			/* copy the vector to the host */
			cudaMemcpy(host_def, def, dim*dim*sizeof(double), cudaMemcpyDeviceToHost);

			max[0]=0.0;
			for(i=0;i<dim;i++){
				if(max[0]<host_def[i])
					max[0]=host_def[i];
			}
		}
	}
}
