/*
 * TimeIntegration.h
 *
 *  Created on: Nov 1, 2013
 *      Author: ninoy
 */

#ifndef TIMEINTEGRATION_H_
#define TIMEINTEGRATION_H_

#include "SmoothParticle.h"
#include "Force.h"
#include "Vector.h"
#include "SmoothParticle.h"

class TimeIntegration{
public:
	virtual void updateposition(SmoothParticle *particles, float dt) = 0;
	virtual void updateposition(int n, SmoothParticle **particles, float dt) = 0;
	virtual void updatevelocity(SmoothParticle *particles, float dt) = 0;
	virtual void updatevelocity(int n, SmoothParticle **particles, float dt) = 0;
};

#endif /* TIMEINTEGRATION_H_ */
