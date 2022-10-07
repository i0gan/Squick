
#ifndef SQUICK_INTF_PROXYNET_SERVERMODULE_H
#define SQUICK_INTF_PROXYNET_SERVERMODULE_H

#include <iostream>
#include <squick/base/module.h>
#include <squick/base/net_client.h>

class IProxyServerNet_ServerModule
    :  public IModule
{

public:
    virtual int Transport(const SQUICK_SOCKET sockIndex, const int msgID, const char* msg, const uint32_t len) = 0;
    virtual int EnterGameSuccessEvent(const Guid xClientID, const Guid xPlayerID) = 0;
};

#endif