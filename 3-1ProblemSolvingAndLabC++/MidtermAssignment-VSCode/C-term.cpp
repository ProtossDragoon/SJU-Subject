#include"term.h"
#include<iostream>

// Term class
void Term::Show(bool for_debug, bool in_line) const
{
    if (for_debug == true)
    {
        std::cout << "variable : " << "x"      << std::endl;
        std::cout << "coef : " << Get_nCoef()  << std::endl;
        std::cout << "exp : "  << Get_nExp()   << std::endl;
    }
    else
    {
        if (m_nCoef > 0)
            std::cout << '+';
        std::cout << m_nCoef;

        if (m_nExp < 0)
            std::cout << "x^" << "(" << m_nExp << ")";
        else if (m_nExp == 0)
            std::cout;
        else
            std::cout << "x^" << m_nExp;
        
        if (in_line == false) std::cout << std::endl;    
    }
}

void Term::operator=(const Term& righthand)
{
    this->m_nCoef = righthand.m_nCoef;
    this->m_nExp = righthand.m_nExp;
}
Term &Term::operator++()
{
    ++(this->m_nCoef);
    return *this;
}
Term Term::operator++(int)
{
    Term temp(0,0);
    temp = *this;
    ++(this->m_nCoef);
    return temp;
}
Term &Term::operator--()
{
    --(this->m_nCoef);
    return *this;
}
Term Term::operator--(int)
{
    Term temp(0,0);
    temp = *this;
    --(this->m_nCoef);
    return temp;
}
Term Term::operator-() const
{
    Term answer(0,0);
    answer = *this;
    answer.m_nCoef *= (-1);
    return answer;
}
Term Term::operator+(const Term& righthand) const
{
    Term answer(0,0);
    answer = *this;
    answer.m_nCoef = this->m_nCoef + righthand.m_nCoef; 
    return answer;
}
Term Term::operator-(const Term& righthand) const
{
    Term answer(0, 0);
    answer = *this;
    answer.m_nCoef = this->m_nCoef - righthand.m_nCoef;
    return answer;
}


/********************************************/
/*              Polynomial class            */
/********************************************/


// Polynomial class
Polynomial::Polynomial()
{
    for(int i = 0; i < 100; i++)
    {
        m_arrTermValidity[i] = 0;
        m_arrTerm[i].Set_nExp(i);
        m_arrTerm[i].Set_nCoef(0);
    }
    m_nTermCnt = 0;
}

void Polynomial::Set_arrTerm(int coef, int exp)
{
    if ((exp > 100) || (exp < 0))
    {
        std::cout << "invalid exp value" << std::endl;
        std::cout << "should be 0 <= coef <= 100" << std::endl;
    }
    else
    {
        Term term(coef, exp);
        m_arrTerm[exp] = term;
        m_arrTermValidity[exp] = true;
    }

    m_nTermCnt++;
}
void Polynomial::Set_arrTermValidity(int index, bool setting)
{
    m_arrTermValidity[index] = setting;
}
void Polynomial::Set_nTermCnt(int number)
{
    m_nTermCnt = number;
}
void Polynomial::Set_nTermCnt(bool plus, int number)
{
    if (plus)
    {
        m_nTermCnt += number;
    }
    else
    {
        m_nTermCnt -= number;
    }
}


void Polynomial::Show()
{
    for (int i = 100-1; i >= 0; i--)
    {
        if (m_arrTermValidity[i] && (m_arrTerm[i].Get_nCoef() != 0))
        {
            m_arrTerm[i].Show(false, true);
        }
    }
    std::cout << std::endl;    
}

void Polynomial::operator=(const Polynomial& righthand)
{
    // copy m_arrTerm
    for (int i = 0; i <= 100; i++)
        this->m_arrTerm[i] = righthand.m_arrTerm[i];

    // copy m_arrTermValidity
    for (int i = 0; i <= 100; i++)
        this->m_arrTermValidity[i] = righthand.m_arrTermValidity[i];

    // copy m_nTermCnt
    this->m_nTermCnt = this->m_nTermCnt;
}
Polynomial Polynomial::operator-() const
{
    Polynomial answer;
    answer = *this;
    for (int i = 0; i < 100; i++)
    {
        if (m_arrTermValidity[i])
        {
            answer.m_arrTerm[i] = -(m_arrTerm[i]);
        }
    }
    return answer;
}
Polynomial Polynomial::operator+(const Polynomial& righthand) const
{
    Polynomial answer;
    answer = *this;
    for (int i = 0; i < 100; i++)
    {
        if (this->m_arrTermValidity[i] || righthand.m_arrTermValidity[i])
        {
            answer.m_arrTerm[i] = this->m_arrTerm[i] + righthand.m_arrTerm[i];
            answer.m_arrTermValidity[i] = true;
        }
    }
    return answer;
}
Polynomial Polynomial::operator-(const Polynomial& righthand) const
{
    Polynomial answer;
    answer = *this;
    for (int i = 0; i < 100; i++)
    {
        if (this->m_arrTermValidity[i] || righthand.m_arrTermValidity[i])
        {
            answer.m_arrTerm[i] = this->m_arrTerm[i] - righthand.m_arrTerm[i];
            answer.m_arrTermValidity[i] = true;
        }
    }
    return answer;
}