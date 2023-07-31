#include "app.h"
#include "hal/hal.h"
#include "Utils/PageManager/PageManager.h"
#include "Pages/AppFactory.h"
#include "Resources/ResourcePool.h"


void App_Init()
{
    static AppFactory factory; 
    static PageManager manager(&factory);

    Resource.Init();

    manager.Install("Startup","Pages/StartUp");
    manager.Install("Menu","Pages/Menu");

    manager.SetGlobalLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500);
    manager.Push("Pages/StartUp");
    _INIT_DONE();
}