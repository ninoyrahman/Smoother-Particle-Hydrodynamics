/*
 * VelocityStoermerVerlet.h
 *
 *  Created on: Nov 2, 2013
 *      Author: ninoy
 */

#ifndef VELOCITYSTOERMERVERLET_H_
#define VELOCITYSTOERMERVERLET_H_

#include "TimeIntegration.h"

class VelocityStoermerVerlet: public TimeIntegration{
public:
	VelocityStoermerVerlet(): TimeIntegration(){}
	void updatevelocity(SmoothParticle *particles, float dt){
		Vector newvelocity(3);
		newvelocity = (particles->getvelocity()) + (particles->getforce())*(dt/(2.0*(particles->getmass())));
		particles->setvelocity(newvelocity);
	}
	void updatevelocity(int n, SmoothParticle **particles, float dt){
		Vector newvelocity(3);
		for(int i = 0; i < n; i++){
//			std::cout << "particle id = " << particles[i]->getid() << ", Force = ";
//			particles[i]->getforce().print();
//			std::cout << std::endl;
			newvelocity = (particles[i]->getvelocity()) + (particles[i]->getforce())*(dt/(2.0*(particles[i]->getmass())));
			particles[i]->setvelocity(newvelocity);
		}
	}
	void updateposition(SmoothParticle *particles, float dt){
		Vector newposition(3);
		newposition = (particles->getposition()) + (particles->getvelocity())*dt;
		particles->setposition(newposition);
	}
	void updateposition(int n, SmoothParticle **particles, float dt){
		Vector newposition(3);
		for(int i = 0; i < n; i++){
			newposition = (particles[i]->getposition()) + (particles[i]->getvelocity())*dt;
			particles[i]->setposition(newposition);
		}
	}
};

#endif /* VELOCITYSTOERMERVERLET_H_ */
