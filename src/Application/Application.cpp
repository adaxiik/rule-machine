#include "Application.hpp"
#include <unistd.h>
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
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, 0);
    SDL_RenderSetLogicalSize(this->renderer, simulationWidth, simulationHeight);

    this->texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, simulationWidth, simulationHeight);
    if (!this->texture)
    {
        std::cout << "SDL_CreateTexture Error: " << SDL_GetError() << std::endl;
        goto sdl_create_texture_error;
    }

    this->pixels = new BGRA[simulationWidth * simulationHeight];
    for (int i = 0; i < simulationWidth * simulationHeight; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
        this->pixels[i].a = 255;
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
    SDL_VideoQuit();

    SDL_Quit();
}

void Application::Render()
{

    SDL_UpdateTexture(this->texture, NULL, this->pixels, this->simulationWidth * sizeof(BGRA));
    SDL_RenderCopy(this->renderer, this->texture, NULL, NULL);

    SDL_RenderPresent(this->renderer);
    SDL_RenderClear(this->renderer);
}

void Application::Run()
{
    this->running = true;

    Board* board = new Board(this->simulationWidth, this->simulationHeight);
    board->AddElement(1,new Element("Sand",1,BGRA{255,0,0,255}));
    
    std::vector<std::vector<ElementID>> sandRuleInput= {
        {1},{0}
    };
    std::vector<std::vector<ElementID>> sandRuleOutput= {
        {0},{1}
    };
    board->GetElement(1)->AddRule(Rule(sandRuleInput,sandRuleOutput));
    board->SetAtom(25,0,1);
    
    while (this->running)
    {
        this->ProcessEvents();
        board->Update();
        board->DrawPixels(this->pixels);
        usleep(100000);
        this->Render();
    }
    delete board;
    this->CleanUp();
}

void Application::ProcessEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            this->running = false;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                this->running = false;
                break;
            }
            break;
        }
    }
}

void Application::SetPixel(int x, int y, BGRA color)
{
    this->pixels[y * this->simulationWidth + x] = color;
}