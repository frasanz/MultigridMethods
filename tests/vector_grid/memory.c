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
  int i;
  g->basevertex = pow(2,SIZE)+1;
  g->totalvertex= g->basevertex*(g->basevertex+1)/2;
  g->u1 = (double **) malloc (g->basevertex*sizeof(double*));
  g->u2 = (double **) malloc (g->basevertex*sizeof(double*));
  g->u3 = (double **) malloc (g->basevertex*sizeof(double*));
  for(i=0; i<g->basevertex; i++){
     g->u1[i] = (double *)malloc((g->basevertex-i)*sizeof(double));
     g->u2[i] = (double *)malloc((g->basevertex-i)*sizeof(double));
     g->u3[i] = (double *)malloc((g->basevertex-i)*sizeof(double));
  }
}

void freeGrid(Grid *g){
  int i;
  for(i=0; i<g->basevertex; i++){
    free(g->u1[i]);
    free(g->u2[i]);
    free(g->u3[i]);
  }
  free(g->u1);
  free(g->u2);
  free(g->u3);
}

