#include "inc/Tensors/__init__.h"
// #include "inc/Tensors/__init__.h"

#include <algorithm>
#include <array>


// ------------------------------------Shape---------------------------------

int index_sum(int val){
    int i = 0;
    while (val >0){
        i += val & 1;
        val = val >> 1;
    }
    return i;
}

bool operator==(const Shape& sl, const Shape& sr){
    return sl.pos_up.m == sr.pos_up.m & sl.pos_down.m == sr.pos_down.m;
}

int index_shape_change(int id, const std::map<Qubit, int>& up, const std::map<Qubit, int>& down){
    int new_id=0;
    int pos =0;
    for(auto qub: down){
        if ( (id & 1) != 0){
            new_id += (1 << qub.second);
        }
        id = id >> 1;
        pos++;
    }
    for(auto qub: up){
        if ((id & 1) != 0){
            new_id += (1 << qub.second);
        }
        id = id >> 1;
        pos++;
    }
    return new_id;
}

Shape prod(const Shape& shl, const Shape& shr){
    int intersect = ( shr.pos_up.m & shl.pos_down.m );
    return Shape(mask(shl.pos_up.m | (shr.pos_up.m ^ intersect)), 
                 mask(shr.pos_down.m | (shl.pos_down.m ^ intersect)));
}


std::ostream& operator<<(std::ostream& os, const Shape& sh){
    int up = sh.pos_up.m;
    int i = 0;
    os << "up  : ";
        while (up > 0){
            if ((up&1) == 1)
                os << i << " ";
            i++;
            up=up>>1;
        }

    i = 0;
    up = sh.pos_down.m;
    os << "\ndown: ";
        while (up > 0){
            if ((up&1) == 1)
                os << i << " ";
            i++;
            up=up>>1;
        }
    return os << "\n";
}

bool operator==(const Tensor& Tl, const Tensor& Tr){
    if (!(Tl.get_shape() == Tr.get_shape())){
        return false;
    }
    for (int i = 0; i < Tl.size(); i++ ){
        if (Tl[i] != Tr[i]){
            return false;
        }
    }
    return true;
}


bool compare(const Tensor& Tl, const Tensor& Tr, double pres){
    if (!(Tl.get_shape() == Tr.get_shape())){
        return false;
    }
    for (int i = 0; i < Tl.size(); i++ ){
        DataType d = Tl[i] - Tr[i];
        if (std::abs(d) > pres){
            return false;
        }
    }
    return true;
}
std::ostream& operator<<(std::ostream& os, const Tensor& T){
    os << "[ ";
    for(int i = 0; i < T.size(); i++ ){
        os << T[i] << " ";
    }
    return os << "]\n";
}


// {
//     for (auto x: *T.get_dptr())
//         os << x;
//     return os << std::endl;
// }