#include"term.h"
#include<iostream>

int main ()
{
    Polynomial fx, gx, kx;
    fx.Set_arrTerm(6, 2);
    fx.Set_arrTerm(5, 1);
    fx.Set_arrTerm(4, 0);
    fx.Show();

    gx.Set_arrTerm(13, 4);
    gx.Set_arrTerm(12, 3);
    gx.Set_arrTerm(5, 2);
    gx.Set_arrTerm(5, 1);    
    gx.Set_arrTerm(5, 0);
    gx.Show();

    (fx + gx).Show();
    kx = (fx + gx);
    kx.Show();
    (fx - gx).Show();
    kx = (fx - gx);
    kx.Show();
    (-kx).Show();


    /* member function test */
    // getter
    Term *term_tester;
    bool *bool_tester;

    term_tester = kx.Get_arrTerm();
    bool_tester = kx.Get_arrTermValidigy();
    for (int i = 0; i < 100; i++)
    {
        std::cout << bool_tester[i] << " : ";
        term_tester[i].Show();
    }


    // setter
    kx.Set_arrTermValidity(3, 0);
    kx.Set_nTermCnt(false, -1);
    for (int i = 0; i < 100; i++)
    {
        std::cout << bool_tester[i] << " : ";
        term_tester[i].Show();
    }
    kx.Show();
}