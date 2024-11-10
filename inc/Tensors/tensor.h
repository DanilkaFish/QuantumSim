#include "shape.h"
#include "stddata.h"

class Tensor{
public:
    Tensor(const Shape& sh): shape{sh}, data(1 << sh.size(), 0){}
    
private:
    Shape shape;
    Container data;
};