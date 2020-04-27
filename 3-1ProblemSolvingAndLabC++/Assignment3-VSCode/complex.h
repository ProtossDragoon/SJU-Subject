#pragma once
#include<iostream>
using namespace std;

class Complex
{
    private:
    int m_nReal;
    int m_nImag;

    public:
    /* constructor */
    Complex(int real, int imag) { m_nReal = real; m_nImag = imag; };

    /* destructor  */

    /* operators   */
    Complex operator+(const Complex&) const;
    Complex operator-(const Complex&) const;
    void operator=(const Complex&);
    Complex operator-();
    Complex& operator++();       // pre
    Complex operator++(int);    // post
    Complex& operator--();      // pre
    Complex operator--(int);   // post

    /* setter here */
    void Set_nReal(int n) { m_nReal = n; };
    void Set_nImag(int n) { m_nImag = n; };

    /* getter here */
    int Get_nReal() const { return m_nReal; };
    int Get_nImag() const { return m_nImag; };

    /* method here */
    void PrintNumber();
    
    /* friend here */
    friend void PrintUnaryOperators(Complex);
    friend void PrintBinaryOperators(Complex, Complex);
};
