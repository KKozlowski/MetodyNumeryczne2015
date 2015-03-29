#ifndef EQUATION_H
#define EQUATION_H

#include "simpleeq.h"

using namespace std;

class Equation : public SimpleEq
{
public:
    int main;

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
    }
    ~Equation();
};

#endif // EQUATION_H
