#include "inc/Tensors/__init__.h"
// #include "inc/Tensors/__init__.h"

#include <algorithm>
#include <array>

Shape::Shape(const Qubits& up, const Qubits& down){
    Int pos=0;
    for (auto x: up){
        this->pos_up[x] = pos;
        pos++;
    }
    for (auto x: down){
        this->pos_down[x] = pos;
        pos++;
    }
};

// void Shape::transpose(const Qubits& qubs){
//     for (auto qub: qubs){
//         auto itu = this->pos_up.find(qub);
//         auto itd = this->pos_down.find(qub);
//         if (itu != pos_up.end() && itd != pos_down.end()){
//             std::swap(itu->second, itd->second);
//         }else if (itu != pos_up.end()){
//             pos_down[itu->first] = itu->second;
//             pos_up.erase(itu);
//         }else if (itd != pos_down.end()){
//             pos_up[itd->first] = itd->second;
//             pos_down.erase(itd);
//         }
//     }
// }

std::map<Qubit, Int>& Shape::get_qtype(QType qt){
    switch (qt){
        case QType::up:
            return pos_up;
        case QType::down:
            return pos_down;
        case QType::cup:
            return pos_up_conv;
        default:
            return pos_down_conv;
    }
}

const std::map<Qubit, Int>& Shape::get_qtype(QType qt) const{
    switch (qt){
        case QType::up:
            return pos_up;
        case QType::down:
            return pos_down;
        case QType::cup:
            return pos_up_conv;
        default:
            return pos_down_conv;
    }
}

void Shape::to_conv(const Qubits& qubs){
    // TODO
    if (pos_down_conv.size() + pos_up_conv.size() != 0 ){
        return;
    } 
    for (auto qub: qubs){
        auto itu = this->pos_up.find(qub);
        auto itd = this->pos_down.find(qub);
        if (itu != pos_up.end() && itd != pos_down.end()){
            pos_up_conv[itu->first] = itu->second;
            pos_down_conv[itd->first] = itd->second;
            pos_down.erase(itd);
            pos_up.erase(itu);
        } else{
            // TODO
            std::cerr << "wanrngin: nor a pair -> ignore";
        }
    }
}

Shape prod_shape_fin(const Shape& s1, const Shape& s2){
    Shape newsh;
    Int pos = 0;
    QType lqt = QType::down;
    QType rqt = QType::up;
    for(auto x: s1.get_qtype(rqt)){
        newsh.get_qtype(rqt)[x.first] = pos++;
    }
    for(auto x: s2.get_qtype(lqt)){
        newsh.get_qtype(lqt)[x.first] = pos++;
    }

    for(auto x: s1.get_qtype(lqt)){
        if (s2.get_qtype(rqt).find(x.first) == s2.get_qtype(rqt).end()){
            newsh.get_qtype(lqt)[x.first] = pos++;
        } 
    }

    for(auto x: s2.get_qtype(rqt)){
        if (s1.get_qtype(lqt).find(x.first) == s1.get_qtype(lqt).end()){
            newsh.get_qtype(rqt)[x.first] = pos++;
        }
    }
    return newsh;
}


std::pair<Shape, Shape> prod_shape(const Shape& _s1, const Shape& _s2){
    Shape s1{_s1};
    Shape s2{_s2};
    QType lqt = QType::down;
    QType lcqt = QType::cdown;
    QType rqt = QType::up;
    QType rcqt = QType::cup;
    for(auto it1=s1.get_qtype(lqt).begin(); it1 != s1.get_qtype(lqt).end();){
        auto it2 = s2.get_qtype(rqt).find(it1->first);
        if (it2 != s2.get_qtype(rqt).end()){
            s1.get_qtype(lcqt)[it1->first] = it1->second;
            s2.get_qtype(rcqt)[it2->first] = it2->second;
            s2.get_qtype(rqt).erase(it2);
            it1 = s1.get_qtype(lqt).erase(it1);
        }else{
            it1++;
        }
    }
    return std::make_pair(s1,s2);
}

Shape sum_shape_fin(const Shape& s1, const Shape& s2){
    Shape newsh;
    Int pos = 0;

    std::array<QType, 2> qta{{QType::up, QType::down}};
    for (auto qt: qta){
        for(auto x: s1.get_qtype(qt)){
            newsh.get_qtype(qt)[x.first] = pos++;
        }
        for(auto x: s2.get_qtype(qt)){
            if (s1.get_qtype(qt).find(x.first) == s1.get_qtype(qt).end()){
                newsh.get_qtype(qt)[x.first] = pos++;
            } 
        }
    }
    return newsh;
}

