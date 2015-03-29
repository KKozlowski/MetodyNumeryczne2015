#ifndef SIMPLEEQ_H
#define SIMPLEEQ_H

#include <vector>
#include <iostream>

class SimpleEq
{
public:
    std::vector<double> wsp;
    SimpleEq();
    SimpleEq(int rozm);
    int GetLevel();
    ~SimpleEq();
    double & operator[](int pos) {return wsp.at(pos-1);}
    virtual void Write();
};

#endif // SIMPLEEQ_H
