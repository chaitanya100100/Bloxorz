extern int proj_type;
extern float nearr;
extern float farr;
extern float leftt;
extern float rightt;
extern float topp;
extern float bottomm;


void keyboard (GLFWwindow* window, int key, int scancode, int action, int mods);
void keyboardChar (GLFWwindow* window, unsigned int key);
void mouseButton (GLFWwindow* window, int button, int action, int mods);
void reshapeWindow (GLFWwindow* window, int width, int height);
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void scroll(GLFWwindow* window, double x, double y);
