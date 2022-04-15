#include <iostream>
#include "Application/Application.hpp"
int main(int argc, char const *argv[])
{
    Application::GetInstance()->Init(800, 600, "rule-machine", 800, 600);
    Application::GetInstance()->Run();
    Application::GetInstance()->DestroyInstance();

    return 0;
}
