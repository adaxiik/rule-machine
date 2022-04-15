#include <iostream>
#include "Application/Application.hpp"
int main(int argc, char const *argv[])
{
    Application::GetInstance()->Init(800, 600, "rule-machine", 50, 50,15);
    Application::GetInstance()->Run();
    Application::GetInstance()->DestroyInstance();

    return 0;
}
