#pragma once

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

class IHelloProperty
	: public IModule
{

};

class HelloProperty
    : public IHelloProperty
{
public:
    HelloProperty(IPluginManager* p)
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
    int OnPropertyCallBackEvent(const Guid& self, const std::string& propertyName, const NFData& oldVarList, const NFData& newVarList, const int64_t reason);



};

