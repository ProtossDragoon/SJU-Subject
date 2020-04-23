#pragma once
#include "activation_function.h"
#include <iostream>
using namespace std;

class Perceptron
{
private :
	int input_size_;
	bool weight_initialized_;
	bool inputdata_exist_;
	double* input_;
	double* weights_;
	double output_;
	double (Activations::*activation_function_)(double);
	static Activations activations_;

	//setter
	void set_input_size(int input_size) { input_size_ = input_size; };
	void set_output(double output) { output_ = output; };

public :
	
	// constructor & destructor
	Perceptron(int input_size, string activation_function);
	~Perceptron();

	// getter
	int get_input_size() const { return input_size_; };
	bool IsWeightInitialized() const { return weight_initialized_; };
	bool IsInputdataExist() const { return inputdata_exist_; };
	double* get_input() const { return input_; };
	double* get_weights() const { return weights_; };
	double get_output() const { return output_; };
	double (Activations::*get_activation_function())(double) { return activation_function_; };

	// setter
	void set_input(double* input) { input_ = input; inputdata_exist_ = true; };
	void set_activation_function(string activation_function);

	// methods
	void ShowAllForDebug() const;
	void WeightInitializer(string weight_initialize_function);
	void Run();
};