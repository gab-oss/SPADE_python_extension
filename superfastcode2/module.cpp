#include <Windows.h>
#include <pybind11/pybind11.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Spade.h"

void frequent_patterns_search(std::string filepath, double minSupport, bool depthFirst) {
	auto *spade = new Spade();
	spade->run(filepath, minSupport, depthFirst);
	//spade->printResults();
}

namespace py = pybind11;

PYBIND11_MODULE(spade, m) {
    m.def("frequent_patterns_search", &frequent_patterns_search, R"pbdoc(
        Compute a hyperbolic tangent of a single argument expressed in radians.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif
}