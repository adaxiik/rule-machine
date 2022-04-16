#include <iostream>
#include "Application/Application.hpp"
int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    Application::GetInstance()->Init(800, 600, "rule-machine", 80, 60,15);
    Application::GetInstance()->Run();
    Application::GetInstance()->DestroyInstance();

    return 0;
}
