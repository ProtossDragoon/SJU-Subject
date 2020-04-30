#pragma once

class Term
{
    private:
    
    int m_nCoef;
    int m_nExp;

    // methods
    void _Debug() const;


    public:

    // constructor
    Term(int coef = 0, int exp = 0):m_nCoef(coef), m_nExp(exp) {};
 
    // getter
    int Get_nCoef() const { return m_nCoef; };
    int Get_nExp()  const { return m_nExp; };

    // setter
    void Set_nCoef(int coef)    { m_nCoef = coef; };
    void Set_nExp(int exp)      { m_nExp = exp; };

    // methods
    void Show(bool for_debug = false, bool in_line = false) const;

    // operators
    void operator=(const Term&);

    Term &operator++();
    Term operator++(int);
    Term &operator--();
    Term operator--(int);
    Term operator-()            const;
    Term operator+(const Term&) const;    
    Term operator-(const Term&) const;
};


class Polynomial
{
    private:

    Term m_arrTerm[100];
    bool m_arrTermValidity[100];
    int m_nTermCnt;  


    public:

    // constructor
    Polynomial();

    // getter
    Term* Get_arrTerm() { return m_arrTerm; }
    bool* Get_arrTermValidigy() { return m_arrTermValidity; }
    int Get_nTermCnt() const { return m_nTermCnt; };

    // setter
    void Set_arrTerm(int coef, int exp);
    void Set_arrTermValidity(int index, bool setting);
    void Set_nTermCnt(int number);
    void Set_nTermCnt(bool plus, int number);

    // methods
    void Show();

    // operations
    void operator=(const Polynomial&);

    Polynomial operator-() const;
    Polynomial operator+(const Polynomial&) const;
    Polynomial operator-(const Polynomial&) const;
};
