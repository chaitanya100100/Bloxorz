#include "headers.h"
#include "noedit.h"
#include "superblock.h"
#include "tile.h"
#include "game.h"

int X=0, Y=1, Z=2;
int U=1, D=2, R=3, L=4, NO=0;
float rotation_unit = 5.0f;

SuperBlock::SuperBlock(){}

SuperBlock::SuperBlock(glm::vec3 pos, glm::vec3 dim, Color c, int a)
{
    this->initialize(pos, dim, c, a);
}

glm::vec2 SuperBlock::get_current_pos()
{
    return glm::vec2(ix, iy);
}
glm::vec3 SuperBlock::get_pos()
{
    return pos;
}
glm::vec3 SuperBlock::get_real_pos()
{
    return real_pos;
}

void SuperBlock::initialize(glm::vec3 pos, glm::vec3 dim, Color c, int a)
{
    this->pos = pos;
    this->dim = dim;
    this->color = c;
    real_pos = pos;
    along = a;
    rot_dir = 0;
    rem_rotation = 0.0f;
    done_rotation = 0.0f;
    pair<int, int> pp = stage.get_initial_index();
    ix=pp.first;
    iy=pp.second;

    float x = dim.x/2;
    float y = dim.y/2;
    float z = dim.z/2;

    GLfloat vertex_buffer_data[] = {
        -x,-y,-z, x,-y,-z, x,-y,z,
        -x,-y,-z, -x,-y,z, x,-y,z,

        -x,y,-z, x,y,-z, x,y,z,
        -x,y,-z, -x,y,z, x,y,z,

        -x,-y,-z, -x,y,-z, -x,y,z,
        -x,-y,-z, -x,-y,z, -x,y,z,

        x,-y,-z, x,y,-z, x,y,z,
        x,-y,-z, x,-y,z, x,y,z,

        -x,-y,-z, x,-y,-z, x,y,-z,
        -x,-y,-z, -x,y,-z, x,y,-z,

        -x,-y,z, x,-y,z, x,y,z,
        -x,-y,z, -x,y,z, x,y,z
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

    vao = create3DObject(GL_TRIANGLES, 6*2*3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void SuperBlock::update()
{
    if(rot_dir!=NO)
    {
        done_rotation += rotation_unit;
        rem_rotation -= rotation_unit;
    }
    if(rot_dir!=NO && rem_rotation<=0.0f)
    {
        float x = tile_side_length;
        if(along==X)
        {
            if(rot_dir==L)
            {
                along = Z;
                pos = glm::vec3(-3*x/2, 0, x/2) + pos;
                ix--;
            }
            else if(rot_dir==R)
            {
                along = Z;
                pos = glm::vec3(3*x/2, 0, x/2) + pos;
                ix+=2;
            }
            else if(rot_dir==U)
            {
                along = X;
                pos = glm::vec3(0, x, 0) + pos;
                iy++;
            }
            else if(rot_dir==D)
            {
                along = X;
                pos = glm::vec3(0, -x, 0) + pos;
                iy--;
            }
        }
        else if(along==Y)
        {
            if(rot_dir==U)
            {
                along = Z;
                pos = glm::vec3(0, 3*x/2, x/2) + pos;
                iy+=2;
            }
            else if(rot_dir==D)
            {
                along = Z;
                pos = glm::vec3(0, -3*x/2, x/2) + pos;
                iy--;
            }
            if(rot_dir==R)
            {
                along = Y;
                pos = glm::vec3(x, 0, 0) + pos;
                ix++;
            }
            else if(rot_dir==L)
            {
                along = Y;
                pos = glm::vec3(-x, 0, 0) + pos;
                ix--;
            }
        }
        else if(along==Z)
        {
            if(rot_dir==L)
            {
                along = X;
                pos = glm::vec3(-3*x/2, 0, -x/2) + pos;
                ix-=2;
            }
            else if(rot_dir==R)
            {
                along = X;
                pos = glm::vec3(3*x/2, 0, -x/2) + pos;
                ix++;
            }
            else if(rot_dir==U)
            {
                along = Y;
                pos = glm::vec3(0, 3*x/2, -x/2) + pos;
                iy++;
            }
            else if(rot_dir==D)
            {
                along = Y;
                pos = glm::vec3(0, -3*x/2, -x/2) + pos;
                iy-=2;
            }
        }
        rot_dir = NO;
        game.check_after_step();
    }
}

void SuperBlock::draw(glm::mat4 M)
{
    glm::mat4 VP = (proj_type?Matrices.projectionP:Matrices.projectionO) * Matrices.view;

    glm::mat4 translate = glm::translate (pos);
    glm::mat4 rev;
    M = M * translate;

    glm::mat4 rotate(1.0f);
    if(along==Y)
        rotate = rotate * glm::rotate(glm::mat4(1.0f), float(-M_PI/2), glm::vec3(0,0,1));
    else if(along==Z)
        rotate = rotate * glm::rotate(glm::mat4(1.0f), float(-M_PI/2), glm::vec3(0,1,0));

    M = M * rotate;

    float x = tile_side_length;
    real_pos = pos;
    real_pos.z = 0;

    if(along==X)
    {
        if(rot_dir==R)
        {
            translate = glm::translate(glm::vec3(x, 0, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(0,1,0));
            rev = glm::translate(glm::vec3(-x, 0, x/2));
            M = M * translate * rotate * rev;
            real_pos.x += tile_side_length * (1-cos(done_rotation*M_PI/180) + 0.5*sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==L)
        {
            translate = glm::translate(glm::vec3(-x, 0, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(-M_PI*done_rotation/180.0f), glm::vec3(0,1,0));
            rev = glm::translate(glm::vec3(x, 0, x/2));
            M = M * translate * rotate * rev;
            real_pos.x -= tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==U)
        {
            translate = glm::translate(glm::vec3(0, x/2, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(-1,0,0));
            rev = glm::translate(glm::vec3(0, -x/2, x/2));
            M = M * translate * rotate * rev;
            real_pos.y += 0.5*tile_side_length * (1-cos(done_rotation*M_PI/180)+ sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==D)
        {
            translate = glm::translate(glm::vec3(0, -x/2, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(-M_PI*done_rotation/180.0f), glm::vec3(-1,0,0));
            rev = glm::translate(glm::vec3(0, x/2, x/2));
            M = M * translate * rotate * rev;
            real_pos.y -= 0.5*tile_side_length * (1-cos(done_rotation*M_PI/180)+ sin(done_rotation*M_PI/180));
        }
    }
    else if(along==Y)
    {
        if(rot_dir==R)
        {
            translate = glm::translate(glm::vec3(0, x/2, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(-1,0,0));
            rev = glm::translate(glm::vec3(0, -x/2, x/2));
            M = M * translate * rotate * rev;
            real_pos.x += 0.5*tile_side_length * (1-cos(done_rotation*M_PI/180)+ sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==L)
        {
            translate = glm::translate(glm::vec3(0, -x/2, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(1,0,0));
            rev = glm::translate(glm::vec3(0, x/2, x/2));
            M = M * translate * rotate * rev;
            real_pos.x -= 0.5*tile_side_length * (1-cos(done_rotation*M_PI/180)+ sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==U)
        {
            translate = glm::translate(glm::vec3(-x, 0, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(0,-1,0));
            rev = glm::translate(glm::vec3(x, 0, x/2));
            M = M * translate * rotate * rev;
            real_pos.y += tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==D)
        {
            translate = glm::translate(glm::vec3(x, 0, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(0,1,0));
            rev = glm::translate(glm::vec3(-x, 0, x/2));
            M = M * translate * rotate * rev;
            real_pos.y -= tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
    }
    else if(along==Z)
    {
        if(rot_dir==R)
        {
            //cout << pos.x << " " << pos.y << " " << pos.z << endl;
            translate = glm::translate(glm::vec3(-x, 0, -x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(0,1,0));
            rev = glm::translate(glm::vec3(x, 0, x/2));
            M = M * translate * rotate * rev;
            real_pos.x += tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==L)
        {
            translate = glm::translate(glm::vec3(-x, 0, x/2));
            rotate = glm::rotate(glm::mat4(1.0f), float(-M_PI*done_rotation/180.0f), glm::vec3(0,1,0));
            rev = glm::translate(glm::vec3(x, 0, -x/2));
            M = M * translate * rotate * rev;
            real_pos.x -= tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==U)
        {
            translate = glm::translate(glm::vec3(-x, x/2, 0));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(0,0,1));
            rev = glm::translate(glm::vec3(x, -x/2, 0));
            M = M * translate * rotate * rev;
            real_pos.y += tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
        else if(rot_dir==D)
        {
            translate = glm::translate(glm::vec3(-x, -x/2, 0));
            rotate = glm::rotate(glm::mat4(1.0f), float(M_PI*done_rotation/180.0f), glm::vec3(0,0,-1));
            rev = glm::translate(glm::vec3(x, x/2, 0));
            M = M * translate * rotate * rev;
            real_pos.y -= tile_side_length * (1-cos(done_rotation*M_PI/180)+ 0.5*sin(done_rotation*M_PI/180));
        }
    }

    Matrices.model = M;
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(vao);
}

void SuperBlock::move(int m)
{
    if(rot_dir!=NO)return;

    if(m==GLFW_KEY_UP)
    {
        rot_dir = U;
        rem_rotation = 90.0f;
        done_rotation = 0.0f;
    }
    else if(m==GLFW_KEY_DOWN)
    {
        rot_dir = D;
        rem_rotation = 90.0f;
        done_rotation = 0.0f;
    }
    else if(m==GLFW_KEY_LEFT)
    {
        rot_dir = L;
        rem_rotation = 90.0f;
        done_rotation = 0.0f;
    }
    else if(m==GLFW_KEY_RIGHT)
    {
        rot_dir = R;
        rem_rotation = 90.0f;
        done_rotation = 0.0f;
    }
}

SuperBlock::~SuperBlock()
{
    delete vao;
}
/*
SuperBlock::SuperBlock(){}
SuperBlock::SuperBlock(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c)
{
    initialize(pos, dim, rot, c);
}
void SuperBlock::initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c)
{
    Sprite::initialize(pos, rot);
    rot_mat = glm::mat4(1.0f);
}
void SuperBlock::draw(glm::mat4 M){}
void SuperBlock::move(int m){}
SuperBlock::SuperBlock(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, glm::vec3 axis, glm::vec3 up)
{
    initialize(pos, dim, rot, c, axis, up);
}

SuperBlock::SuperBlock(){}

SuperBlock::SuperBlock(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, glm::vec3 axis, glm::vec3 up)
{
    initialize(pos, dim, rot, c, axis, up);
}

void SuperBlock::initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, glm::vec3 axis, glm::vec3 up)
{
    Sprite::initialize(pos, rot);
    this->axis = axis;
    this->up = up;
    this->rot_mat = glm::mat4(1.0f);
    add_block(new Block(glm::vec3(0,0,0), dim, glm::vec3(0,0,0), c));
}
*/
/*

void SuperBlock::initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, glm::vec3 axis, glm::vec3 up)
{
    Sprite::initialize(pos, rot);
    this->axis = axis;
    this->up = up;
    this->rot_mat = glm::mat4(1.0f);
    add_block(new Block(glm::vec3(0,0,0), dim, glm::vec3(0,0,0), c));
}

void SuperBlock::approx(glm::vec3 & v)
{
    v.x = float(int(v.x*(10000+10))/10000);
    v.y = float(int(v.y*(10000+10))/10000);
    v.z = float(int(v.z*(10000+10))/10000);
}

void SuperBlock::draw(glm::mat4 M)
{
    glm::mat4 translate = glm::translate (pos);

    glm::mat4 yaw = glm::rotate(rot.z, glm::vec3(0,0,1));
    glm::mat4 pitch = glm::rotate(rot.x, glm::vec3(1,0,0));
    glm::mat4 roll = glm::rotate(rot.y, glm::vec3(0,1,0));

    M = M * translate * rot_mat;

    for(vector<Block*>::iterator it = blocks.begin(); it!=blocks.end(); it++)
        (*it)->draw(M);
}

bool compare_vec3(const glm::vec3 &vecA, const glm::vec3 &vecB)
{
 return (vecA[0] == vecB[0])
        && (vecA[1] == vecB[1])
        && (vecA[2] == vecB[2]);
}
//vec = glm::vec3(rotationMat * glm::vec4(vec, 1.0));
void SuperBlock::move(int m)
{
    glm::vec3 r;
    if(m==GLFW_KEY_UP)
    {
        r = glm::vec3(0,1,0);
    }
    else if(m==GLFW_KEY_DOWN)
    {
        r = glm::vec3(0,-1,0);
    }
    else if(m==GLFW_KEY_LEFT)
    {
        r = glm::vec3(-1,0,0);
    }
    else if(m==GLFW_KEY_RIGHT)
    {
        r = glm::vec3(1,0,0);
    }
    r = glm::cross(glm::vec3(0,0,1), r);



    up = glm::vec3(glm::rotate(glm::mat4(1.0f), float(1.0*M_PI/2.0),r) * glm::vec4(up, 1.0f));
    axis = glm::vec3(glm::rotate(glm::mat4(1.0f), float(1.0*M_PI/2.0),r) * glm::vec4(axis, 1.0f));
    approx(up);
    approx(axis);

    //cout << r.x << " " << r.y << " " << r.z << endl;
    //cout << up.x << " " << up.y << " " << up.z << endl;
    //glm::vec4 up4 = glm::vec4(up, 1.0f);
    //cout << up4.x << " " << up4.y << " " << up4.z << " " << up4.w << endl;

    glm::mat4 ro = glm::rotate(glm::mat4(1.0f), float(-1.0f*M_PI/2.0f),r);
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            printf("%.6f ", ro[i][j]);
        }
        cout << endl;
    }


    //cout << up.x << " " << up.y << " " << up.z << endl;
    //cout << up.x << " " << up.y << " " << up.z << endl;
    //cout << endl;

    upn = glm::cross(r, up);
    axisn = glm::cross(r, axis);
    if(!((up==upn) || ((-1.0f*up)==upn)))
        up = upn;

}
*/
