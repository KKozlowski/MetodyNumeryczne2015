#include "simpleeq.h"

SimpleEq::SimpleEq()
{

}

SimpleEq::SimpleEq(int rozm)
{
    for(int i=0; i<=rozm ; i++) wsp.push_back(0);
}

SimpleEq::~SimpleEq()
{

}

void SimpleEq::Write()
{
    for(int i=0; i< wsp.size()-1; i++)
        std::cout << wsp.at(i) << "*x" << i+1 << " + ";


    std::cout << "\b\b\b = " << wsp.at(wsp.size()-1) << std:: endl;
}

