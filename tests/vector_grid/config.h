/*
 * =====================================================================================
 *
 *       Filename:  config.h
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  21/04/14 23:03:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

typedef struct{
  char * name;
  int * basevertex;
  int * totalvertex;
  double *** u1;
  double *** u2;
  double *** u3;
} Grid;

#define SIZE 3
#endif

