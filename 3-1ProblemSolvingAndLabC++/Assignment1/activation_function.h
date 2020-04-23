#pragma once
#include <iostream>
using namespace std;

class Activations
{
private :
	double (Activations::*sigmoid_)(double);

	// setter
	void _set_sigmoid() { sigmoid_ = &Activations::_Sigmoid; };

	// methods
	double _Sigmoid(double x) { return 1 / (1 + exp(-x)); };

public :
	// constructor
	Activations();

	// getter
	double (Activations::*get_sigmoid())(double) { return sigmoid_; } // sigmoid 함수를의 주소를 반환합니다.


};