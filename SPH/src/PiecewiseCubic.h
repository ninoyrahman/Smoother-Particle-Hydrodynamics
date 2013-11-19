/*
 * PiecewiseCubic.h
 *
 *  Created on: Nov 3, 2013
 *      Author: ninoy
 */

#ifndef PIECEWISECUBIC_H_
#define PIECEWISECUBIC_H_

#include "SmoothingKernal.h"
#define PI 3.14159

class PiecewiseCubic: public SmoothingKernal{
public:
	PiecewiseCubic(): SmoothingKernal(){}
	PiecewiseCubic(float hp): SmoothingKernal(){
		this->h = hp;
	}
	PiecewiseCubic(const PiecewiseCubic &a): SmoothingKernal(){
		this->h = a.h;
	}
	float gethalfwidth(){
		return this->h;
	}
	void sethalfwidth(float hp){
		this->h = hp;
	}
	float evaluate(SmoothParticle *particals){
		Vector p1(3), p2(3);
		p1 = particals[0].getposition();
		p2 = particals[1].getposition();
		float r = (p1 - p2).length()/(this->h);
		float c = 1.0/(PI*(this->h)*(this->h)*(this->h));
		if (1.0 >= r){
			return c*(1 - 1.5*r*r + 0.75*r*r*r);
		}else if (2.0 >= r){
			return (c/4.0)*(2 - r)*(2 - r)*(2 - r);
		}
		return 0.0;
	}
	Vector& gradient(SmoothParticle *particals){
		Vector *grad = new Vector(3);
		Vector p1(3), p2(3);
		p1 = particals[0].getposition();
		p2 = particals[1].getposition();
		float r = (p1 - p2).length()/(this->h);
		float c = 1.0/(PI*(this->h)*(this->h)*(this->h)*(this->h));
		float value;
		if (1.0 >= r){
			value = c*(-3*r + 2.25*r*r);
		}else if (2.0 >= r){
			value = -(3.0*c/4.0)*(2 - r)*(2 - r);
		}else{
			value = 0.0;
		}
		*grad = (p1 - p2)*(value/(r*(this->h)));
		return *grad;
	}
	void printinfo(){
		std::cout << "Piecewise Cubic Smoothing Function" << std:: endl;
		std::cout << std::endl;
		std::cout << "Halfwidth, h = " << this->h << std::endl;
		std::cout << " W(r, h) = " << std::endl;
		std::cout << " (1/pi*h^3)*[1 - (3/2)*(r/h)^2 + (3/4)*(r/h)^3],	0 < r/h <= 1" << std::endl;
		std::cout << " (1/4*pi*h^3)*[2 - (r/h)]^3,				1 < r/h <= 2" << std::endl;
		std::cout << " 0, 							r/h > 2" << std::endl;
	}
private:
	float h;
};



#endif /* PIECEWISECUBIC_H_ */
