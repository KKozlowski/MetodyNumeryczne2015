#include <iostream>
#include <cmath>
#include <list>
#include <fstream>
#include <vector>
#include "gnuplot_i.hpp"

#define GNUPLOT_PATH "C:/gnuplot/bin"
#define M_PI 3.1415926

using namespace std;

double start, stop;
double dokladnosc=0.1;
double h;
double (*funk)(double);
double (*funkN)(double);
bool metodaNewt = true;



double wezel(int k, int n){
    return cos((2*k-1)/(2.0*n)*M_PI);
}

double polynomial(double x, int n){
    return cos(n*acos((x)));
}

double calka(int n){
    double sum = 0;
    for(int k=1; k<=n;k++){
        sum += funk(wezel(k,n));
    }
    sum *= M_PI/n;

    return sum;
}

double cj(int j, int N){
    double sum = 0;
    for(int i=1; i<=N; i++)
        sum+=(funk(wezel(i,N))*cos(M_PI*j*(i-0.5)/N));

    sum*= (2.0/N);
    return sum;
}

double approx(double x, int N){
    double result = 0;
    for(int i = 0;i<=N-1;i++){
        result+= (cj(i,N)*polynomial(x,i));
    }
    result -= (0.5*cj(0,N));
    return result;
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
    return sin(x*5);
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

double *wspolczynniki;
int stopien;

double waga(double x){
    return sqrt(1-x*x);
}

void wybierzFunk(){
    cout << "Wybierz funkcje: \n1. f(x) = sinus(5x)\n2. f(x) = 2^(5x)\n3. Wielomian \n4. f(x) = |2x| \n> ";
    int wybor;

    cin >> wybor;

    switch(wybor){
    case 1:
        funk=sinus;
        break;
    case 2:
        funk=[](double x) -> double {return power(2,x*5);};
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
        funk=[](double x) -> double {return abs(2*x);};
        break;
    default:
        throw string("Function not found");
    }
}

int main()
{
    Gnuplot::set_GNUPlotPath( GNUPLOT_PATH );

    try{
        wybierzFunk();
    } catch (string s){
        cout << s << endl;
        return 0;
    }

    start = -1;
    stop = 1;

    Gnuplot main_plot;

    main_plot.set_title( "Wykres" );
    main_plot.set_xlabel( "X" );
    main_plot.set_ylabel( "Y" );


    main_plot.set_grid();
    main_plot.set_xrange( start , stop ) ;
    main_plot.set_yrange(-2,2);
    main_plot.set_style( "lines" );
    int precyzja = 1000;
    double skok = (stop-start)/precyzja;
    vector<double> x;
    vector<double> y;
    vector<double> y_approx2;
    vector<double> y_approx4;
    vector<double> y_approx5;
    vector<double> y_approx7;
    vector<double> y_approx10;
    for(double d=start; d<=stop;d+=skok){
        x.push_back(d);
        y.push_back(funk(d));
        y_approx2.push_back(approx(d,2));
        y_approx4.push_back(approx(d,4));
        y_approx5.push_back(approx(d,5));
        y_approx7.push_back(approx(d,7));
        y_approx10.push_back(approx(d,10));
    }

    main_plot.plot_xy( x, y, "Wykres funkcji." );

    main_plot.plot_xy( x, y_approx2, "2 wezly" );
    main_plot.plot_xy( x, y_approx4, "4 wezly" );
    main_plot.plot_xy( x, y_approx5, "5 wezlow" );
    main_plot.plot_xy( x, y_approx7, "7 wezlow" );
    main_plot.plot_xy( x, y_approx10, "10 wezlow" );

    getchar();
    getchar();
    return 0;
}

