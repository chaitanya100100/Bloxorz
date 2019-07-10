#include "headers.h"
#include "noedit.h"
#include "camera.h"
#include "superblock.h"

int proj_type;
float nearr = 0.1f;
float farr = 500.0f;
float leftt = -4.0f;
float rightt = 4.0f;
float topp = 4.0f;
float bottomm = -4.0f;

/* Executed when a regular key is pressed/released/held-down */
/* Prefered for Keyboard events */
void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_RELEASE)
    {
        switch(key)
        {
            case GLFW_KEY_SPACE:
                proj_type ^= 1;
                break;
            case GLFW_KEY_X:
            case GLFW_KEY_C:
            case GLFW_KEY_V:
            case GLFW_KEY_B:
            case GLFW_KEY_N:
            case GLFW_KEY_M:
                camera.change_view(key);
            case GLFW_KEY_A:
            case GLFW_KEY_S:
            case GLFW_KEY_W:
            case GLFW_KEY_D:
            case GLFW_KEY_T:
            case GLFW_KEY_G:
                camera.cam_move(0);
                break;
            case GLFW_KEY_I:
            case GLFW_KEY_K:
            case GLFW_KEY_J:
            case GLFW_KEY_L:
                camera.ori_move(0);
                break;
            case GLFW_KEY_UP:
            case GLFW_KEY_DOWN:
            case GLFW_KEY_LEFT:
            case GLFW_KEY_RIGHT:
                superblock.move(key);
                break;
        	default:
        	    break;
        }
    }
    else if (action == GLFW_PRESS)
    {
        switch(key)
        {
        	case GLFW_KEY_ESCAPE:
        	    quit(window);
        	    break;
            case GLFW_KEY_A:
            case GLFW_KEY_S:
            case GLFW_KEY_W:
            case GLFW_KEY_D:
            case GLFW_KEY_T:
            case GLFW_KEY_G:
                camera.cam_move(key);
                break;
            case GLFW_KEY_I:
            case GLFW_KEY_K:
            case GLFW_KEY_J:
            case GLFW_KEY_L:
                camera.ori_move(key);
        	default:
        	    break;
        }
    }
}

/* Executed for character input (like in text boxes) */
void keyboardChar (GLFWwindow* window, unsigned int key)
{
    switch (key)
    {
        case 'Q':
        case 'q':
    	   quit(window);
    	   break;

        default:
	       break;
    }
}

/* Executed when a mouse button is pressed/released */
void mouseButton (GLFWwindow* window, int button, int action, int mods)
{

	if(action == GLFW_RELEASE)
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
            camera.left_button_release();
               break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                break;

            default:
                break;
        }
    }
	else if(action == GLFW_PRESS)
    {
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                camera.left_button_press();
               break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                break;

            default:
                break;
        }
    }

}

/*
void calculate_perspective()
{
    //int fbwidth=width, fbheight=height;
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    GLfloat fov = M_PI/2;

    // sets the viewport of openGL renderer
    glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

    // Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    Matrices.projectionP = glm::perspective(fov, (GLfloat) fbwidth / (GLfloat) fbheight, nearr, farr);
}
void calculate_ortho()
{
    // Ortho projection for 2D views
    Matrices.projectionO = glm::ortho(leftt, rightt, bottomm, topp, nearr, farr);
}
*/
/* Executed when window is resized to 'width' and 'height' */
/* Modify the bounds of the screen here in glm::ortho or Field of View in glm::Perspective */
void reshapeWindow (GLFWwindow* window, int width, int height)
{
    int fbwidth=width, fbheight=height;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);

    GLfloat fov = M_PI/2;

    // sets the viewport of openGL renderer
    glViewport (0, 0, (GLsizei) fbwidth, (GLsizei) fbheight);

    // Store the projection matrix in a variable for future use
    // Perspective projection for 3D views
    Matrices.projectionP = glm::perspective(fov, (GLfloat) fbwidth / (GLfloat) fbheight, nearr, farr);
    // Ortho projection for 2D views
    Matrices.projectionO = glm::ortho(leftt, rightt, bottomm, topp, nearr, farr);

}

void scroll(GLFWwindow* window, double x, double y)
{
    int i = camera.get_view_type();
    if(i!=drag_view && i!= mouse_view)return;

    x = int(x);
    y = int(y);
    if(x==0)camera.zoom_change(-y);
}


void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
    int i = camera.get_view_type();
    if(i!=helicopter)return;

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
    camera.dir_change(x, y);
}
