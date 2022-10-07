

#ifndef SQUICK_HELLO_WORLD_H
#define SQUICK_HELLO_WORLD_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/navigation.h"

/*
IN THIS PLUGIN:
YOU WILL KNOW HOW TO USE THE "INavigationModule" TO FIND THE PATH FOR AI OBJECT
*/

class IHelloWorld6
	: public IModule
{

};

class HelloWorld6
    : public IHelloWorld6
{
public:
    HelloWorld6(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Execute();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:
	INavigationModule* m_pNavigationModule;
};

#endif
