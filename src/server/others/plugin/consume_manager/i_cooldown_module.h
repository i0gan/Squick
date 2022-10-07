

#ifndef SQUICK_INTF_COOLDOWN_MODULE_H
#define SQUICK_INTF_COOLDOWN_MODULE_H

#include <iostream>
#include <squick/base/module.h>

class ICooldownModule
    : public IModule
{
public:

    virtual void AddCooldown(const Guid& self, const std::string& configID) = 0;
    virtual bool ExistCooldown(const Guid& self, const std::string& configID) = 0;
};

#endif