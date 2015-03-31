#include "equation.h"


Equation::~Equation()
{

}

void Equation::Write()
{
    cout << "x" << main << " = ";
    for(int i=1; i < wsp.size(); i++){
        if (i!= main)
            cout << operator [](i) << "*x"<< i << " + ";
    }

    cout << free << endl;

    //vector<double> v {0,0,0,0};
    //cout << Calculate(v) << endl;
}

double Equation::Calculate(Wektor vec)
{
    double wynik;
    for(int i = 1; i <= GetLevel(); i++){
        wynik+= operator [](i) * vec[i];
    }
    wynik+=free;
    return wynik;
}

double Equation::AbsoluteSum()
{
    double suma;
    for(int i=1; i<=GetLevel(); i++){
        suma += abs(operator [](i));
    }
    return suma;
}

