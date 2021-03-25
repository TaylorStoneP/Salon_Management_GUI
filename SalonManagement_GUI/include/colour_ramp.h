#ifndef COLOUR_RAMP_H
#define COLOUR_RAMP_H
#include "colourquad.h"
#include "llist.h"
float lerp(float v0, float v1, float t);




class colour_ramp
{
	class colour_ramp_point
	{
	public:
		colour_quad colour;
		float pos;
		colour_ramp_point(colour_quad col = colour_quad(0, 0, 0, 0), float position = 0);
	};
public:
	llist<colour_ramp_point> colours;
	colour_ramp();
	void add_stamp(const colour_quad& colour, float position);
	void add_band(const colour_quad& colour, float end_position);
	colour_quad lerp_colours(float p);
};

class grey_ramp
{
	class grey_ramp_point
	{
	public:
		float grey;
		float pos;
		grey_ramp_point(float grey = 0, float position = 0);
	};
public:
	llist<grey_ramp_point> greys;
	grey_ramp();
	void add_stamp(float grey, float position);
	void add_band(float grey, float end_position);
	float lerp_colours(float p);
};

#endif