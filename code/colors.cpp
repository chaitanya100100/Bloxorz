//#include "colors.h"

struct Color
{
    float r;
    float g;
    float b;
};
typedef struct Color Color;


Color * colors = new Color[50];

int BLUE = 0;
int RED = 1;
int GREEN = 2;
int SKYBLUE = 3;
int BLACK = 4;
int WHITE = 5;
int GREY = 6;
int ORANGE = 7;
int DARKGREEN = 8;

void initialize_colors()
{
    colors[BLUE].r = 0.0f;
    colors[BLUE].g = 0.0f;
    colors[BLUE].b = 1.0f;

    colors[RED].r = 1.0f;
    colors[RED].g = 0.0f;
    colors[RED].b = 0.0f;

    colors[GREEN].r = 0.0f;
    colors[GREEN].g = 1.0f;
    colors[GREEN].b = 0.0f;

    colors[GREY].r = 0.8f;
    colors[GREY].g = 0.8f;
    colors[GREY].b = 0.8f;

    colors[SKYBLUE].r = 0.6f;
    colors[SKYBLUE].g = 0.94f;
    colors[SKYBLUE].b = 0.94f;

    colors[ORANGE].r = 255.0/255.0;
    colors[ORANGE].g = 127.0/255.0;
    colors[ORANGE].b = 80.0/255.0;

    colors[DARKGREEN].r = 0/255.0;
    colors[DARKGREEN].g = 100.0/255.0;
    colors[DARKGREEN].b = 0.0/255.0;
}
