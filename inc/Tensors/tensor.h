#include "inc/Tensors/tensorexpr.h"

class Tensor : Expression<Tensor>{
public:
    Tensor()=default;
    Tensor(DataType d): shape{}, data{d} { }
    Tensor(const Shape& shape): shape{shape}, data(1<<shape.size()) { }
    Tensor(const Shape& shape, const Data& data): shape{shape}, data{data} { }
    Tensor(const Tensor& T): data{T.data}, shape{T.shape} {} 
    template<typename E>
	Tensor(const Expression<E> &e)
	{
		shape = e.get_shape();
		for (int i=0; i<(1<<shape.size()); i++){
            data.push_back(e[i]);
        }
	}
    
    DataType operator[](int i) const { return data[i]; }
    DataType get_conv_sorted(int i) const { 
        Shape st_shape{shape.get_qtype_qubits(QType::up), shape.get_qtype_qubits(QType::down)};
        return data[Transform::index_shape_change(i, st_shape, shape)]; 
    }
    const Data& get_data() const { return data; }
    const Shape& get_shape() const { return shape; } 
    size_t size() const { return data.size(); } 
private:
    Data data;
    Shape shape;
};


bool operator==(const Tensor& Tl, const Tensor& Tr);
std::ostream& operator<<(std::ostream& os, const Tensor& T);
