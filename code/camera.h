#ifndef CAMERA
#define CAMERA

class Camera
{
    private:
        glm::vec3 eye;
        glm::vec3 dir;
        glm::vec3 up;
        int cam_move_dir;
        int ori_move_dir;
        pair<double, double> prev;
        int view;
        int flag;
    public:
        void initialize_camera();
        glm::mat4 get_view();
        void cam_move(int to);
        void ori_move(int to);
        void update();
        void dir_change(double x, double y);
        void change_view(int v);
        void change_view_small(int v);
        int get_view_type();
        void set_mouse_view();
        void set_drag_view();
        void set_mouse_view_cs();
        void left_button_press();
        void left_button_release();
        void zoom_change(int a);
};

#endif

extern Camera camera;
extern float camera_move_unit;
extern float camera_dir_change_unit;
extern int helicopter, vertical, tower, follow, block_view, mouse_view, mouse_view_cs, drag_view;
