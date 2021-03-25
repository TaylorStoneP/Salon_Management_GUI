#include "vector.h"

vec2::vec2(float x, float y):x(x),y(y){}
float vec2::cross(vec2& rhs)
{
	return mag()*rhs.mag()*sin(angle_between(rhs));
}

float vec2::dot(vec2& rhs)
{
	return x * rhs.x + y * rhs.y;
}

float vec2::mag()
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float vec2::arg()
{
	float offset = (x<0?0.5*pi():0);
	if (x != 0)
	{

		return (y<0?-1:1)*(atan(abs(y) / abs(x))+offset);
		
	}
	else if (x == 0)
	{
		if (y > 0)
		{
			return 0.5 * pi();
		}
		else if(y<0)
		{
			return -0.5 * pi();
		}
	}
	return 0;
}

float vec2::angle_between(vec2& rhs)
{
	int offset = arg() > rhs.arg() ? 1 : -1;
	return acos(dot(rhs)/(mag()*rhs.mag()));
}

std::string vec2::to_string_rect()
{
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}
std::string vec2::to_string_pol()
{
	return "(" + std::to_string(mag()) + "," + std::to_string(arg()*180.0/pi()) + ")";
}