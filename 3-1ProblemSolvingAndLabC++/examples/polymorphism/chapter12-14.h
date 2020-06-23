#pragma once
#include<iostream>
using namespace std;

class Animal
{
private:

protected:
	int _age;
	int _weight;

public:
	Animal(int age, int weight) :_age(age), _weight(weight) {};
	void sleep();
	void eat();
	virtual void speak() = 0;
	void print();
};

class Dog : public Animal
{
private:

protected:
	string _breed;
	
public:
	Dog(int age, int weight, string breed) :Animal(age, weight), _breed(breed) {};
	void speak();
	void print();
};


class Bird : public Animal
{
private:

protected:
	
public:
	Bird(int age, int weight) :Animal(age, weight) {};
	void speak();
};

