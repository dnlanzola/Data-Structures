// Programmer: Daniel Anzola Delgado
// Last modification date: 3/16

#include <iostream>
#include "line.h"

double Line::intersect(const Line L) const 
{
    //Equal lines
    if (L.a == this->a && L.b == this->b)
        throw EqualLines();
    
    //Parallel lines
    if (L.a == this->a)
        throw ParallelLines();
    
    double result = 0.0;
    
    //Calculation X-coordinate of intersection
    result = (this->b - L.b) / (L.a - this->a);
    
    return result;
}


