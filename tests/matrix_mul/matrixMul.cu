// system includes
#include <stdio.h>
#include <assert.h>


// CUDA runtime
#include <cuda_runtime.h>

// Helper functions
#include "helper_functions.h"

template <int BLOCK_SIZE> __global__ void matrixMulCUDA(float *C, float *A, float *B, int wA, int wB){

	// Block index
	int bx = blockIdx.x;
	int by = blockIdx.y;

	// Thread index
	int tx = threadIdx.x;
	int ty = threadIdx.y;

	// Index of the first submatrix of A processed by the block
	int aBegin = wA * BLOCK_SIZE * by;

	// Index of the last submatrix of A processed by the block
	int aEnd = aBegin + wA -1 ;

	// Step size used to iterate through the sub-matrices of A
	int aStep = BLOCK_SIZE;

	// Index of the first submatrix of B processed by the block
	int bBegin = BLOCK_SIZE * bx;

	// Step size used to iterate through the submatrices of B
	int bStep = BLOCK_SIZE * wB;

	// Csub is used to store the element of the block sub-matrix
	float cSub = 0;

		// Loop over all the submatrices of A and B required to compute the block submatrix
		for(int a = aBegin, b = bBegin; a <=aEnd; a += aStep , b+= bStep){
			// Declaration of the shared memory array As used to store the submatrix of A
			__shared__ float As[BLOCK_SIZE][BLOCK_SIZE];

			// Declaration of the shared memory array Bs used to store the submatrix of B
			__shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];

			// Load the matrices from device memory to shared memory, each thread loads 
			// one element of each matrix
			As[ty][tx] = A[a + wA * ty + tx];
			Bs[ty][tx] = B[b + wB * ty + tx];

			// Synchronize to make sure the matrices are loaded
			__syncthreads();

			// Multiply the two matrices together;
			// each thread computes one element
			// of the block submatrix
#pragma unroll

			for (int k=0; k < BLOCK_SIZE ; ++k){
				cSub += As[ty][k] * Bs[k][tx];
		}
		// Synchronize to make sure that the preceding caomputation is done begore loading
		// two new sub-matrices of A and B in the next iteration
		__syncthreads();
		}

		int c = wB * BLOCK_SIZE * by + BLOCK_SIZE * bx;
		C[c + wB * ty + tx ]=cSub;
}

void constantInit(float * data, int size, float val){
	for (int i=0; i< size ; i++){
		data[i] = val;
	}
}

/**
 * Run a simple test of matrix multiplication using CUDA 
 */

