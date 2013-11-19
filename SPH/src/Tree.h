/*
 * tree.h
 *
 *  Created on: Nov 8, 2013
 *      Author: ninoy
 */

#ifndef TREE_H_
#define TREE_H_

#include "Node.h"
#include "Gravity.h"

class Tree{
public:
	Tree(){
		this->root = nullptr;
	}
	Tree(Node treeroot){
		this->root = new Node(treeroot);
		this->count = 0;
	}
	~Tree(){
		this->treetraversaldeletenode(this->getroot());
	}
	void treetraversaldeletenode(Node *node){
		if(node != nullptr){
			if(node->getchild() != nullptr){
				for(int i = 0; i < 8; i++){
					if(node->getischildthere(i) == true){
						this->treetraversaldeletenode(node->getchild(i));
					}
				}
			}
			//Post-traversal TODO
			node->~Node();
		}
	}
	void insertparticle(SmoothParticle *particle){
		this->insertparticle(particle,this->getroot());
	}
	void insertparticle(SmoothParticle *particle, Node *node){
		int whichchild;
		if(node->getchild() == nullptr){
			if(node->getkey() == nullptr)
				node->setkey(particle);
			else{
				whichchild = whichbranch(particle, node);
				node->setchild(particle, whichchild);
				insertparticle(node->getkey(),node);
			}
		}else {
			whichchild = whichbranch(particle, node);
			if(node->getischildthere(whichchild) == false)
				node->setchild(particle, whichchild);
			else if(node->getischildthere(whichchild) == true){
				insertparticle(particle,node->getchild(whichchild));
			}
		}
	}
	int whichbranch(SmoothParticle *particle, Node *node){
		int whichchild;
		Vector dist(3);
		dist = particle->getposition() - (node->getend() + node->getstart())*0.5;
		if(dist.getvalue(0) <= 0.0 && dist.getvalue(1) <= 0.0 && dist.getvalue(2) <= 0.0)
			whichchild = 0;
		else if(dist.getvalue(0) <= 0.0 && dist.getvalue(1) > 0.0 && dist.getvalue(2) <= 0.0)
			whichchild = 1;
		else if(dist.getvalue(0) <= 0.0 && dist.getvalue(1) <= 0.0 && dist.getvalue(2) > 0.0)
			whichchild = 2;
		else if(dist.getvalue(0) <= 0.0 && dist.getvalue(1) > 0.0 && dist.getvalue(2) > 0.0)
			whichchild = 3;
		else if(dist.getvalue(0) > 0.0 && dist.getvalue(1) <= 0.0 && dist.getvalue(2) <= 0.0)
			whichchild = 4;
		else if(dist.getvalue(0) > 0.0 && dist.getvalue(1) > 0.0 && dist.getvalue(2) <= 0.0)
			whichchild = 5;
		else if(dist.getvalue(0) > 0.0 && dist.getvalue(1) <= 0.0 && dist.getvalue(2) > 0.0)
			whichchild = 6;
		else if(dist.getvalue(0) > 0.0 && dist.getvalue(1) > 0.0 && dist.getvalue(2) > 0.0)
			whichchild = 7;

		return whichchild;
	}
	void treetraversal(Node *node){
		if(node != nullptr){
			//Pre-Traversal TODO
			bool is_leaf = true;
			for(int i = 0; i < 8; i++){
				if(node->getischildthere(i) == true){
					treetraversal(node->getchild(i));
					is_leaf = false;
				}
			}
			//Post-traversal TODO
			if(is_leaf == true){
				//At leaf TODO
			}
		}
	}
	void treetraversalcalculateforce(SmoothParticle *particle, float theta){
//		std::cout << "particle id = " << particle->getid() << std::endl;
		this->count = 0;
		this->treetraversalcalculateforce(particle, this->getroot(), theta);
	}
	void treetraversalcalculateforce(SmoothParticle *particle, Node *node, float theta){

		if(node != nullptr){
			//Pre-Traversal TODO

			float r = this->calculatedistance(particle, node);
			float diam = this->calculatediam(node);
			if((diam <= theta*r || node->getchild() == nullptr) && r > 0){
				SmoothParticle *body = new SmoothParticle[2];
				body[0] = *particle;
				body[1] = *(node->getkey());
				particle->appendforce(fg.evaluate(body));
				(this->count)++;
				delete[] body;
				return;
			} else {
				for(int i = 0; i < 8; i++){
					if(node->getischildthere(i) == true){
						this->treetraversalcalculateforce(particle, node->getchild(i), theta);
					}
				}
			}
		}
	}
	float calculatedistance(SmoothParticle *particle, Node *node){
		return (particle->getposition() - node->getkey()->getposition()).length();
	}
	float calculatediam(Node *node){
		return node->getdomainsize().length();
	}
	float calculatepesudomass(Node *node){
		float m = 0;
		for(int i = 0; i < 8; i++){
			if(node->getischildthere(i) == true)
				m+= node->getchild(i)->getkey()->getmass();
		}
		return m;
	}
	Vector& calculatepesudoposition(Node *node){
		Vector *nodeposition = new Vector(3);
		for(int i = 0; i < 8; i++){
			if(node->getischildthere(i) == true)
				(*nodeposition)+= (node->getchild(i)->getkey()->getposition())*(node->getchild(i)->getkey()->getmass());
		}
		(*nodeposition) = (*nodeposition)*(1.0/node->getkey()->getmass());
		return *nodeposition;
	}
	void setpseudoparticle(Node *node){
		node->unsetkey();
		float m = this->calculatepesudomass(node);
		node->setkey(m);
		Vector position(3);
		position = this->calculatepesudoposition(node);
		node->getkey()->setposition(position);
	}
	void treetraversalsetpeudoparticle(){
		this->treetraversalsetpeudoparticle(this->getroot());
	}
	void treetraversalsetpeudoparticle(Node *node){
		if(node != nullptr){
			bool is_leaf = true;
			for(int i = 0; i < 8; i++){
				if(node->getischildthere(i) == true){
					this->treetraversalsetpeudoparticle(node->getchild(i));
					is_leaf = false;
				}
			}
			//Post-traversal TODO
			if(is_leaf == false){
				this->setpseudoparticle(node);
			}
		}
	}
	Node* getroot(){
		return this->root;
	}
	int getcount(){
		return this->count;
	}
	void printinfo(){
		this->root->printinfo();
	}
private:
	Node *root;
	Gravity fg;
	int count;
};

#endif /* TREE_H_ */
