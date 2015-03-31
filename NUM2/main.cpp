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
    if(!plik.good()){cout << "blad" << endl; return false;}

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

    m.Write();
    cout << endl;
    m.Transform();
    m.Write();
    cout << endl;


    Wektor wynik = m.licz(0.001);
    cout<<"\nWYNIK:\n";
    wynik.wypisz();
}
