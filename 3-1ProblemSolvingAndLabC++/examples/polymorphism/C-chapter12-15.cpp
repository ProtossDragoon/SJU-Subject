#include"chapter12-15.h"
using namespace std;

void Person::print() const
{
	cout << "이름	: " << _name << endl;
	cout << "나이	: " << _age << endl;
	cout << "성별	: " << _gender << endl;
}

void Employee::print() const
{
	cout << "이름	: " << _name << endl;
	cout << "나이	: " << _age << endl;
	cout << "성별	: " << _gender << endl;
	cout << "사번	: " << _salary << endl;
	cout << "급여	: " << _gender << endl;
	cout << "부서	: " << _department << endl;
}

void Manager::print() const
{
	cout << "이름	: " << _name << endl;
	cout << "나이	: " << _age << endl;
	cout << "성별	: " << _gender << endl;
	cout << "사번	: " << _salary << endl;
	cout << "급여	: " << _gender << endl;
	cout << "부서	: " << _department << endl;
	cout << "보너스	: " << _bonus << endl;
}


