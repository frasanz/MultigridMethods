/*
 * =====================================================================================
 *
 *       Filename:  norms.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  26/04/14 16:51:23
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
#include "norms.h"
#include "config.h"

void maxnormTriangle(double ** data, int baseSize, char * name){
  int i,j;
  double max;
  for(i=0; i<baseSize; i++){
    for(j=0; j<baseSize-i; j++){
      if(max<abs(data[i][j]))
        max=abs(data[i][j]);
    }
  }
  printf("Max of %s: %1.3e\n", name, max);
}

void maxnormGrid(Grid * g){
  printf("Calculating max norm of all the grid %s\n",g->name);
  maxnormTriangle(g->u1, g->basevertex, "g->u1");
  maxnormTriangle(g->u2, g->basevertex, "g->u2");
  maxnormTriangle(g->u3, g->basevertex, "g->u3");
}
