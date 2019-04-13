//This is an example on vectorAdd just to remember how CUDA works

#include <stdio.h>
#include <cuda_runtime.h>
#include <helper_cuda.h>

__global__ void vectorAdd(const float *A, const float *B, float *C, int numElements){
  int i = blockDim.x*blockIdx.x + threadIdx.x;
  if(i<numElements){
    C[i] = A[i]+B[i];
  }
}

int main(void){
  cudaError_t err = cudaSuccess;

  int numElements=50000;
  size_t size = numElements*sizeof(float);
  printf("[Vector addition of %d elements\n", numElements);
  printf("[We will need %d bytes]\n", size);

  // Allocate in host for input A/B outputC
  float *h_A = (float*)malloc(size);
  float *h_B = (float*)malloc(size);
  float *h_C = (float*)malloc(size);

  //Is it ok?
  if(h_A == NULL || h_B == NULL || h_C == NULL){
    fprintf(stderr, "Failure in allocation\n");
    exit(EXIT_FAILURE);
  }

  // Initializing in host
  for(int i=0; i< numElements; i++){
    h_A[i] = rand()/(float)RAND_MAX;
    h_B[i] = rand()/(float)RAND_MAX;
  }

  // Allocate in the device input vector *A
  float *d_A = NULL;
  err = cudaMalloc((void**)&d_A, size);
  if(err!=cudaSuccess){
     fprintf(stderr, "Failed(error code %s)!\n", cudaGetErrorString(err));
    printf("error1\n");
    exit(EXIT_FAILURE);
  }
  float *d_B = NULL;
  err = cudaMalloc((void**)&d_B, size);
  if(err!=cudaSuccess){
    printf("error2\n");

    exit(EXIT_FAILURE);
  }

  float *d_C = NULL;
  err = cudaMalloc((void**)&d_C, size);
  if(err!=cudaSuccess){
    exit(EXIT_FAILURE);
  }

  // Copying
  err = cudaMemcpy(d_A,h_A,size, cudaMemcpyHostToDevice);
  if(err!=cudaSuccess){
    printf("error3\n");

    exit(EXIT_FAILURE);
  }

  err = cudaMemcpy(d_B,h_B,size, cudaMemcpyHostToDevice);
  if(err!=cudaSuccess){
     fprintf(stderr, "(error code %s)!\n", cudaGetErrorString(err));

    printf("error7\nn");

    exit(EXIT_FAILURE);
  }

  // launch the Kernel
  int threadsPerBlock = 256;
  int blocksPerGrid = (numElements + threadsPerBlock -1) / threadsPerBlock;
  printf("Launching %d blocks of %d threads\n", blocksPerGrid, threadsPerBlock);
  vectorAdd<<<blocksPerGrid,threadsPerBlock>>>(d_A,d_B,d_C, numElements);
  err = cudaGetLastError();
  if (err!=cudaSuccess){
    printf("error4\n");

    exit(EXIT_FAILURE);
  }

  // COpyback the solution
  err = cudaMemcpy(h_C,d_C,size, cudaMemcpyDeviceToHost);
  if(err !=cudaSuccess){
    printf("error5\n");
    fprintf(stderr, "(error code %s)!\n", cudaGetErrorString(err));
    exit(EXIT_FAILURE);
  }

  // Verify solution
  for(int i=0;i<numElements; i++){
    if(fabs(h_A[i] + h_B[i] - h_C[i]) > 1e-5 ){
    printf("error6\n");

      exit(EXIT_FAILURE);
    }
  }
  printf("Test PASSED\n");

 cudaFree(d_A);
 cudaFree(d_B);
 cudaFree(d_C);
 free(h_A);
 free(h_C);
 free(h_B);
}
