

#ifndef SQUICK_HELLO_WORLD4_H
#define SQUICK_HELLO_WORLD4_H

#include <thread>
#include "squick/base/kernel.h"
#include "squick/base/actor.h"
#include "squick/base/component.h"
#include "squick/base/thread_pool.h"



class HttpComponent : public IComponent
{
public:
	HttpComponent() : IComponent(typeid(HttpComponent).name())
	{
	}

	virtual ~HttpComponent()
	{

	}

	virtual bool Init()
	{
		AddMsgHandler(0, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(1, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(2, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(3, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(4, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(5, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(6, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(7, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(8, this, &HttpComponent::OnMsgEvent);
		AddMsgHandler(9, this, &HttpComponent::OnMsgEvent);

		return true;
	}

	//it's very important to note here:
	//sometimes, the function below not finished but other thread call it at the same time
	//the reason is the main thread post a new message to this actor and the schedulel assigned another thread to take the execution right
	//so, you wouldnot use the data which not thread-safe in this function
	virtual int OnMsgEvent(ActorMessage& arg)
	{

		std::cout << "Thread: " << std::this_thread::get_id() << " MsgID: " << arg.msgID << " Data:" << arg.data << std::endl;


		return 0;
	}
};

class IHelloWorld4Module
	: public IModule
{
};

class HelloWorld4Module
    : public IHelloWorld4Module
{
public:
    HelloWorld4Module(IPluginManager* p)
    {
        m_bIsExecute = true;
        pPluginManager = p;
    }

    virtual bool Init();
    virtual bool AfterInit();

    virtual bool Execute();

    virtual bool BeforeShut();
    virtual bool Shut();

protected:
	void RequestAsyEnd(ActorMessage& actorMessage);
	
protected:
    IActorModule* m_pActorModule;
	IThreadPoolModule* m_pThreadPoolModule;
};

#endif
