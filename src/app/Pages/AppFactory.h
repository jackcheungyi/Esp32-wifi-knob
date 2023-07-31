#include "app/Utils/PageManager/PageManager.h"


#define APP_CLASS_MATCH(className)\
do{\
    if (strcmp(name, #className) == 0){return new Page::className;}\
}while(0)


class AppFactory : public PageFactory
{
public:
    virtual PageBase* CreatePage(const char* name);
private:

};