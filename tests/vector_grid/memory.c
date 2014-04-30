/*
 * =====================================================================================
 *
 *       Filename:  memory.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 22:36:18
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
#include "memory.h"

void mallocGrid(Grid *g){
  int i,j;
  g->basevertex  = (int*) malloc (SIZE*sizeof(int));
  g->totalvertex = (int*) malloc (SIZE*sizeof(int));
  g->u1          = (double***) malloc(SIZE*sizeof(double**));
  g->u2          = (double***) malloc(SIZE*sizeof(double**));
  g->u3          = (double***) malloc(SIZE*sizeof(double**));
  for(i=0; i< SIZE; i++){
    g->basevertex[i] = pow(2,i)+1;
    g->totalvertex[i]= g->basevertex[i]*(g->basevertex[i]+1)/2;
    g->u1[i] = (double **) malloc (g->basevertex[i]*sizeof(double*));
    g->u2[i] = (double **) malloc (g->basevertex[i]*sizeof(double*));
    g->u3[i] = (double **) malloc (g->basevertex[i]*sizeof(double*));
    for(j=0; j<g->basevertex[i]; j++){
     g->u1[i][j] = (double *)malloc((g->basevertex[i]-j)*sizeof(double));
     g->u2[i][j] = (double *)malloc((g->basevertex[i]-j)*sizeof(double));
     g->u3[i][j] = (double *)malloc((g->basevertex[i]-j)*sizeof(double));
    }
  }
}

void freeGrid(Grid *g){
  int i,j;
  for(i=0; i<SIZE; i++){
    for(j=0; j<g->basevertex[i]; j++){
      free(g->u1[i][j]);
      free(g->u2[i][j]);
      free(g->u3[i][j]);
    }
  }
  for(i=0; i<SIZE; i++){
    free(g->u1[i]);
    free(g->u2[i]);
    free(g->u3[i]);
  }
  free(g->u1);
  free(g->u2);
  free(g->u3);
}

