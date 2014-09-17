/*
 * =====================================================================================
 *
 *       Filename:  jacobirelax.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17/04/14 19:52:03
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define SIZE 2048

double max(double * array){
  int i;
  double max=0.0;
  for(i=0; i< SIZE*SIZE; i++)
    if(array[i]>max)
      max=array[i];
  return max;
}

void initializeCero(double * array){
  int i;
  for(i=0; i<SIZE*SIZE; i++)
    array[i]=0.0;
}

void interiorRandom(double * array){
  int i,j;
  for(i=1; i<SIZE-1;i++)
    for(j=1; j<SIZE-1; j++)
      array[i*SIZE+j]=(float)rand()/(float)RAND_MAX;
}

void printMatrix(double * array){
  int i,j;
  for(i=1; i<SIZE-1; i++){
    for(j=1; j<SIZE-1; j++)
      printf("%f\t",array[i*SIZE+j]);
  }
}

int main(){
  double h2 = 1.0/SIZE;
  double  * u;
  double  * u_new;
  double  * temp;
  double  * f;
  int i,j,k;
  u     = (double*) malloc(SIZE*SIZE*sizeof(double));
  u_new = (double*) malloc(SIZE*SIZE*sizeof(double));
  f     = (double*) malloc(SIZE*SIZE*sizeof(double));

  /* Inizializamos  a cero */
  initializeCero(u);
  initializeCero(f);
  initializeCero(u_new);

  /* Inicializamos random en el interior de u */
  interiorRandom(u);
  printf("Initial=%f\n",max(u));

  for(k=0; k<10; k++){
    for(i=1; i < SIZE-1; i++){
      for(j=1; j< SIZE-1; j++){
        u_new[i*SIZE+j] = 0.25*(h2*f[i*SIZE+j] + u[(i-1)*SIZE+j] + u[(i+1)*SIZE+j] + 
                                     + u[i*SIZE+j-1]   + u[i*SIZE+j+1]); 
      }
    }
    temp=u;
    u=u_new;
    u_new=temp;
    printf("Iter %d: max=%f\n",k,max(u_new));
  }
}

