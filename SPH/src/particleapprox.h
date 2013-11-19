/*
 * particleapprox.h
 *
 *  Created on: Nov 3, 2013
 *      Author: ninoy
 */

#ifndef PARTICLEAPPROX_H_
#define PARTICLEAPPROX_H_

#include "smoothparticle.h"

//class ParticleApprox{
//public:
//	ParticleApprox(){}
//	ParticleApprox(float hp){
//		this->W.sethalfwidth(hp);
//	}
//
//private:
//	PiecewiseCubic W;
//};
//
//
//
//double calculateDensity(int n, int i, SmoothParticle **particle){
//	double rho = 0.0;
//	for (int j = 0; j < n; j++)
//		rho+= particle[j]->getmass() * particle[j]->getW(particle[i]->getposition());
//	return rho;
//}
//
//Vector& calculategradP(int n, int i, SmoothParticle **particle){
//	Vector *gradP = new Vector(3);
//	double P;
//	double length;
//	for (int j = 0; j < n; j++){
//		P = calculateP(particle[j]->getdensity());
//		*gradP-= (particle[j]->getgradW(particle[i]->getposition())) * (P * (particle[j]->getmass()/particle[j]->getdensity()));
//	}
//	return *gradP;
//}
//
//double calculateP(double density){
//	return density;
//}

#endif /* PARTICLEAPPROX_H_ */
