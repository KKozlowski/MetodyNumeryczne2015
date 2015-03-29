#ifndef EQUATION_H
#define EQUATION_H

#include "simpleeq.h"
#include <cmath>

using namespace std;

class Equation : public SimpleEq
{
public:
    int main;
    double free;

    Equation(SimpleEq &se, int cel) : SimpleEq() {
        for(int i=0; i<se.wsp.size(); i++){
            wsp.push_back(se[i+1]);
        }

        //operator [](1) = operator[](4);
        main = cel;

        double mainValue = operator [](main);
        for(int i = 1; i <=wsp.size(); i++){
            operator [](i) /= mainValue;
        }

        for(int i = 1; i <wsp.size(); i++){
            operator [](i) = -operator [](i);
        }

        operator [](main) = 0;

        free = wsp[wsp.size()-1];

    }
    ~Equation();

    void Write();

    double Calculate(vector<double> vec);

    double AbsoluteSum();
};

#endif // EQUATION_H
