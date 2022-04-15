#pragma once
#include <SDL2/SDL.h>
#include <string>
#include <iostream>


struct RGB
{
    u_char b;
    u_char g;
    u_char r;
    u_char a;
};

class Application
{
private:
    Application();
    ~Application();
    static Application* instance;
    bool running;

    SDL_Window *window;
    int width, height;
    int simulationWidth, simulationHeight;

    RGB* pixels;


    SDL_Renderer *renderer;
    SDL_Texture *texture;

    void CleanUp();
    void Render();
    void ProcessEvents();



public:
    static Application* GetInstance();
    static void DestroyInstance();

    void Init(int width, int height, std::string title, int simulationWidth, int simulationHeight);
    void Run();


};

