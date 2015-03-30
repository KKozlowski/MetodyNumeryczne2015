#include "matrix.h"
#include "wektor.h"

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
    //TODO: Prawidlowe wybieranie rownan dla danych niewiadomych.
    if(!transformed){
        for(int i = 1; i<=size; i++){
            przeksztalcone.push_back(new Equation(operator [](i), i));
        }
        transformed = true;
    }
}

bool Matrix::WarunekWierszy()
{
    for(int i=0;i < size; i++){
        double tempSize = przeksztalcone[i]->AbsoluteSum();
        if (tempSize >= 1) return false;
    }

    return true;
}

bool Matrix::WarunekKolumn()
{
    return true;
}

bool Matrix::WarunekKwadratowy()
{
    return true;
}

Wektor Matrix::licz(double eps)
{
    Wektor w1(size);
    Wektor w2(size);

    int i=0;
    while(i<10){
        for(int i=1; i<=size; i++){
            w2.wypisz();
            w2[i]=przeksztalcone.at(i-1)->Calculate(w1);
        }
        Wektor test = w2-w1;
        cout << "norma: " << test.norma() << endl;
        if (test.norma() < eps ) break;
        w1 = w2;
        i++;
    }

    return w2;
}
