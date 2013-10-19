/*
 * =====================================================================================
 *
 *       Filename:  gauss_middle.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  19/10/13 10:11:10
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Some defines
/*
 *  How data structure is described?
 *
 *  We have  NGRID grids,
 */
#define SIZE 8

#define HS  0  // Horizontal Side
#define US  1  // Upper Side
#define OS  2  // Oblicuous Side

typedef struct{
	double hx;
	double hy;
	double vx;
	double vy;
	double ox;
	double oy;
} point;

int main(){
	int i,j;
	point **u;
	point **u_n;
	point **f;

	/* Section: lookup memory */
	u     = (point **)malloc(SIZE*sizeof(point*));
	u_n   = (point **)malloc(SIZE*sizeof(point*));
	f     = (point **)malloc(SIZE*sizeof(point*));

	for(i=0;i<SIZE;i++){
			u[i]     = (point *)malloc((SIZE-i)*sizeof(point));
			u_n[i]   = (point *)malloc((SIZE-i)*sizeof(point));
			f[i]     = (point *)malloc((SIZE-i)*sizeof(point));
	}
	printf("We need about %f mb of memory\n", 1.0*sizeof(point)*SIZE*SIZE/2/1024/1024);


	/* Initialization */
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE-i;j++){
		}
	}

	for(i=0;i<SIZE;i++){
		printf("New file-------------------------------------\n");
		for(j=0;j<SIZE-i;j++){
			printf("%x\n",&u[i][j]);
		}
	}
	/* Free memory 
	for(i=0;i<NGRID;i++){
		for(j=0;j<SIZE;j++){
			printf("%d %d\n",i,j);
			free(u[i][j]);
			free(u_n[i][j]);
			free(f[i][j]);
		}
		free(u[i]);
		free(u_n[i]);
		free(f[i][j]);
	}
	free(u);
	free(u_n);
	free(f);
	*/


	return 0;


}
