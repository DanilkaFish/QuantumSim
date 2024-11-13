#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <stdexcept>

/**
 * @brief Exceptions for any linalg functions
 */
class Exception: public std::runtime_error
{
public:
	using runtime_error::runtime_error;
};

#endif // EXCEPTION_H
