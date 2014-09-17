/*
 * =====================================================================================
 *
 *       Filename:  vector_grid.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 22:10:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vector_grid.h"
#include "memory.h"
#include "initialize.h"
#include "config.h"
#include "output.h"
#include "norms.h"

int main(){
  /* Definitions */
  Grid u;
  Grid v;
  Grid f;

  /* Auxiliary definitions */
  int i;

  /* Malloc */
  mallocGrid(&u);
  mallocGrid(&v);
  mallocGrid(&f);

  /* Initialize in the finest grid */
  randomInitialize(&u, SIZE-1, "u random");
  boundaryInitialization(&u, SIZE-1, 0.0);

  for(i=0; i<SIZE; i++){
    zeroInitialize(&v, i, "v zero");
    zeroInitialize(&f, i, "f zero"); 
  }


  /* Free grids */
  freeGrid(&u);
  freeGrid(&v);
  freeGrid(&f);
  return 0;
}
