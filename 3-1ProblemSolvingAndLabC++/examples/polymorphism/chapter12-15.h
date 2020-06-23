#pragma once
#include<iostream>
using namespace std;

class Person
{
protected:
	string _name;
	int _age;
	bool _gender;

public:
	Person(string name, int age, bool gender) :
		_name(name), _age(age), _gender(gender) {};

	void print() const;
};

class Employee : public Person
{
protected:
	string _no;
	int _salary;
	string _department;

public:
	Employee(string name, int age, bool gender,
		string no, int salary, string department)
		: Person(name, age, gender), _no(no),
		_salary(salary), _department(department) {};
	
	void print() const;
};

class Manager : public Employee
{
protected:
	int _bonus;

public:
	Manager(string name, int age, bool gender,
		string no, int salary, string department,
		int bonus)
		: Employee(name, age, gender, no, salary, department),
		_bonus(bonus) {};

	void print() const;
};