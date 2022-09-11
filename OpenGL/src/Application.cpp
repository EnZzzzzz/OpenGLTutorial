#include "tasks/TestClearColor.h"
#include "tasks/TestTexture2D.h"
#include "tasks/TestBatchRender.h"
#include "export/Window.h"

int main(void)
{
    
    Window window = Window(640, 480, "Hello World");
    std::cout << "window created" << std::endl;

    task::Task* currentTest = nullptr;
    task::TaskMenu testMenu = task::TaskMenu();
    currentTest = &testMenu;

    testMenu.RegisterTest<task::TestClearColor>("Clear Color");
    testMenu.RegisterTest<task::TestTexture2D>("2D Texture");
    testMenu.RegisterTest<task::TestBatchRender>("Batch Render");

    std::cout << "start showing menu" << std::endl;
    window.show(currentTest);

    return 0;
}