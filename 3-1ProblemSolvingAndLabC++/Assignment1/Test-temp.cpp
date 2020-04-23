#include "activation_function.h"
#include "perceptron.h"


int main() {

	Perceptron node(3, "sigmoid");

	// print 1
	node.ShowAllForDebug();

	cout << endl;
	cout << endl;


	node.WeightInitializer("constant");

	double input3[3] = { 1.5, 2.3, 6.9 };

	node.set_input(input3);
	node.Run();

	// print 2
	node.ShowAllForDebug();

	cout << endl;
	cout << endl;


	Perceptron node2(5, "sigmoid");
	double input5[5] = { 1.5, 2.3, 6.9, 1, 2 };
	node2.set_input(input5);
	node2.WeightInitializer("constant");
	node2.Run();
	// print 3
	node2.ShowAllForDebug();

	cout << endl;
	cout << endl;


	Perceptron node3(0, "sigmoid");
	double input1[1] = { 5 };
	node3.set_input(input1);
	node3.WeightInitializer("constant");
	node3.Run();
	// print 4
	node3.ShowAllForDebug();

}