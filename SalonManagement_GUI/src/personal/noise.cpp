#include "noise.h"

noise* noise::instance = nullptr;
static const int p[512] = { 151,160,137,91,90,15,                 // Hash lookup table as defined by Ken Perlin.  This is a randomly
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,    // arranged array of all numbers from 0-255 inclusive.
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

float clamp(float min, float max, float num)
{
    return num > max ? max : num < min ? min : num;
}

float lerp(float v0, float v1, float t) {
    return (v0 * (1.0f - t)) + (v1 * t);
}

float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}
noise* noise::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new noise();
    }
    return instance;
}

noise::noise(int seed_in) :seed(seed_in) { instance = this; srand(seed); }

int hash(float x, float y)
{
    int aa = p[p[(int)x % 256] + (int)y % 256];
    int ab = p[p[(int)x % 256] + ((int)y + 1) % 256];
    int ba = p[p[((int)x + 1) % 256] + (int)y % 256];
    int bb = p[p[((int)x + 1) % 256] + ((int)y + 1) % 256];
    int hash = aa + ab + ba + bb + (int)x % 27398 + (int)y % 93621;
    hash *= sin(hash + x);
    hash *= cos(hash + y);
    return hash;
}

vec2 noise::gradVec2(vec2 position)
{
    int aa = p[p[(int)position.x%256]+(int)position.y%256];
    int ab = p[p[(int)position.x%256]+((int)position.y+1)%256];
    int ba = p[p[((int)position.x+1)%256]+(int)position.y%256];
    int bb = p[p[((int)position.x+1)%256]+((int)position.y+1)%256];
    int hash = aa + ab + ba + bb + (int)position.x % 27398 + (int)position.y % 93621;
    hash *= sin(hash+position.x);
    hash *= cos(hash+position.y);
    srand(seed+hash);
    return vec2((float)(-100.0+rand()%200)/100.0,(float)(-100.0+rand()%200)/100.0);
}
float noise::dotGridGradientVec2(int ix, int iy, float x, float y) {

    vec2 gradient = gradVec2(vec2(ix, iy));
    vec2 distance = vec2(x - (float)ix, y - (float)iy);
    return (gradient.dot(distance));
}

float noise::perlin2D(float x, float y, float frequencyX, float frequencyY, float amplitude, int octaves) {
    
    float value = 0;
    for (int i = 0; i < octaves; i++)
    {
        value+=(perlin2D(x,y,frequencyX/pow(2,i),frequencyY / pow(2, i),amplitude/pow(2,i+1)));
    }
    return value*1.2f;
}
float noise::perlin2D(float x, float y, float frequencyX, float frequencyY, float amplitude) {
    // Determine grid cell coordinates
    x /= frequencyX;
    y /= frequencyY;
    x += frequencyX;
    y += frequencyY;
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;
    // Determine interpolation weights
    float sx = x - (float)x0;
    float sy = y - (float)y0;
    sx = fade(sx);
    sy = fade(sy);
    // Interpolate between grid point gradients
    float n0, n1, n2, n3, ix0, ix1, value;

    n0 = dotGridGradientVec2(x0, y0, x, y);
    n1 = dotGridGradientVec2(x1, y0, x, y);
    n2 = dotGridGradientVec2(x0, y1, x, y);
    n3 = dotGridGradientVec2(x1, y1, x, y);
    ix0 = lerp(n0, n1, sx);

    ix1 = lerp(n2, n3, sx);

    value = lerp(ix0, ix1, sy);

    return value * amplitude;
}

void noise::setSeed(int seed)
{
    GetInstance()->seed = seed;
}

vec2 noise::genVec2(int x, int y)
{
    srand(seed+hash(x,y));
    //LOG_TRACE("1"+vec2(x,y).to_string_rect());
    float n_x = ((float)(rand() % 10000) / 10000.0f) + (float)x;
    float n_y = ((float)(rand() % 10000) / 10000.0f) + (float)y;
    //LOG_TRACE("2"+vec2(n_x,n_y).to_string_rect());
    return vec2(n_x, n_y);
}

float easeInOutExpo(float x){
  return x < 0 ? 0 : x>1 ? 0 : x < 0.5f ? (pow(2, 20 * x - 10) / 2) : ((2 - pow(2, -20 * x + 10)) / 2);
}
float easeInOutCubic(float x){
return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
}
float noise::cell2D(float x, float y, float frequency, float amplitude)
{
    x /= frequency;
    y /= frequency;
    x += frequency;
    y += frequency;
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;
    vec2 cells[9];
    cells[0] = genVec2(x0-1,y0-1);
    cells[1] = genVec2(x0-1,y0);
    cells[2] = genVec2(x0-1,y0+1);
    cells[3] = genVec2(x0,y0-1);
    cells[4] = genVec2(x0,y0);
    cells[5] = genVec2(x0,y0+1);
    cells[6] = genVec2(x0+1,y0-1);
    cells[7] = genVec2(x0+1,y0);
    cells[8] = genVec2(x0+1,y0+1);
    float min = 32000;
    float mag = 0;
    int index;
    for (int i = 0; i < 9; i++)
    {   
        //LOG_TRACE(cells[i].to_string_rect());
        //LOG_TRACE(vec2(abs(cells[i].x - x), abs(cells[i].y - y)).to_string_rect());
        mag = vec2(cells[i].x - x, cells[i].y - y).mag();
        if (mag < min)
        {
            min = mag;
            index = i;
        }
    }
    mag = vec2(cells[index].x - x, cells[index].y - y).mag();
    return amplitude*((mag)/1.2f);
}


