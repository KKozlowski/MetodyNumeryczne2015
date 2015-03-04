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

int main()
{
    cout << "Hello World!" << endl;
    //bisekcja(-1,1.1,sinus,0.02);
    auto exponent = [](double x) -> double {return power(2,x);};
    auto wiel = [](double x) -> double {return wielomian(2,3,2,1,x);};
    bisekcja(-1,1.1,sinus,0.001);
    /*for(list<double>::iterator it = rozwiazania.begin(); it != rozwiazania.end(); it++){
        cout << *it << endl;
    }*/

    return 0;
}

