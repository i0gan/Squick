

#ifndef SQUICK_INVENTORY_MODULE_H
#define SQUICK_INVENTORY_MODULE_H

#include "squick/base/kernel.h"
#include "squick/base/element.h"
#include "squick/base/log.h"
#include "squick/base/plugin_manager.h"

#include "if_inventory_module.h"
#include "server/game/plugin/logic/if_property_module.h"
#include "server/game/plugin/logic/if_scene_process_module.h"
class InventoryModule
    : public IInventoryModule
{
public:

	InventoryModule(IPluginManager* p )
    {
        pPluginManager = p;
    }
    virtual ~InventoryModule() {};

    virtual bool Init() override;
    virtual bool Shut() override;
    virtual bool Update() override;
    virtual bool AfterInit() override;

	///////////
	virtual Guid CreateEquip( const Guid& self, const std::string& configName, const int count = 1);
	virtual bool CreateItem(const Guid& self, const std::string& configName, const int count);

	virtual int ItemCount(const Guid& self, const std::string& strItemConfigID);

	virtual bool DeleteEquip(const Guid& self, const Guid& id);
    virtual bool DeleteItem(const Guid& self, const std::string& strItemConfigID, const int count);
    virtual bool EnoughItem(const Guid& self, const std::string& strItemConfigID, const int count);

protected:
	bool CreateItemInNormalBag(const Guid& self, const std::string& configName, const int count);

private:
    IKernelModule* m_pKernelModule;
    ILogModule* m_pLogModule;
    IElementModule* m_pElementModule;
    ISceneProcessModule* m_pSceneProcessModule;
    IPropertyModule* m_pPropertyModule;
};


#endif