Shape transpose(Shape sh ) {
    std::swap(sh.get_qtype(QType::up), sh.get_qtype(QType::down)); 
    return sh;
}


Int Shape::get_pos(const Qubit& qub, QType qt) const { 
    return get_qtype(qt).at(qub);
}

bool operator==(const Shape& sl, const Shape& sr){
    Int ls = sl.size();
    Int rs = sr.size();
    if (ls != rs){
        return false;
    }
    Int pos;
    std::array<QType, 2> qta{{QType::up, QType::down}};
    for (auto qt: qta){
        auto itl = sl.get_qtype(qt).begin();
        auto itr = sr.get_qtype(qt).begin();
        for (Int i=0; i<ls; i++){
            if (itl->first != itr->first){
                return false;
            }
        }
    }
    return true;
}



Int Transform::to_sub_shape(Int id, const Shape& oldsh, const Shape& subsh){
    Int new_id=0;
    std::array<QType, 2> qta{{QType::up, QType::down}};
    for (auto qt: qta){
        for(auto qub: subsh.get_qtype(qt)){
            if (bit_on_pos(id, oldsh.get_pos(qub.first, qt)) != 0){
                new_id += (1 << qub.second);
            }
        }
    }
    return new_id;
}

Int Transform::bit_on_pos(Int val, Int pos ){
    return (val >> pos) & 1;
}

Int Transform::index_sum(Int val){
    Int i = 0;
    while (val >0){
        i += val & 1;
        val = val >> 1;
    }
    return i;
}

Int Transform::change_on_pos(Int index, Int pos, Int bit){
    return (bit == 1) ? (index | (1<<pos)) : (index & ~(1<<pos));
}

Int Transform::conv_id_for_prod(Int conv_id, const Shape& sh){
    Int new_id=0;
    std::array<QType, 2> qta{{QType::cup, QType::cdown}};
    for (auto qt: qta){
        for(auto qub: sh.get_qtype(qt)){
            if (bit_on_pos(conv_id, sh.get_pos(qub.first, qt)) != 0){
                new_id += (1 << qub.second);
            }
        }
    }
    return new_id;
}
Int Transform::conv_id_for_conv(Int conv_id, const Shape& sh){
    Int new_id=0;
    for(auto qub: sh.get_qtype(QType::cup)){
        if (bit_on_pos(conv_id, sh.get_pos(qub.first, QType::cup)) != 0){
            new_id += (1 << qub.second);
            new_id += (1 << sh.get_pos(qub.first, QType::cdown));

        }
    }
    return new_id;
}

std::ostream& operator<<(std::ostream& os, const Shape& sh){
    os << "up  : ";
    for (auto x: sh.get_qtype(QType::up))
        os << x.first << " ";
    os << "\ndown: ";
    for (auto x: sh.get_qtype(QType::down))
        os << x.first << " ";
    os << "\ncup  : ";
    for (auto x: sh.get_qtype(QType::cup))
        os << x.first << " ";
    os << "\ncdown: ";
    for (auto x: sh.get_qtype(QType::cdown))
        os << x.first << " ";
    return os << "\n";
}



// ----------------------------------BIN TOOLS------------------------------

// bool is_power_2(Int l){
//     Int x = 1;
//     while(x < l){
//         x = x << 1;
//     }
//     return (x = l);
// }

// Int find_power_2(Int l){
//     Int x = 1;
//     Int n = 0;
//     while(x < l){
//         x = x << 1;
//         n++;
//     }
//     return n;
// }



// Int del_on_pos(Int val, IntArr pos){
//     Int i = 0;
//     Int j = 0;
//     Int j10 = 2;
//     std::sort(pos.begin(), pos.end());
//     while(i < pos.size()){
//         if (pos[i] == j){
//             val = ((val / j10) << (j - i)) + val % (j10/2);
//             i++;
//         }else{
//             j10 = j10 << 1;
//         }
//         j++;
//     }
//     return val;
// }

// Int bit_on_pos(Int val, IntArr positions){
//     Int x = 0;
//     for (auto pos=positions.rbegin(); pos != positions.rend(); pos++)
//         x = (x<<1) + bit_on_pos(val, *pos);
//     return x;
// }

// Int change_on_pos(Int value, IntArr positions, Int bits){
//     for (Int i=0; i<positions.size(); i++)
//         value = change_on_pos(value, positions[i], bit_on_pos(bits, i));
//     return value;
// }
  