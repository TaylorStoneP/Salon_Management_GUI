#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
#include <iostream>
#include <string>
inline double pi() { return std::atan(1) * 4; }
class vec2
{
public:
	float x;
	float y;
	vec2(float x = 0, float y = 0);
	float cross(vec2& rhs);
	float dot(vec2& rhs);
	float mag();
	float arg();
	float angle_between(vec2& rhs);
	std::string to_string_rect();
	std::string to_string_pol();
};

#endif
