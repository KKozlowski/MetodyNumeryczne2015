#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <vector>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:/gnuplot/bin"

using namespace std;

double start, stop;
double h;
double (*funk)(double);

double simpson(double x1, double x2){ //Nie dziala
    double result = (1/3)*h*(funk(x1)+4*funk((x1+x2)/2)+funk(x2));
    cout << "Simpson " << result << endl;
    return result;
}

double newton(){

    double integral = 0;
    double d =start;
    double buf = start;
    while(d<stop){
        double buf = d;
        d+=h;
        if(d>stop) break;
        integral+=simpson(buf,d);
    }

    integral+=simpson(buf,stop);
    return integral;
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




    cout << "Podaj poczatek i koniec przedzialu: ";
    cin >> start >> stop;

    Gnuplot main_plot;

    main_plot.set_title( "Wykres" );
    main_plot.set_xlabel( "X" );
    main_plot.set_ylabel( "Y" );


    main_plot.set_grid();
    main_plot.set_xrange( start , stop ) ;
    main_plot.set_yrange(-2,2);
    main_plot.set_style( "lines" );
    int precyzja = 10000;
    double skok = (stop-start)/precyzja;
    vector<double> x;
    vector<double> y;
    for(double d=start; d<=stop;d+=skok){
        x.push_back(d);
        y.push_back(funk(d));
    }

    main_plot.plot_xy( x, y, "Wykres funkcji." );


    cout << "Podaj dokladnosc calkowania: ";
    cin >> h;

    cout << newton() << endl;


    getchar();
    getchar();
    return 0;
}

