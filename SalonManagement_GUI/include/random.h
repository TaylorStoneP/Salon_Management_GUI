#ifndef RANDOM_H
#define RANDOM_H
#include <chrono>
class random
{
	static random* instance;
public:
	int seed;
	static random* GetInstance();
	random();
	int rand_int(int min, int max);
};

#endif