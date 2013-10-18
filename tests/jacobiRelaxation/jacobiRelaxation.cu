
/*
 * This is the jacobi relaxation method in gpu 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <cuda.h>

#define SIZE 2048
#define BLOCK_SIZE 32
#define NITER 1000

float ratio(float*u, float ant, int iter){
	float tmp=0.0;
	int i,j;
	for(i=0;i<SIZE;i++)
	{
		for(j=0;j<SIZE;j++)
		{
			if(u[j*SIZE+i]>tmp)
				tmp=u[j*SIZE+i];
		}
	}
	printf(" iter=%d ratio=%f ant=%f max=%f\n",iter,tmp/ant,ant,tmp);
	return tmp;
}

__global__ void jacobi(float *d_u_new, float *d_u, float *d_f, float h2){
	int i = blockIdx.x*blockDim.x + threadIdx.x;
	int j = blockIdx.y*blockDim.y + threadIdx.y;
	d_u_new[i*SIZE+j]=0.25*(
			h2*d_f[i    *SIZE+j     ]+
			d_u[(i-1)*SIZE+j     ]+
			d_u[(i+1)*SIZE+j     ]+
			d_u[i    *SIZE+j-1   ]+
			d_u[i    *SIZE+j+1   ]);


}

int main(){
	float * h_u, *h_f;
	float * d_u, *d_u_new, *d_f;
	float * tmp;
	float ant = 1.0;
	int i,j;
	size_t size;
	float h = 1.0/SIZE;

	/* Host memory malloc */
	size = SIZE*SIZE*sizeof(float);
	printf("We need %dmb of memory\n",3*size/1024/1024);
	h_u = (float*)malloc(size);
	h_f = (float*)malloc(size);

	/* memory for the gpu */
	cudaMalloc(&d_u, size);
	cudaMalloc(&d_u_new, size);
	cudaMalloc(&d_f, size);

	/* Initialization */
	for(i=0;i<SIZE; i++){
		for(j=0; j<SIZE; j++){
			h_f[i*SIZE+j]=0.0;
			h_u[i*SIZE+j]=rand();
		}
	}

	/* Bounds */
	for(i=0;i<SIZE;i++){
		h_u[i]=0.0;
		h_u[i*SIZE]=0.0;
		h_u[i*SIZE+SIZE-1]=0.0;
		h_u[SIZE*(SIZE-1)+i]=0.0;
	}
	/* Copy from host to device */
	cudaMemcpy(d_f,h_f,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_u,h_u,size,cudaMemcpyHostToDevice);
	cudaMemcpy(d_u_new,h_u,size,cudaMemcpyHostToDevice);

	/* Grid dimension */
	dim3 dimBlock(BLOCK_SIZE,BLOCK_SIZE);
	dim3 dimGrid(SIZE/BLOCK_SIZE,SIZE/BLOCK_SIZE);
	float h2=h*h;

	/* Call NITER times to the jacobi method */
	for(i=0;i<NITER;i++)
	{
		jacobi<<<dimGrid,dimBlock>>>(d_u_new,d_u,d_f,h2);
		cudaDeviceSynchronize;
		if(i%100==0){
			cudaMemcpy(h_u, d_u_new, size, cudaMemcpyDeviceToHost);
			ant=ratio(h_u,ant,i);
		}
		tmp=d_u_new;
		d_u_new=d_u;
		d_u=tmp;

	}

	/* free memory */
	free(h_u);
	free(h_f);
	cudaFree(d_u_new);
	cudaFree(d_u);
	cudaFree(d_f);
}
