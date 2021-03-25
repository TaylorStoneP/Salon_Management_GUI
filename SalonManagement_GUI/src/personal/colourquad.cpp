#include "colourquad.h"
colour_quad::colour_quad(){ quad[0] = 0;quad[1] = 0;quad[2] = 0;quad[3] = 0; }
colour_quad::colour_quad(const unsigned char& value){ quad[0] = value; quad[1] = value; quad[2] = value; quad[3] = value; }
colour_quad::colour_quad(const unsigned char&& value){ quad[0] = value; quad[1] = value; quad[2] = value; quad[3] = value; }
colour_quad::colour_quad(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a){ quad[0] = r; quad[1] = g; quad[2] = b; quad[3] = a; }
colour_quad::~colour_quad() {}
unsigned char colour_quad::r() { return quad[0]; }
unsigned char colour_quad::g() { return quad[1]; }
unsigned char colour_quad::b() { return quad[2]; }
unsigned char colour_quad::a() { return quad[3]; }
void colour_quad::set(const unsigned char& value) { quad[0] = value; quad[1] = value; quad[2] = value; quad[3] = value; }
void colour_quad::set(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a) { quad[0] = r; quad[1] = g; quad[2] = b; quad[3] = a; }
void colour_quad::blend() { const unsigned char g((quad[0] + quad[1] + quad[2] / 3)); set(g); }
colour_quad& colour_quad::operator=(const colour_quad& other)
{
    // Guard self assignment
    if (this == &other)
        return *this;
    quad[0] = other.quad[0];
    quad[1] = other.quad[1];
    quad[2] = other.quad[2];
    quad[3] = other.quad[3];
    
    return *this;
}
