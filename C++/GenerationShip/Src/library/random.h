#ifndef __Generation_Ship__random__
#define __Generation_Ship__random__

#include <stdio.h>
#include <iostream>
#include <random>
#include "../library/non_copyable.h"

class Random: public NonCopyable {
public:
    double GetRandom0_1();
	int GetRandom(int range);
private:
    std::uniform_real_distribution<double> mDistribution0_1 {0, 1};
    std::mt19937 mRandom;
};

#endif
