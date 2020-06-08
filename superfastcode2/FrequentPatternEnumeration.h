#ifndef SPADE_FREQUENTPATTERNENUMERATION_H
#define SPADE_FREQUENTPATTERNENUMERATION_H

#include "CandidateGenerator.h"
#include "EquivalenceClass.h"
#include <map>

class FrequentPatternEnumeration {
    CandidateGenerator *candidateGenerator;
    double minSupport;
    int frequentPatternCount = 0;
	std::vector<Pattern *> *frequentPatterns = new std::vector<Pattern *>;

    void insertClassByPrefix(EquivalenceClass *eq, EquivalenceClass *eqX, EquivalenceClass *eqY);

public:
    FrequentPatternEnumeration(CandidateGenerator *candidateGenerator, double minSupport) : candidateGenerator(
            candidateGenerator), minSupport(minSupport) {}

    void setFrequentPatterns(int frequentPatternCount) {
        this->frequentPatternCount = frequentPatternCount;
    }

	std::vector<Pattern *> *getFrequentPatterns() {
        return frequentPatterns;
    }

	int getFrequentPatternCount() {
		return frequentPatternCount;
	}

    void execute(EquivalenceClass *eq, bool depthFirst);
};


#endif //SPADE_FREQUENTPATTERNENUMERATION_H
