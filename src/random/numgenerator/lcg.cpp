#include "basegen.h"
#ifndef _LCG
#define _LCG

class LCG: public BaseGenerator{
public:
    LCG(
        int seed, 
        int init_step=100,
        int a=75, 
        int c=74, 
        int m=(1<<16) + 1
        );
    int    get_int(int min, int max) override;
    void   get_int_array(veci_iter begin, veci_iter end, int min, int max) override;
    double get_double(double min, double max) override;
    void   get_double_array(vecd_iter begin, vecd_iter end, int min, int max) override;

    ~LCG() override {};
private:
    int seed;
    struct Data{
        int a;
        int c;
        int m;
        int x;
    };
    Data data;
};

LCG::LCG(int seed, int init_step, int a, int c, int m)
         : seed{seed}, data{a,c,m,seed}
{
    for (int i=0; i<init_step-1; i++)
        data.x = (data.a*data.x + data.c) % data.m;
}

int LCG::get_int(int min, int max){ 
    data.x = (data.a*data.x + data.c) % data.m;
    return min + data.x % (max - min); 
} 

double LCG::get_double(double min, double max){ 
    data.x = (data.a*data.x + data.c) % data.m;
    return min + (double(data.x)/data.m)*(max - min); 
} 

void LCG::get_int_array(veci_iter begin, veci_iter end, int min, int max){
    for(auto i=begin; i != end; i++)
        *i = get_int(min, max);
};

void LCG::get_double_array(vecd_iter begin, vecd_iter end, int min, int max){
    for(auto i=begin; i != end; i++)
        *i = get_double(min, max);
};
    
#endif