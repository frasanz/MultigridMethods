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
  printf("\n===%s===  printed Up->Down\n",g->name);
  printf("\tbasevertex: %d , totalvertex: %d\n", g->basevertex, g->totalvertex);
  /* We can print all the triangle */
  if(SIZE < 4){
    printf("u1\n");
    printTriangleUp(g->u1, g->basevertex);
    printf("u2\n");
    printTriangleUp(g->u2, g->basevertex);
    printf("u3\n");
    printTriangleUp(g->u3, g->basevertex);

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
  printf("\n===%s=== printed Down->Up\n",g->name);
  printf("\tbasevertex: %d , totalvertex: %d\n", g->basevertex, g->totalvertex);
  if(SIZE < 4){ /* We can print all the triangle */
    printf("u1\n");
    printTriangleDown(g->u1, g->basevertex);
    printf("u2\n");
    printTriangleDown(g->u2, g->basevertex);
    printf("u3\n");
    printTriangleDown(g->u3, g->basevertex);

  } else { /* Print a formatted version */
    printf("u1\n");
    printBigTriangleDown(g->u1, g->basevertex);
    printf("u2\n");
    printBigTriangleDown(g->u2, g->basevertex);
    printf("u3\n");
    printBigTriangleDown(g->u3, g->basevertex);
  }
}
void prettyprint(double value){
  if(value >= 0){
    printf(" %1.3e ", value);
  }else{
    printf("%1.3e ", value);
  }
}

void printTriangleUp(double ** data, int baseSize){
  int i,j;
  for(i=baseSize-1; i>=0; i--){
    for(j=0; j<baseSize-i; j++){
      prettyprint(data[i][j]);
    }
    printf("\n");
  }
}
void printTriangleDown(double ** data, int baseSize){
  int i,j;
  for(i=0; i<baseSize; i++){
    for(j=0; j<baseSize-i; j++){
      prettyprint(data[i][j]);
    }
    printf("\n");
  }
}

void printPoints(){
    printf(" ......... ");
}

void printBigTriangleUp(double ** data, int baseSize){
  int i,j;
  int roundSize=4;
  for(i=baseSize-1; i>=baseSize-roundSize; i--){
    for(j=0; j<baseSize-i; j++){
        prettyprint(data[i][j]);
    }
    printf("\n");
  }
  prettyprint(data[baseSize-(roundSize+1)][0]);
  for(i=0; i<roundSize-1; i++){
    printPoints();
  }
  prettyprint(data[baseSize-(roundSize+1)][baseSize-(roundSize+1)]);
  printf("\n");
  for(i=0; i<=roundSize+1; i++){
     printPoints();
  }
  printf("\n");
  prettyprint(data[0][0]);
  prettyprint(data[0][1]);
  for(i=0; i<roundSize-1; i++){
    printPoints();
  }
  prettyprint(data[0][baseSize-2]);
  prettyprint(data[0][baseSize-1]);
  printf("\n");
}
void printBigTriangleDown(double **data, int baseSize){
  int i,j;
  int roundSize=4;
  /* First file */
  printf("%1.3e %1.3e ", data[0][0], data[0][1]);
  for(i=0; i<roundSize-1; i++){
    printf("......... ");
  }
  printf("%1.3e %1.3e\n", data[0][baseSize-2], data[0][baseSize-1]);
  /* Intermediate ... */ 
  for(i=0; i<=roundSize+1; i++){
    printf("......... ");
  }
  printf("\n");
  /* Upper */
  printf("%1.3e ", data[baseSize-(roundSize+1)][0]);
  for(i=0; i<roundSize-1; i++){
    printf("......... ");
  }
  printf("%1.3e\n", data[baseSize-(roundSize+1)][baseSize-(roundSize+1)]);
  for(i=baseSize-roundSize; i<baseSize; i++){
    for(j=0; j<baseSize-i; j++){
        printf("%1.3e ", data[i][j]);
    }
    printf("\n");
  }
}
