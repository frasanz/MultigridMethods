#include "multigrid_kernel.cu"
#include <stdio.h>
#define N_MALLAS 12
#define BLOCK_SIZE 16

void g_imprime(Grid g);
void multigrid(Grid *u, Grid *f, Grid *v, Grid *d, int nivel, double *max, int *iter);

void imprime_malla(double *f, int dim, const char * nombre){
	FILE *fil;
	fil = fopen(nombre,"w");
	int i,j;
	double h=1.0/(dim-1);
	for( i=0; i<dim; i++) {
		for( j=0; j<=i; j++) {
			fprintf(fil,"%f %f %f\n", 1.0*j*h, 1.0-1.0*i*h, f[IDT(i,j)]);
		}
		fprintf(fil,"\n");
	}
	fclose(fil);
}

int main(){
	int i;
	int dim;
	int size;
	double max=100;
	double max_ant;
	int sizetotal=0;
	
	/* Definition of the grid */
	Grid u[N_MALLAS];
	Grid f[N_MALLAS];
	Grid v[N_MALLAS];
	Grid d[N_MALLAS];

	/* Memory alloc */
	for(i=2; i<N_MALLAS; i++){
		dim=pow(2,i)+1; //Dim is the number of elements in the diag
		size = ((dim-1)*(dim-1)+3*(dim-1))/2+2;
		u[i].dim=dim;
		f[i].dim=dim;
		v[i].dim=dim;
		d[i].dim=dim;
		u[i].size=size;
		f[i].size=size;
		v[i].size=size;
		d[i].size=size;

		cudaMalloc(&u[i].v,size*sizeof(double));
		cudaMalloc(&f[i].v,size*sizeof(double));
		cudaMalloc(&v[i].v,size*sizeof(double));
		cudaMalloc(&d[i].v,size*sizeof(double));
		sizetotal = sizetotal+4*size;
	}


	/* To CALL CUDA */
	int m = N_MALLAS -1;
	dim = (int) pow(2,m)+1;
	dim3 dimBlock (BLOCK_SIZE, BLOCK_SIZE);
	dim3 dimGrid((dim+BLOCK_SIZE-1)/dimBlock.x, (dim+BLOCK_SIZE-1)/dimBlock.y);
	printf("%d %d %d\n",dimBlock.x, dimBlock.y, dimGrid.x, dimGrid.y);
	printf("We need about %d Mb\n", sizetotal*sizeof(double)/1024/1024);

	/* Starting the grid of f */
	cero<<<dimGrid, dimBlock>>>(f[m]);

	/* Initialize u with random values */
	random <<<dimGrid, dimBlock>>>(u[m]);

	/* Main loop */
	int iter=0;
	for(i=0;i<20;i++){
		max_ant = max;
		max =0.0;
		multigrid(&u[0], &f[0], &v[0], &d[0], m, &max, &iter);
		printf("Iteration %d nd=%d ratio=%d\n", i, max, max/max_ant);
		iter++;
	}

	/* Free memory */
	for(i=0; i< N_MALLAS; i++){
		cudaFree(&u[i].v);
		cudaFree(&f[i].v);
		cudaFree(&v[i].v);
		cudaFree(&d[i].v);
	}
	return 0;
}

/* This function prints a grid located in the GPU */
void g_print(Grid g, const char *name){
	double *dg;
	FILE *file;
	file = fopen(name,"w");
	double h=1.0/(g.dim-1);
	int i,j;
	size_t size=((g.dim-1)*(g.dim-1)+3*(g.dim-1))/2+1;
	dg = (double*)malloc(size*sizeof(double));
	
	cudaMemcpy(dg,g.v, size*sizeof(double), cudaMemcpyDeviceToHost);

	for(i=0;i<g.dim;i++){
		for(j=0;j<=i;j++){
			fprintf(file,"%f %f %f\n",1.0*j*h,1.0-1.0*i*h,dg[IDT(i,j)]);
		}
		fprintf(file,"\n");
	}
	fclose(file);
	free(dg);
}

