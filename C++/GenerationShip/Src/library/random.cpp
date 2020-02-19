#include "random.h"

double Random::GetRandom0_1() {
    return mDistribution0_1(mRandom);
}

int Random::GetRandom(int range) {
    std::random_device rd;
	std::uniform_int_distribution<int> distribution{ 0, range - 1 };
    return distribution(rd);
}
