#ifndef _VQE
#define _VQE

#include<utility>

#include "nlopt.hpp"

#include "instruction.h"
#include "q_errors.h"


typedef std::vector<double> DoubleVec;


class Callback{
public:
    virtual void general_write(DoubleVec, double){};
    virtual void sub_write(DoubleVec, double){};
};

class EmptyCallback : public Callback{
public:
    EmptyCallback(){}
};


class Optimizer{
public:
    // Optimizer(MetaProvider& mp, const ParameterVector& pv):  mp{mp}, pv{pv} { cb=EmptyCallback{}; }
    Optimizer(MetaProvider& mp, ParameterVector& pv, Callback& cb): cb{cb}, mp{mp}, pv{pv} {}
    
    virtual std::pair<DoubleVec, double> optimize(int max_iter){
        int i = 0;
        SetUp();
        auto res = _update();
        while((!is_to_stop(res)) & (i<max_iter)){
            pv.set_row_values(res.first);
            cb.general_write(res.first, res.second);
            i++;
            res = _update();
            pv.set_row_values(res.first);
        }
        return res;
    };

    virtual ~Optimizer() {}
protected:
    virtual std::pair<DoubleVec, double> _update() = 0;
    virtual void SetUp() = 0;
    virtual bool is_to_stop(std::pair<DoubleVec, double> data) = 0;
    Callback& cb;
    MetaProvider& mp;
    ParameterVector& pv;
};


struct quantum_obj_data{
    MetaProvider& mp;
    ParameterVector& pv;
}

// class COBYLA()
double eval_cost(const std::vector<double> &x, std::vector<double> &grad, void *data){
    quantum_obj_data *d = reinterpret_cast<quantum_obj_data *>(data);
    
}
class Nlopt_Optimizer: public Optimizer{
public:
    Nlopt_Optimizer(const nlopt_opt& opt, MetaProvider& mp, ParameterVector& pv, Callback& cb): opt{opt}, Optimizer{mp,pv,cb} {
        nlopt_set_min_objective(opt, mp.evaluate_cost(), NULL);
    }
    static double eval_cost()
private:
    nlopt_opt opt;
    
}

#endif