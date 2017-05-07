#include "headers.h"
#include "tile.h"
#include "superblock.h"
#include "controls.h"

float tile_side_length = 1.0f;
float tile_height = 0.2f;
int normal=1, fragile=2, normal_bridge=3, heavy_bridge=4;

Tile::Tile(){}

Tile::Tile(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, int tile_type)
{
    initialize(pos, dim, rot, c, tile_type);
}

void Tile::initialize(glm::vec3 pos, glm::vec3 dim, glm::vec3 rot, Color c, int tile_type)
{
    Sprite::initialize(pos, rot);
    this->tile_type = tile_type;
    add_block( new Block(glm::vec3(0,0,0), dim, glm::vec3(0,0,0), c) );
}
int Tile::get_tile_type()
{
    return tile_type;
}


Floor::Floor(){}

Floor::Floor(string filename)
{
    initialize(filename);
}
int Floor::get_color(int k)
{
    if(k==1)return GREY;
    else if(k==2)return ORANGE;
    else if(k==3)return GREEN;
    else if(k==4)return DARKGREEN;
}

void Floor::initialize(string filename)
{
    ifstream fin(filename);
    if(!fin)
    {
        cerr << "Error : Can't open file " << filename << "." << endl;
        exit(EXIT_FAILURE);
    }

    fin >> n >> m;
    tiles = new Tile**[n];

    for(int i=0; i<n; i++)
        tiles[i] = new Tile*[m];

    int k;
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
        {
            fin >> k;
            if(k)
                tiles[i][j] = new Tile(
                                        glm::vec3(i*tile_side_length, j*tile_side_length, 0.0f),
                                        glm::vec3(tile_side_length, tile_side_length, -tile_height),
                                        glm::vec3(0,0,0),
                                        colors[get_color(k)],
                                        k
                                        );
            else
                tiles[i][j] = NULL;
        }
    fin >> sx >> sy;

    char q; fin >> q;
    if(q=='X')along = X;
    else if(q=='Y')along = Y;
    else if(q=='Z')along = Z;
    else exit(EXIT_FAILURE);

    fin >> tx >> ty;

    leftt = -1.0f;
    rightt = 1.0f + n*tile_side_length;
    topp = 1.0f + m*tile_side_length;
    bottomm = -1.0f;
    fin >> num_normal_bridge; normal_bridge.clear();
    for(int i=0; i<num_normal_bridge; i++)
    {
        int x, y, a, b;
        fin >> x >> y >> a >> b;
        normal_bridge[x*m+y] = a*m+b;
    }

    fin >> num_heavy_bridge; heavy_bridge.clear();
    for(int i=0; i<num_heavy_bridge; i++)
    {
        int x, y, a, b;
        fin >> x >> y >> a >> b;
        heavy_bridge[x*m+y] = a*m+b;
    }

    fin.close();
}

void Floor::draw(glm::mat4 M)
{
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(tiles[i][j])
                tiles[i][j]->draw(M);
}

int Floor::get_along()
{
    return along;
}

pair<int, int> Floor::get_initial_index()
{
    return make_pair(sx, sy);
}

glm::vec3 Floor::get_initial_pos()
{
    float l = tile_side_length;

    glm::vec3 r(
        sx*l,
        sy*l,
        0.0f
    );
    int a = get_along();

    if(a==X)
        r = r + glm::vec3(l, l/2, l/2);
    else if(a==Y)
        r = r + glm::vec3(l/2, l, l/2);
    else if(a==Z)
        r = r + glm::vec3(l/2, l/2, l);

    return r;
}

int Floor::get_tile_type(int i, int j)
{
    return tiles[i][j]->get_tile_type();
}

void Floor::heavy_bridge_toggle(int i, int j)
{
    int q = heavy_bridge[i*m+j];
    int a = q/m;
    int b = q%m;
    if(!tiles[a][b])
    {
        tiles[a][b] = new Tile(
                                glm::vec3(a*tile_side_length, b*tile_side_length, 0.0f),
                                glm::vec3(tile_side_length, tile_side_length, -tile_height),
                                glm::vec3(0,0,0),
                                colors[get_color(1)],
                                1
                                );
    }
    else
    {
        free(tiles[a][b]);
        tiles[a][b] = NULL;
    }
}

void Floor::normal_bridge_toggle(int i, int j)
{
    int q = normal_bridge[i*m+j];
    int a = q/m;
    int b = q%m;
    if(!tiles[a][b])
    {
        tiles[a][b] = new Tile(
                                glm::vec3(a*tile_side_length, b*tile_side_length, 0.0f),
                                glm::vec3(tile_side_length, tile_side_length, -tile_height),
                                glm::vec3(0,0,0),
                                colors[get_color(1)],
                                1
                                );
    }
    else
    {
        free(tiles[a][b]);
        tiles[a][b] = NULL;
    }
}

Floor::~Floor()
{
    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            delete tiles[i][j];
    for(int i=0; i<n; i++)
        delete tiles[i];
    delete tiles;

    normal_bridge.clear();
    heavy_bridge.clear();
}
