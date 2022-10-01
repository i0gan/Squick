

#include "Tutorial6.h"
#include "HelloWorld6.h"

#ifdef NF_DYNAMIC_PLUGIN

NF_EXPORT void DllStartPlugin(IPluginManager* pm)
{

    CREATE_PLUGIN(pm, Tutorial6)

};

NF_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, Tutorial6)
};

#endif
//////////////////////////////////////////////////////////////////////////

const int Tutorial6::GetPluginVersion()
{
    return 0;
}

const std::string Tutorial6::GetPluginName()
{
	return GET_CLASS_NAME(Tutorial6);
}

void Tutorial6::Install()
{
    REGISTER_MODULE(pPluginManager, NFIHelloWorld6, NFHelloWorld6)
    
}

void Tutorial6::Uninstall()
{
    UNREGISTER_MODULE(pPluginManager, NFIHelloWorld6, NFHelloWorld6)
}