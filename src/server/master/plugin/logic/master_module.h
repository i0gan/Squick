
#ifndef SQUICK_MASTER_MODULE_H
#define SQUICK_MASTER_MODULE_H

#include "squick/base/kernel.h"
//#include "../server/if_server_module.h"
#include "if_master_module.h"


class MasterModule
    : public IMasterModule
{

public:
    MasterModule(IPluginManager* p)
    {
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool Shut();
    virtual bool Update();
protected:


private:

    IKernelModule* m_pKernelModule;
};

#endif