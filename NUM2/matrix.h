#ifndef MATRIX_H
#define MATRIX_H

#include "simpleeq.h"
#include "equation.h"

class Matrix
{
public:
    Matrix(int rozmiar);
    SimpleEq & operator[](int pos) const {return *rownania[pos-1];}
    ~Matrix();
    void Write();
    void Transform();

    bool WarunekWierszy();
    bool WarunekKolumn();
    bool WarunekKwadratowy();

private:
    bool transformed = false;
    int size;
    std::vector<SimpleEq *> rownania;
    std::vector<Equation *> przeksztalcone;

};

#endif // MATRIX_H
