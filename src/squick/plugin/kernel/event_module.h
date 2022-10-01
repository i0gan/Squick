

#ifndef SQUICK_EVENT_MODULE_H
#define SQUICK_EVENT_MODULE_H

#include <iostream>
#include "squick/core/intf_object.h"
#include "squick/base/guid.h"
#include "squick/base/event.h"
#include "squick/base/kernel.h"

class EventModule
    : public IEventModule
{
public:
    EventModule(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }


    virtual ~EventModule()
    {
    }

	virtual bool Init();
	virtual bool AfterInit();
	virtual bool BeforeShut();
	virtual bool Shut();
	virtual bool Execute();

	virtual bool DoEvent(const int eventID, const DataList& valueList);

	virtual bool ExistEventCallBack(const int eventID);

	virtual bool RemoveEventCallBack(const int eventID);

	//////////////////////////////////////////////////////////
	virtual bool DoEvent(const Guid self, const int eventID, const DataList& valueList);

	virtual bool ExistEventCallBack(const Guid self, const int eventID);

	virtual bool RemoveEventCallBack(const Guid self, const int eventID);
	virtual bool RemoveEventCallBack(const Guid self);

protected:

	virtual bool AddEventCallBack(const int eventID, const MODULE_EVENT_FUNCTOR cb);
    virtual bool AddEventCallBack(const Guid self, const int eventID, const OBJECT_EVENT_FUNCTOR cb);
    virtual bool AddCommonEventCallBack(const OBJECT_EVENT_FUNCTOR cb);

private:

	IKernelModule* m_pKernelModule;

private:
	// for module
	List<int> mModuleRemoveListEx;
	MapEx<int, List<MODULE_EVENT_FUNCTOR>> mModuleEventInfoMapEx;

	//for object
	List<Guid> mObjectRemoveListEx;
	MapEx<Guid, MapEx<int, List<OBJECT_EVENT_FUNCTOR>>> mObjectEventInfoMapEx;

    //for common event
    List<OBJECT_EVENT_FUNCTOR> mCommonEventInfoMapEx;
};

#endif