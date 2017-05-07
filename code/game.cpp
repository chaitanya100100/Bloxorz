#include "headers.h"
#include "tile.h"
#include "superblock.h"
#include "controls.h"
#include "game.h"

Game::Game()
{
    level = 2;
    number_of_steps = 0;
    gameover = false;
    won = false;
}

int Game::check()
{
    int sx = superblock.ix, sy = superblock.iy;
    int tx = stage.tx, ty = stage.ty;
    int along = superblock.along;

    if(!stage.tiles[sx][sy])
    {
        if(!(sx==tx && sy==ty))
            gameover = true;
        else if(along==Z)
            won = true;
    }
    else if(along==Z)
    {
        if(stage.tiles[sx][sy]->tile_type==fragile)//stage.get_tile_type(superblock.ix, superblock.iy) == fragile)
            gameover = true;
    }

    if(along == X && !stage.tiles[sx+1][sy])
        if(!(sx+1==tx && sy==ty))
            gameover = true;
    if(along == Y && !stage.tiles[sx][sy+1])
        if(!(sx==tx && sy+1==ty))
            gameover = true;

    if(gameover)return 0;
    else if(won)return 1;
    else return -1;
}

void Game::check_after_step()
{
    number_of_steps++;
    int p = check();
    if(p!=-1)return;

    int sx = superblock.ix, sy = superblock.iy;
    int along = superblock.along;

    if(stage.tiles[sx][sy] && stage.tiles[sx][sy]->tile_type==normal_bridge)
        stage.normal_bridge_toggle(sx, sy);

    if(along==X && stage.tiles[sx+1][sy] && stage.tiles[sx+1][sy]->tile_type==normal_bridge)
        stage.normal_bridge_toggle(sx+1, sy);

    if(along==Y && stage.tiles[sx][sy+1] && stage.tiles[sx][sy+1]->tile_type==normal_bridge)
        stage.normal_bridge_toggle(sx, sy+1);

    if(along==Z && stage.tiles[sx][sy] && stage.tiles[sx][sy]->tile_type==heavy_bridge)
        stage.heavy_bridge_toggle(sx, sy);
}

bool Game::is_gameover()
{
    return gameover;
}
bool Game::is_won()
{
    return won;
}

void Game::initialize(int level)
{
    this->level = level;
    string name;

    name = string("data/") + to_string(level) + string(".data");
    stage.initialize(name);
    superblock.initialize(
                    stage.get_initial_pos(),
                    glm::vec3(2*tile_side_length, tile_side_length, tile_side_length),
                    colors[RED],
                    stage.get_along()
                );
}

void Game::gameover_fun()
{
    cout << "GAME OVER" << endl;
    cout << "Steps : " << number_of_steps << endl;
    //stage.~Floor();
    //superblock.~SuperBlock();
    //initialize();
}
void Game::won_fun()
{
    cout << "WON" << endl;
    cout << "Steps : " << number_of_steps << endl;
    //stage.~Floor();
    //superblock.~SuperBlock();
    //if(level!=1)level++;
    //initialize();
}
int Game::get_level()
{
    return level;
}
void Game::increase_level()
{
    if(level!=1)
        level++;
}


void Game::done()
{
    stage.~Floor();
    superblock.~SuperBlock();
}
