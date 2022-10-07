#pragma once

#include <iostream>
#include <squick/core/i_module.h>

class ICreateRoleModule : public IModule
{
public:
	virtual void SetDefaultSceneID(const int sceneID) = 0;
};
