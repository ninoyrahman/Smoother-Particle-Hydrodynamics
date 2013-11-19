/*
 * list.h
 *
 *  Created on: Nov 17, 2013
 *      Author: ninoy
 */

#ifndef LIST_H_
#define LIST_H_

#include "SmoothParticle.h"
#include "Gravity.h"

class List{
public:
	List(){
		this->p = nullptr;
		this->next = nullptr;
	}
	List(SmoothParticle *particle){
		this->p = new SmoothParticle;
		this->p = particle;
		this->next = nullptr;
	}
	~List(){
		if(this->next != nullptr){
			this->next->~List();
		}
		if(this->p != nullptr)
			this->p = nullptr;
	}
	void insertparticle(SmoothParticle *particle){
		if(this->p == nullptr){
			this->p = new SmoothParticle;
			this->p = particle;
		} else if(this->next == nullptr){
			this->next = new List(particle);
		} else {
			this->next->insertparticle(particle);
		}
	}
	void listtraversalcalculateforce(float halfwidth){
		if(this->p != nullptr){
			this->listtraversalcalculateforce(this->p, halfwidth);
			if(this->next != nullptr)
				this->next->listtraversalcalculateforce(halfwidth);
		}

	}
	void listtraversalcalculateforce(List *list, float halfwidth){
		if(this->p != nullptr){
			list->listtraversalcalculateforce(this->p, halfwidth);
			if(this->next != nullptr)
				this->next->listtraversalcalculateforce(list, halfwidth);
		}
	}
	void listtraversalcalculateforce(SmoothParticle *particle, float halfwidth){
		if(this->p != nullptr){
			SmoothParticle *body = new SmoothParticle[2];
			body[0] = *particle;
			body[1] = *(this->p);
			Vector gradP(3);
			float P = this->calculatepressure(this->p->getdensity());
			this->W.sethalfwidth(halfwidth);
			gradP = (this->W.gradient(body))*(P*(this->p->getmass()/this->p->getdensity()));
			particle->appendforce(gradP*(-1.0));
			this->p->appendforce(gradP);
			delete[] body;
			if(this->next != nullptr)
				this->next->listtraversalcalculateforce(particle, halfwidth);
		}
		return;
	}
	void listtraversalcalculatedensity(float halfwidth){
		if(this->p != nullptr){
			this->listtraversalcalculatedensity(this->p, halfwidth);
			if(this->next != nullptr)
				this->next->listtraversalcalculatedensity(halfwidth);
		}
	}
	void listtraversalcalculatedensity(List *list, float halfwidth){
		if(this->p != nullptr){
			list->listtraversalcalculatedensity(this->p, halfwidth);
			if(this->next != nullptr)
				this->next->listtraversalcalculatedensity(list, halfwidth);
		}
	}
	void listtraversalcalculatedensity(SmoothParticle *particle, float halfwidth){
		if(this->p != nullptr){
			SmoothParticle *body = new SmoothParticle[2];
			body[0] = *particle;
			body[1] = *(this->p);
			this->W.sethalfwidth(halfwidth);
			float rho = (this->W.evaluate(body))*(this->p->getmass());
			particle->appenddensity(rho);
			this->p->appenddensity(rho);
			delete[] body;
			if(this->next != nullptr)
				this->next->listtraversalcalculatedensity(particle, halfwidth);
		}
		return;
	}

	float calculatedistancesq(SmoothParticle *p1, SmoothParticle *p2){
		return (p1->getposition() - p2->getposition()).lengthsq();
	}
	float calculatepressure(float density){
		return density;
	}
	void printinfo(){
		if(this->p != nullptr){
			this->p->printinfo();
			if(this->next != nullptr)
				this->next->printinfo();
		}
		return;
	}

private:
	SmoothParticle *p;
	List *next;
	PiecewiseCubic W;
};



#endif /* LIST_H_ */
