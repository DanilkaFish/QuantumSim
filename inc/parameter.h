#ifndef _PARAMETER
#define _PARAMETER

#include <string>
#include <map>
#include <iostream>

class Parameter{
public:
    Parameter(const std::string& name, double d=0): name{name}, val{d} { set_parameter(); }
    int get_id() const { return id; }
private:
    void set_parameter(){ static int counter = 0; counter++; id=counter;}
    std::string name;
    double val;
    int id;
};

struct ParameterSet{
    std::map<Parameter, double> name;
};

bool operator<(const Parameter& pl, const Parameter& pr );
std::ostream& operator<<(std::ostream& os, const Parameter& p);

#endif