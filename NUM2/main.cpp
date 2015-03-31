#include <iostream>
#include "simpleeq.h"
#include "matrix.h"
#include "equation.h"
#include "wektor.h"
#include <fstream>
using namespace std;


Matrix readfile(string filename){
    //string filename = "1";
    ifstream plik;
    string txt = ".txt";

    plik.open(filename.c_str()+txt);
    if(!plik.good()) return Matrix(0);

    int size;
    plik >> size;
    Matrix x(size);

    //wczytywanie macierzy
    for(int i=1; i<=size; i++){
        for (int j=1; j<=size+1; j++){
            plik  >> x[i][j];
        }
    }

    //wypisywanie macierzy
    /*
    for(int i=1; i<=size; i++){
        for (int j=1; j<=size+1; j++){
            cout << x[i][j] << " ";
        }
      cout << endl;
    }
    */

    return x;
}

int main()
{
    cout << "Podaj nazwe pliku: ";
    string filename;
    cin >> filename;
    int ileRownan = 3;
    Matrix m = readfile(filename);

    if(m.size == 0) {
        cout << "Blad wczytywania pliku" << endl;
        return 0;
    }

    m.Write();
    m.Transform();
    cout << endl;
    m.Write();
    if(m.WarunekKolumn() || m.WarunekWierszy() || m.WarunekKwadratowy())
        cout << "\nUklad spelnia warunek zbieznosci\n";
    else{
        cout << "\nUklad nie spelnia warunku zbieznosci\n";
        return 0;
    }


    cout << endl;

    cout << "Podaj dokladnosc: ";
    double eps;
    cin >> eps;

    Wektor wynik = m.licz(eps);
    cout<<"\nWYNIK:\n";
    wynik.wypisz();
}
