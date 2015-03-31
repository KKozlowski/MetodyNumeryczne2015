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
    string filename;
    cin >> filename;
    int ileRownan = 3;
    Matrix m = readfile(filename);
    /*
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
    */
    /*
    m[1][1] =2;
    m[1][2] =3;
    m[1][3] =-1;
    m[1][4] =1;

    m[2][1] =4;
    m[2][2] =-1;
    m[2][3] =1;
    m[2][4] =2;

    m[3][1] =-1;
    m[3][2] =2;
    m[3][3] =-5;
    m[3][4] =3;
    */

    m.Transform();
    m.Write();
    cout << endl;


    Wektor wynik = m.licz(0.001);
    cout<<"\nWYNIK:\n";
    wynik.wypisz();
}
