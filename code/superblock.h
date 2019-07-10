#include "colors.h"

#ifndef SUPERBLOCK
#define SUPERBLOCK
class Game;

class SuperBlock
{
    private:
        VAO * vao;
        glm::vec3 pos, real_pos;
        glm::vec3 dim;
        Color color;
        int along;
        int rot_dir;
        float rem_rotation, done_rotation;
        int ix, iy;
    public:
        friend class Game;
        SuperBlock();
        SuperBlock(glm::vec3 pos, glm::vec3 dim, Color c, int a);
        void initialize(glm::vec3 pos, glm::vec3 dim, Color c, int a);
        void draw(glm::mat4 M);
        void move(int m);
        void update();
        glm::vec2 get_current_pos();
        glm::vec3 get_pos();
        glm::vec3 get_real_pos();
        ~SuperBlock();
};

extern int X,Y,Z;
extern int U, D, R, L, NO;
extern float rotation_unit;
extern SuperBlock superblock;

#endif
/*
class SuperBlock : public Sprite
{
    private:
        glm::mat4 rot_mat;
        glm::vec3 axis;
        glm::vec3 up;
    public:
        SuperBlock();
        SuperBlock(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, glm::vec3 axis, glm::vec3 up);
        void initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, glm::vec3 axis, glm::vec3 up);
        void draw(glm::mat4 M);
        void move(int m);
        void approx(glm::vec3 & v);
};

class SuperBlock : public Sprite
{
    private:
        glm::mat4 rotation;
        glm::mat4 translate;
    public:
        SuperBlock();
        SuperBlock(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c);
        void initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c);
        void draw(glm::mat4 M);
        void move(int m);
};


*/
