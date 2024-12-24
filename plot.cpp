#include <pybind11/embed.h>
#include "python_singleton.h"
using namespace pybind11::literals;

py::object to_array(const std::vector<double>& arr){
    py::object numpy = py::module_::import("numpy");
    int size = arr.size();
    py::array_t<double> array({size}, new double[size]);
    for (int j =0; j<size; j++){
        array[py::int_(j)] = arr[j];
    }
    return array;
}


class Plot{
public:
    Plot(): rp{RunPython::getInstance()}{
        plt = py::module_::import("matplotlib.pyplot");
        plt.attr("semilogx")();
        // plt.attr("ylim")(py::int_(-12), py::int_(5));
    }
    void set_x(const std::vector<double>& arr){
        x = to_array(arr);
    }
    void set_y(const std::vector<double>& arr){
        y = to_array(arr);
    }
    void plot(std::string str){
        plt.attr("plot")(x,y, "label"_a = str);
    }
    void save(){
        plt.attr("legend")();
        plt.attr("savefig")("../fig.png");
    }
private:
    RunPython& rp;
    py::object plt;
    py::object x;
    py::object y;
};