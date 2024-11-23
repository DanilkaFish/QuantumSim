#include "tensorexpr.h"

int index_shape_change(int id, const std::map<Qubit, int>& up, const std::map<Qubit, int>& down);


class Tensor : public Expression<Tensor>{
public:
    Tensor()=default;
    Tensor(DataType d): shape{}, dptr{new Data{d}} { }
    Tensor(const Shape& shape): shape{shape}, dptr{new Data(1 << shape.size())} { }
    Tensor(const Qubits& up, const Qubits& down, const Data& data): shape{up, down}, dptr{new Data(1 << up.size() + down.size())} {
        std::map<Qubit, int> posmapd;
        std::map<Qubit, int> posmapu;
        int pos=0;
        for (auto x: down){
            posmapu[x] = pos;
            pos++;
        }
        for (auto x: up){
            posmapd[x] = pos;
            pos++;
        }
        for (int i=0;i<dptr->size(); i++){
            (*dptr)[index_shape_change(i, posmapd, posmapu)] = data[i]; 
        }
    }
    Tensor(const Shape& shape, DataPtr dptr): shape{shape}, dptr{dptr} { }
    Tensor(const Tensor& T): dptr{T.dptr}, shape{T.shape} {} 
    
    template<typename E>
	Tensor(const Expression<E> &e): dptr{new Data{}}, shape{e.get_shape()}
	{
		for (int i=0; i<(1<<shape.size()); i++){
            dptr->push_back(e[i]);
        }
	}
    
    DataType operator[](int i) const { return (*dptr)[i]; }

    const DataPtr& get_dptr() const { return dptr; }
    const Shape& get_shape() const { return shape; } 
    size_t size() const { return dptr->size(); } 
protected:
    DataPtr dptr;
    Shape shape;
};



std::ostream& operator<<(std::ostream& os, const Tensor& T);
bool operator==(const Tensor& Tl, const Tensor& Tr);
bool compare(const Tensor& Tl, const Tensor& Tr, double pres=0.0000001);
bool compare(const Tensor& Tl, const Tensor& Tr, double pres);
// {
//     for (auto x: *T.get_dptr())
//         os << x;
//     return os << std::endl;
// }
