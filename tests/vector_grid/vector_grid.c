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
  Grid g1;

  /* Auxiliary definitions */

  /* Malloc */
  mallocGrid(&g1);

  /* Initializacion */
  randomInitialize(&g1, 3, "g1 random");
  maxnormGrid(&g1,3);
  printUp(&g1,3);
  freeGrid(&g1);
  return 0;
}
