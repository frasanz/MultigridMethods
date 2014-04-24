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

/* This function prints the triangle Up->Down */
void printUp(Grid *g){
  int i,j;
  printf("\n===%s===  printed Up->Down\n",g->name);
  printf("\tbasevertex: %d , totalvertex: %d\n", g->basevertex, g->totalvertex);
  /* We can print all the triangle */
  if(SIZE < 4){
    printf("u1\n");
    for(i=g->basevertex-1; i>=0; i--){
      for(j=0; j<g->basevertex-i; j++){
        printf("%1.3e ", g->u1[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    printf("u2\n");
    for(i=g->basevertex-1; i>=0; i--){
      for(j=0; j<g->basevertex-i; j++){
        printf("%1.3e ", g->u3[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    printf("u3\n");
    for(i=g->basevertex-1; i>=0; i--){
      for(j=0; j<g->basevertex-i; j++){
        printf("%1.3e ", g->u3[i][j]);
      }
      printf("\n");
    }
  } else { /* Print a formatted version */
    printf("u1\n");
    printBigTriangleUp(g->u1, g->basevertex);
    printf("u2\n");
    printBigTriangleUp(g->u2, g->basevertex);
    printf("u3\n");
    printBigTriangleUp(g->u3, g->basevertex);
  }
}

/* This functions prints the triangle Down->UP */
void printDown(Grid *g){
  int i,j;
  printf("\n===%s=== printed Down->Up\n",g->name);
  printf("\tbasevertex: %d , totalvertex: %d\n", g->basevertex, g->totalvertex);
  if(SIZE < 4){ /* We can print all the triangle */
    printf("u1\n");
    for(i=0; i<g->basevertex; i++){
      for(j=0; j<g->basevertex-i; j++){
        printf("%1.3e ", g->u1[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    printf("u2\n");
    for(i=0; i<g->basevertex; i++){
      for(j=0; j<g->basevertex-i; j++){
        printf("%1.3e ", g->u3[i][j]);
      }
      printf("\n");
    }
    printf("\n");
    printf("u3\n");
    for(i=0; i<g->basevertex; i++){
      for(j=0; j<g->basevertex-i; j++){
        printf("%1.3e ", g->u3[i][j]);
      }
      printf("\n");
    }
  } else { /* Print a formatted version */
  }
}

void printBigTriangleUp(double ** data, int baseSize){
  int i,j;
  int roundSize=4;
  for(i=baseSize-1; i>=baseSize-roundSize; i--){
    for(j=0; j<baseSize-i; j++){
        printf("%1.3e ", data[i][j]);
    }
    printf("\n");
  }
  printf("%1.3e ", data[baseSize-(roundSize+1)][0]);
  for(i=0; i<roundSize-1; i++){
    printf("......... ");
  }
  printf("%1.3e\n", data[baseSize-(roundSize+1)][baseSize-(roundSize+1)]);
  for(i=0; i<=roundSize+1; i++){
    printf("......... ");
  }
  printf("\n");
  printf("%1.3e %1.3e ", data[0][0], data[0][1]);
  for(i=0; i<roundSize-1; i++){
    printf("......... ");
  }
  printf("%1.3e %1.3e\n", data[0][baseSize-2], data[0][baseSize-1]);
}
