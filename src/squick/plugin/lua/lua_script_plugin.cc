
#include "lua_script_module.h"
#include "lua_pb_module.h"
#include "lua_script_plugin.h"
#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, LuaScriptPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, LuaScriptPlugin)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int LuaScriptPlugin::GetPluginVersion()
{
    return 0;
}

const std::string LuaScriptPlugin::GetPluginName()
{
	return GET_CLASS_NAME(LuaScriptPlugin);
}

void LuaScriptPlugin::Install()
{
	REGISTER_MODULE(pPluginManager, ILuaScriptModule, LuaScriptModule)
	REGISTER_MODULE(pPluginManager, ILuaPBModule, LuaPBModule)

}

void LuaScriptPlugin::Uninstall()
{
	UNREGISTER_MODULE(pPluginManager, ILuaPBModule, LuaPBModule)
	UNREGISTER_MODULE(pPluginManager, ILuaScriptModule, LuaScriptModule)
}