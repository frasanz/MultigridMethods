/*
 * =====================================================================================
 *
 *       Filename:  initialize.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 22:51:32
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
#include "initialize.h"
#include "memory.h"

void randomInitialize(Grid *g){
  int i;
  for(i=0; i<SIZE; i++){
    g->u1[i]=random();
    g->u2[i]=random();
    g->u3[i]=random();
  }
}

