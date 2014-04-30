/*
 * =====================================================================================
 *
 *       Filename:  initialize.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  21/04/14 22:48:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef _INITIALIZE_H_
#define _INITIALIZE_H_

#include "config.h"


void initializeText(Grid *, char *);
void randomInitialize(Grid *, int, char *);
void zeroInitialize(Grid *, int, char *);
void fileInitialize(Grid *, int, char *);
void columnInitialize(Grid *, int, char *);
void sumInitialize(Grid *, int, char *);
void boundaryInitialization(Grid *, int, double);


#endif

