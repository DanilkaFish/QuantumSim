#ifndef _ERRORS
#define _ERRORS
#include "code/alias.h"
#include <string>

void error_qubits_range(IntArr qubits, int n_qubits);
void error_qubits_coinc(IntArr qubits);
void tensor_error(int l);
void custom_error(const std::string& s);
#endif