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

int main(){
  /* Definitions */
  Grid g1;

  /* Auxiliary definitions */

  /* Malloc */
  mallocGrid(&g1);

  /* Initializacion */
  randomInitialize(&g1, "g1 random");
  printUp(&g1);
  printDown(&g1);
  zeroInitialize(&g1, "g1 zero");
  printUp(&g1);
  printDown(&g1);
  fileInitialize(&g1, "g1 file");
  printUp(&g1);
  printDown(&g1);
  boundaryInitialization(&g1, -9.0);
  printUp(&g1);
  printDown(&g1);

  /* Free */
  freeGrid(&g1);
  return 0;
}
