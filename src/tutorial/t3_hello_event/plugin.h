#pragma once

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"


class Tutorial3Plugin : public IPlugin
{
public:
    Tutorial3Plugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};