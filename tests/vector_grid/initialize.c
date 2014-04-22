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

void initializeText(Grid *g, char * text){
  g->name = text;
}

void randomInitialize(Grid *g, char * text){
  int i;
  initializeText(g,text);
  for(i=0; i<SIZE; i++){
    g->u1[i]=random();
    g->u2[i]=random();
    g->u3[i]=random();
  }
}

void zeroInitialize(Grid *g, char * text){
  int i;
  initializeText(g,text);
  for(i=0; i<SIZE; i++){
    g->u1[i]=0.0;
    g->u2[i]=0.0;
    g->u3[i]=0.0;
  }
}
