#ifndef WEKTOR_H
#define WEKTOR_H

#include <vector>

class Wektor : public std::vector<double>
{
public:
    Wektor(int rozm);
    ~Wektor();

    Wektor operator -( const Wektor & x ) const
    {
        Wektor result(size()-1);
        for(unsigned int i=1; i<size(); i++){
            result[i] = at(i) - x.at(i);
        }
        return result;
    }

    void wypisz();

    double norma();
};

#endif // WEKTOR_H
