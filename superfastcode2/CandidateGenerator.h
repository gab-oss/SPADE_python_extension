#ifndef SPADE_CANDIDATEGENERATOR_H
#define SPADE_CANDIDATEGENERATOR_H

#include <list>
#include "EquivalenceClass.h"
#include "Pattern.h"
#include "IdList.h"

class CandidateGenerator {
public:
    std::vector<Pattern *> *generateCandidates(Pattern *p1, Pattern *p2, double minSupport);

    IdList *join(Pattern *extension, EquivalenceClass *e1, EquivalenceClass *e2);
};


#endif //SPADE_CANDIDATEGENERATOR_H
