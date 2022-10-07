
#include "kernel_plugin.h"
#include "kernel_module.h"
#include "scene_module.h"
#include "event_module.h"
#include "schedule_module.h"
#include "data_tail_module.h"
#include "cell_module.h"
#include "thread_pool_module.h"
#include "elo_module.h"

#ifdef SQUICK_DYNAMIC_PLUGIN

SQUICK_EXPORT void DllStartPlugin(IPluginManager* pm)
{
    CREATE_PLUGIN(pm, KernelPlugin)

};

SQUICK_EXPORT void DllStopPlugin(IPluginManager* pm)
{
    DESTROY_PLUGIN(pm, KernelPlugin)
};

#endif

//////////////////////////////////////////////////////////////////////////

const int KernelPlugin::GetPluginVersion()
{
    return 0;
}

const std::string KernelPlugin::GetPluginName()
{
	return GET_CLASS_NAME(KernelPlugin);
}

void KernelPlugin::Install()
{
    REGISTER_MODULE(pPluginManager, ISceneModule, SceneModule)
	REGISTER_MODULE(pPluginManager, IKernelModule, NFKernelModule)
	REGISTER_MODULE(pPluginManager, IEventModule, EventModule)
	REGISTER_MODULE(pPluginManager, IScheduleModule, NFScheduleModule)
	REGISTER_MODULE(pPluginManager, IDataTailModule, NFDataTailModule)
	REGISTER_MODULE(pPluginManager, NFICellModule, CellModule)
	REGISTER_MODULE(pPluginManager, IThreadPoolModule, ThreadPoolModule)
	REGISTER_MODULE(pPluginManager, IELOModule, ELOModule)

	/*
	REGISTER_TEST_MODULE(pPluginManager, IKernelModule, NFKernelTestModule)
	REGISTER_TEST_MODULE(pPluginManager, IEventModule, NFEventTestModule)
	REGISTER_TEST_MODULE(pPluginManager, IScheduleModule, NFScheduleTestModule)
	*/
}

void KernelPlugin::Uninstall()
{
	/*
	UNREGISTER_TEST_MODULE(pPluginManager, IEventModule, NFEventTestModule)
	UNREGISTER_TEST_MODULE(pPluginManager, IKernelModule, NFKernelTestModule)
	UNREGISTER_TEST_MODULE(pPluginManager, IScheduleModule, NFScheduleTestModule)
*/
	UNREGISTER_MODULE(pPluginManager, IELOModule, ELOModule)
	UNREGISTER_MODULE(pPluginManager, IThreadPoolModule, ThreadPoolModule)
	UNREGISTER_MODULE(pPluginManager, NFICellModule, CellModule)
	UNREGISTER_MODULE(pPluginManager, IDataTailModule, NFDataTailModule)
	UNREGISTER_MODULE(pPluginManager, IEventModule, EventModule)
	UNREGISTER_MODULE(pPluginManager, IKernelModule, NFKernelModule)
	UNREGISTER_MODULE(pPluginManager, ISceneModule, SceneModule)
	UNREGISTER_MODULE(pPluginManager, IScheduleModule, NFScheduleModule)

}