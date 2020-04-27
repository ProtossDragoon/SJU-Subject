#include"complex.h"

int main()
{

    Complex complex1(1,3);
    Complex complex2(2,5);

    // 이 함수들은 C-complex.cpp 에 구현되어 있습니다.
    // friend 로 선언한 이유는 연산을 조금 더 잘 보여주기 위함입니다.
    // 아래 함수들은 모든 연산의 결과를 출력합니다.

    PrintUnaryOperators(complex1);
    std::cout << endl;
    PrintUnaryOperators(complex2);
    std::cout << endl;
    PrintBinaryOperators(complex1, complex2);
    std::cout << endl;

    return 0;
}


