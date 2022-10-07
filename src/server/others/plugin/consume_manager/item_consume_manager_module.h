

#ifndef SQUICK_ITEM_CONSUME_MANAGER_MODULE_H
#define SQUICK_ITEM_CONSUME_MANAGER_MODULE_H

#include <iostream>
#include <squick/base/plugin_manager.h>

#include "if_item_consume_manager_module.h"
class ItemConsumeManagerModule
    : public IItemConsumeManagerModule
{
public:

    ItemConsumeManagerModule( IPluginManager* p )
    {
        pPluginManager = p;
    }
    virtual bool Init() override;
    virtual bool Shut() override;
    virtual bool Update() override;
    virtual bool AfterInit() override;

	virtual bool SetConsumeModule(const int itemType, IItemConsumeProcessModule* pModule);
	virtual bool SetConsumeModule(const int itemType, const int itemSubType, IItemConsumeProcessModule* pModule);

	virtual IItemConsumeProcessModule* GetConsumeModule(const int itemType);
	virtual IItemConsumeProcessModule* GetConsumeModule(const int itemType, const int itemSubType);

private:

    std::map<Guid, IItemConsumeProcessModule*> mItemConsumeModule;
};

#endif
