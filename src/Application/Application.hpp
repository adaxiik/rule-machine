#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>
#include "../Simulation/Board.hpp"


class Application
{
private:
    Application();
    ~Application();
    static Application* instance;
    bool running;
    bool simulating;
    SDL_Window *window;
    int width, height;
    int simulationWidth, simulationHeight;
    uint64_t simulationSpeed;

    BGRA* pixels;


    SDL_Renderer *renderer;
    SDL_Texture *texture;

    void CleanUp();
    void Render();
    void ProcessEvents();



public:
    static Application* GetInstance();
    static void DestroyInstance();

    void Init(int width, int height, std::string title, int simulationWidth, int simulationHeight, uint64_t simulationSpeed);
    void Run();
    void SetPixel(int x, int y, BGRA color);


};

