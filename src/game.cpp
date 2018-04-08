#include "game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::run(){

}

void Game::loop()
{
    while(true)
    {
        eventManager(renderer.getWindow());

        glfwPollEvents();
    }
}
