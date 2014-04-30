/*
 * =====================================================================================
 *
 *       Filename:  output.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 23:10:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _OUTPUT_H_
#define _OUTPUT_H_
#include "config.h"

void printUp(Grid *g, int level);
void printDown(Grid *g, int level);
void printBigTriangleUp(double **, int);
void printBigTriangleDown(double **, int);
void printTriangleUp(double **, int);
void printTriangleDown(double **, int);
#endif

