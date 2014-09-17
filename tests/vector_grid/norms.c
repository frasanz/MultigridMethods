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

void maxnormTriangle(double ** data, int baseSize, char * name, int level){
  int i,j;
  double max;
  for(i=0; i<baseSize; i++){
    for(j=0; j<baseSize-i; j++){
      if(max<abs(data[i][j]))
        max=abs(data[i][j]);
    }
  }
  printf("Max of %s(%d): %1.3e\n", name, level, max);
}

void maxnormGrid(Grid * g, int level){
  printf("Calculating max norm of all the grid %s\n",g->name);
  maxnormTriangle(g->u1[level], g->basevertex[level], "g->u1", level);
  maxnormTriangle(g->u2[level], g->basevertex[level], "g->u2", level);
  maxnormTriangle(g->u3[level], g->basevertex[level], "g->u3", level);
}
