#ifndef COLOURQUAD_H
#define COLOURQUAD_H
//Colour quad byte Library.
//Author: Taylor Phillips - taylorstone.p@gmail.com
//Date: 26/01/2021
//Potential Work: 
//	- Add more functionality to member function, i.e. HSV conversion, H, S and V shifting


class colour_quad
{
public:
	unsigned char quad[4];
	colour_quad();
	colour_quad(const unsigned char& value);
	colour_quad(const unsigned char&& value);
	colour_quad(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a);
	~colour_quad();
	unsigned char r();
	unsigned char g();
	unsigned char b();
	unsigned char a();
	void set(const unsigned char& value);
	void set(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a);
	void blend();
	colour_quad& operator=(const colour_quad& other);
};



#endif