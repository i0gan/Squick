
#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"

#ifdef WORLDNET_CLIENTPLUGIN_EXPORTS
#define WORLDNET_CLIENTPLUGIN_API __declspec(dllexport)
#else
#define WORLDNET_CLIENTPLUGIN_API __declspec(dllimport)
#endif

//////////////////////////////////////////////////////////////////////////
class WorldNet_ClientPlugin : public IPlugin
{
public:
    WorldNet_ClientPlugin(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual const int GetPluginVersion();

    virtual const std::string GetPluginName();

    virtual void Install();

    virtual void Uninstall();
};

