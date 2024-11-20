// #include "inc/Tensors/__init__.h"
// // #include "inc/Tensors/__init__.h"

// #include <algorithm>
// #include <array>


// // ------------------------------------Shape---------------------------------


// Shape::Shape(const Qubits& up, const Qubits& down){
//     Int pos=0;
//     for (auto x: down){
//         this->pos_down[x] = pos;
//         pos++;
//     }
//     for (auto x: up){
//         this->pos_up[x] = pos;
//         pos++;
//     }

// };
// Int Transform::index_shape_change_forward(Int id, const Shape& sh){
//     return Transform::index_shape_change(id, Shape{sh.get_qtype_qubits(QType::up), sh.get_qtype_qubits(QType::down)}, sh);
// }

// Qubits Shape::get_qtype_qubits(QType qt) const{
//     Qubits qubs;
//     auto m = get_qtype(qt);
//     for(auto x: m){
//         qubs.push_back(x.first);
//     }
//     return qubs;
// }


// PosMap& Shape::get_qtype(QType qt){
//     switch (qt){
//         case QType::up:
//             return pos_up;
//         default:
//             return pos_down;
//     }
// }

// const PosMap& Shape::get_qtype(QType qt) const{
//     switch (qt){
//         case QType::up:
//             return pos_up;
//         default:
//             return pos_down;
//     }
// }

// bool operator==(const Shape& sl, const Shape& sr){
//     Int ls = sl.size();
//     Int rs = sr.size();
//     if (ls != rs){
//         return false;
//     }
//     std::array<QType, 2> qta{{QType::up, QType::down}};
//     for (auto qt: qta){
//         auto itl = sl.get_qtype(qt).begin();
//         auto itr = sr.get_qtype(qt).begin();
//         for (Int i=0; i<ls; i++){
//             if (itl->first != itr->first){
//                 return false;
//             }
//         }
//     }
//     return true;
// }

// // -------------------------------Transform-------------------------------------


// std::vector<Shape> Transform::prod_shape_div(const Shape& _s1, const Shape& _s2){
//     Shape s1{_s1};
//     Shape s2{_s2};
//     Shape s1c{};
//     Shape s2c{};
//     QType lqt = QType::down;
//     QType rqt = QType::up;
//     for(auto it1 = s1.get_qtype(lqt).begin(); it1 != s1.get_qtype(lqt).end(); ){
//         auto it2 = s2.get_qtype(rqt).find(it1->first);
//         if (it2 != s2.get_qtype(rqt).end()){
//             s1c.get_qtype(lqt)[it1->first] = it1->second;
//             s2c.get_qtype(rqt)[it2->first] = it2->second;
//             s2.get_qtype(rqt).erase(it2);
//             it1 = s1.get_qtype(lqt).erase(it1);
//         }else{
//             it1++;
//         }
//     }
//     return std::vector<Shape>{s1,s1c,s2,s2c};
// }

// Shape Transform::prod_shape_res(const Shape& s1, const Shape& s2){
//     auto shapes = Transform::prod_shape_div(s1,s2);
//     return Transform::sum_shape_res(shapes[0], shapes[2]);
// }

// Shape Transform::sum_shape_res(const Shape& s1, const Shape& s2){
//     Shape newsh;
//     Int pos = 0;
//     std::array<QType, 2> qta{{QType::down, QType::up}};
//     for (auto qt: qta){
//         for(auto x: s1.get_qtype(qt)){
//             newsh.get_qtype(qt)[x.first] = pos++;
//         }
//         for(auto x: s2.get_qtype(qt)){
//             if (s1.get_qtype(qt).find(x.first) == s1.get_qtype(qt).end()){
//                 newsh.get_qtype(qt)[x.first] = pos++;
//             } 
//         }
//     }
//     return newsh;
// }

// Shape Transform::transpose(Shape sh){
//     std::swap(sh.get_qtype(QType::up), sh.get_qtype(QType::down)); 
//     return sh;
// }


// Int Shape::get_pos(const Qubit& qub, QType qt) const { 
//     return get_qtype(qt).at(qub);
// }


// Int Transform::index_shape_change(Int id, const Shape& oldsh, const Shape& subsh){
//     Int new_id=0;
//     std::array<QType, 2> qta{{QType::up, QType::down}};
//     for (auto qt: qta){
//         for(auto qub: subsh.get_qtype(qt)){
//             if (bit_on_pos(id, oldsh.get_pos(qub.first, qt)) != 0){
//                 new_id += (1 << qub.second);
//             }
//         }
//     }
//     return new_id;
// }



// Int Transform::index_shape_change_back(Int id, const Shape& sh){
//     return Transform::index_shape_change(id, sh, Shape{sh.get_qtype_qubits(QType::up), sh.get_qtype_qubits(QType::down)});
// }

// Int Transform::bit_on_pos(Int val, Int pos ){
//     return (val >> pos) & 1;
// }

// Int Transform::index_sum(Int val){
//     Int i = 0;
//     while (val >0){
//         i += val & 1;
//         val = val >> 1;
//     }
//     return i;
// }

// Shape prod(const Shape& shl, const Shape& shr){
//     int intersect = ( shr.pos_up.m & shl.pos_down.m );
//     // breakpoint();
//     mask up = shl.pos_up.m | (shr.pos_up.m ^ intersect);
//     std::cerr << up.m << '\n';
//     return Shape(shl.pos_up.m | (shr.pos_up.m ^ intersect), 
//                  shr.pos_down.m | (shl.pos_down.m ^ intersect));
// }

// Int Transform::change_on_pos(Int index, Int pos, Int bit){
//     return (bit == 1) ? (index | (1<<pos)) : (index & ~(1<<pos));
// }


// std::ostream& operator<<(std::ostream& os, const Shape& sh){
//     os << "up  : ";
//     for (auto x: sh.get_qtype(QType::up))
//         os << x.first << " ";
//     os << "\ndown: ";
//     for (auto x: sh.get_qtype(QType::down))
//         os << x.first << " ";
//     return os << "\n";
// }

// bool operator==(const Tensor& Tl, const Tensor& Tr){
//     if (!(Tl.get_shape() == Tr.get_shape())){
//         return false;
//     }
//     for (int i = 0; i < Tl.size(); i++ ){
//         if (Tl[i] != Tr[Transform::index_shape_change(i, Tl.get_shape(), Tr.get_shape())]){
//             return false;
//         }
//     }
//     return true;
// }


// bool compare(const Tensor& Tl, const Tensor& Tr, double pres){
//     if (!(Tl.get_shape() == Tr.get_shape())){
//         return false;
//     }
//     for (int i = 0; i < Tl.size(); i++ ){
//         DataType d = Tl[i] - Tr[Transform::index_shape_change(i, Tl.get_shape(), Tr.get_shape())];
//         if (std::abs(d) > pres){
//             return false;
//         }
//     }
//     return true;
// }
// std::ostream& operator<<(std::ostream& os, const Tensor& T){
//     os << "[ ";
//     for(int i = 0; i < T.size(); i++ ){
//         os << T.get_conv_sorted(i) << " ";
//     }
//     return os << "]\n";
// }

