#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#ifndef VAOVAO
#define VAOVAO

struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projectionO;
    glm::mat4 projectionP;
    glm::mat4 model;
    glm::mat4 view;
    GLuint MatrixID;
};

#endif

extern struct GLMatrices Matrices;
extern int proj_type;
extern GLuint programID;
extern GLFWwindow* window;
