#ifndef _SHAPE
#define _SHAPE
#include <algorithm>
#include <map>
#include "stddata.h"
#include "inc/qubits.h"


enum class QType{ up=0, down=1};
struct Shape{
public:
    Shape()=default;
    Shape(const Qubits& up, const Qubits& down);
    Shape(const Shape& sh): pos_up(sh.pos_up), pos_down(sh.pos_down) { }
    PosMap&       get_qtype(QType qt);
    const PosMap& get_qtype(QType qt) const;
    Int                         get_pos(const Qubit& q, QType qt) const;
    size_t                      size() const { return pos_up.size() + pos_down.size(); }
    Qubits                      get_qtype_qubits(QType qt) const;
private:
    PosMap pos_up;
    PosMap pos_down;
};

class Transform{
public:
    static Shape transpose(Shape sh);  
    static Shape sum_shape_res(const Shape& _s1, const Shape& _s2);
    static Shape prod_shape_res(const Shape& _s1, const Shape& _s2);
    static std::vector<Shape> prod_shape_div(const Shape& _s1, const Shape& _s2);
    static Int index_shape_change(Int id_oldsh, const Shape& oldsh, const Shape& subsh);
    static Int index_shape_change_forward(Int id_oldsh, const Shape& forward);
    static Int index_shape_change_back(Int id_oldsh, const Shape& back);
    static Int index_sum(Int val);
private:
    static Int bit_on_pos(Int val, Int pos);
    static Int change_on_pos(Int value, Int pos, Int bits);
};


bool operator==(const Shape& sl, const Shape& sr);
std::ostream& operator<<(std::ostream& os, const Shape& shape);

#endif