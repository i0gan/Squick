#pragma once

#include <iostream>
#include <squick/core/i_module.h>
#include <squick/plugin/net/i_net_client_module.h>

class IProxyServerToWorldModule
    : public  IModule
{
public:
    virtual bool VerifyConnectData(const std::string& account, const std::string& strKey) = 0;
};
