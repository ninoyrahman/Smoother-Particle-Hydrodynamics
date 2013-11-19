/*
 * WriteVTK.h
 *
 *  Created on: Nov 2, 2013
 *      Author: ninoy
 */

#ifndef WRITEVTK_H_
#define WRITEVTK_H_

#include <iostream>
#include <fstream>
#include <string>
#include "SmoothParticle.h"

void writevtkpointdata(char *filename, SmoothParticle *particles, int n){
	std::ofstream file;
	file.open(filename, std::ofstream::out);
	file << "# vtk DataFile Version 2.0\n";
	file << "written by Ninoy Rahman \n";
	file << "ASCII\n";
	file << "\n";

	file << "DATASET UNSTRUCTURED_GRID\n";
	file << "POINTS " << n << " float\n";
	file << "\n";

	for (int i = 0; i < n; i++)
		file << (particles[i].getposition()).getvalue(0) << " " << (particles[i].getposition()).getvalue(1) << " " << (particles[i].getposition()).getvalue(2) << "\n";

	file << "\n";
	file << "POINT_DATA " << n << "\n";
	/*file << "SCALARS Mass float\n";
	file << "LOOKUP_TABLE default\n";

	for (int i = 0; i < n; i++)
		file << (particles[i].getmass()) << " " << (particles[i].getmass()) << " " << (particles[i].getmass()) << "\n";

	file << "\n";*/
	file << "VECTORS Velocity float\n";

	for (int i = 0; i < n; i++)
		file << (particles[i].getvelocity()).getvalue(0) << " " << (particles[i].getvelocity()).getvalue(1) << " " << (particles[i].getvelocity()).getvalue(2) << "\n";

	file << "\n";
	file << "VECTORS Force float\n";

	for (int i = 0; i < n; i++)
		file << (particles[i].getforce()).getvalue(0) << " " << (particles[i].getforce()).getvalue(1) << " " << (particles[i].getforce()).getvalue(2) << "\n";

	file.close();
}

void writevtkpointdata(char *filename, SmoothParticle **particles, int n){
	std::ofstream file;
	file.open(filename, std::ofstream::out);
	file << "# vtk DataFile Version 2.0\n";
	file << "written by Ninoy Rahman \n";
	file << "ASCII\n";
	file << "\n";

	file << "DATASET UNSTRUCTURED_GRID\n";
	file << "POINTS " << n << " float\n";
	file << "\n";

	for (int i = 0; i < n; i++)
		file << (particles[i]->getposition()).getvalue(0) << " " << (particles[i]->getposition()).getvalue(1) << " " << (particles[i]->getposition()).getvalue(2) << "\n";

	file << "\n";
	file << "POINT_DATA " << n << "\n";
	/*file << "SCALARS Mass float\n";
	file << "LOOKUP_TABLE default\n";

	for (int i = 0; i < n; i++)
		file << (particles[i].getmass()) << " " << (particles[i].getmass()) << " " << (particles[i].getmass()) << "\n";

	file << "\n";*/
	file << "VECTORS Velocity float\n";

	for (int i = 0; i < n; i++)
		file << (particles[i]->getvelocity()).getvalue(0) << " " << (particles[i]->getvelocity()).getvalue(1) << " " << (particles[i]->getvelocity()).getvalue(2) << "\n";

	file << "\n";
	file << "VECTORS Force float\n";

	for (int i = 0; i < n; i++)
		file << (particles[i]->getforce()).getvalue(0) << " " << (particles[i]->getforce()).getvalue(1) << " " << (particles[i]->getforce()).getvalue(2) << "\n";

	file.close();
}



#endif /* WRITEVTK_H_ */
