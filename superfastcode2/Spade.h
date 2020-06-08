#ifndef SPADE_SPADE_HPP
#define SPADE_SPADE_HPP

#include <iostream>
#include <vector>
#include "EquivalenceClass.h"
#include "Pattern.h"

class Spade {
    std::vector<EquivalenceClass *> *frequentItems;

	std::map<int, std::vector<Pattern *> *> *frequentPatterns;

    std::vector<Pattern *> *getPatterns(std::vector<EquivalenceClass *> *frequentItems);

    int frequentPatternCount;

public:
	Spade() {
		frequentPatterns = new std::map<int, std::vector<Pattern *> *>;
		for (int i = 1; i < 10; i++)
			frequentPatterns->insert({ i, new std::vector<Pattern *> });
	}

    void run(std::string filepath, double sup, bool depthFirst);

	void addPatterns(std::vector<Pattern *> *patterns) {
		for (auto &pattern : *patterns) {
			frequentPatterns->at(pattern->getElements()->size())->push_back(pattern);
		}
	}

    void printResults() {
        std::cout << "Number of frequent patterns: " << frequentPatternCount << std::endl;
        
		int i = 1;
		for (auto &patternList : *frequentPatterns) {
			std::cout << i++ << "-patterns: ";
			for (auto &pattern : *patternList.second) {
				std::cout << "( ";
				for (auto el : *pattern->getElements()) {
					std::cout << el->getId();
					if((el + 1) != *pattern->getElements()->end())
						if((el+1)->isEqualRelation())
							std::cout << ", ";
						else
							std::cout << " -> ";
				}
				std::cout << "), sup:" << pattern->getSupport() << " ";
			}
			std::cout << std::endl;
		}
    }
};


#endif //SPADE_SPADE_HPP
