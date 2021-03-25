#ifndef NOISE_H
#define NOISE_H
#include <chrono>
#include "vector.h"
#include "random.h"
class noise
{
	static noise* instance;
public:
	int seed;
	static noise* GetInstance();
	noise(int seed = 1000);
	vec2 gradVec2(vec2 position);
	float dotGridGradientVec2(int ix, int iy, float x, float y);
	float perlin2D(float x, float y, float frequencyX, float frequencyY, float amplitude, int octaves);
	float perlin2D(float x, float y, float frequencyX=1, float frequencyY=1, float amplitude=1);
	static void setSeed(int seed);
	vec2 genVec2(int x, int y);
	float cell2D(float x, float y, float frequency, float amplitude);
};

float lerp(float v0, float v1, float t);
float clamp(float min, float max, float num);
float easeInOutExpo(float x);
float easeInOutCubic(float x);

#endif