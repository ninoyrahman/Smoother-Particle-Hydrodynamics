/*
 * Gravity.h
 *
 *  Created on: Nov 1, 2013
 *      Author: ninoy
 */

#ifndef GRAVITY_H_
#define GRAVITY_H_

#include "Force.h"

class Gravity: public Force{
public:
	Gravity(): Force(){
		n = 1;
		param = new float[n];
		param[0] = 6.67384e-11;
	}
	Vector& evaluate(SmoothParticle *particals){
		Vector *force = new Vector(3);
		Vector p1(3), p2(3), d(3);
		p1 = particals[0].getposition();
		p2 = particals[1].getposition();
		d  = p2 - p1;
		float dvalue = d.length();
		float fvalue = (param[0])*(particals[0].getmass())*(particals[1].getmass())/(dvalue*dvalue*dvalue);
		*force = d*fvalue;
		return *force;
	}
	float evalpotential(SmoothParticle *particals){
		float pot;
		Vector p1(3), p2(3), d(3);
		p1 = particals[0].getposition();
		p2 = particals[1].getposition();
		d  = p2 - p1;
		float dvalue = d.length();
		pot = -(param[0])*(particals[0].getmass())*(particals[1].getmass())/dvalue;
		return pot;
	}
	void setparameter(float *parameter){
		param[0] = parameter[0];
	}
	float* getparameter(){
		return param;
	}
	void printparameter(){
		std::cout << "Gravitational Constant, G = " << param[0] << std::endl;
	}
	void printforce(){
		std::cout << "Fg = G*M1*M2/r^2" << std::endl;
		std::cout << "G = Gravitational Constant (parameter)" << std::endl;
		std::cout << "M1, M2 = Mass of particle" << std::endl;
		std::cout << "r = Distance between particle" << std::endl;
	}

};


#endif /* GRAVITY_H_ */
