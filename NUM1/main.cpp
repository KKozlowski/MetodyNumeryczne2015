#include <iostream>
#include <cmath>
#include <list>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:/gnuplot/bin"

using namespace std;

double sinus(double x){
    return sin(x);
}

double power(double base, double exp){
    return pow(base, exp);
}

double wielomian(double a, double b, double c, double d, double x){
    return a*x*x*x -b*x*x +c*x -d;
}

bool foundMiejZerBi = false;
double miejZerBi=0;
double miejZerYBi;
template<class F>void bisekcja(double start, double end, F funk, double epsilon){
    if( (funk(start) >=0 && funk(end) < 0) || (funk(start)<0 && funk(end) >=0) ){
        double center = (start+end)/2;
        double centerValue = funk(center);
        if(abs(centerValue) < epsilon){
            //rozwiazania.push_back(center);
            //cout << center << endl;
            miejZerBi = center;
            foundMiejZerBi = true;
        } else {
            bisekcja(start, center, funk, epsilon);
            bisekcja(center, end, funk, epsilon);
        }
    }
}

bool foundMiejZerSiecz = false;
double miejZerSiecz=0;
double miejZerYSiecz;
template<class F> double siecznych(F funk, double a, double b, double eps){
    double x0;
    double x00;
    x0 = a - funk(a) * (a - b) / (funk(a) - funk(b));
    if (x0 != x0){cout << "blad sieczna pionowa, najblizsza wartosc " << x00 << endl; return 0;}
    if (fabs(funk(x0)) < eps){
        //cout << x0 << endl;
        //cout << funk(x0) << endl;
        foundMiejZerSiecz = true;
        return x0;
    }
    else{
        //cout << x0 << endl;
        //cout << funk(x0) << endl;
        return siecznych(funk, x0, a, eps);
    }
    x00=x0;
}

int main()
{
    Gnuplot::set_GNUPlotPath( GNUPLOT_PATH );

    cout << "Wybierz funkcje: \n1. Sinus\n2. Wykladnicza\n3. Wielomian\n> ";
    int wybor;
    double (*funk)(double);
    cin >> wybor;

    switch(wybor){
    case 1:
        funk=sinus;
        break;
    case 2:
        funk=[](double x) -> double {return power(2,x);};
        break;
    case 3:
        funk=[](double x) -> double {return wielomian(2,3,2,1,x);};
        break;
    default:
        return 0;
    }

    double start, end;
    double eps = 0.001;
    cout << "Podaj poczatek zakresu: ";
    cin >> start;
    cout << "Podaj koniec zakresu: ";
    cin >> end;



    cout << "METODA BISEKCJI:\n";
    bisekcja(start,end,funk,0.001);
    miejZerYBi=funk(miejZerBi);
    if(foundMiejZerBi)
        cout << "Znalezione miejsce zerowe: (" << miejZerBi << ", " << miejZerYBi << ")";
    else
        cout << "Nie znaleziono odpowiedniego miejsca zerowego";

    cout << endl << endl;

    cout << "METODA SIECZNYCH:\n";
    miejZerSiecz = siecznych(funk, start, end, 0.001);
    miejZerYSiecz=funk(miejZerSiecz);
    if(foundMiejZerBi)
        cout << "Znalezione miejsce zerowe: (" << miejZerSiecz << ", " << miejZerYSiecz << ")";
    else
        cout << "Nie znaleziono odpowiedniego miejsca zerowego";

    Gnuplot main_plot;

    main_plot.set_title( "Wykres" );
    main_plot.set_xlabel( "X" );
    main_plot.set_ylabel( "Y" );

    main_plot.set_style( "lines" );
    main_plot.set_grid();

    // zakres osi x
    main_plot.set_xrange( start , end ) ;

    int precyzja = 50;
    double skok = (end-start)/50;
    vector<double> x;
    vector<double> y;
    for(double d=start; d<=end;d+=skok){
        x.push_back(d);
        y.push_back(funk(d));
    }

    main_plot.plot_xy( x, y, "Wykres funkcji" );

    main_plot.set_style( "points" );
    main_plot.set_pointsize( 2.0 );


    vector<double> miejZerX;
    miejZerX.push_back(miejZerBi);
    miejZerX.push_back(miejZerSiecz);
    vector<double> miejZerY;
    miejZerY.push_back(miejZerYBi);
    miejZerY.push_back(miejZerYSiecz);
    cout << foundMiejZerBi <<  foundMiejZerSiecz;
    if(foundMiejZerBi && foundMiejZerSiecz)
        main_plot.plot_xy( miejZerX, miejZerY, "Znalezione miejsca zerowe" );

    getchar();
    getchar();

    return 0;
}

