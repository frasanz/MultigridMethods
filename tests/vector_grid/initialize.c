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

void randomInitialize(Grid *g, int level, char * text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex[level]; i++){
    for(j=0; j<g->basevertex[level]-i; j++){
      g->u1[level][i][j]=random();
      g->u2[level][i][j]=random();
      g->u3[level][i][j]=random();
    }
  }
}

void zeroInitialize(Grid *g, int level, char * text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex[level]; i++){
    for(j=0; j<g->basevertex[level]-i; j++){
      g->u1[level][i][j]=0.0;
      g->u2[level][i][j]=0.0;
      g->u3[level][i][j]=0.0;
    }
  }
}

void fileInitialize(Grid *g, int level, char *text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex[level]; i++){
    for(j=0; j<g->basevertex[level]-i; j++){
      g->u1[level][i][j]=1.0*i;
      g->u2[level][i][j]=1.0*i;
      g->u3[level][i][j]=1.0*i;
    }
  }
}

void columnInitialize(Grid *g, int level, char *text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex[level]; i++){
    for(j=0; j<g->basevertex[level]-i; j++){
      g->u1[level][i][j]=1.0*j;
      g->u2[level][i][j]=1.0*j;
      g->u3[level][i][j]=1.0*j;
    }
  }
}
void sumInitialize(Grid *g, int level, char *text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex[level]; i++){
    for(j=0; j<g->basevertex[level]-i; j++){
      g->u1[level][i][j]=1.0*i+j;
      g->u2[level][i][j]=1.0*i+j;
      g->u3[level][i][j]=1.0*i+j;
    }
  }
}




void boundaryInitialization(Grid *g, int level, double val){
  int i;
  /* Initialization of lower side (0,i) */
  for(i=0; i<g->basevertex[level]; i++){
    g->u1[level][0][i]=(double)val;
    g->u2[level][0][i]=(double)val;
    g->u3[level][0][i]=(double)val;
    g->u1[level][i][0]=(double)val;
    g->u2[level][i][0]=(double)val;
    g->u3[level][i][0]=(double)val;
    g->u1[level][i][g->basevertex[level]-i-1]=(double)val;
    g->u2[level][i][g->basevertex[level]-i-1]=(double)val;
    g->u3[level][i][g->basevertex[level]-i-1]=(double)val;
  }
}
