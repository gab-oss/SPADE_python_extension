#include <Windows.h>
#include <pybind11/pybind11.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Event.h"


void frequent_patterns_search(std::string filepath) {
    // load file to a list of Event objects
    // eventually should only contain algorithm's main function call with loading moved to SequenceDatabase > loadFile(...) (?)
    std::string line;
    std::ifstream myfile(filepath);
    std::list<Event*> events; // DANE
    if (myfile.is_open())
    {
        while (std::getline(myfile, line))
        {
            std::stringstream lineStream(line);
            int seqId, numItems, item;
            std::string eventId; // convertion to unix time (int)?
            std::list<int> items;
            lineStream >> seqId;
            lineStream >> eventId;
            lineStream >> numItems;
            for (int i = 0; i < numItems; ++i) {
                lineStream >> item;
                items.push_back(item);
            }
            events.push_back(new Event(seqId, eventId, items)); 
        } 
        myfile.close();
    }
    else std::cout << "Unable to open file"; // should throw
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