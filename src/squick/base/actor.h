

#ifndef SQUICK_INTF_ACTOR_MODULE_H
#define SQUICK_INTF_ACTOR_MODULE_H

#include "module.h"
#include "component.h"

///////////////////////////////////////////////////

class IActorModule : public IModule
{
public:
	template<typename TypeComponent>
	bool AddComponent(const Guid nActorIndex)
	{
		if (!TIsDerived<TypeComponent, IComponent>::Result)
		{
			//BaseTypeComponent must inherit from IComponent;
			return false;
		}

		SQUICK_SHARE_PTR<IActor> pActor = GetActor(nActorIndex);
		if (pActor)
		{
			auto component = pActor->AddComponent<TypeComponent>();
			if (component)
			{
				return true;
			}
		}

		return false;
	}

	template<typename BaseType>
	int AddEndFunc(const int subMessageID, BaseType* pBase, void (BaseType::*handler_end)(ActorMessage&))
	{
		ACTOR_PROCESS_FUNCTOR functor_end = std::bind(handler_end, pBase, std::placeholders::_1);
		ACTOR_PROCESS_FUNCTOR_PTR functorPtr_end(new ACTOR_PROCESS_FUNCTOR(functor_end));

		return AddEndFunc(subMessageID, functorPtr_end);
	}

    int AddEndFunc(const int subMessageID, ACTOR_PROCESS_FUNCTOR functor_end)
	{
		ACTOR_PROCESS_FUNCTOR_PTR functorPtr_end(new ACTOR_PROCESS_FUNCTOR(functor_end));

		return AddEndFunc(subMessageID, functorPtr_end);
	}

	virtual SQUICK_SHARE_PTR<IActor> RequireActor() = 0;
	virtual SQUICK_SHARE_PTR<IActor> GetActor(const Guid nActorIndex) = 0;
	virtual bool ReleaseActor(const Guid nActorIndex) = 0;

	virtual bool SendMsgToActor(const Guid actorIndex, const Guid who, const int eventID, const std::string& data, const std::string& arg = "") = 0;

	//only be called by actor's processor
    virtual bool AddResult(const ActorMessage& message) = 0;

protected:

	virtual bool AddEndFunc(const int subMessageID, ACTOR_PROCESS_FUNCTOR_PTR functorPtr_end) = 0;
};

#endif
