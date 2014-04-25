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
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      g->u1[i][j]=random();
      g->u2[i][j]=random();
      g->u3[i][j]=random();
    }
  }
}

void zeroInitialize(Grid *g, char * text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      g->u1[i][j]=0.0;
      g->u2[i][j]=0.0;
      g->u3[i][j]=0.0;
    }
  }
}

void fileInitialize(Grid *g, char *text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      g->u1[i][j]=1.0*i;
      g->u2[i][j]=1.0*i;
      g->u3[i][j]=1.0*i;
    }
  }
}

void columnInitialize(Grid *g, char *text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      g->u1[i][j]=1.0*j;
      g->u2[i][j]=1.0*j;
      g->u3[i][j]=1.0*j;
    }
  }
}
void sumInitialize(Grid *g, char *text){
  int i,j;
  initializeText(g,text);
  for(i=0; i<g->basevertex; i++){
    for(j=0; j<g->basevertex-i; j++){
      g->u1[i][j]=1.0*i+j;
      g->u2[i][j]=1.0*i+j;
      g->u3[i][j]=1.0*i+j;
    }
  }
}




void boundaryInitialization(Grid *g, double val){
  int i;
  /* Initialization of lower side (0,i) */
  for(i=0; i<g->basevertex; i++){
    g->u1[0][i]=(double)val;
    g->u2[0][i]=(double)val;
    g->u3[0][i]=(double)val;
    g->u1[i][0]=(double)val;
    g->u2[i][0]=(double)val;
    g->u3[i][0]=(double)val;
    g->u1[i][g->basevertex-i-1]=(double)val;
    g->u2[i][g->basevertex-i-1]=(double)val;
    g->u3[i][g->basevertex-i-1]=(double)val;
  }
}
