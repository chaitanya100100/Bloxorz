#include "headers.h"
#include "noedit.h"
#include "block.h"

Block::Block(){}

Block::Block(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c)
{
    this->initialize(pos, dim, rot, c);
}

void Block::initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c)
{
    this->pos = pos;
    this->dim = dim;
    this->rot = rot;
    this->color = c;

    float x = dim.x;
    float y = dim.y;
    float z = dim.z;

    GLfloat vertex_buffer_data[] = {
        0,0,0, x,0,0, x,y,0,
        0,0,0, x,y,0, 0,y,0,

        0,0,z, x,0,z, x,y,z,
        0,0,z, x,y,z, 0,y,z,

        0,0,0, 0,y,0, 0,y,z,
        0,0,0, 0,y,z, 0,0,z,

        x,0,0, x,y,0, x,y,z,
        x,0,0, x,y,z, x,0,z,

        0,0,0, x,0,0, x,0,z,
        0,0,0, x,0,z, 0,0,z,

        0,y,0, x,y,0, x,y,z,
        0,y,0, x,y,z, 0,y,z
    };
    float r = c.r;
    float g = c.g;
    float b = c.b;
    GLfloat color_buffer_data[] = {
        r,g,b, 0,0,0, r,g,b,
        r,g,b, r,g,b, 0,0,0,

        r,g,b, 0,0,0, r,g,b,
        r,g,b, r,g,b, 0,0,0,

        r,g,b, 0,0,0, r,g,b,
        r,g,b, r,g,b, 0,0,0,

        r,g,b, 0,0,0, r,g,b,
        r,g,b, r,g,b, 0,0,0,

        r,g,b, 0,0,0, r,g,b,
        r,g,b, r,g,b, 0,0,0,

        r,g,b, 0,0,0, r,g,b,
        r,g,b, r,g,b, 0,0,0
    };
    /*
    float rr = colors[RED].r;
    float rg = colors[RED].g;
    float rb = colors[RED].b;

    float gr = colors[GREEN].r;
    float gg = colors[GREEN].g;
    float gb = colors[GREEN].b;

    float br = colors[BLUE].r;
    float bg = colors[BLUE].g;
    float bb = colors[BLUE].b;

    GLfloat color_buffer_data[] = {
        rr,rg,rb, rr,rg,rb, rr,rg,rb,
        rr,rg,rb, rr,rg,rb, rr,rg,rb,

        rr,rg,rb, rr,rg,rb, rr,rg,rb,
        rr,rg,rb, rr,rg,rb, rr,rg,rb,

        gr,gg,gb, gr,gg,gb, gr,gg,gb,
        gr,gg,gb, gr,gg,gb, gr,gg,gb,

        gr,gg,gb, gr,gg,gb, gr,gg,gb,
        gr,gg,gb, gr,gg,gb, gr,gg,gb,

        br,bg,bb, br,bg,bb, br,bg,bb,
        br,bg,bb, br,bg,bb, br,bg,bb,

        br,bg,bb, br,bg,bb, br,bg,bb,
        br,bg,bb, br,bg,bb, br,bg,bb
    };
    */
    /*
    int n = 6*2*3;
    GLfloat color_buffer_data[3*n];

    for(int i=0; i<n; i++)
    {
        color_buffer_data[3*i] = r;
        color_buffer_data[3*i+1] = g;
        color_buffer_data[3*i+2] = b;
    }
    */
    vao = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}


void Block::draw(glm::mat4 M)
{
    glm::mat4 VP = (proj_type?Matrices.projectionP:Matrices.projectionO) * Matrices.view;

    glm::mat4 translate = glm::translate (pos);
    glm::mat4 yaw = glm::rotate(rot.z, glm::vec3(0,0,1));
    glm::mat4 pitch = glm::rotate(rot.x, glm::vec3(1,0,0));
    glm::mat4 roll = glm::rotate(rot.y, glm::vec3(0,1,0));

    M = M * translate * roll * pitch * yaw;
    Matrices.model = M;
    glm::mat4 MVP = VP * Matrices.model;

    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(vao);
}
Block::~Block()
{
    delete vao;
}


Sprite::Sprite(){}
Sprite::Sprite(glm::vec3 pos, glm::vec3 rot)
{
    this->initialize(pos, rot);
}

void Sprite::initialize(glm::vec3 pos, glm::vec3 rot)
{
    this->pos = pos;
    this->rot = rot;
    (this->blocks).clear();
}

void Sprite::draw(glm::mat4 M)
{
    glm::mat4 translate = glm::translate (pos);
    glm::mat4 yaw = glm::rotate(rot.z, glm::vec3(0,0,1));
    glm::mat4 pitch = glm::rotate(rot.x, glm::vec3(1,0,0));
    glm::mat4 roll = glm::rotate(rot.y, glm::vec3(0,1,0));
    M = M * translate * roll * pitch * yaw;

    for(vector<Block*>::iterator it = blocks.begin(); it!=blocks.end(); it++)
        (*it)->draw(M);
}
void Sprite::add_block(Block * b)
{
    blocks.push_back(b);
}
Sprite::~Sprite()
{
    for(int i=0; i<blocks.size(); i++)
        delete blocks[i];
}
