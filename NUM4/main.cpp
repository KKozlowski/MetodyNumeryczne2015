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

double czebyszew(int n){
    double sum = 0;
    for(int k=1; k<=n;k++){
        sum += funk(cos((2*k-1)/(2.0*n)*M_PI));
    }
    sum *= M_PI/n;

    return sum;
}

double simpson(double x1, double x2){ //Nie dziala
    double result;
    double I_Ti = h*(funk(x1)+funk(x2))/2;
    double I_Pi = h*funk(x1);
    result = (2.0/3.0)*I_Pi+(1.0/3.0)*I_Ti;
    //cout << "Simpson " << result << endl;
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

double specialSinus(double x){
    return sin((x+1)*M_PI/2);
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
    cout << "Wybierz funkcje: \n1. Sinus\n2. Wykladnicza\n3. Wielomian \n4. sin((x-1)*pi/2) \n> ";
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
        funk=[](double x) -> double {return specialSinus(x);};
        break;
    default:
        throw string("Function not found");
    }
}

int main()
{
    Gnuplot::set_GNUPlotPath( GNUPLOT_PATH );

    {
        cout << "Wybierz metode: \n1. Newtona-Cotesa\n2. Gaussa-Czebyszewa\n> ";
        int wybor;

        cin >> wybor;
        if (wybor == 2) metodaNewt = false;
        else if (wybor != 1)
        {
            cout << "Method not found\n";
            return 0;
        }
    }

    try{
        wybierzFunk();
    } catch (string s){
        cout << s << endl;
        return 0;
    }

    if (metodaNewt)
    {
        cout << "Z waga[1], czy bez[2] ? ";
        int czyWaga;
        cin >> czyWaga;
        if(czyWaga == 1){
            cout << "Z waga.\n";
            funkN = funk;
            funk = [](double x) -> double {return funkN(x)/waga(x);};
            start = -0.99999999;
            stop = 0.999999999;
        } else {
        cout << "Bez wagi. Podaj poczatek i koniec przedzialu: ";
        cin >> start >> stop;
        }
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

        while(true){
            cout << "Podaj dokladnosc calkowania (niedodatnia przerwie program): ";
            cin >> dokladnosc;
            if (dokladnosc <=0 ) break;
            h=abs(start-stop)/10.0;

            double prev, now;
            prev = newton();
            int j = 0;
            while(true){
                j++;
                h/=2;
                now = newton();
                //cout << now<< endl;
                if(abs(now-prev) < dokladnosc){
                    cout << "WYNIK: " << newton() << " [" << j << " iteracja]\n";
                    break;
                }
                else{
                    prev = now;
                }
            }
        }


        getchar();
        getchar();
    }
    else
    {
        for(int i=2; i<=10; i++)
            cout << "Liczba wezlow: " << i <<"; WYNIK: " << czebyszew(i) << endl;
    }
    return 0;
}

