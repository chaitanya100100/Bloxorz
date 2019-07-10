#ifndef COLORSTRUCT
#define COLORSTRUCT

struct Color
{
    float r;
    float g;
    float b;
};
typedef struct Color Color;

#endif

void initialize_colors();

extern Color * colors;
extern int BLUE;
extern int RED;
extern int GREEN;
extern int SKYBLUE;
extern int BLACK;
extern int WHITE;
extern int GREY;
extern int ORANGE;
extern int DARKGREEN;
