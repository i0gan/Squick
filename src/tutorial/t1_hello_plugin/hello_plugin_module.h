#pragma once

#include <squick/base/plugin.h>
#include <squick/base/plugin_manager.h>

class IHelloPlugin
	: public IModule
{
};

class HelloWorld1
    : public IHelloPlugin
{
public:
    HelloWorld1(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Execute();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:

};

