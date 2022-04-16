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

void Application::Init(int width, int height, std::string title,int simulationWidth,int simulationHeight, uint64_t simulationSpeed)
{
    this->width = width;
    this->height = height;
    this->simulationWidth = simulationWidth;
    this->simulationHeight = simulationHeight;
    this->simulationSpeed = simulationSpeed;
    
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
    
    this->board = new Board(simulationWidth, simulationHeight);
    

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
    this->simulating = false;

    this->board->AddElement(1,new Element("Sand",1,BGRA{255,255,255,255}));
    this->board->AddElement(2,new Element("Wall",2,BGRA{0,0,255,255}));
    
    // std::vector<std::vector<ElementID>> sandFallRuleInput= {
    //     {1},
    //     {0}
    // };
    // std::vector<std::vector<ElementID>> sandFallRuleOutput= {
    //     {0},
    //     {1}
    // };

    std::vector<std::vector<ElementID>> sandFallSide1RuleInput= {
        {1,0},
        {1,0}
    };
    std::vector<std::vector<ElementID>> sandFallSide1RuleOutput= {
        {0,0},
        {1,1}
    };

    // std::vector<std::vector<ElementID>> sandFallSide2RuleInput= {
    //     {0,1},
    //     {0,1}
    // };
    // std::vector<std::vector<ElementID>> sandFallSide2RuleOutput= {
    //     {0,0},
    //     {1,1}
    // };
    
    // board->GetElement(1)->AddRule(Rule(sandFallRuleInput,sandFallRuleOutput,1));
    // board->GetElement(1)->AddRule(Rule(sandFallSide1RuleInput,sandFallSide1RuleOutput,1));
    // board->GetElement(1)->AddRule(Rule(sandFallSide2RuleInput,sandFallSide2RuleOutput,1));

    //rule 110
    std::vector<std::vector<ElementID>> rule1_i= {
        {1,1,1},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule1_o= {
        {1,1,1},
        {0,0,0}
    };

    std::vector<std::vector<ElementID>> rule2_i= {
        {1,1,0},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule2_o= {
        {1,1,0},
        {0,1,0}
    };

    std::vector<std::vector<ElementID>> rule3_i= {
        {1,0,1},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule3_o= {
        {1,0,1},
        {0,1,0}
    };

    std::vector<std::vector<ElementID>> rule4_i= {
        {1,0,0},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule4_o= {
        {1,0,0},
        {0,0,0}
    };

    std::vector<std::vector<ElementID>> rule5_i= {
        {0,1,1},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule5_o= {
        {0,1,1},
        {0,1,0}
    };

    std::vector<std::vector<ElementID>> rule6_i= {
        {0,1,0},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule6_o= {
        {0,1,0},
        {0,1,0}
    };

    std::vector<std::vector<ElementID>> rule7_i= {
        {0,0,1},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule7_o= {
        {0,0,1},
        {0,1,0}
    };

    std::vector<std::vector<ElementID>> rule8_i= {
        {0,0,0},
        {0,0,0}
    };
    std::vector<std::vector<ElementID>> rule8_o= {
        {0,0,0},
        {0,0,0}
    };

    //board->AddGlobalRule(Rule(rule1_i,rule1_o,1));
    board->AddGlobalRule(Rule(rule2_i,rule2_o,1));
    board->AddGlobalRule(Rule(rule3_i,rule3_o,1));
    //board->AddGlobalRule(Rule(rule4_i,rule4_o,1));
    board->AddGlobalRule(Rule(rule5_i,rule5_o,1));
    board->AddGlobalRule(Rule(rule6_i,rule6_o,1));
    board->AddGlobalRule(Rule(rule7_i,rule7_o,1));
    //board->AddGlobalRule(Rule(rule8_i,rule8_o,1));

    // for (size_t i = 0; i < 80; i++)
    // {
    //     this->board->SetAtom(i,59,2);
    //     this->board->SetAtom(i,40,2);
    // }
    
    this->board->Update();
    this->DrawPixels();
    
    uint64_t NOW = SDL_GetPerformanceCounter();
    uint64_t LAST = 0;
    double elapsed = 0;

    while (this->running)
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        elapsed += (NOW - LAST) / (double)SDL_GetPerformanceFrequency();
        if (elapsed > (1/(double)this->simulationSpeed) && this->simulating)
        {
            this->board->Update();
            this->DrawPixels();
            elapsed = 0;
        }
        this->Render();
        ProcessEvents();
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
            case SDLK_SPACE:
                this->simulating = !this->simulating;
                std::cout << (this->simulating ? "Simulating" : "Paused") << std::endl;
                break;
            }
            break;
        }
    }

    SDL_PumpEvents();
    int x, y;
    uint32_t mouseState = SDL_GetMouseState(&x, &y);

    x = x * this->simulationWidth / this->width;
    y = y * this->simulationHeight / this->height;
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        this->board->SetAtom(x,y,1,false);
    }
    else if (mouseState & SDL_BUTTON(SDL_BUTTON_RIGHT))
    {
        this->board->SetAtom(x,y,0,false);
    }

}

void Application::SetPixel(int x, int y, BGRA color)
{
    this->pixels[y * this->simulationWidth + x] = color;
}

void Application::DrawPixels()
{
    for (int y = 0; y < this->simulationHeight; y++)
    {
        for (int x = 0; x < this->simulationWidth; x++)
        {
            this->pixels[y * this->simulationWidth + x] = this->board->GetElement(this->board->GetAtom(x,y).id)->GetColor();
        }
    }
}