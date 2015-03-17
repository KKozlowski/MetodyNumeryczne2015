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

double horner(double wsp[],int st, double x)
{
  if(st==0){
    return wsp[0];}
  return x*horner(wsp,st-1,x)+wsp[st];
}

double wielomianprosty(double a, double b, double c, double d, double x){
    return a*x*x*x -b*x*x +c*x -d;
}

bool foundMiejZerBi = false;
double miejZerBi=0;
double miejZerYBi=99999999;
template<class F>void bisekcja(double start, double end, F funk, double epsilon){
    if( (funk(start) >=0 && funk(end) < 0) || (funk(start)<0 && funk(end) >=0) ){
        double center = (start+end)/2;
        double centerValue = funk(center);
        if(abs(centerValue) < epsilon){
            miejZerBi = center;
            foundMiejZerBi = true;
        } else {
            bisekcja(start, center, funk, epsilon);
            bisekcja(center, end, funk, epsilon);
        }
    }
}

double najdokladniejszyWynik = 99;
template<class F>void bisekcjaIt(double start, double end, F funk, int it){
    //cout << it << endl;
    if( (funk(start) >=0 && funk(end) < 0) || (funk(start)<0 && funk(end) >=0) ){
        double center = (start+end)/2;
        double centerValue = funk(center);
        if(abs(centerValue) < abs(miejZerYBi)){
            //cout << "Przypisywanie" << endl;
            miejZerBi = center;
            miejZerYBi = centerValue;
            foundMiejZerBi = true;
        }
        if(it > 1 ){
            //cout << "Nastepne wywolywanie" << endl;
            bisekcjaIt(start, center, funk, --it);
            bisekcjaIt(center, end, funk, --it);
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
        foundMiejZerSiecz = true;
        return x0;
    }
    else{
        return siecznych(funk, x0, a, eps);
    }
    x00=x0;
}

template<class F> double siecznychIt(F funk, double a, double b, double it){
    double x0;
    //double x00;
    x0 = a - funk(a) * (a - b) / (funk(a) - funk(b));
    if (x0 != x0){cout << "blad sieczna pionowa, najblizsza wartosc " << miejZerSiecz << endl; return miejZerSiecz;}
    if(abs(funk(x0)) <abs( miejZerYSiecz )) miejZerSiecz = x0;
    foundMiejZerSiecz = true;
    if (it <= 1 || funk(x0) == 0){
        return x0;
    }
    else{
        return siecznychIt(funk, x0, a, --it);
    }
    //x00=x0;
}

double *wspolczynniki;
int stopien;

int main()
{
    Gnuplot::set_GNUPlotPath( GNUPLOT_PATH );

    cout << "Wybierz funkcje: \n1. Sinus\n2. Wykladnicza\n3. Wielomian \n4. Wielomian przykladowy \n> ";
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

    Gnuplot main_plot;

    main_plot.set_title( "Wykres" );
    main_plot.set_xlabel( "X" );
    main_plot.set_ylabel( "Y" );

    main_plot.set_style( "lines" );
    main_plot.set_grid();

    {
        double start = -5;
        double end = 5;
        main_plot.set_xrange( start , end ) ;
        main_plot.set_yrange(-2,2);
        int precyzja = 50;
        double skok = (end-start)/50;
        vector<double> x;
        vector<double> y;
        for(double d=start; d<=end;d+=skok){
            x.push_back(d);
            y.push_back(funk(d));
        }

        main_plot.plot_xy( x, y, "Wykres pogladowy." );
    }

    double start, end;
    double eps = 0.001;
    cout << "Podaj poczatek zakresu: ";
    cin >> start;
    cout << "Podaj koniec zakresu: ";
    cin >> end;

    bool czyEpsilon;

    cout << "Wybierz warunek stopu: \n1. Epsilon \n2. Liczba iteracji \n> ";
    cin >> wybor;

    switch(wybor){
    case 1:
        czyEpsilon = true;
        break;
    case 2:
        czyEpsilon = false;
        break;
    default:
        return 0;
    }

    while(eps>=0){
        if(czyEpsilon)
            cout << "\n\n\nPodaj wymagana dokladnosc (ujemna zakonczy program): ";
        else
            cout << "\n\n\nPodaj wymagana liczbe iteracji (ujemna zakonczy program): ";
        cin >> eps;
        if(eps<0) break;

        cout << "METODA BISEKCJI:\n";
        czyEpsilon ? bisekcja(start,end,funk,eps) : bisekcjaIt(start,end,funk,(int)eps);
        miejZerYBi=funk(miejZerBi);
        if(foundMiejZerBi)
            cout << "Znalezione miejsce zerowe: (" << miejZerBi << ", " << miejZerYBi << ")";
        else
            cout << "Nie znaleziono odpowiedniego miejsca zerowego";

        cout << endl << endl;

        cout << "METODA SIECZNYCH:\n";
        miejZerSiecz = czyEpsilon ? siecznych(funk, start, end, eps) : siecznychIt(funk, start, end, eps);
        miejZerYSiecz=funk(miejZerSiecz);
        if(foundMiejZerBi)
            cout << "Znalezione miejsce zerowe: (" << miejZerSiecz << ", " << miejZerYSiecz << ")";
        else
            cout << "Nie znaleziono odpowiedniego miejsca zerowego";

        main_plot.reset_plot();

        // zakres osi x
        main_plot.set_xrange( start , end ) ;

        int precyzja = 50;
        double skok = (end-start)/precyzja;
        vector<double> x;
        vector<double> y;
        for(double d=start; d<=end+1;d+=skok){
            x.push_back(d);
            y.push_back(funk(d));
        }
        main_plot.set_style( "lines" );
        main_plot.plot_xy( x, y, "Wykres funkcji" );

        main_plot.set_style( "points" );
        main_plot.set_pointsize( 2.0 );

        vector<double> miejZerXBiVec;
        miejZerXBiVec.push_back(miejZerBi);
        vector<double> miejZerXSieczVec;
        miejZerXSieczVec.push_back(miejZerSiecz);
        vector<double> miejZerYBiVec;
        miejZerYBiVec.push_back(miejZerYBi);
        vector<double> miejZerYSieczVec;
        miejZerYSieczVec.push_back(miejZerYSiecz);
        //cout << foundMiejZerBi <<  foundMiejZerSiecz;
        if(foundMiejZerBi && foundMiejZerSiecz){
            main_plot.plot_xy( miejZerXBiVec, miejZerYBiVec, "Znalezione miejsce zerowe, metoda bisekcji: ["
                               + to_string(miejZerBi)+", "+to_string(miejZerYBi)+"]" );
            main_plot.plot_xy( miejZerXSieczVec, miejZerYSieczVec, "Znalezione miejsce zerowe, metoda siecznych: ["
                               + to_string(miejZerSiecz)+", "+to_string(miejZerYSiecz)+"]" );
        }

        foundMiejZerBi = false;
        foundMiejZerSiecz = false;
        miejZerYBi=99999999;
    }

    getchar();
    getchar();

    return 0;
}

