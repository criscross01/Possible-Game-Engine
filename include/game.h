#ifndef GAME_H
#define GAME_H
#include "renderer.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void run();

    private:
        void loop();
        void inputManager(GLFWwindow* window);

        Renderer renderer();
};

#endif // GAME_H
