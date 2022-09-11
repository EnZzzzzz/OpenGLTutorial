#include "effectTasks/TestClearColor.h"
#include "effectTasks/TestTexture2D.h"
#include "effectTasks/TestBatchRender.h"
#include "effectTasks/OG6Coordinate.h"
#include "effectTasks/OG6Coordinate2.h"
#include "export/Window.h"

int main(void)
{
    
    Window window = Window(800, 600, "Hello World");
    std::cout << "window created" << std::endl;

    Task* currentTest = nullptr;
    TaskMenu testMenu = TaskMenu();
    currentTest = &testMenu;

    testMenu.RegisterTest<TestClearColor>("Clear Color");
    testMenu.RegisterTest<TestTexture2D>("2D Texture");
    testMenu.RegisterTest<TestBatchRender>("Batch Render");
    testMenu.RegisterTest<OG6Coordinate>("OG6Coordinate");
    testMenu.RegisterTest<OG6Coordinate2>("OG6Coordinate2");

    std::cout << "start showing menu" << std::endl;
    window.show(currentTest);

    return 0;
}