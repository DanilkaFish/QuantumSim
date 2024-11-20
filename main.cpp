#include <iostream>
#include <string>
#include <python3.12/Python.h>

int main()
{
  Py_Initialize();

  const double input = 5.0;

  PyObject *main = PyImport_AddModule("__main__");
  PyObject *dict = PyModule_GetDict(main);
//   std::string cur = ".";
//   Py_SetPath(std::wstring(cur.begin(), cur.end()).c_str());
  PyObject *module = PyImport_Import(PyUnicode_FromString("qiskit"));
  PyModule_AddObject(main, "mycl", module);

  PyObject *instance = PyRun_String("mycl.MyCl()", Py_eval_input, dict, dict);
  PyObject *result = PyObject_CallMethod(instance, "myfunc", (char *)"(O)" ,PyFloat_FromDouble(input));

  PyObject *error = PyErr_Occurred();
  if (error) {
    std::cerr << "Error occured in PyRun_String" << std::endl;
    PyErr_Print();
  }

  double ret = PyFloat_AsDouble(result);
  std::cout << ret << std::endl;

  Py_Finalize();
  return 0;
}