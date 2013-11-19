/*
 * SmoothingKernal.h
 *
 *  Created on: Nov 3, 2013
 *      Author: ninoy
 */

#ifndef SMOOTHINGKERNAL_H_
#define SMOOTHINGKERNAL_H_

#include "Vector.h"
#include "SmoothParticle.h"

class SmoothingKernal{
public:
	virtual float gethalfwidth() = 0;
	virtual void sethalfwidth(float hp) = 0;
	virtual float evaluate(SmoothParticle *particals) = 0;
	virtual Vector& gradient(SmoothParticle *particals) = 0;
	virtual void printinfo() = 0;
};



#endif /* SMOOTHINGKERNAL_H_ */
