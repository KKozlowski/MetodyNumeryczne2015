#include <iostream>
#include <cmath>
#include <list>

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


//list<double> rozwiazania;
template<class F>void bisekcja(double start, double end, F funk, double epsilon){
    if( (funk(start) >=0 && funk(end) < 0) || (funk(start)<0 && funk(end) >=0) ){
        double center = (start+end)/2;
        double centerValue = funk(center);
        if(abs(centerValue) < epsilon){
            //rozwiazania.push_back(center);
            cout << center << endl;
        } else {
            bisekcja(start, center, funk, epsilon);
            bisekcja(center, end, funk, epsilon);
        }
    }
}

template<class F> double siecznych(F funk, double a, double b, double eps){
    double x0;
    double x00;
    x0 = a - funk(a) * (a - b) / (funk(a) - funk(b));
    if (x0 != x0){cout << "blad sieczna pionowa, najblizsza wartosc " << x00 << endl; return 0;}
    if (fabs(funk(x0)) < eps){
        //cout << x0 << endl;
        //cout << funk(x0) << endl;
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
    cout << "Hello World!" << endl;
    //bisekcja(-1,1.1,sinus,0.02);
    auto exponent = [](double x) -> double {return power(2,x);};
    auto wiel = [](double x) -> double {return wielomian(2,3,2,1,x);};
    bisekcja(-1,1.1,sinus,0.001);
    cout << endl << endl;
    double a = 2;
    cout << siecznych([a](double x)->double {return power(a, x);}, 2, 6, 0.2);
    /*for(list<double>::iterator it = rozwiazania.begin(); it != rozwiazania.end(); it++){
        cout << *it << endl;
    }*/

    return 0;
}

