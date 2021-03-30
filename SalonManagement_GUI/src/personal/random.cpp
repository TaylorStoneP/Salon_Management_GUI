#include "random.h"

random* random::instance = nullptr;

random* random::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new random();
    }
    return instance;
}

random::random() :seed(((int)time(0) % 1000)) { instance = this; srand(seed); }

int random::rand_int(int min, int max)
{
    //srand(seed);  //caused same number to repeat, unwanted output - left here for archival reasons.
	return (rand() % (max + 1)) + min;
}