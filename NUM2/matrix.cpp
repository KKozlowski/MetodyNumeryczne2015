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


        /*for(int i = 1; i<=size; i++){
            przeksztalcone.push_back(new Equation(operator [](i), i));
        }*/

        for(int i=0; i<size; i++){
            double maxVal = 0;
            int valuer = 0;
            for(int k=0; k<rownania.size(); k++){
                double d = rownania[k]->wsp.at(i);
                if (abs(d) > abs(maxVal)){
                    maxVal = d;
                    valuer = k;
                }
            }

            if(maxVal == 0) cout << "Iteracja rozbiezna";
            else{
                SimpleEq *eq = rownania.at(valuer);
                SimpleEq req(size);
                for(int i=1; i<=size+1; i++){
                    req[i]=eq->operator [](i);
                }
                Equation *neq = new Equation(req, i+1);
                przeksztalcone.push_back(neq);
                rownania.erase(rownania.begin() + valuer);
            }
        }

        transformed = true;

    }
}

bool Matrix::WarunekWierszy()
{
    for(int i=0;i < size; i++){
        double tempSize = przeksztalcone[i]->AbsoluteSum();
        //cout << "S" << tempSize << endl;
        if (tempSize >= 1) return false;
    }

    return true;
}

bool Matrix::WarunekKolumn()
{
    for (int i=1; i<=size; i++){
        double sum = 0;
        for(int k=0; k<size; k++){
            double skladnik = abs(przeksztalcone[k]->operator[](i));
            sum+=skladnik;

        }
        //cout << "SK" << sum << endl;
        if (sum >= 1) return false;
    }

    return true;
}

bool Matrix::WarunekKwadratowy()
{
    double sum = 0;
    for (int i=1; i<=size; i++){
        for(int k=0; k<size; k++){
            double skladnik = abs(przeksztalcone[k]->operator[](i));
            sum+=skladnik*skladnik;
            //cout << "skladnik " << skladnik << endl;
        }
    }

    sum = sqrt(sum);

    if(sum <1)
        return true;
    else
        return false;
}

Wektor Matrix::licz(double eps)
{
    Wektor w1(size);
    Wektor w2(size);
    while(true){
        for(int i=1; i<=size; i++){
            w2.wypisz();
            w2[i]=przeksztalcone.at(i-1)->Calculate(w1);
        }
        Wektor test = w2-w1;
        cout << "norma: " << test.norma() << endl << endl;
        if (test.norma() < eps ) break;
        w1 = w2;
    }

    return w2;
}

double **Matrix::toTable()
{
    double **tab = new double*[size];
    for(int i = 0; i<size; i++){
        tab[i] = new double[size];
        for(int k=0; i< size; i++){
            tab[i][k] = przeksztalcone[i]->operator[](k);
        }
    }

    return tab;
}
