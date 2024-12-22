#ifndef RUNPYTHON
#define RUNPYTHON
#include <pybind11/embed.h> // everything needed for embedding
#include <pybind11/numpy.h>
#include <pybind11/complex.h>

namespace py = pybind11;

class RunPython
{
    public:
        static RunPython& getInstance()
        {
            static RunPython instance; // Guaranteed to be destroyed.
            return instance;
        }
    private:
        RunPython() { py::initialize_interpreter(); }                    // Constructor? (the {} brackets) are needed here.
        ~RunPython(){
            py::finalize_interpreter();
        }
        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are inaccessible(especially from outside), otherwise, you may accidentally get copies of
        // your singleton appearing.
    public:
        RunPython(RunPython const&) = delete;
        void operator=(RunPython const&)  = delete;
        
        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};

#endif

