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

void printPlain(Grid *g){
  int i;
  printf("u1\n");
  for(i=0; i<SIZE; i++){
    printf("%f ", g->u1[i]);
  }
  printf("\n");
  printf("u2\n");
  for(i=0; i<SIZE; i++){
    printf("%f ", g->u3[i]);
  }
  printf("\n");
  printf("u3\n");
  for(i=0; i<SIZE; i++){
    printf("%f ", g->u3[i]);
  }
}

