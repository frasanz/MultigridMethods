/*
 * =====================================================================================
 *
 *       Filename:  vector_grid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 22:10:52
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
#include "vector_grid.h"

int main(){
  /* Definitions */
  Grid g1;

  /* Auxiliary definitions */
  int i;

  /* Malloc */
  g1.u1 = (double*) malloc (SIZE*sizeof(double));
  g1.u2 = (double*) malloc (SIZE*sizeof(double));
  g1.u3 = (double*) malloc (SIZE*sizeof(double));

  for(i=0; i<SIZE; i++){
    g1.u1[i]=rand();
    g1.u2[i]=rand();
    g1.u3[i]=rand();
  }


  /* Free */
  free(g1.u1);
  free(g1.u2);
  free(g1.u3);


  return 0;
}
