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

double M = 5.974e24;
double G = 6.67e-11;
double h = 3; //wielkosc kroku calkowania
const int table_size = 30000;

double x[table_size];
double y[table_size];
double vx[table_size];
double vy[table_size];

//http://scicomp.stackexchange.com/questions/12854/simulate-motion-of-the-kepler-orbit-using-runge-kutta-4-method-in-c

double func1(double y2, double y1, double y4, double y3){
    return y2;
}

double func2(double y2, double y1, double y4, double y3){
    double r = sqrt(y1*y1+y3*y3);
    return -G*M*y1/(r*r*r);
}

double func3(double y2, double y1, double y4, double y3){
    return y4;
}

double func4(double y2, double y1, double y4, double y3){
    double r = sqrt(y1*y1+y3*y3);
    return -G*M*y3/(r*r*r);
}

void liczAlgorytmemRungegoKutty(double *y1, double *y2, double *y3, double *y4 ){

    for(int i=1; i<table_size; i++){
        double k11=h*func1(y2[i-1], y1[i-1], y4[i-1], y3[i-1]);
        double k21=h*func2(y2[i-1], y1[i-1], y4[i-1], y3[i-1]);
        double k31=h*func3(y2[i-1], y1[i-1], y4[i-1], y3[i-1]);
        double k41=h*func4(y2[i-1], y1[i-1], y4[i-1], y3[i-1]);

        double k12=h*func1(0.5*k21+y2[i-1], 0.5*k11+y1[i-1], 0.5*k41+y4[i-1], 0.5*k31+y3[i-1]);
        double k22=h*func2(0.5*k21+y2[i-1], 0.5*k11+y1[i-1], 0.5*k41+y4[i-1], 0.5*k31+y3[i-1]);
        double k32=h*func3(0.5*k21+y2[i-1], 0.5*k11+y1[i-1], 0.5*k41+y4[i-1], 0.5*k31+y3[i-1]);
        double k42=h*func4(0.5*k21+y2[i-1], 0.5*k11+y1[i-1], 0.5*k41+y4[i-1], 0.5*k31+y3[i-1]);

        double k13=h*func1(0.5*k22+y2[i-1], 0.5*k12+y1[i-1], 0.5*k42+y4[i-1], 0.5*k32+y3[i-1]);
        double k23=h*func2(0.5*k22+y2[i-1], 0.5*k12+y1[i-1], 0.5*k42+y4[i-1], 0.5*k32+y3[i-1]);
        double k33=h*func3(0.5*k22+y2[i-1], 0.5*k12+y1[i-1], 0.5*k42+y4[i-1], 0.5*k32+y3[i-1]);
        double k43=h*func4(0.5*k22+y2[i-1], 0.5*k12+y1[i-1], 0.5*k42+y4[i-1], 0.5*k32+y3[i-1]);

        double k14=h*func1(k23+y2[i-1], k13+y1[i-1], k43+y4[i-1], k33+y3[i-1]);
        double k24=h*func2(k23+y2[i-1], k13+y1[i-1], k43+y4[i-1], k33+y3[i-1]);
        double k34=h*func3(k23+y2[i-1], k13+y1[i-1], k43+y4[i-1], k33+y3[i-1]);
        double k44=h*func4(k23+y2[i-1], k13+y1[i-1], k43+y4[i-1], k33+y3[i-1]);

        y1[i] = y1[i-1] + (k11+2*k12+2*k13+k14)/6;
        y2[i] = y2[i-1] + (k21+2*k22+2*k23+k24)/6;
        y3[i] = y3[i-1] + (k31+2*k32+2*k33+k34)/6;
        y4[i] = y4[i-1] + (k41+2*k42+2*k43+k44)/6;
    }

}

double min(double *tab){
    double mini = tab[0];
    for (int i=1; i< table_size; i++){
        if (tab[i] < mini) mini = tab[i];
    }

    return mini;
}

double max(double *tab){
    double maxi = tab[0];
    for (int i=1; i< table_size; i++){
        if (tab[i] > maxi) maxi = tab[i];
    }

    return maxi;
}

