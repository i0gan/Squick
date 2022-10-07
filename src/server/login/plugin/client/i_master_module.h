
#ifndef SQUICK_INTF_LOGINNET_CLIENTMODULE_H
#define SQUICK_INTF_LOGINNET_CLIENTMODULE_H

#include <iostream>
#include <squick/base/module.h>
#include <squick/base/net_client.h>
#include "squick/struct/msg_pre_game.pb.h"

class ILoginToMasterModule
    : public IModule
{
public:
	virtual INetClientModule* GetClusterModule() = 0;
    virtual MapEx<int, SquickStruct::ServerInfoReport>& GetWorldMap() = 0;
};

#endif
