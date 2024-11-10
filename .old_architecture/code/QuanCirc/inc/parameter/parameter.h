
#include <string>

class name_generation{
public:
    static std::string get_name(){
        return std::to_string(counts++);
    }
private:
    static int counts;
};
int name_generation::counts = 0;

class Parameter{
public:
    Parameter(double val, std::string name): name{name_generation::get_name()}, val{val} { }
    Parameter(std::string name): name{name}, val{0} { }
    const std::string& get_name() const { return name; } 
private:
    std::string name;
    Double val;
};
