#pragma once

#include <squick/core/map.h>
#include <squick/plugin/kernel/i_kernel_module.h>
#include <squick/plugin/config/i_class_module.h>
#include "./i_game_server_module.h"
class GameServerModule
    : public IGameServerModule
{
public:
    GameServerModule(IPluginManager* p)
    {
        m_bIsUpdate = true;
        pPluginManager = p;
    }
    virtual ~GameServerModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Update();

    virtual bool AfterInit();
    virtual bool BeforeShut();


protected:


protected:
    IClassModule* m_pClassModule;
    IKernelModule* m_pKernelModule;
private:
};

