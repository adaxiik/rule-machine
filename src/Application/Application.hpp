#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>

struct RGB
{
    u_char r;
    u_char g;
    u_char b;
};

class Application
{
private:
    Application();
    ~Application();
    static Application* instance;

    SDL_Window *window;
    int width, height;
    int simulationWidth, simulationHeight;

    RGB* pixels;


    SDL_Renderer *renderer;
    SDL_Texture *texture;

    void CleanUp();


public:
    static Application* GetInstance();
    static void DestroyInstance();

    void Init(int width, int height, std::string title, int simulationWidth, int simulationHeight);

};

