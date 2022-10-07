

#ifndef SQUICK_INTF_MASTERNET_SERVERMODULE_H
#define SQUICK_INTF_MASTERNET_SERVERMODULE_H

#include <iostream>
#include <squick/base/module.h>

class IMasterNet_ServerModule
    : public IModule
{

public:
	virtual std::string GetServersStatus() = 0;
};

#endif