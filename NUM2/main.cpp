#include <iostream>
#include "simpleeq.h"
#include "matrix.h"
#include "equation.h"
using namespace std;

int main()
{
    int ileRownan = 3;
    Matrix m(3);
    m[1][1] =3;
    m[1][2] =3;
    m[1][3] =1;
    m[1][4] =12;

    m[2][1] =2;
    m[2][2] =5;
    m[2][3] =7;
    m[2][4] =33;

    m[3][1] =1;
    m[3][2] =2;
    m[3][3] =1;
    m[3][4] =8;

    m.Transform();
    m.Write();
}
