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


typedef struct{
	double x;
	double y;
} point;


typedef struct{
	double hx;
	double hy;
	double vx;
	double vy;
	double ox;
	double oy;
	double x;
	double y;
} value;

void print_values(value **);

int main(){
	int i,j;
	point **p;
	value **u;
	value **u_n;
	value **f;

	point a;
	point b;
	point c;

	a.x=0.0;
	a.y=0.0;
	b.x=1.0;
	b.y=0.0;
	c.x=0.5;
	c.y=1.0;



	/* Section: lookup memory */
	p     = (point **)malloc(SIZE*sizeof(point*));
	u     = (value **)malloc(SIZE*sizeof(value*));
	u_n   = (value **)malloc(SIZE*sizeof(value*));
	f     = (value **)malloc(SIZE*sizeof(value*));

	for(i=0;i<SIZE;i++){
			p[i]     = (point *)malloc((SIZE-i)*sizeof(point));
			u[i]     = (value *)malloc((SIZE-i)*sizeof(value));
			u_n[i]   = (value *)malloc((SIZE-i)*sizeof(value));
			f[i]     = (value *)malloc((SIZE-i)*sizeof(value));
	}


	/* Initialize the values of points */
	// For a triangle, we have tree points
	// a=(a.x,a.y)     x(c)
	// b=(b.x,b.y)
	// c=(c.x,c.y)  x(a)    x(b)
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE-i;j++){
			p[i][j].x=a.x+((b.x-a.x)*j)/(SIZE-1)+((c.x-a.x)*i)/(SIZE-1);
			p[i][j].y=a.y+((b.y-a.y)*j)/(SIZE-1)+((c.y-a.y)*i)/(SIZE-1);
		}
	}

	//TODO: Add sizeof point
	printf("We need about %f mb of memory\n", 1.0*sizeof(value)*SIZE*SIZE/2/1024/1024);

	/* Initialize f */
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE-i;j++){
			f[i][j].x=p[i][j].x;
			f[i][j].y=-p[i][j].y;
		}
	}

	/* Initialize other functions */
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE-i;j++){
			u[i][j].x=rand();
			u[i][j].y=rand();
			u[i][j].hx=rand();
			u[i][j].hy=rand();
			u[i][j].vx=rand();
			u[i][j].vy=rand();
			u[i][j].ox=rand();
			u[i][j].oy=rand();

		}
	}
	print_values(u);





	/* Free memory */
	for(i=0;i<SIZE;i++){
		free(u[i]);
		free(u_n[i]);
		free(f[i]);
		free(p[i]);
	}
	free(u);
	free(u_n);
	free(f);
	free(p);

	return 0;
}

void print_values(value **tri){
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE-i;j++){
			printf("%.2f %.2f\t",tri[i][j].x, tri[i][j].y);
		}
		printf("\n");
	}
}
