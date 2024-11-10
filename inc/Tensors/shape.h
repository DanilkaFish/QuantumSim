#include "stddata.h"
struct Shape{
    Shape(Int up, Int down): up{up}, down{down} {};
    Int size() const { return up.size() + down.size();}
private:
    Positions up;
    Positions down;
};