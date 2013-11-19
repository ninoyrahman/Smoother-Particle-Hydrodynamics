/*
 * Force.h
 *
 *  Created on: Nov 1, 2013
 *      Author: ninoy
 */

#ifndef FORCE_H_
#define FORCE_H_

#include "Vector.h"
#include "SmoothParticle.h"

class Force{
public:
	virtual Vector& evaluate(SmoothParticle *particals) = 0;
	virtual float evalpotential(SmoothParticle *particals) = 0;
	virtual void setparameter(float *parameters) = 0;
	virtual float* getparameter() = 0;
	virtual void printparameter() = 0;
	virtual void printforce() = 0;
protected:
	int n;
	float *param;
};



#endif /* FORCE_H_ */
