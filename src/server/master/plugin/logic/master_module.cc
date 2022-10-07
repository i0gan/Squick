
#include "master_module.h"
#include "plugin.h"

bool MasterModule::Init()
{

    m_pKernelModule = pPluginManager->FindModule<IKernelModule>();

    return true;
}

bool MasterModule::Shut()
{
    return true;
}

bool MasterModule::Update()
{


    return true;
}
