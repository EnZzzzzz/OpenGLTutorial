#include "effectTasks/TestClearColor.h"
#include "effectTasks/OG6Coordinate.h"
#include "effectTasks/OG6Coordinate2.h"
#include "effectTasks/OG7Camera.h"
#include "effectTasks/OG7Camera2.h"
#include "export/Window.h"

int main(void)
{
    
    Window window = Window(800, 600, "Hello World");
    std::cout << "window created" << std::endl;

    Task* currentTest = nullptr;
    TaskMenu testMenu = TaskMenu();
    currentTest = &testMenu;

    testMenu.RegisterTest<OG6Coordinate>("OG6Coordinate");
    testMenu.RegisterTest<OG6Coordinate2>("OG6Coordinate2");
    testMenu.RegisterTest<OG7Camera>("OG7Camera");
    testMenu.RegisterTest<OG7Camera2>("OG7Camera2");

    std::cout << "start showing menu" << std::endl;
    window.show(currentTest);

    return 0;
}