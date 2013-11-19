/*
 * cell.h
 *
 *  Created on: Nov 16, 2013
 *      Author: ninoy
 */

#ifndef CELL_H_
#define CELL_H_

#include "List.h"

class Cell{
public:
	Cell(){
		this->start = nullptr;
		this->end = nullptr;
		this->list = nullptr;
		this->n = 0;
	}
	Cell(int idnum, Vector domainstart, Vector domainend){
		this->start = new Vector(domainstart);
		this->end = new Vector(domainend);
		this->list = new List;
		this->n = 0;
		this->id = idnum;
	}
	~Cell(){
		this->start->~Vector();
		this->end->~Vector();
		this->list->~List();
	}

	Vector& getdomainstart(){
		return *(this->start);
	}
	Vector& getdomainend(){
			return *(this->end);
		}
	int getnumofparticle(){
		return this->n;
	}
	List* getlist(){
		return this->list;
	}
	void insertparticle(SmoothParticle *particle){
		this->list->insertparticle(particle);
		(this->n)++;
	}
	void calculateforce(float halfwidth){
		this->list->listtraversalcalculateforce(halfwidth);
	}
	void calculateforce(List *neighblist, float halfwidth){
		this->list->listtraversalcalculateforce(neighblist, halfwidth);
	}
	void calculatedensity(float halfwidth){
		this->list->listtraversalcalculatedensity(halfwidth);
	}
	void calculatedensity(List *neighblist, float halfwidth){
		this->list->listtraversalcalculatedensity(neighblist, halfwidth);
	}
	void printinfo(){
		std::cout << "Cell id = " << this->id << std::endl;
		if(this->start != nullptr){
			std::cout << "Cell Domain Start = ";
			this->start->print();
			std::cout << std::endl;
		}
		if(this->end != nullptr){
			std::cout << "Cell Domain End = ";
			this->end->print();
			std::cout << std::endl;
		}
		std::cout << "Number of particle, n = " << this->n << std::endl;
//		this->list->printinfo();
	}

private:
	int id;
	int n;
	Vector *start;
	Vector *end;
	List *list;
};


#endif /* CELL_H_ */
