#include "colors.h"

#ifndef BLOCK
#define BLOCK

class SuperBlock;

class Block
{
    private:
        VAO * vao;
        glm::vec3 pos;
        glm::vec3 dim;
        glm::vec3 rot;
        Color color;
    public:
        Block();
        Block(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c);
        void initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c);
        void draw(glm::mat4 M);
        ~Block();
};

#endif


#ifndef SPRITE
#define SPRITE

class Sprite
{
    private:
        vector<Block*> blocks;
        glm::vec3 pos;
        glm::vec3 rot;
    public:
        friend class SuperBlock;
        Sprite();
        Sprite(glm::vec3 pos, glm::vec3 rot);
        void initialize(glm::vec3 pos, glm::vec3 rot);
        void draw(glm::mat4 M);
        void add_block(Block * b);
        ~Sprite();
};

#endif
