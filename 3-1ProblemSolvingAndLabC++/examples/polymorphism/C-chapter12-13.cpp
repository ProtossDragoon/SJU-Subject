#include<iostream>
#include"chapter12-13.h"

void Person::print()
{
	cout <<"이름		: " << _name << endl;
	cout <<"주소		: " << _address << endl;
	cout <<"휴대폰번호	: " << _phone<< endl;
}

void Customer::print()
{
	cout << "이름		: " << _name << endl;
	cout << "주소		: " << _address << endl;
	cout << "휴대폰번호	: " << _phone << endl;
	cout << "아이디		: " << _id << endl;
	cout << "포인트접수	: " << _point << endl;
}