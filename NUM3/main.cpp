#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <vector>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:/gnuplot/bin"

using namespace std;

vector<double> wezly;
vector<double> wartosci;
vector<double> wspol;
bool wartosciZPliku = false;

vector<double> czytaj(string filename){
    ifstream plik;
    string txt = ".txt";

    plik.open(filename.c_str()+txt);
    if(!plik.good()) return vector<double>();

    int size;
    plik >> size;
    vector<double> x;

    //wczytywanie znaków
    for(int i=0; i<size; i++){
        double d;
        plik >> d;
        x.push_back(d);
    }

    return x;
}

vector<double> obliczWezly(double (*funk)(double), vector<double> w){
    vector<double> result;
    for(int i=0; i<w.size(); i++){
        result.push_back(funk(w[i]));
    }

    return result;
}

double iloraz(int i, int k){
    if(k == 0)
        return (wartosci[i]);
    else
        return (iloraz(i+1,k-1) - iloraz(i,k-1))/(wezly[i+k]-wezly[i]);
}


void obliczWsp(){
    wspol.clear();
    for(int i=0; i<wartosci.size(); i++){
        wspol.push_back( iloraz(0,i));
    }
}

double fi(double x, int lvl){
    if (lvl == 0) return 1;
    return fi(x,lvl-1)*(x-wezly[lvl-1]);
}

void wypiszWektor(vector<double> w){
    for(int i=0; i< w.size(); i++){
        cout << w[i] << " ";
    }

    cout << endl;
}

void wypiszWektor(vector<double> w, string opis){
    cout << "\n" << opis << ": ";
    wypiszWektor(w);
}

/*double iloraz(int x1, int x2){
    if (x1 == x2) return wartosci[x1];

    double topOne = iloraz(x1+1,x2);
    double topTwo = iloraz(x1,x2-1);
    double mianownik = wezly[x2] - wezly[x1];
    return (topOne-topTwo)/mianownik;
}*/

double interpol(double x){
    double y = 0;
    for(int i=0; i<wezly.size(); i++){
        y+=wspol[i]*fi(x,i);
    }
    return y;
}

double sinus(double x){
    return sin(x);
}

double power(double base, double exp){
    return pow(base, exp);
}

double horner(double wsp[],int st, double x)
{
  if(st==0){
    return wsp[0];}
  return x*horner(wsp,st-1,x)+wsp[st];
}

double wielomianprosty(double a, double b, double c, double d, double x){
    return a*x*x*x -b*x*x +c*x -d;
}

double *wspolczynniki;
int stopien;

int main()
{
    Gnuplot::set_GNUPlotPath( GNUPLOT_PATH );
    string nazwaPliku;


    do{
        cout << "Podaj nazwe pliku z lista wezlow: ";
        cin >> nazwaPliku;
        wezly = czytaj(nazwaPliku);
        wypiszWektor(wezly, "Wezly");
    }while(wezly.size()==0);

    cout << "Podaj nazwe pliku z lista wartosci \n(wpisz '0' aby wybrac gotowa funkcje): ";
    cin >> nazwaPliku;
    if (nazwaPliku!="0"){
        wartosci = czytaj(nazwaPliku);
        if (wartosci.size() != wezly.size())
            cout << "Niezgodna liczba argumentow i wartosci.";
        else
            wartosciZPliku = true;
    }

    cout << endl;

    double (*funk)(double);
    if(!wartosciZPliku){
        cout << "Wybierz funkcje: \n1. Sinus\n2. Wykladnicza\n3. Wielomian \n4. Wielomian przykladowy \n> ";
        int wybor;

        cin >> wybor;

        switch(wybor){
        case 1:
            funk=sinus;
            break;
        case 2:
            funk=[](double x) -> double {return power(2,x);};
            break;
        case 3:
            cout<<"Podaj stopien wielomianu: ";
            cin>>stopien;
            wspolczynniki = new double [stopien+1];
            //wczytanie wspolczynnikow
            for(int i=0;i<=stopien;i++)
            {
              cout<<"Podaj wspolczynnik stojacy przy potedze "<<stopien-i<<": ";
              cin>>wspolczynniki[i];
            }
            funk=[](double x) -> double {return horner(wspolczynniki,stopien,x);};
            break;
        case 4:
            funk=[](double x) -> double {return wielomianprosty(2,3,2,1.05,x);};
            break;
        default:
            return 0;
        }

        wartosci = obliczWezly(funk, wezly);
    }
    wypiszWektor(wartosci, "Wartosci funkcji w wezlach");
    obliczWsp();
    cout << "Liczba wspol: " << wspol.size() << endl;
    wypiszWektor(wspol, "Wspolczynniki a");

    Gnuplot main_plot;

    main_plot.set_title( "Wykres" );
    main_plot.set_xlabel( "X" );
    main_plot.set_ylabel( "Y" );


    main_plot.set_grid();

    double start = -5;
    double end = 5;
    main_plot.set_style( "points" );
    main_plot.set_pointsize( 2.0 );
    main_plot.set_xrange( start , end ) ;
    main_plot.set_yrange(-2,2);

    {
        main_plot.plot_xy( wezly, wartosci, "Wezly." );
    }
    main_plot.set_style( "lines" );
    if(!wartosciZPliku)
    {
        int precyzja = 10000;
        double skok = (end-start)/precyzja;
        vector<double> x;
        vector<double> y;
        for(double d=start; d<=end;d+=skok){
            x.push_back(d);
            y.push_back(funk(d));
        }

        main_plot.plot_xy( x, y, "Wykres funkcji." );
    }
    {
        int precyzja = 10000;
        double skok = (end-start)/precyzja;
        vector<double> x;
        vector<double> y;
        for(double d=start; d<=end;d+=skok){
            x.push_back(d);
           // cout << interpol(d) << endl;
            y.push_back(interpol(d));
        }

        main_plot.plot_xy( x, y, "Wykres interpolacyjny." );
    }


    getchar();
    getchar();
    return 0;
}

