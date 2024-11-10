#ifndef _BIN_UTILS
#define _BIN_UTILS
#include "stddata.h"


bool is_power_2(int l);
int  find_power_2(int l);

int  bit_on_pos(int val, int pos);
int  bit_on_pos(int val, Positions positions);

int  del_on_pos(int val, int pos);
int  del_on_pos(int val, Positions posistions);

int  change_on_pos(int value, int pos, int bits);
int  change_on_pos(int value, Positions positions, int bits);

#endif