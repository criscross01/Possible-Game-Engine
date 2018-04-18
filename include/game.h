#ifndef GAME_H
#define GAME_H
#include "renderer.h"
#include "ObjectRender.h"

class Game
{
    public:
        Game();
        virtual ~Game();
        void init();

    private:
        void run();
        void update();
        void inputManager(GLFWwindow* window);

        Renderer renderer   {Renderer(800,600,"Testing")};
};

#endif // GAME_H
