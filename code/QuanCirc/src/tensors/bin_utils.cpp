#include <code/QuanCirc/inc/tensors/bin_utils.h>
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
  