#pragma once

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"


class Tutorial2 : public IPlugin
{
public:
    Tutorial2(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};