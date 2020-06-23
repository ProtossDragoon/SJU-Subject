#pragma once
#include<iostream>
using namespace std;

class Person
{
protected:
	string _name;
	string _address;
	string _phone;

public:
	Person();
	Person(string name, string address, string phone)
		: _name(name), _address(address), _phone(phone) {};

	void print();

};

class Customer : Person
{
protected:
	string _id;
	int _point;

public:
	Customer();
	Customer(string name, string address, string phone, string id, int point)
		: Person(name, address, phone), _id(id), _point(point) {};

	void print();
};