void multigrid(Grid *u, Grid *f, Grid *v, Grid *d, int m, double *max, int *iter){
	int dim;
	int dim_;
	int i,j;
	double * hf;
	double * hu;


	/* Definition of h^2 */
	double h2=pow(u[m].dim-1,2);

	/* Definition of an operador (copied from another site) */
	double operador[9]={0.0,-1.0*h2,0.0,-1.0*h2,4.0*h2,-1.0*h2,0.0,-1.0*h2,0.0};
	double * a_op;
	cudaMalloc(&a_op,9*sizeof(double));
	cudaMemcpy(a_op,&operador[0],9*sizeof(double),cudaMemcpyHostToDevice);


	if(m==2){ /* In this case, we've to solve */
		dim = (int)pow(2,m)+1;
		size_t size=((f[m].dim-1)*(f[m].dim-1)+3*(f[m].dim-1))/2+1;
		hf=(double*)malloc(size*sizeof(double));
		cudaMemcpy(hf,f[m].v,size*sizeof(double),cudaMemcpyDeviceToHost);
		hu=(double*)malloc(size*sizeof(double));

		/* Construimos el sistema a resolver */
		double A[3][3];
		A[0][0]=operador[4];
		A[0][1]=operador[7];
		A[0][2]=operador[8];
		A[1][0]=operador[2];
		A[1][1]=operador[4];
		A[1][2]=operador[5];
		A[2][0]=operador[0];
		A[2][1]=operador[3];
		A[2][2]=operador[4];

		double B[3];
		B[0]=hf[IDT(2,1)];
		B[1]=hf[IDT(3,1)];
		B[2]=hf[IDT(3,2)];

		/* Hacemos eliminación gausiana */
		A[1][1]=A[1][1]-A[0][1]*A[1][0]/A[0][0];
		A[1][2]=A[1][2]-A[0][2]*A[1][0]/A[0][0];
		B[1]=B[1]-B[0]*A[1][0]/A[0][0];
		A[2][1]=A[2][1]-A[0][1]*A[2][0]/A[0][0];
		A[2][2]=A[2][2]-A[0][2]*A[2][0]/A[0][0];
		B[2]=B[2]-B[0]*A[2][0]/A[0][0];
		A[2][2]=A[2][2]-A[1][2]*A[2][1]/A[1][1];
		B[2]=B[2]-B[1]*A[2][1]/A[1][1];

		/* Resolvemos */
		hu[IDT(3,2)]=B[2]/A[2][2];
		hu[IDT(3,1)]=(B[1]-A[1][2]*hu[IDT(3,2)])/A[1][1];
		hu[IDT(2,1)]=(B[0]-A[0][2]*hu[IDT(3,2)]-A[0][1]*hu[IDT(3,1)])/A[0][0];

		/* Subimos la solución a la GPU */
		cudaMemcpy(u[m].v,hu,size*sizeof(double),cudaMemcpyHostToDevice);
		free(hf);
	} else {
		/* To call CUDA */
		dim =(int)pow(2,m)+1;
		dim_=(int)pow(2,m-1)+1;
		dim3 dimBlock(BLOCK_SIZE,BLOCK_SIZE);
		dim3 dimGrid ((dim +BLOCK_SIZE-1)/dimBlock.x,(dim +BLOCK_SIZE-1)/dimBlock.y);
		dim3 dimGrid_((dim_+BLOCK_SIZE-1)/dimBlock.x,(dim_+BLOCK_SIZE-1)/dimBlock.y);

		/* Set 0 in the appropiated grids */
		cero<<<dimGrid ,dimBlock>>>(v[m]);
		cero<<<dimGrid ,dimBlock>>>(d[m]);
		cero<<<dimGrid_,dimBlock>>>(u[m-1]);
		cero<<<dimGrid_,dimBlock>>>(f[m-1]);

		/* smooth three colors */
		suaviza_r<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_g<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_b<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);

		/* smooth three colors */
		suaviza_r<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_g<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_b<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);

		/* Compute the defect */
		defecto<<<dimGrid, dimBlock>>>(u[m],f[m],d[m],a_op);

		/* Restrict the defect */
		restringe<<<dimGrid_, dimBlock>>>(d[m], f[m-1]);


		/* Recall to multigrid */
		for(i=0; i<2; i++){
			multigrid(&u[0],&f[0],&v[0],&d[0],m-1,max,iter);
		}

		/* Interpolate from u[m-1] to v[m] */
		interpola<<<dimGrid_, dimBlock>>>(u[m-1],v[m]);

		/* Sum */
		suma<<<dimGrid_, dimBlock>>>(u[m],v[m]);

		/* smooth three colors */
		suaviza_r<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_g<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_b<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);

		/* smooth three colors */
		suaviza_r<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_g<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);
		suaviza_b<<<dimGrid, dimBlock>>>(u[m],f[m],a_op);

		/* In the uppper grid, check defect */
		if(m==N_MALLAS-1){
			char nombre[256];
			sprintf(nombre,"defecto_%d",iter[0]);
			defecto<<<dimGrid,dimBlock>>>(u[m],f[m],d[m],a_op);
			double *def;
			size_t size=((f[m].dim-1)*(f[m].dim-1)+3*(f[m].dim-1))/2+1;
			def=(double*)malloc(size*sizeof(double));
			cudaMemcpy(def,d[m].v,size*sizeof(double), cudaMemcpyDeviceToHost);
			for(i=0;i<size;i++)
			{
				if(max[0]<fabs(def[i]))
					max[0]=fabs(def[i]);
			}
			free(def);
		}
	}
	cudaFree(a_op);
}
