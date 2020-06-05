#ifndef SPADE_FREQUENTPATTERNENUMERATION_H
#define SPADE_FREQUENTPATTERNENUMERATION_H

#include "CandidateGenerator.h"
#include "EquivalenceClass.h"
#include <map>

class FrequentPatternEnumeration {
    CandidateGenerator *candidateGenerator;
    int minSupport;
    int frequentPatterns = 0;
    int joinCount = 0;

    void insertClassByPrefix(EquivalenceClass *eq, EquivalenceClass *eqX, EquivalenceClass *eqY);

public:
    FrequentPatternEnumeration(CandidateGenerator *candidateGenerator, int minSupport) : candidateGenerator(
            candidateGenerator), minSupport(minSupport) {}

    void setFrequentPatterns(int frequentPatternCount) {
        frequentPatterns = frequentPatternCount;
    }

    int getFrequentPatterns() {
        return frequentPatterns;
    }

    int getJoinCount() {
        return joinCount;
    }

    void execute(EquivalenceClass *eq, bool depthFirst, std::map<int, std::map<int, int>> *coocMapAfter, std::map<int, std::map<int, int>> *coocMapEquals);
};


#endif //SPADE_FREQUENTPATTERNENUMERATION_H