int matrixMultiply(int argc, char ** argv, int block_size, dim3 &dimsA, dim3 &dimsB){
	// Allocate host memory for matrices A and B
	unsigned int size_A     = dimsA.x * dimsA.y;
	unsigned int mem_size_A = sizeof(float) * size_A;
	float *h_A = (float *)malloc(mem_size_A);
	unsigned int size_B = dimsB.x * dimsB.y;
	unsigned int mem_size_B = sizeof(float) * size_B;
	float *h_B = (float *)malloc(mem_size_B);

	// Initialize host memory
	const float valB = 0.01f;
	constantInit(h_A, size_A, 1.0f);
	constantInit(h_B, size_B, valB);

	// Allocate device memory
	float *d_A, *d_B, *d_C;

	// Allocate host matrix C
	dim3 dimsC(dimsB.x, dimsA.y, 1);
	unsigned int mem_size_C = dimsC.x * dimsC.y * sizeof(float);
	float *h_C = (float *) malloc(mem_size_C);

	if(h_C == NULL){
		fprintf(stderr, "Failed to allocate host matrix C!\n");
		exit(EXIT_FAILURE);
	}

	cudaError_t error;

	error = cudaMalloc((void **) &d_A, mem_size_A);
	if(error != cudaSuccess){
		printf("cudaMalloc d_A returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaMalloc((void **) &d_B, mem_size_B);
	if(error != cudaSuccess){
		printf("cudaMallco d_B returned error code %d, line (%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaMalloc((void **) &d_C, mem_size_C);
	if(error != cudaSuccess){
		printf("cudaMalloc d_C returned error code %d, line (%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	error = cudaMemcpy(d_B, h_B, mem_size_B, cudaMemcpyHostToDevice);

	if(error != cudaSuccess){
		printf("cudaMemcpy (d_B, h_B) returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}

	//Setup execution parameters
	dim3 threads(block_size, block_size);
	dim3 grids(dimsB.x / threads.x, dimsA.y / threads.y);

	// Create and start timer
	printf("Computing result using CUDA Kernel...\n");

	// Performs warmup operation using matrixMul CUDA kernel
	if(block_size == 16){
		matrixMulCUDA<16><<<grids, threads>>>(d_C, d_A, d_B, dimsA.x, dimsB.x);
	} else {
		matrixMulCUDA<32><<<grids, threads>>>(d_C, d_A, d_B, dimsA.x, dimsB.x);
	}
	printf("done\n");

	cudaDeviceSynchronize();

	// Allocate CUDA events that we'll use for timing
	cudaEvent_t start;
	error = cudaEventCreate(&start);
	if(error != cudaSuccess){
		fprintf(stderr, "Failed to create start event (error code %s)!\n", cudaGetErrorString(error));
		exit(EXIT_FAILURE);
	}

	cudaEvent_t stop;
	error = cudaEventCreate(&stop);
	if(error != cudaSuccess){
		fprintf(stderr, "Failed to create stop event (error code %s)!\n", cudaGetErrorString(error));
		exit(EXIT_FAILURE);
	}

	// Record the start event
	error = cudaEventRecord(start, NULL);
	if(error != cudaSuccess){
		fprintf(stderr, "Failed to record start event (error code %s)!\n", cudaGetErrorString(error));
		exit(EXIT_FAILURE);
	}

	// Execute the kernel
	int nIter = 300;
	for (int j=0; j< nIter; j++){
		if(block_size ==16){
			matrixMulCUDA<16><<<grids, threads>>>(d_C, d_A, d_B, dimsA.x, dimsB.x);
		} else {
			matrixMulCUDA<32><<<grids, threads>>>(d_C, d_A, d_B, dimsA.x, dimsB.x);
		}
	}

	// Record the stop event
	error = cudaEventRecord(stop, NULL);
	if (error != cudaSuccess){
		fprintf(stderr, "Failed to record stop event (error code %s)!\n", cudaGetErrorString(error));
		exit(EXIT_FAILURE);
	}

	// Wait for the stop event to complete
	error = cudaEventSynchronize(stop);
	if(error != cudaSuccess){
		fprintf(stderr, "Failed to synchronize on the stop event (error code %s)!\n", 
			cudaGetErrorString(error));
		exit(EXIT_FAILURE);
	}
	float  msecTotal = 0.0f;
	error = cudaEventElapsedTime(&msecTotal, start, stop);
	if(error != cudaSuccess){
		fprintf(stderr, "Failed to get time elapsed between events (error code %s)!\n",
			cudaGetErrorString(error));
		exit(EXIT_FAILURE);
	}

	// Compute and print the perfomance
	float msecPerMatrixMul   = msecTotal / nIter;
	double flopsPerMatrixMul = 2.0 * (double)dimsA.x * (double)dimsA.y * (double)dimsB.x;
	double gigaFlops = (flopsPerMatrixMul * 1.0e-9f) / (msecPerMatrixMul / 1000.0f);
	printf( "Perfomance = %.2f GFlops/s, Time       = %.3f msec, Size       = %.0f Ops, WorkGoupSiz= %u threads/block\n",
		 	gigaFlops,
			msecPerMatrixMul,
			flopsPerMatrixMul,
			threads.x * threads.y);

	// Copy results from device to host
	error = cudaMemcpy(h_C, d_C, mem_size_C, cudaMemcpyDeviceToHost);
	if(error != cudaSuccess){
		printf("cudaMemcpy (h_C, d_C) returned error code %d, line(%d)\n", error, __LINE__);
		exit(EXIT_FAILURE);
	}
	printf("Checking computed result for correctness: ");
	bool correct = true;

	// test relative error by the formula
	// |<x, y>_cpu - <x,y>_gpu|/<|x|, |y|> <eps
	double eps = 1.e-6; // machine zero
	for(int i = 0; i < (int) (dimsC.x * dimsC.y); i++){
		double abs_err = fabs(h_C[i] - (dimsA.x * valB));
		double dot_length = dimsA.x;
		double abs_val = fabs(h_C[i]);
		double rel_err = abs_err/abs_val/dot_length;
		if ( rel_err > eps){
			printf("Error! Matrix[%05d]=%.8f error term is > %E\n", i, h_C[i], dimsA.x*valB, eps);
			correct = false;
		}
	}

	printf("%s\n", correct ? "Result = PASS" : "Result = FAIL");

	// Clean up memory
	free(h_A);
	free(h_B);
	free(h_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	printf("\nNote: For peak perfomance, please refer to the matrixMulCUBLAS example.\n");

	cudaDeviceReset();
	if(correct)
		return EXIT_SUCCESS;
	else
		return EXIT_FAILURE;
}

/* *
 * Program main
 */

int main(int argc, char **argv){

	printf("[Matrix Multiply Using CUDA] - Starting...\n");

	if(checkCmdLineFlag(argc, (const char **)argv, "help") ||
		 checkCmdLineFlag(argc, (const char **)argc, "?")){
		printf("Usage -device=n (n>=0 for deviceID)\n");
		printf("\t-wA=WidthA -hA=HeightA (Width * Height of Matrix A)\n");
		printf("\t-wB=WidthB -hB=HeightB (Width * Height of Matrix B)\n");
		printf("Note: Outer matrix dimensions of A & B matrices must be equal.\n");

		exit(EXIT_SUCCESS);
	}

	// By default, we use device 0, otherwise we override the device ID based on what is provided at the command line
	int devID = 0;

	if(checkCmdLineFlag(argc, (const char **)argv, "device")){
		devID = getCmdLineArgumentInt(argc, (const char **)argv, "device");
		cudaSetDevice(devID);
	}

	cudaError_t error;
	cudaDeviceProp deviceProp;
	error = cudaGetDevice(&devID);

	if(error != cudaSuccess){
		printf("cudaGetDevice returned error code %d, line(%d)\n", error, __LINE__);
	}
	error = cudaGetDeviceProperties(&deviceProp, devID);

	if(deviceProp.computeMode == cudaComputeModeProhibited){
		fprintf(stderr, "error,: device is running in <Compute Mode Prohibited>, no threads ca use ::cudaSetDevice().\n");
		exit(EXIT_SUCCESS);
	}
	if(error != cudaSuccess){
		printf("cudaGetFeviceProperties returned error code %d, line (%d)\n", error, __LINE__);
	} else {
		printf("GPU Device %d: \"%s\" with compute capability %d.%d\n\n", devID, deviceProp.name, 
			deviceProp.major, deviceProp.minor);
	}

	// Use a larger block size for Fermi and above
	int block_size = (deviceProp.major < 2) ? 16 : 32;

	dim3 dimsA(5*2*block_size, 5*2*block_size, 1);
	dim3 dimsB(5*4*block_size, 5*2*block_size,1);	

	 // width of Matrix A
    if (checkCmdLineFlag(argc, (const char **)argv, "wA"))
    {
        dimsA.x = getCmdLineArgumentInt(argc, (const char **)argv, "wA");
    }

    // height of Matrix A
    if (checkCmdLineFlag(argc, (const char **)argv, "hA"))
    {
        dimsA.y = getCmdLineArgumentInt(argc, (const char **)argv, "hA");
    }

    // width of Matrix B
    if (checkCmdLineFlag(argc, (const char **)argv, "wB"))
    {
        dimsB.x = getCmdLineArgumentInt(argc, (const char **)argv, "wB");
    }

    // height of Matrix B
    if (checkCmdLineFlag(argc, (const char **)argv, "hB"))
    {
        dimsB.y = getCmdLineArgumentInt(argc, (const char **)argv, "hB");
    }

    if (dimsA.x != dimsB.y)
    {
        printf("Error: outer matrix dimensions must be equal. (%d != %d)\n",
               dimsA.x, dimsB.y);
        exit(EXIT_FAILURE);
    }

    printf("MatrixA(%d,%d), MatrixB(%d,%d)\n", dimsA.x, dimsA.y, dimsB.x, dimsB.y);

    int matrix_result = matrixMultiply(argc, argv, block_size, dimsA, dimsB);

    exit(matrix_result);
}
