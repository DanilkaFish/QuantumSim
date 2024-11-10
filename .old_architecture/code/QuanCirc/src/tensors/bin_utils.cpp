#include <code/QuanCirc/inc/tensors/bin_utils.h>
#include <algorithm>

// ----------------------------------BIN TOOLS------------------------------

bool is_power_2(int l){
    int x = 1;
    while(x < l){
        x = x << 1;
    }
    return (x = l);
}

int find_power_2(int l){
    int x = 1;
    int n = 0;
    while(x < l){
        x = x << 1;
        n++;
    }
    return n;
}

int bit_on_pos(int val, int pos ){
    return (val >> pos) & 1;
}

int change_on_pos(int index, int pos, int bit){
    return (bit == 1) ? (index | (1<<pos)) : (index & ~(1<<pos));
}

int del_on_pos(int val, IntArr pos){
    int i = 0;
    int j = 0;
    int j10 = 2;
    std::sort(pos.begin(), pos.end());
    while(i < pos.size()){
        if (pos[i] == j){
            val = ((val / j10) << (j - i)) + val % (j10/2);
            i++;
        }else{
            j10 = j10 << 1;
        }
        j++;
    }
    return val;
}

int bit_on_pos(int val, IntArr positions){
    int x = 0;
    for (auto pos=positions.rbegin(); pos != positions.rend(); pos++)
        x = (x<<1) + bit_on_pos(val, *pos);
    return x;
}

int change_on_pos(int value, IntArr positions, int bits){
    for (int i=0; i<positions.size(); i++)
        value = change_on_pos(value, positions[i], bit_on_pos(bits, i));
    return value;
}
  