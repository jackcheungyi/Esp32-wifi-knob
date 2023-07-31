#include "AppFactory.h"
#include "StartUp/StartUp.h"
#include "Menu/Menu.h"



PageBase* AppFactory::CreatePage(const char* name)
{
    // APP_CLASS_MATCH(Template);
    
	// APP_CLASS_MATCH(Playground);
	// APP_CLASS_MATCH(SurfaceDial);
	APP_CLASS_MATCH(Startup);
    APP_CLASS_MATCH(Menu);
	// APP_CLASS_MATCH(Hass);
    // APP_CLASS_MATCH(Scene3D);

    return nullptr;
}
