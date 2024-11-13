#ifndef _BIN_UTILS
#define _BIN_UTILS
#include "stddata.h"


bool is_power_2(int l);
int  find_power_2(int l);

int  bit_on_pos(int val, int pos);
int  bit_on_pos(int val, std::vector<int> positions);

int  del_on_pos(int val, int pos);
int  del_on_pos(int val, std::vector<int> posistions);

int  change_on_pos(int value, int pos, int bits);
int  change_on_pos(int value, std::vector<int> positions, int bits);

#endif