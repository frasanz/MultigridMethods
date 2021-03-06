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
void printUp(Grid *g, int level){
  printf("\n===%s===  printed Up->Down\n",g->name);
  printf("basevertex: %d , totalvertex: %d\n", g->basevertex[level], 
    g->totalvertex[level]);
  /* We can print all the triangle */
  if(g->basevertex[level] < 10){
    printf("u1\n");
    printTriangleUp(g->u1[level], g->basevertex[level]);
    printf("u2\n");
    printTriangleUp(g->u2[level], g->basevertex[level]);
    printf("u3\n");
    printTriangleUp(g->u3[level], g->basevertex[level]);

  } else { /* Print a formatted version */
    printf("u1\n");
    printBigTriangleUp(g->u1[level], g->basevertex[level]);
    printf("u2\n");
    printBigTriangleUp(g->u2[level], g->basevertex[level]);
    printf("u3\n");
    printBigTriangleUp(g->u3[level], g->basevertex[level]);
  }
}

/* This functions prints the triangle Down->UP */
void printDown(Grid *g, int level){
  printf("\n===%s=== printed Down->Up\n",g->name);
  printf("basevertex: %d , totalvertex: %d\n", g->basevertex[level], 
    g->totalvertex[level]);
  if(g->basevertex[level] < 10){ /* We can print all the triangle */
    printf("u1\n");
    printTriangleDown(g->u1[level], g->basevertex[level]);
    printf("u2\n");
    printTriangleDown(g->u2[level], g->basevertex[level]);
    printf("u3\n");
    printTriangleDown(g->u3[level], g->basevertex[level]);

  } else { /* Print a formatted version */
    printf("u1\n");
    printBigTriangleDown(g->u1[level], g->basevertex[level]);
    printf("u2\n");
    printBigTriangleDown(g->u2[level], g->basevertex[level]);
    printf("u3\n");
    printBigTriangleDown(g->u3[level], g->basevertex[level]);
  }
}

/* This allow to print numbers in 
 * column independent of the "-" sign */
void prettyprint(double value){
  if(value >= 0){
    printf(" %1.3e ", value);
  }else{
    printf("%1.3e ", value);
  }
}

/*  */
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

/* This function prints a big triangle up, printing points when needed */
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
  prettyprint(data[baseSize-(roundSize+1)][roundSize]);
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

/* This function prints a triangle down, printing points when needed  */
void printBigTriangleDown(double **data, int baseSize){
  int i,j;
  int roundSize=4;
  /* First file */
  prettyprint(data[0][0]);
  prettyprint(data[0][1]);
  for(i=0; i<roundSize-1; i++){
    printPoints();
  }
  prettyprint(data[0][baseSize-2]);
  prettyprint(data[0][baseSize-1]);
  printf("\n");
  /* Intermediate ... */ 
  for(i=0; i<=roundSize+1; i++){
    printPoints();
  }
  printf("\n");
  /* Upper */
  prettyprint(data[baseSize-(roundSize+1)][0]);
  for(i=0; i<roundSize-1; i++){
    printPoints();
  }
  printf("%1.3e\n", data[baseSize-(roundSize+1)][roundSize]);
  for(i=baseSize-roundSize; i<baseSize; i++){
    for(j=0; j<baseSize-i; j++){
      prettyprint(data[i][j]);
    }
    printf("\n");
  }
}
