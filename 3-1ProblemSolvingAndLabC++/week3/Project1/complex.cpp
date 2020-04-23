#include "complex.h"
#include <iostream>

// consturctor
Complex::Complex() {

	m_nReal = -1;
	m_nImaginary = 0;
}

// setter
void Complex :: setReal(int new_r) {
	
	m_nReal = new_r;
}

void Complex :: setImaginary(int new_i) {

	m_nImaginary = new_i;
}

// getter
int Complex :: getReal() {

	return m_nReal;
}

int Complex :: getImaginary() {
	
	return m_nImaginary;
}

// submethod
void Complex :: show() {

	std::cout << "(" << m_nReal << "+" << m_nImaginary << "i)" << std::endl;
}