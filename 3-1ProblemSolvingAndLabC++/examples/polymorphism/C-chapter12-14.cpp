#include"chapter12-14.h"

void Animal::print()
{
	cout << "나이	: " << _age << endl;
	cout << "몸무게	: " << _weight << endl;
}

void Animal::sleep()
{
	cout << "자다" << endl;
}

void Animal::eat()
{
	cout << "먹다" << endl;
}

void Dog::speak()
{
	cout << "그르르르르르... 그월! 웕 월!! 월월!!!" << endl;
}

void Dog::print()
{
	cout << "나이	: " << _age << endl;
	cout << "몸무게	: " << _weight << endl;
	cout << "품종	: " << _breed << endl;
}

void Bird::speak()
{
	cout << "짹짹" << endl;
}
