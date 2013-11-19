/*
 * node.h
 *
 *  Created on: Nov 6, 2013
 *      Author: ninoy
 */

#ifndef NODE_H_
#define NODE_H_

#include "SmoothParticle.h"

class Node{
public:
	Node(){
		this->k = nullptr;
		this->p = nullptr;
		this->child = nullptr;
		this->is_child_there = nullptr;
		this->domainsize = nullptr;
		this->start = nullptr;
		this->end = nullptr;
	}
	Node(Vector domainstart, Vector domainend){
		this->k = nullptr;
		this->p = nullptr;
		this->child = nullptr;
		this->is_child_there = nullptr;
		this->start = new Vector(3);
		this->end = new Vector(3);
		this->domainsize = new Vector(3);
		*(this->start) = domainstart;
		*(this->end) = domainend;
		*(this->domainsize) = *(this->end) - *(this->start);
	}
	Node(Node &a){
		if(a.k == nullptr)
			this->k = nullptr;
		else
			this->k = a.k;

		if(a.p == nullptr)
			this->p = nullptr;
		else
			this->p = a.p;

		if(a.domainsize == nullptr)
			this->domainsize = nullptr;
		else{
			this->domainsize = new Vector(3);
			*(this->domainsize) = *(a.domainsize);
		}

		if(a.start == nullptr)
			this->start = nullptr;
		else{
			this->start = new Vector(3);
			*(this->start) = *(a.start);
		}

		if(a.end == nullptr)
			this->end = nullptr;
		else{
			this->end = new Vector(3);
			*(this->end) = *(a.end);
		}

		if(a.child == nullptr){
			this->child = nullptr;
			this->is_child_there = nullptr;
		}
		else{
			this->child = new Node*[8];
			this->is_child_there = new bool[8];
			for(int i = 0; i < 8; i++){
				(this->is_child_there)[i] = (a.is_child_there)[i];
				if((a.is_child_there)[i] == true){
					(this->child)[i] = (a.child)[i];
					(this->child)[i]->p = this;
				}else{
					(this->child)[i] = nullptr;
				}
			}
		}
	}
	~Node(){
		if(this->domainsize != nullptr)
			this->domainsize->~Vector();
		if(this->start != nullptr)
			this->start->~Vector();
		if(this->end != nullptr)
			this->end->~Vector();
		if(this->k != nullptr)
			this->k = nullptr;
		if(this->is_child_there != nullptr)
			delete[] this->is_child_there;
	}
	SmoothParticle* getkey(){
		return this->k;
	}
	Node* getparent(){
		return this->p;
	}
	Node** getchild(){
		return this->child;
	}
	Node* getchild(int i){
		if(this->child != nullptr){
			if((this->child)[i] != nullptr){
				return (this->child)[i];
			} else{
				return nullptr;
			}
		}else{
			return nullptr;
		}
	}
	bool getischildthere(int i){
		if(this->is_child_there == nullptr)
			return false;
		else
			return (this->is_child_there)[i];
	}
	int getcurrentchildno(){
		int n = 0;
		for(int i = 0; i < 8; i++){
			if((this->is_child_there)[i] == true)
				n++;
		}
		return n;
	}
	Vector& getdomainsize(){
		return *(this->domainsize);
	}
	Vector& getstart(){
		return *(this->start);
	}
	Vector& getend(){
		return *(this->end);
	}
	void setkey(SmoothParticle *key){
		if(this->k == nullptr)
			this->k = new SmoothParticle;
		(this->k) = key;
	}
	void unsetkey(){
		this->k = nullptr;
	}
	void setkey(float mass){
		if(this->k == nullptr)
			this->k = new SmoothParticle(0,mass);
	}
	void setdomainsize(Vector size){
		if(this->domainsize == nullptr)
			this->domainsize = new Vector(3);
		*(this->domainsize) = size;
	}
	void setstart(Vector domainstart){
		if(this->start == nullptr)
			this->start = new Vector(3);
		*(this->start) = domainstart;
	}
	void setend(Vector domainend){
		if(this->end == nullptr)
			this->end = new Vector(3);
		*(this->end) = domainend;
	}
	void setchild(Node *who, int where){
		if(this->child == nullptr){
			this->child = new Node*[8];
			this->is_child_there = new bool[8];
			for (int i = 0; i < 8; i++){
				(this->child)[i] = nullptr;
				(this->is_child_there)[i] = false;
			}
		}
		(this->child)[where] = who;
		(this->is_child_there)[where] = true;
	}
	void setchild(SmoothParticle *particle, int whichchild){
		if(this->child == nullptr){
			this->child = new Node*[8];
			this->is_child_there = new bool[8];
			for (int i = 0; i < 8; i++){
				(this->child)[i] = new Node;
				(this->is_child_there)[i] = false;
			}
		}
		(this->is_child_there)[whichchild] = true;
		(this->child)[whichchild]->setdomainsize((*(this->domainsize))*0.5);
		(this->child)[whichchild]->p = this;
		(this->child)[whichchild]->setkey(particle);

		Vector xtemp(3);
		Vector ytemp(3);
		Vector ztemp(3);
		xtemp.setvalue((this->child)[whichchild]->domainsize->getvalue(0),0);
		ytemp.setvalue((this->child)[whichchild]->domainsize->getvalue(1),1);
		ztemp.setvalue((this->child)[whichchild]->domainsize->getvalue(2),2);
		Vector childstart(3);
		Vector childend(3);
		childstart = *(this->start);

		switch(whichchild){
			case 0:
			break;
			case 1:
				childstart = childstart + ytemp;
			break;
			case 2:
				childstart = childstart + ztemp;
			break;
			case 3:
				childstart = childstart + ytemp + ztemp;
			break;
			case 4:
				childstart = childstart + xtemp;
			break;
			case 5:
				childstart = childstart + xtemp + ytemp;
			break;
			case 6:
				childstart = childstart + xtemp + ztemp;
			break;
			case 7:
				childstart = childstart + xtemp + ytemp + ztemp;
			break;
			default:
				std::cout << "Child number should be between 0 to 7" << std::endl;
		}
		childend = childstart + *((this->child)[whichchild]->domainsize);
		(this->child)[whichchild]->setstart(childstart);
		(this->child)[whichchild]->setend(childend);

	}
	void printinfo(){

		if(this->p == nullptr)
			std::cout << "root node" << std::endl;
		if(this->child == nullptr)
			std::cout << "leaf node" << std::endl;
		if(this->p != nullptr && this->child != nullptr)
			std::cout << "inner node" << std::endl;

		if(this->domainsize != nullptr){
			std::cout << "node domain size = ";
			this->domainsize->print();
			std::cout << std::endl;
		}
		if(this->start != nullptr){
			std::cout << "node domain start = ";
			this->start->print();
			std::cout << std::endl;
		}
		if(this->end != nullptr){
			std::cout << "node domain end = ";
			this->end->print();
			std::cout << std::endl;
		}

		if(this->k != nullptr){
			std::cout << "Particle = " << std::endl;
			this->k->printinfo();
		}

		if(this->child != nullptr){
			for(int i = 0; i < 8; i++){
				if((this->is_child_there)[i] == true && (this->child)[i] != nullptr){
					std::cout << "child at " << i << " branch" << std::endl;
					(this->child)[i]->printinfo();
				}else {
					std::cout << "no child at " << i << " branch" << std::endl;
				}
			}
		}
	}
private:
	SmoothParticle *k;
	Node *p;
	Node **child;
	bool *is_child_there;
	Vector *domainsize;
	Vector *start;
	Vector *end;
};


#endif /* NODE_H_ */
