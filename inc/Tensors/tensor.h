#include "inc/Tensors/tensorexpr.h"

class Tensor : public Expression<Tensor>{
public:
    Tensor()=default;
    Tensor(DataType d): shape{}, dptr{new Data{d}} { }
    Tensor(const Shape& shape): shape{shape}, dptr(new Data(1<<shape.size(), 0)) { }
    Tensor(const Shape& shape, const Data& data): shape{shape}, dptr{new Data{data}} { }
    Tensor(const Shape& shape, DataPtr dptr): shape{shape}, dptr{dptr} { }
    Tensor(const Tensor& T): dptr{T.dptr}, shape{T.shape} {} 
    
    template<typename E>
	Tensor(const Expression<E> &e): dptr{new Data{}}
	{
		shape = e.get_shape();
		for (int i=0; i<(1<<shape.size()); i++){
            dptr->push_back(e[i]);
        }
	}
    
    DataType operator[](int i) const { return (*dptr)[i]; }
    DataType get_conv_sorted(int i) const { 
        Shape st_shape{shape.get_qtype_qubits(QType::up), shape.get_qtype_qubits(QType::down)};
        return (*dptr)[Transform::index_shape_change(i, st_shape, shape)]; 
    }
    const DataPtr& get_dptr() const { return dptr; }
    const Shape& get_shape() const { return shape; } 
    size_t size() const { return dptr->size(); } 
protected:
    DataPtr dptr;
    Shape shape;
};


bool operator==(const Tensor& Tl, const Tensor& Tr);
bool compare(const Tensor& Tl, const Tensor& Tr, double pres=0.0000001);
bool compare(const Tensor& Tl, const Tensor& Tr, double pres);
std::ostream& operator<<(std::ostream& os, const Tensor& T);
