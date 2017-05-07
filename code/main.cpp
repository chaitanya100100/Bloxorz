#include "headers.h"
#include "noedit.h"
#include "controls.h"
#include "colors.h"
#include "camera.h"
#include "block.h"
#include "tile.h"
#include "superblock.h"
#include "game.h"

//change here to change level : 1 or 2
int level = 2;


struct GLMatrices Matrices;
GLuint programID;
GLFWwindow* window;

/**************************
 * Customizable functions *
 **************************/

glm::mat4 world_model;
Floor stage;
SuperBlock superblock;
Game game;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw (GLFWwindow* window, float x, float y, float w, float h, int varo)
{
    int fbwidth, fbheight;
    glfwGetFramebufferSize(window, &fbwidth, &fbheight);
    glViewport((int)(x*fbwidth), (int)(y*fbheight), (int)(w*fbwidth), (int)(h*fbheight));

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram(programID);

    if(varo==0)
    {
        camera.update();
        superblock.update();
        int a = game.check();
        if(a==0)
        {
            game.gameover_fun();
            exit(0);
        }
        else if(a==1)
        {
            game.won_fun();
            exit(0);
        }

        Matrices.view = camera.get_view();
        stage.draw(world_model);
        superblock.draw(world_model);
    }
    else
    {
        int prev = camera.get_view_type();
        camera.change_view(vertical);

        Matrices.view = camera.get_view();
        stage.draw(world_model);
        superblock.draw(world_model);

        camera.change_view(prev);
    }
}

/* Initialise glfw window, I/O callbacks and the renderer to use */
/* Nothing to Edit here */
GLFWwindow* initGLFW (int width, int height){
    GLFWwindow* window; // window desciptor/handle

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "BLOXORZ", NULL, NULL);

    if (!window) {
        glfwTerminate();
	    exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwSwapInterval( 1 );
    glfwSetFramebufferSizeCallback(window, reshapeWindow);
    glfwSetWindowSizeCallback(window, reshapeWindow);
    glfwSetWindowCloseCallback(window, quit);
    glfwSetKeyCallback(window, keyboard);      // general keyboard input
    glfwSetCharCallback(window, keyboardChar);  // simpler specific character handling
    glfwSetMouseButtonCallback(window, mouseButton);  // mouse button clicks
    //glfwSetCursorPosCallback(window, cursor_pos_callback);
    glfwSetScrollCallback(window, scroll);

    return window;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL (GLFWwindow* window, int width, int height)
{
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    //myblock.initialize(glm::vec3(2, 0, 0), glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), colors[GREY]);

    game.initialize(level);
    /*
    superblock.initialize(
                    stage.get_initial_pos(),
                    glm::vec3(2*tile_side_length, tile_side_length, tile_side_length),
                    colors[RED],
                    stage.get_along()
                );
    */
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders( "Sample_GL.vert", "Sample_GL.frag" );
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    //glClearColor (0.3f, 0.3f, 0.3f, 0.0f); // R, G, B, A
    glClearColor (colors[SKYBLUE].r, colors[SKYBLUE].g, colors[SKYBLUE].b, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    // cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    // cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    // cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    // cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

int main (int argc, char** argv)
{
    world_model = glm::mat4(1.0f);
    initialize_colors();
    camera.initialize_camera();

    int width = 800;
    int height = 800;
    proj_type = 0;

    window = initGLFW(width, height);
    //initGLEW();
    initGL (window, width, height);

    double last_update_time = glfwGetTime(), current_time;

    /* Draw in loop */

    while (!glfwWindowShouldClose(window)) {

    	// clear the color and depth in the frame buffer
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // OpenGL Draw commands
    	draw(window, 0, 0, 1, 1, 0);
        draw(window, 0, 0, 0.3, 0.3, 1);

        // Swap Frame Buffer in double buffering
        glfwSwapBuffers(window);

        // Poll for Keyboard and mouse events
        glfwPollEvents();

        // Control based on time (Time based transformation like 5 degrees rotation every 0.5s)
        current_time = glfwGetTime(); // Time in seconds
        if ((current_time - last_update_time) >= 0.5) { // atleast 0.5s elapsed since last frame
            // do something every 0.5 seconds ..
            last_update_time = current_time;
        }
    }

    glfwTerminate();
    //    exit(EXIT_SUCCESS);
}
