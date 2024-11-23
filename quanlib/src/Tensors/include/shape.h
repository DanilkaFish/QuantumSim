#ifndef _SHAPE
#define _SHAPE
#include <algorithm>
#include <map>
#include <array>

#include "common.h"


constexpr int ld_bits = 5;
enum class QType{ up=0, down=1};



int index_sum(int val);


struct mask{
    mask()=default;
    explicit mask(int m): m{m} { set_mv(); }
    explicit mask(const Qubits& qubs): m{0}{
        for (auto x: qubs){
            m += (1 << x.num);
        }
        set_mv();
    }
    mask(const mask& ms): m{ms.m}, mv{ms.mv} {} 
    int compress(int x) const {
        x = x & m;
        int t;
        for (int i = 0; i < mv[ld_bits]; i++) {
            t = x & mv[i]; 
            x = (x ^ t) | (t >> (1 << i));
        }
        return x;
    }
    int expand(int x) const {
        for (int i = mv[ld_bits] - 1; i >=0 ; i--) {
            x = (((x << (1 << i)) ^ x) & mv[i]) ^ x;
        }

        return  x & m;
        

    }
    void set_mv(){
        int _m = m;
        int mk = (~_m) << 1; 
        int mp;
        mv[ld_bits] = ld_bits;
        for (int i = 0; i < ld_bits; i++) {
            mp = mk ^ (mk << 1); // Parallel prefix.
            mp = mp ^ (mp << 2);
            mp = mp ^ (mp << 4);
            mp = mp ^ (mp << 8);
            mp = mp ^ (mp << 16);
            mv[i] = mp & _m; // Bits to move.
            _m = (_m ^ mv[i]) | (mv[i] >> (1 << i)); // Compress m.
            mk = mk & (~mp);
            if (mk == 0){
                mv[ld_bits] = i + 1;
                break;
            }
        }
    }
    int m;
private:
    std::array<int,ld_bits + 1> mv;
};

struct Shape{
public:
    Shape(): pos_up{0}, pos_down{0}, nu{0}, nd{0} {}
    Shape(const mask& up, const mask& down): pos_up{up}, pos_down{down} { nu = index_sum(up.m); nd = index_sum(down.m);}
    Shape(const Qubits& up, const Qubits& down): pos_up{up}, pos_down{down} {
        nu = up.size(); 
        nd = down.size();
    }
    Shape(const Shape& sh): Shape(sh.pos_up, sh.pos_down) {}

    size_t size() const { return nu + nd; }
    int nu;
    int nd;
    mask pos_up;
    mask pos_down;

};


// int index_shape_change_forward(int id, const Shape& sh){

//     return Transform::index_shape_change(id, Shape{sh.get_qtype_qubits(QType::up), sh.get_qtype_qubits(QType::down)}, sh);
// }


Shape prod(const Shape& shl, const Shape& shr);


// Shape sum(const Shape& shl, const Shape& shr){
//     int intersect = ( shr.pos_up.m & shl.pos_down.m );
//     mask up = shl.pos_up.m | (shr.pos_up.m ^ intersect);
//     return Shape(shl.pos_up.m | (shr.pos_up.m ^ intersect), 
//                  shr.pos_down.m | (shl.pos_down.m ^ intersect));
// }

class Transform{
public:
    static Shape transpose(Shape sh);  
    static Shape sum_shape_res(const Shape& _s1, const Shape& _s2);
    static Shape prod_shape_res(const Shape& _s1, const Shape& _s2);
    static std::vector<Shape> prod_shape_div(const Shape& _s1, const Shape& _s2);
    static int index_shape_change(int id_oldsh, const Shape& oldsh, const Shape& subsh);
    static int index_shape_change_forward(int id_oldsh, const Shape& forward);
    static int index_shape_change_back(int id_oldsh, const Shape& back);
    static int index_sum(int val);
private:
    static int bit_on_pos(int val, int pos);
    static int change_on_pos(int value, int pos, int bits);
};


bool operator==(const Shape& sl, const Shape& sr);
std::ostream& operator<<(std::ostream& os, const Shape& shape);

#endif