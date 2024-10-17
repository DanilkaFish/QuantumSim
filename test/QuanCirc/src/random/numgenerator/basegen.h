
#ifndef _BASE_GEN
#define _BASE_GEN

#include <vector>

using veci_iter = std::vector<int>::iterator;
using vecd_iter = std::vector<double>::iterator;

class BaseGenerator{
public:
    virtual int    get_int(int min, int max) = 0;
    virtual double get_double(double min, double max) = 0;
    virtual void   get_int_array(veci_iter begin, veci_iter end, int min, int max) = 0;
    virtual void   get_double_array(vecd_iter begin, vecd_iter end, int min, int max) = 0;
    virtual ~BaseGenerator(){};
};
#endif


