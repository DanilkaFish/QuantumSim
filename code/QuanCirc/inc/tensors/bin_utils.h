#ifndef _BIN_UTILS
#define _BIN_UTILS

#include "alias.h"


bool is_power_2(int l);
int  find_power_2(int l);

int  bit_on_pos(int val, int pos);
int  bit_on_pos(int val, IntArr positions);

int  change_on_pos(int value, int pos, int bits);
int  change_on_pos(int value, IntArr positions, int bits);

#endif