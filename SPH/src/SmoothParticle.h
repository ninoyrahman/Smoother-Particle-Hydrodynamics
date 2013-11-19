/*
 * particle.h
 *
 *  Created on: Nov 1, 2013
 *      Author: ninoy
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vector.h"
#include "PiecewiseCubic.h"

class SmoothParticle{
public:
	SmoothParticle(){
		this->position = nullptr;
		this->velocity = nullptr;
		this->force = nullptr;
	}
	SmoothParticle(int idnum, float mass){
		this->id = idnum;
		this->m = mass;
		this->energy = 0.0;
		this->density = 1.0;
		position = new Vector(3);
		velocity = new Vector(3);
		force = new Vector(3);
	}
	SmoothParticle(SmoothParticle &a){
		this->id = a.id;
		this->m = a.m;
		this->energy = a.energy;
		this->density = a.density;
		this->position = new Vector(3);
		this->velocity = new Vector(3);
		this->force = new Vector(3);
		Vector vect(3);
		if(a.position != nullptr)
			*(this->position) = a.getposition();
		if(a.velocity != nullptr)
			*(this->velocity) = a.getvelocity();
		if(a.force != nullptr)
			*(this->force) = a.getforce();

	}
	SmoothParticle& operator=(SmoothParticle a){
		if(this->position == nullptr)
			this->position = new Vector(3);
		if(this->velocity == nullptr)
			this->velocity = new Vector(3);
		if(this->force == nullptr)
			this->force = new Vector(3);

		this->id = a.id;
		this->m = a.m;
		this->energy = a.energy;
		this->density = a.density;
		if(a.position != nullptr)
			*(this->position) = a.getposition();
		if(a.velocity != nullptr)
			*(this->velocity) = a.getvelocity();
		if(a.force != nullptr)
			*(this->force) = a.getforce();

		return *this;
	}
	~SmoothParticle(){
		delete this->position;
		delete this->velocity;
		delete this->force;
	}
	int getid(){
		return this->id;
	}
	float getmass(){
		return this->m;
	}
	Vector& getposition(){
		return *position;
	}
	Vector& getvelocity(){
		return *velocity;
	}
	Vector& getforce(){
		return *force;
	}
	float getenergy(){
		return energy;
	}
	float getdensity(){
		return this->density;
	}
	void setmass(float mass){
		this->m = mass;
	}
	void setposition(Vector p){
		*(this->position) = p;
	}
	void setposition(Vector *p){
		this->position = p;
	}
	void setvelocity(Vector *v){
		this->velocity = v;
	}
	void setvelocity(Vector v){
		*(this->velocity) = v;
	}
	void setforce(Vector *f){
		this->force = f;
	}
	void appendforce(Vector *f){
		*(this->force)+= *f;
	}
	void appendforce(Vector f){
		*(this->force)+= f;
	}
	void setforcezero(){
		float f[] = {0.0, 0.0, 0.0};
		this->force->setvalue(f);
	}
	void setenergy(float E){
		this->energy = E;
	}
	void setdensity(float rho){
		this->density = rho;
	}
	void appenddensity(float rho){
		this->density+= rho;
	}
	void setdensityzero(){
		this->density = 0.0;
	}

	void printinfo(){
		std::cout << "SmoothParticle id = " << this->id << std::endl;
		std::cout << "Mass = " << this->m << std::endl;
		std::cout << "Energy = " << this->energy << std::endl;
		std::cout << "Density = " << this->density << std::endl;
		std::cout << "Position = ";
		this->position->print();
		std::cout << std::endl;
		std::cout << "Velocity = ";
		this->velocity->print();
		std::cout << std::endl;
		std::cout << "Force = ";
		this->force->print();
		std::cout << std::endl;
	}
protected:
	int id;
	float m;
	Vector *position;
	Vector *velocity;
	Vector *force;
	float energy;
	float density;
};


#endif /* PARTICLE_H_ */
