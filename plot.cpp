#include <pybind11/embed.h>
#include "python_singleton.h"

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
    }
    void set_x(const std::vector<double>& arr){
        x = to_array(arr);
    }
    void set_y(const std::vector<double>& arr){
        y = to_array(arr);
    }
    void plot(){
        plt.attr("plot")(x,y);
    }
    void save(){
        plt.attr("savefig")("../fig.png");
    }
private:
    RunPython& rp;
    py::object plt;
    py::object x;
    py::object y;
};