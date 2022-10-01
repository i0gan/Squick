

#include "security_module.h"
#include "plugin.h"

//
//
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, SecurityPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, SecurityPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int SecurityPlugin::GetPluginVersion()
{
    return 0;
}

const std::string SecurityPlugin::GetPluginName()
{
	return GET_CLASS_NAME(SecurityPlugin);
}

void SecurityPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, ISecurityModule, SecurityModule)

}

void SecurityPlugin::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, ISecurityModule, SecurityModule)
}