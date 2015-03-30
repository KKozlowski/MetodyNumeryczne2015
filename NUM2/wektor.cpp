#include "wektor.h"
#include <iostream>
#include <cmath>

using namespace std;

Wektor::Wektor(int rozm)
{
    for (unsigned int i=0; i<=rozm; i++)
        push_back(0);
}

Wektor::~Wektor()
{

}

void Wektor::wypisz()
{
    for (unsigned int i=1; i<size(); i++){
        cout << "x" << i << " = " << at(i) << " ";
    }
    cout << endl;
}

double Wektor::norma()
{
    double max=0;
    for(int i=1; i<size();i++){
        if(abs(at(i)) > max) max = abs(at(i));
    }

    return max;
}

