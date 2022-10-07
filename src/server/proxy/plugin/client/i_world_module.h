
#ifndef SQUICK_INTF_PROXYNET_CLIENTMODULE_H
#define SQUICK_INTF_PROXYNET_CLIENTMODULE_H

#include <iostream>
#include <squick/base/module.h>
#include <squick/base/net_client.h>

class IProxyServerToWorldModule
    : public  IModule
{
public:
    virtual bool VerifyConnectData(const std::string& account, const std::string& strKey) = 0;
};

#endif