void wybierzFunk(){
    cout << "Wybierz przypadek [1-3]: \n> ";
    int wybor;

    cin >> wybor;
    x[0] = 6.578e6;
    y[0] = 0;
    vx[0] = 0;
    switch(wybor){
    case 1:
        vy[0] = 7900;
        break;
    case 2:
        vy[0] = 9000;
        break;
    case 3:
        vy[0] = 11200;
        break;
    default:
        throw string("Example not found");
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

    liczAlgorytmemRungegoKutty(x,vx,y,vy);

    start = 0;
    stop = table_size-1;

    Gnuplot X_plot;
    Gnuplot Y_plot;
    Gnuplot Vx_plot;
    Gnuplot Vy_plot;
    Gnuplot XY_plot;

    {
        X_plot.set_title( "X" );
        X_plot.set_xlabel( "X" );
        X_plot.set_ylabel( "Y" );


        X_plot.set_grid();
        X_plot.set_xrange( start , stop ) ;
        X_plot.set_yrange(min(x),max(x));
        X_plot.set_style( "lines" );
        vector<double> poz;
        vector<double> pion;
        for(int i=0; i<table_size; i++){
            poz.push_back(i);
            pion.push_back(x[i]);
        }

        X_plot.plot_xy( poz, pion, "Wykres funkcji." );
    }

    {
        Y_plot.set_title( "Y" );
        Y_plot.set_xlabel( "X" );
        Y_plot.set_ylabel( "Y" );


        Y_plot.set_grid();
        Y_plot.set_xrange( start , stop ) ;
        Y_plot.set_yrange(min(y),max(y));
        Y_plot.set_style( "lines" );
        vector<double> poz;
        vector<double> pion;
        for(int i=0; i<table_size; i++){
            poz.push_back(i);
            pion.push_back(y[i]);
        }

        Y_plot.plot_xy( poz, pion, "Wykres funkcji." );
    }

    {
        Vx_plot.set_title( "Vx" );
        Vx_plot.set_xlabel( "X" );
        Vx_plot.set_ylabel( "Y" );

        Vx_plot.set_grid();
        Vx_plot.set_xrange( start , stop ) ;
        Vx_plot.set_yrange(min(vx),max(vx));
        Vx_plot.set_style( "lines" );
        vector<double> poz;
        vector<double> pion;
        for(int i=0; i<table_size; i++){
            poz.push_back(i);
            pion.push_back(vx[i]);
        }

        Vx_plot.plot_xy( poz, pion, "Wykres funkcji." );
    }

    {
        Vy_plot.set_title( "Vy" );
        Vy_plot.set_xlabel( "X" );
        Vy_plot.set_ylabel( "Y" );

        Vy_plot.set_grid();
        Vy_plot.set_xrange( start , stop ) ;
        Vy_plot.set_yrange(min(vy),max(vy));
        Vy_plot.set_style( "lines" );
        vector<double> poz;
        vector<double> pion;
        for(int i=0; i<table_size; i++){
            poz.push_back(i);
            pion.push_back(vy[i]);
        }

        Vy_plot.plot_xy( poz, pion, "Wykres funkcji." );
    }

    {
        XY_plot.set_title( "XY" );
        XY_plot.set_xlabel( "X" );
        XY_plot.set_ylabel( "Y" );

        XY_plot.set_grid();
        XY_plot.set_xrange( min(x)*1.1 , max(x)*1.1 ) ;
        XY_plot.set_yrange(min(y)*1.1,max(y)*1.1);
        XY_plot.set_style( "lines" );
        vector<double> poz;
        vector<double> pion;
        for(int i=0; i<table_size; i++){
            poz.push_back(x[i]);
            pion.push_back(y[i]);
        }

        XY_plot.plot_xy( poz, pion, "Wykres funkcji." );

        XY_plot.set_style( "points" );
        vector<double> poz0 {x[0]};
        vector<double> pion0{y[0]};
        XY_plot.plot_xy( poz0, pion0, "Pocz¹tek ruchu." );

        vector<double> zero {0};
        XY_plot.plot_xy( zero, zero, "Punkt zerowy." );
    }

    getchar();
    getchar();

    return 0;
}

