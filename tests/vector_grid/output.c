/*
 * =====================================================================================
 *
 *       Filename:  output.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 23:11:47
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
#include "output.h"
#include "config.h"

void printPlain(Grid *g){
  int i,j;
  printf("\n===%s===\n",g->name);
  printf("\tbasevertex: %d , totalvertex: %d\n", g->basevertex, g->totalvertex);
  printf("u1\n");
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      printf("%f ", g->u1[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("u2\n");
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      printf("%f ", g->u3[i][j]);
    }
    printf("\n");
  }
  printf("\n");
  printf("u3\n");
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      printf("%f ", g->u3[i][j]);
    }
    printf("\n");
  }
}

