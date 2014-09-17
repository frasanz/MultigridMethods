#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Level of partitions
#define SIZE 5

typedef struct{
	double x1; // Values on G1
	double x2; // Values on G2
	double x3; // Values on G3
} value;

int main(int argc, char ** argv){
	int base_triangles  = pow(2,SIZE);
	int total_triangles = base_triangles*(base_triangles+1)/2;
	value ** u;
	value ** f;
	int i,j;


	/* Here goes the malloc section */
	u = (value **)malloc(base_triangles*sizeof(value*));
	f = (value **)malloc(base_triangles*sizeof(value*));
	for(i=0;i<base_triangles;i++){
		u[i] =(value*)malloc((base_triangles-i)*sizeof(value));
		f[i] =(value*)malloc((base_triangles-i)*sizeof(value));
	}

	/* Here goes the initialization. u_bound = 0, u= rand, f=0 */
	for(i=0; i<base_triangles; i++){
		for(j=0; j<base_triangles-i; j++){
			f[i][j].x1=0.0;
			f[i][j].x2=0.0;
			f[i][j].x3=0.0;
			u[i][j].x1=rand();
			u[i][j].x2=rand();
			u[i][j].x3=rand();
			// TODO: This is a very big bound
			if(i==0 || j==0 || i+j ==base_triangles-1){
				u[i][j].x1 = rand();
				u[i][j].x2 = rand();
				u[i][j].x3 = rand();
			}
		}
	}


	/* Here goes the free section */
	for(i = 0; i < base_triangles; i++){
		free(u[i]);
		free(f[i]);
	}
	free(u);
	free(f);

	return 0;
}
