#include"complex.h"

/* constructor */
// inline

/* destructor  */
// no overloading

/* operators   */
Complex Complex::operator+(const Complex &complex) const
{
    // this + complex
    Complex answer(0,0);
    answer.m_nImag = this->m_nImag + complex.m_nImag;
    answer.m_nReal = this->m_nReal + complex.m_nReal;
    return answer;
}

Complex Complex::operator-(const Complex &complex) const
{
    // this - complex
    Complex answer(0,0);
    answer.m_nImag = this->m_nImag - complex.m_nImag;
    answer.m_nReal = this->m_nReal - complex.m_nReal;    
    return answer;
}

void Complex::operator=(const Complex &complex)
{
    // this = complex
    this->m_nImag = complex.m_nImag;
    this->m_nReal = complex.m_nReal;
}

Complex Complex::operator-()
{
    // -this
    Complex answer(0,0);
    answer.m_nImag = -(this->m_nImag);
    answer.m_nReal = -(this->m_nReal);
    return answer;
}

Complex& Complex::operator++()
{
    // ++this
    ++(this->m_nImag);
    ++(this->m_nReal);
    return *this;
}

Complex Complex::operator++(int)
{
    // this++
    Complex answer(0,0);
    answer = *this;
    ++(this->m_nImag);
    ++(this->m_nReal);
    return answer;
}

Complex& Complex::operator--()
{
    // --this
    --(this->m_nImag);
    --(this->m_nReal);
    return *this;
}

    
Complex Complex::operator--(int)
{   
    // this--
    Complex answer(0,0);
    answer = *this;
    --(this->m_nImag);
    --(this->m_nReal);
    return answer;
}

/* method here */
void Complex::PrintNumber()
{
    cout << m_nReal;
    if (m_nImag < 0)
        cout << m_nImag << "i" << endl;
    else
        cout << "+" << m_nImag << "i" << endl;
}


/* friend here */
void PrintUnaryOperators(Complex complex)
{
    (-complex).PrintNumber();    
    (complex++).PrintNumber();
    (++complex).PrintNumber();
    (complex--).PrintNumber();
    (--complex).PrintNumber();
}

void PrintBinaryOperators(Complex complex1, Complex complex2)
{
    (complex1-complex2).PrintNumber(); // 1 - 2
    (complex2-complex1).PrintNumber(); // 2 - 1
    
    (complex1+complex2).PrintNumber(); // 1 + 2
    
    complex1 = complex2;
    complex1.PrintNumber(); // 대입 결과 확인
    complex2.PrintNumber(); // 대입 결과 확인
}