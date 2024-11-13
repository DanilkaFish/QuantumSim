#ifndef _SHAPE
#define _SHAPE
#include <algorithm>
#include <map>
#include "stddata.h"
#include "inc/qubits.h"
// typedef std::map<Qubit, Int> Acontainer;
enum class QType{ up=0, down=1, cup=2, cdown=3 };
struct Shape;
std::ostream& operator<<(std::ostream& os, const Shape& sh);
struct Shape{
public:
    Shape()=default;
    Shape(const Qubits& up, const Qubits& down);
    Shape(const Shape& sh): pos_up(sh.pos_up), pos_down(sh.pos_down), pos_up_conv(sh.pos_up_conv), pos_down_conv(sh.pos_down_conv){ };
    std::map<Qubit, Int>& get_qtype(QType qt);
    const std::map<Qubit, Int>& get_qtype(QType qt) const;
    Int get_pos(const Qubit& q, QType qt) const;
    size_t size() const { return pos_up.size() + pos_down.size(); }

    // void transpose(const Qubits& qubs);
    void to_conv(const Qubits& qubs);
private:
    std::map<Qubit, Int> pos_up;
    std::map<Qubit, Int> pos_down;
    std::map<Qubit, Int> pos_up_conv;
    std::map<Qubit, Int> pos_down_conv;
};

class Transform{
public:
    static Int to_sub_shape(Int id_oldsh, const Shape& oldsh, const Shape& subsh);
    static Int conv_id_for_prod(Int conv_id, const Shape& sh);
    static Int conv_id_for_conv(Int conv_id, const Shape& sh);
    static Int index_sum(Int val);
private:
    static Int bit_on_pos(Int val, Int pos);
    // static Int del_on_pos(Int val, Int pos);
    static Int change_on_pos(Int value, Int pos, Int bits);
};


std::pair<Shape, Shape> prod_shape(const Shape& _s1, const Shape& _s2);
Shape sum_shape_fin(const Shape& _s1, const Shape& _s2);
Shape prod_shape_fin(const Shape& _s1, const Shape& _s2);
Shape transpose(Shape sh );
bool operator==(const Shape& sl, const Shape& sr);

#endif