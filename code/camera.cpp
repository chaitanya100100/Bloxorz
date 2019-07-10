#include "headers.h"
#include "camera.h"
#include "controls.h"
#include "superblock.h"

Camera camera;
float camera_move_unit = 0.1f;
float camera_dir_change_unit = 0.02f;
int helicopter=GLFW_KEY_X, vertical=GLFW_KEY_V, tower=GLFW_KEY_B, follow=GLFW_KEY_C, block_view=GLFW_KEY_Z,
    mouse_view=GLFW_KEY_M, mouse_view_cs, drag_view=GLFW_KEY_N;

void Camera::initialize_camera()
{
    eye = glm::vec3(0, 0, 5);
    dir = glm::vec3(0, 0, -1);
    up = glm::vec3(0, 1, 0);
    cam_move_dir = 0;
    ori_move_dir = 0;
    proj_type = 1;
    view = follow;
    flag=0;
}

glm::mat4 Camera::get_view()
{
    if(proj_type==1)
        return glm::lookAt(eye, eye + dir, up);
    else
        return glm::lookAt(glm::vec3(0,0,5), glm::vec3(0,0,5) + glm::vec3(0,0,-1), glm::vec3(0,1,0));
}
int Camera::get_view_type()
{
    return view;
}
void Camera::set_mouse_view()
{
    int _w, _h;
    double x, y, w, h;
    glfwGetCursorPos (window, &x, &y);
    glfwGetWindowSize(window, &_w, &_h);

    w = _w;
    h = _h;
    x -= w/2;
    y -= h/2;
    y = -y;

    x = 2.0f*x/w;
    y = 2.0f*y/h;
    //dir_change(x, y);

    up = glm::vec3(0,0,1);
    glm::vec3 cr = glm::normalize(glm::cross(dir, up));
    up = glm::normalize(glm::cross(cr, dir));
    cr = glm::normalize(float(x)*cr + float(y)*up);
    dir += 0.005f*(cr-dir);
    dir = glm::normalize(dir);
    //up = glm::cross(new_dir, dir);
    //dir = glm::normalize(new_dir);
    up = glm::vec3(0,0,1);
}
void Camera::set_mouse_view_cs()
{
    int _w, _h;
    double x, y, w, h;
    glfwGetCursorPos (window, &x, &y);
    glfwGetWindowSize(window, &_w, &_h);
    //cout << x << " " << y << " " << _w << " " << _h << endl;
    //glfwSetCursorPos(window, x + 0.03f*(_w/2-x), y + 0.3f*(_h/2-y));

    w = _w;
    h = _h;
    x -= w/2;
    y -= h/2;
    y = -y;

    x = 2.0f*x/w;
    y = 2.0f*y/h;

    up = glm::vec3(0,0,1);
    glm::vec3 cr = glm::normalize(glm::cross(dir, up));
    up = glm::normalize(glm::cross(cr, dir));
    cr = glm::normalize(float(x)*cr + float(y)*up);
    dir += 0.005f*(cr-dir);
    dir = glm::normalize(dir);
    //up = glm::cross(new_dir, dir);
    //dir = glm::normalize(new_dir);
    up = glm::vec3(0,0,1);
}

void Camera::set_drag_view()
{
    if(flag==0)return;

    int _w, _h;
    double x, y, w, h;
    glfwGetCursorPos (window, &x, &y);
    glfwGetWindowSize(window, &_w, &_h);
    //glfwSetCursorPos(window, x + 0.03f*(_w/2-x), y + 0.3f*(_h/2-y));

    w = _w;
    h = _h;
    y = h-y;
    x -= w/2;
    y -= h/2;

    x = 2.0f*x/w;
    y = 2.0f*y/h;

    w = x; h = y;
    //cout << x << " " << y << " " << prev.second << " " << prev.second << endl;

    x = prev.first - x;
    y = prev.second - y;
    //cout << x << " " << y << endl;
    if(abs(x)<1e-4 && abs(y)<1e-4)return;

    up = glm::vec3(0,0,1);
    glm::vec3 cr = glm::normalize(glm::cross(dir, up));
    up = glm::normalize(glm::cross(cr, dir));
    cr = glm::normalize(float(x)*cr + float(y)*up);
    dir += 0.025f*(cr);
    dir = glm::normalize(dir);
    //up = glm::cross(new_dir, dir);
    //dir = glm::normalize(new_dir);
    up = glm::vec3(0,0,1);
    prev = make_pair(w, h);

}

