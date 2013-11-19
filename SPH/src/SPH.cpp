//============================================================================
// Name        : SPH.cpp
// Author      : Ninoy
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "string.h"
#include "PiecewiseCubic.h"
#include "SmoothParticle.h"
#include "Vector.h"
#include "Node.h"
#include "Tree.h"
#include "LCA.h"
#include "VelocityStoermerVerlet.h"
#include "WriteVTK.h"


int main() {
	std::cout << "SPH" << std::endl; // prints SPH
//	SmoothParticle earth(0,1.0);
//	Vector *r = new Vector(3);
//	r->setvalue(1.0,0);
//	earth.printinfo();
//	earth.sethalfwidth(1.0);
//	std::cout << "W = " << earth.getW(*r) << std::endl;
//	std::cout << "gradW = ";
//	earth.getgradW(*r).print();


//	//Tree Algorithm
//	float m = 1.0;
//	int N = 6000;
//	Vector positionvector(3);
//	SmoothParticle **particles = new SmoothParticle*[N];
//	for(int i = 0; i < N; i++){
//		float positionarray[] = {rand()%300000, rand()%300000, rand()%300000};
//		positionvector.setvalue(positionarray);
//		positionvector = positionvector*(1.0/150000.0);
//		particles[i] = new SmoothParticle(i, m);
//		particles[i]->setposition(positionvector);
//	}
//
//	std::cout << "Initialization Complete" << std::endl;
//
//	Vector rootstart(3);
//	Vector rootend(3);
//	rootstart.zeros();
//	rootend.ones();
//	rootend = rootend*2.0;
//	Node *root = new Node(rootstart,rootend);
//	Tree tree(*root);
//
//	float avg = 0.0;
//	clock_t begin = clock();
//
//	for(int i = 0; i < N; i++)
//		tree.insertparticle(particles[i]);
//	tree.treetraversalsetpeudoparticle();
//
//	std::cout << "Force Calculation Start" << std::endl;
//
//	for(int i = 0; i < N; i++){
//		std::cout << "particle id = " << i << std::endl;
//		tree.treetraversalcalculateforce(particles[i],1.0);
//		avg+=tree.getcount();
//	}
//
//	clock_t end = clock();
//	double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;
//	std::cout << "elapsed_secs = " << elapsed_secs << std::endl;
//	std::cout << "Avg hit = " << avg/N << std::endl;
//
//	VelocityStoermerVerlet vsv;
//	vsv.updatevelocity(N, particles, 5e-6);
//	vsv.updateposition(N, particles, 1e-5);
//	vsv.updatevelocity(N, particles, 5e-6);
//
//	writevtkpointdata("treealgorithm.vtk", particles, N);
//	tree.~Tree();

	//Linked cell algorithm
	float m = 1.0;
	int N = 6000;
	Vector positionvector(3);
	SmoothParticle **particles = new SmoothParticle*[N];
	for(int i = 0; i < N; i++){
		float positionarray[] = {rand()%200000, rand()%200000, rand()%200000};
		positionvector.setvalue(positionarray);
		positionvector = positionvector*(0.00005);
		particles[i] = new SmoothParticle(i, m);
		particles[i]->setposition(positionvector);
	}

	float domainstartarray[] = {0.0, 0.0, 0.0};
	float domainendarray[] = {2.0, 2.0, 2.0};
	int cellperlength = 10;
	Vector domainstart(3);
	Vector domainend(3);
	domainstart.setvalue(domainstartarray);
	domainend.setvalue(domainendarray);
	LCA *lca = new LCA(cellperlength, domainstart, domainend);

	clock_t begin = clock();

	lca->insertparticle(N, particles);
	lca->calculatedensity(1.0);
	lca->calculateforce(1.0);

	clock_t end = clock();
	double elapsed_secs = (double) (end - begin) / CLOCKS_PER_SEC;
	std::cout << "elapsed_secs = " << elapsed_secs << std::endl;
	std::cout << "avg num of particle per cell = " << lca->getavgparticlepercell() << std::endl;
	std::cout << "max num of particle per cell = " << lca->getmaxparticlepercell() << std::endl;

	VelocityStoermerVerlet vsv;
	vsv.updatevelocity(N, particles, 5e-6);
	vsv.updateposition(N, particles, 1e-5);
	vsv.updatevelocity(N, particles, 5e-6);
	writevtkpointdata("linkedcellalgorithm.vtk", particles, N);
	delete lca;

	return 0;
}
