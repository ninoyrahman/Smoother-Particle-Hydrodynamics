/*
 * LCA.h
 *
 *  Created on: Nov 16, 2013
 *      Author: ninoy
 */

#ifndef LCA_H_
#define LCA_H_

#include "Cell.h"

class LCA{
public:
	LCA(){
		this->cell = nullptr;
		this->start = nullptr;
		this->end = nullptr;
		this->cellsize = nullptr;
		this->ncell = 0;
	}
	LCA(int cellperlength, Vector domainstart, Vector domainend){
		ncell = cellperlength*cellperlength*cellperlength;
		this->cell = new Cell*[ncell];
		this->start = new Vector(domainstart);
		this->end = new Vector(domainend);
		this->cellsize = new Vector(3);
		this->cellnoperdir = cellperlength;
		int cellindex;
		Vector size(3);
		Vector x(3);
		Vector y(3);
		Vector z(3);
		Vector celldoaminstart(3);
		Vector celldoaminend(3);
		size = *(this->end) - *(this->start);
		*(this->cellsize) = size*(1.0/(this->cellnoperdir));
		x.setvalue(this->cellsize->getvalue(0),0);
		y.setvalue(this->cellsize->getvalue(1),1);
		z.setvalue(this->cellsize->getvalue(2),2);
		for(int i = 0; i < (this->cellnoperdir); i++){
			for(int j = 0; j < (this->cellnoperdir); j++){
				for(int k= 0; k < (this->cellnoperdir); k++){
					cellindex = i*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + k;
					celldoaminstart = domainstart + x*i + y*j + z*k;
					celldoaminend = celldoaminstart + *(this->cellsize);
					cell[cellindex] = new Cell(cellindex, celldoaminstart, celldoaminend);
				}
			}
		}
	}
	~LCA(){
		for(int i = 0; i < ncell; i++)
			this->cell[i]->~Cell();
		delete this->cell;
		this->start->~Vector();
		this->end->~Vector();
	}
	void insertparticle(int n, SmoothParticle **particle){
		if(this->cell != nullptr){
			Vector particleposition(3);
			float xlength, ylength, zlength;
			xlength = this->cellsize->getvalue(0);
			ylength = this->cellsize->getvalue(1);
			zlength = this->cellsize->getvalue(2);
			int i, j, k, cellindex;
			for(int l = 0; l < n; l++){
				particleposition = particle[l]->getposition() + *(this->start);
				i = (int) floor(particleposition.getvalue(0)*(1.0/xlength));
				j = (int) floor(particleposition.getvalue(1)*(1.0/ylength));
				k = (int) floor(particleposition.getvalue(2)*(1.0/zlength));
//				std::cout << "(i, j, k) = " << i << ", " << j << ", " << k << std::endl;
				cellindex = i*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + k;
				this->cell[cellindex]->insertparticle(particle[l]);
			}
		}
	}
	void calculateforce(float halfwidth){
		if(this->cell != nullptr){
			int cellindex;
			int neughbindex;
			for(int i = 0; i < (this->cellnoperdir); i++){
				for(int j = 0; j < (this->cellnoperdir); j++){
					for(int k= 0; k < (this->cellnoperdir); k++){
						cellindex = i*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + k;
						cell[cellindex]->calculateforce(halfwidth);
						if(k < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 && j < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(j < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + k;
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 && j < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 &&  j > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j - 1)*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(j > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j - 1)*(this->cellnoperdir) + k;
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 &&  j > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j - 1)*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + k;
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 &&  j < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(j < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + k;
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 &&  j < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculateforce(cell[neughbindex]->getlist(), halfwidth);
						}
					}
				}
			}
		}
	}
	void calculatedensity(float halfwidth){
		if(this->cell != nullptr){
			int cellindex;
			int neughbindex;
			for(int i = 0; i < (this->cellnoperdir); i++){
				for(int j = 0; j < (this->cellnoperdir); j++){
					for(int k= 0; k < (this->cellnoperdir); k++){
						cellindex = i*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + k;
//						std::cout << "Cell id = " << cellindex << std::endl;
						cell[cellindex]->calculatedensity(halfwidth);
						if(k < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 && j < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(j < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + k;
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 && j < (this->cellnoperdir) - 1){
							neughbindex = i*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 &&  j > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j - 1)*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(j > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j - 1)*(this->cellnoperdir) + k;
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 &&  j > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j - 1)*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + k;
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + j*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k > 0 &&  j < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k - 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(j < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + k;
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
						if(k < (this->cellnoperdir) - 1 &&  j < (this->cellnoperdir) - 1 && i < (this->cellnoperdir) - 1){
							neughbindex = (i + 1)*(this->cellnoperdir)*(this->cellnoperdir) + (j + 1)*(this->cellnoperdir) + (k + 1);
							cell[cellindex]->calculatedensity(cell[neughbindex]->getlist(), halfwidth);
						}
					}
				}
			}
		}
	}
	int getnumberofcell(){
		return this->ncell;
	}
	float getavgparticlepercell(){
		float avg = 0.0;
		for(int i = 0; i < ncell; i++){
			avg+= this->cell[i]->getnumofparticle();
		}
		return avg/(this->ncell);
	}
	int getmaxparticlepercell(){
		int max = 0;
		for(int i = 0; i < ncell; i++){
			max = (this->cell[i]->getnumofparticle() > max) ? this->cell[i]->getnumofparticle() : max;
		}
		return max;
	}
	void printinfo(){
		if(this->start != 0){
			std::cout << "Domain start = ";
			this->start->print();
			std::cout << std::endl;
		}
		if(this->end != 0){
			std::cout << "Domain end = ";
			this->end->print();
			std::cout << std::endl;
		}
		if(this->cell != nullptr){
			std::cout << "Number of cell = " << ncell << std::endl;
			for(int i = 0; i < ncell; i++)
				this->cell[i]->printinfo();
		}
	}

private:
	Cell **cell;
	Vector *start;
	Vector *end;
	Vector *cellsize;
	int ncell;
	int cellnoperdir;
};



#endif /* LCA_H_ */
