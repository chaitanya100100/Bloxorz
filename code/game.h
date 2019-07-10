#ifndef GAME
#define GAME

class Game
{
    private:
        bool gameover;
        bool won;
        int level;
        int number_of_steps;
    public:
        Game();
        void initialize(int level=2);
        int check();
        void check_after_step();
        bool is_gameover();
        bool is_won();
        void gameover_fun();
        void won_fun();
        int get_level();
        void done();
        void increase_level();
};

#endif

extern Game game;
