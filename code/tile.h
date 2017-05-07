#include "block.h"
#include "colors.h"

#ifndef TILES
#define TILES
class Game;
class Tile : public Sprite
{
    private:
        int tile_type;
    public:
        friend class Game;
        Tile();
        Tile(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, int tile_type);
        void initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, int tile_type);
        int get_tile_type();
};

#endif


#ifndef FLOOR
#define FLOOR
class Game;
class Floor
{
    public:
        Tile *** tiles;
        int n;
        int m;
        int tx;
        int ty;
        int sx;
        int sy;
        int along;
        int num_normal_bridge;
        int num_heavy_bridge;
        map<int, int> normal_bridge;
        map<int, int> heavy_bridge;
    public:
        friend class Game;
        Floor();
        Floor(string filename);
        void initialize(string filename);
        void draw(glm::mat4 M);
        int get_along();
        glm::vec3 get_initial_pos();
        pair<int, int> get_initial_index();
        int get_tile_type(int i, int j);
        int get_color(int k);
        void heavy_bridge_toggle(int i, int j);
        void normal_bridge_toggle(int i, int j);
        ~Floor();
};

#endif

extern float tile_side_length;
extern float tile_height;
extern Floor stage;
extern int normal, fragile, normal_bridge, heavy_bridge;
