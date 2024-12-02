
#ifndef _QERROR
#define _QERROR
#include <exception>
#include <string>


class QException : public std::exception{

protected:
  std::string msg;

public:
  QException() : msg("QException") {};
  QException(const std::string& m) : msg(m){};
  QException(const std::string& m, const std::string& d)
  {
      msg = m + d;
  };
  ~QException() = default;

  const char *what() const throw()
  {
      return msg.c_str();
  }
};

#endif