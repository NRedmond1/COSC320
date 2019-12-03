#ifndef HASH_H
#define HASH_H

#include <string>
#include <typeinfo>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

size_t hashI(size_t x)
{
    size_t w = 32;
    size_t p = 31;
    size_t a = 199;

    size_t W = size_t (1) << w;

    return (((a*x)%W) >> (w-p));

}

size_t hashS(std::string x)
{
    int size = x.length()-1;
    size_t temp = 0;
    size_t outerhash = 0;

    for( int t = size; t >= 0; t-- )
    {
	     temp = x[size-t] * (t+1);
	     outerhash += temp;
    }

    return hashI(outerhash);
}

#endif
