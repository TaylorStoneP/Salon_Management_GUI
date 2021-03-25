#include "colour_ramp.h"

colour_ramp::colour_ramp_point::colour_ramp_point(colour_quad col, float position):colour(col),pos(position){}

colour_ramp::colour_ramp(){}

void colour_ramp::add_stamp(const colour_quad& colour, float position)
{
	colours.add_back(colour_ramp_point(colour, position));
}

void colour_ramp::add_band(const colour_quad& colour, float end_position)
{
	float start_position = colours.count() > 0 ? colours[colours.count() - 1].pos : 0.0f;
	colours.add_back(colour_ramp_point(colour, start_position+0.000001f));
	colours.add_back(colour_ramp_point(colour, end_position-0.000001f));
}

colour_quad colour_ramp::lerp_colours(float p)
{
	int belowPosIndex=0;
	int abovePosIndex=colours.count()-1;
	float abovePos = 1;
	float belowPos = 0;
	float curPos=0;
	if (colours.count() > 2) {
		for (int i = 0; i < colours.count(); i++)
		{

			curPos = colours[i].pos;
			if (curPos > belowPos && curPos < p)
			{

				belowPos = curPos;
				belowPosIndex = i;
			}
			if (curPos<abovePos && curPos>p)
			{

				abovePos = curPos;
				abovePosIndex = i;
			}
		}
	}

	float normalisedPos = (p - belowPos) / (abovePos - belowPos);

	return colour_quad(	lerp(colours[belowPosIndex].colour.r(), colours[abovePosIndex].colour.r(),normalisedPos),
						lerp(colours[belowPosIndex].colour.g(), colours[abovePosIndex].colour.g(),normalisedPos),
						lerp(colours[belowPosIndex].colour.b(), colours[abovePosIndex].colour.b(),normalisedPos),
						lerp(colours[belowPosIndex].colour.a(), colours[abovePosIndex].colour.a(),normalisedPos));
}

grey_ramp::grey_ramp_point::grey_ramp_point(float grey, float position) :grey(grey), pos(position) {}

grey_ramp::grey_ramp() {}

void grey_ramp::add_stamp(float grey, float position)
{
	greys.add_back(grey_ramp_point(grey, position));
}

void grey_ramp::add_band(float grey, float end_position)
{
	float start_position = greys.count() > 0 ? greys[greys.count() - 1].pos : 0.0f;
	greys.add_back(grey_ramp_point(grey, start_position + 0.000001f));
	greys.add_back(grey_ramp_point(grey, end_position - 0.000001f));
}

float grey_ramp::lerp_colours(float p)
{
	int belowPosIndex = 0;
	int abovePosIndex = greys.count() - 1;
	float abovePos = 1;
	float belowPos = 0;
	float curPos = 0;
	if (greys.count() > 2) {
		for (int i = 0; i < greys.count(); i++)
		{

			curPos = greys[i].pos;
			if (curPos > belowPos && curPos < p)
			{

				belowPos = curPos;
				belowPosIndex = i;
			}
			if (curPos<abovePos && curPos>p)
			{

				abovePos = curPos;
				abovePosIndex = i;
			}
		}
	}

	float normalisedPos = (p - belowPos) / (abovePos - belowPos);

	return lerp(greys[belowPosIndex].grey, greys[abovePosIndex].grey, normalisedPos);

}