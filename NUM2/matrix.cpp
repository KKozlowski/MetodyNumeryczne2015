#include "matrix.h"

Matrix::Matrix(int rozmiar)
{
    for(int i=0;i<rozmiar;i++)
        rownania.push_back(new SimpleEq(rozmiar));

    size = rozmiar;
}

Matrix::~Matrix()
{

}

void Matrix::Write()
{
    if(!transformed)
        for(SimpleEq *se : rownania)
            se->Write();
    else
        for(Equation *se : przeksztalcone)
            se->Write();
}

void Matrix::Transform()
{
    if(!transformed){
        for(int i = 1; i<=size; i++){
            przeksztalcone.push_back(new Equation(operator [](i), i));
        }
        transformed = true;
    }
}