void Camera::update()
{
    if(view == helicopter || view==mouse_view || view==drag_view)
    {
        up = glm::vec3(0,0,1);
        if(cam_move_dir == 'A')
        {
            glm::vec3 hor = glm::cross(dir, up);
            hor = glm::normalize(hor);
            eye -= camera_move_unit*hor;
        }
        else if(cam_move_dir == 'D')
        {
            glm::vec3 hor = glm::cross(dir, up);
            hor = glm::normalize(hor);
            eye += camera_move_unit*hor;
        }
        else if(cam_move_dir == 'W')
        {
            glm::vec3 hor = glm::cross(dir, up);
            glm::vec3 front = glm::normalize(glm::cross(hor, dir));
            eye += camera_move_unit*front;
        }
        else if(cam_move_dir == 'S')
        {
            glm::vec3 hor = glm::cross(dir, up);
            glm::vec3 back = glm::normalize(glm::cross(hor, dir));
            eye -= camera_move_unit*back;
        }
        else if(cam_move_dir == 'T')
            eye += camera_move_unit*dir;
        else if(cam_move_dir == 'G')
            eye -= camera_move_unit*dir;
    }
    if(view==helicopter)
    {
        if(ori_move_dir == 'J')
        {
            glm::vec3 hor = glm::cross(dir, up);
            hor = glm::normalize(hor);
            dir -= camera_dir_change_unit*hor;
            dir = glm::normalize(dir);
        }
        else if(ori_move_dir == 'L')
        {
            glm::vec3 hor = glm::cross(dir, up);
            hor = glm::normalize(hor);
            dir += camera_dir_change_unit*hor;
            dir = glm::normalize(dir);
        }
        else if(ori_move_dir == 'I')
        {
            glm::vec3 hor = glm::cross(dir, up);
            hor = glm::normalize(hor);
            dir += camera_dir_change_unit*glm::cross(hor, dir);
            dir = glm::normalize(dir);
            up = glm::cross(hor, dir);
            up = glm::normalize(up);
        }
        else if(ori_move_dir == 'K')
        {
            glm::vec3 hor = glm::cross(dir, up);
            hor = glm::normalize(hor);
            dir -= camera_dir_change_unit*glm::cross(hor, dir);
            dir = glm::normalize(dir);
            up = glm::cross(hor, dir);
            up = glm::normalize(up);
        }
    }
    if(view==follow)
    {
        glm::vec3 p, r = superblock.get_real_pos();
        p = r;
        r.z = 6.0f;
        r.x += 1.0f;
        r.y -= 1.5f;
        //eye = r;
        eye = eye + 0.05f*(r-eye);
        dir = glm::normalize(p - eye);
        glm::vec3 q = glm::cross( dir, glm::vec3(0,0,1));
        up = glm::normalize(glm::cross(q, dir));
    }
    if(view==mouse_view)
    {
        set_mouse_view();
    }
    if(view==mouse_view_cs)
    {
        set_mouse_view_cs();
    }
    if(view==drag_view)
    {
        set_drag_view();
    }
}

void Camera::cam_move(int to)
{
    if(view==helicopter || view==mouse_view || view == drag_view)
        cam_move_dir = to;
}
void Camera::ori_move(int to)
{
    if(view==helicopter)
        ori_move_dir = to;
}
void Camera::change_view_small(int v)
{
    view = v;
}
void Camera::zoom_change(int a)
{
    eye += a*camera_move_unit*dir;
}

void Camera::change_view(int v)
{
    view = v;
    if(view==vertical)
    {
        //eye = glm::vec3(0,0,5);
        //dir = glm::vec3(0,0,-1);
        //up = glm::vec3(0,1,0);
        proj_type = 0;
    }
    else if(view==helicopter)
    {
        /*
        eye = glm::vec3(rightt, bottomm-1.0f, 7.0f);
        dir = glm::vec3((rightt+leftt)/2, (topp+bottomm)/2, 0) - eye;
        dir = glm::normalize(dir);
        glm::vec3 r = glm::cross( dir, glm::vec3(0,0,1));
        up = glm::cross(r, dir);
        up = glm::normalize(up);
        */
        proj_type = 1;
    }
    else if(view==tower)
    {
        eye = glm::vec3(rightt-2.0f, bottomm, 10.0f);
        dir = glm::vec3((rightt+leftt)/2, (topp+bottomm)/2, 0) - eye;
        dir = glm::normalize(dir);
        glm::vec3 r = glm::cross( dir, glm::vec3(0,0,1));
        up = glm::cross(r, dir);
        up = glm::normalize(up);
        proj_type = 1;
    }
    else if(view==follow)
    {
        proj_type = 1;
        //update();
    }
    else if(view==block_view)
    {
        proj_type = 1;
    }
    else if(view==mouse_view)
    {
        proj_type = 1;
    }
    else if(view==mouse_view_cs)
    {
        proj_type = 1;
    }
    else if(view==drag_view)
    {
        proj_type = 1;
    }
}

void Camera::dir_change(double x, double y)
{
    //cout << dir.x << " " << dir.y << " " << dir.z << endl;
    up = glm::vec3(0,0,1);
    glm::vec3 cr = glm::normalize(glm::cross(dir, up));
    up = glm::normalize(glm::cross(cr, dir));
    cr = glm::normalize(float(x)*cr + float(y)*up);
    dir += 0.005f*(cr-dir);
    dir = glm::normalize(dir);
    //up = glm::cross(new_dir, dir);
    //dir = glm::normalize(new_dir);
    up = glm::vec3(0,0,1);

}

void Camera::left_button_press()
{
    if(view!=drag_view)return;

    int _w, _h;
    double x, y, w, h;
    glfwGetCursorPos (window, &x, &y);
    glfwGetWindowSize(window, &_w, &_h);
    //glfwSetCursorPos(window, x + 0.03f*(_w/2-x), y + 0.3f*(_h/2-y));

    w = _w;
    h = _h;
    y = h-y;
    x -= w/2;
    y -= h/2;

    x = 2.0f*x/w;
    y = 2.0f*y/h;
    //cout << x << " " << y << endl;

    prev = make_pair(x, y);
    flag = 1;
}
void Camera::left_button_release()
{
    if(view!=drag_view)return;
    flag = 0;
}
