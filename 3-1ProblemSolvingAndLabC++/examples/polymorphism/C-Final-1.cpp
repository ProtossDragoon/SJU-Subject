#include "C-Final-1.h"
#include<iostream>
using namespace std;

Square::Square(int cx, int cy, int l1, int l2, int l3, int l4):Figure(cx, cy)
{
	_l1 = l1;
	_l2 = l2;
	_l3 = l3;
	_l4 = l4;
	_centerx = cx;
	_centery = cy;
}

void Square::erase()
{
	cout << "Square 삭제함" << endl;
}

void Square::draw()
{
	cout << "Square 그림" <<  endl;
	cout << " " << _centerx << " " << _centery << "에 그림" << endl;
	cout << "Square 그리기 완료" << endl;
}

void Square::center()
{
	erase();
	draw();
}




Rectangle::Rectangle(int cx, int cy, int l1, int l2): Square(cx, cy, l1, l2, l1, l2)
{	
	_width = l1;
	_height = l2;
}

void Rectangle::erase()
{
	cout << "Rectangle 삭제함" << endl;
}

void Rectangle::draw()
{
	cout << "Rectangle 그림" << endl;
	cout << " " << _centerx << " " << _centery << "에 그림" << _width << " " << _height << "크기" << endl;
	cout << "Rectangle 그리기 완료" << endl;
}

void Rectangle::center()
{
	erase();
	draw();
}


Triangle::Triangle(int cx, int cy, int l1, int l2, int l3):Figure(cx, cy)
{
	_l1 = l1;
	_l2 = l2;
	_l3 = l3;
}

void Triangle::erase()
{
	cout << "Triangle 삭제함" << endl;
}

void Triangle::draw()
{
	cout << "Triangle 그림" << endl;
	cout << " " << _centerx << " " << _centery << "에 그림" << endl;
	cout << "Triangle 그리기 완료" << endl;
}

void Triangle::center()
{
	erase();
	draw();
}



Circle::Circle(int cx, int cy, int r):Figure(cx, cy)
{
	_r = r;
}

void Circle::erase()
{
	cout << "Circle 삭제함" << endl;
}

void Circle::draw()
{
	cout << "Circle 그림" << endl;
	cout << " " << _centerx << " " << _centery << "에 그림" << _r << "크기" << endl;
	cout << "Circle 그리기 완료" << endl;
}

void Circle::center()
{
	erase();
	draw();
}


