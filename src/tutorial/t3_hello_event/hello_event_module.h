

#ifndef SQUICK_HELLO_WORLD3_H
#define SQUICK_HELLO_WORLD3_H

#include "squick/base/kernel.h"
#include "squick/base/element.h"
#include "squick/base/event.h"
#include "squick/base/schedule.h"

class IHelloEventModule
	: public IModule
{

};

class HelloEventModule
    : public IHelloEventModule
{
public:
    HelloEventModule(IPluginManager* p)
    {
        m_bIsUpdate = true;
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Update();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:
    int OnEvent(const Guid& self, const int event, const DataList& arg);
    int OnClassCallBackEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT event, const DataList& arg);
    int OnPropertyCallBackEvent( const Guid& self, const std::string& propertyName, const SquickData& oldVarList, const SquickData& newVarList, const int64_t reason);
    int OnPropertyStrCallBackEvent( const Guid& self, const std::string& propertyName, const SquickData& oldVarList, const SquickData& newVarList, const int64_t reason);

    int OnHeartBeat(const Guid& self, const std::string& heartBeat, const float time, const int count);

protected:
    int64_t mLastTime;
protected:
    IKernelModule* m_pKernelModule;
    IElementModule* m_pElementModule;
	IEventModule* m_pEventModule;
	IScheduleModule* m_pScheduleModule;
};

#endif
