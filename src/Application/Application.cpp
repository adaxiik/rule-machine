#include "Application.hpp"

Application *Application::instance = nullptr;
Application::Application()
{
}

Application::~Application()
{
    delete[] pixels;
}

Application *Application::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new Application();
    }
    return instance;
}

void Application::DestroyInstance()
{
    if (instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
}

void Application::Init(int width, int height, std::string title,int simulationWidth,int simulationHeight)
{
    this->width = width;
    this->height = height;
    this->simulationWidth = simulationWidth;
    this->simulationHeight = simulationHeight;
    
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        goto sdl_init_error;
    }

    this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!this->window)
    {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        goto sdl_create_window_error;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!this->renderer)
    {
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        goto sdl_create_renderer_error;
    }

    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, simulationWidth, simulationHeight);
    if (!this->texture)
    {
        std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        goto sdl_create_texture_error;
    }

    SDL_RenderSetLogicalSize(this->renderer, simulationWidth, simulationHeight);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);


    this->pixels = new RGB[simulationWidth * simulationHeight];
    for(size_t i = 0; i < (size_t)simulationWidth * simulationHeight; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }

    return;

    sdl_create_texture_error:
        SDL_DestroyRenderer(this->renderer);

    sdl_create_renderer_error:
        SDL_DestroyWindow(this->window);

    sdl_create_window_error:
        SDL_Quit();

    sdl_init_error:
        exit(EXIT_FAILURE);
}


void Application::CleanUp()
{
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    //SDL_VideoQuit();

    SDL_Quit();
}