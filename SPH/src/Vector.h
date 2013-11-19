/*
 * Vector.h
 *
 *  Created on: Nov 1, 2013
 *      Author: ninoy
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include "math.h"

class Vector{
public:
	Vector(){
		this->v = nullptr;
		n = 0;
	}
	Vector(int size){
		n = size;
		v = new float[n];
		for (int i = 0; i < n; i++)
			v[i] = 0.0;
	}
	Vector(const Vector &a){
		n = a.n;
		v = new float[n];
		if(a.v != nullptr){
			for (int i = 0; i < n; i++)
				v[i] = a.v[i];
		}
	}
	~Vector(){
		delete[] v;
	}
	void setvalue(float value, int i){
			v[i] = value;
	}
	void setvalue(float *value){
		for (int i = 0; i < n; i++)
			v[i] = value[i];
	}
	float getvalue(int i) const{
		return v[i];
	}
	void print(){
		for (int i = 0; i < n; i++){
			std::cout << v[i] << ", ";
		}
	}
	float length(){
		float length = 0.0;
		for (int i = 0; i < n; i++)
			length+= v[i]*v[i];
		return sqrt(length);
	}
	float lengthsq(){
		float length = 0.0;
		for (int i = 0; i < n; i++)
			length+= v[i]*v[i];
		return length;
	}

	Vector& operator=(Vector a){
		if(this->v == nullptr){
			this->n = a.n;
			v = new float[n];
		}
		for (int i = 0; i < n; i++)
			this->v[i] = a.v[i];
		return *this;
	}
	Vector& operator+=(Vector a){
		for (int i = 0; i < n; i++){
			this->v[i] = this->v[i] + a.v[i];
		}
		return *this;
	}
	Vector& operator-=(Vector a){
		for (int i = 0; i < n; i++){
			this->v[i] = this->v[i] - a.v[i];
		}
		return *this;
	}
	Vector& operator+(Vector a){
		Vector *result = new Vector(n);
		for (int i = 0; i < n; i++){
			result->v[i] = this->v[i] + a.v[i];
		}
		return *result;
	}
	Vector& operator-(Vector a){
		Vector *result = new Vector(n);
		for (int i = 0; i < n; i++){
			result->v[i] = this->v[i] - a.v[i];
		}
		return *result;
	}
	Vector& operator*(float a){
		Vector *result = new Vector(n);
		for (int i = 0; i < n; i++){
			result->v[i] = a * this->v[i] ;
		}
		return *result;
	}
	void zeros(){
		for (int i = 0; i < n; i++)
			this->v[i] = 0.0;
	}
	void ones(){
		for (int i = 0; i < n; i++)
			this->v[i] = 1.0;
	}

private:
	int n;
	float *v;
};


#endif /* VECTOR_H_ */
