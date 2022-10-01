

#ifndef SQUICK_INTF_WS_MODULE_H
#define SQUICK_INTF_WS_MODULE_H

#include <iostream>
#include <iosfwd>
#include "guid.h"
#include "module.h"
#include "log.h"
#include "plugin_manager.h"
#include "squick/plugin/net/inet.h"
#include "squick/core/queue.h"
#ifdef _MSC_VER
#pragma warning(disable: 4244 4267)
#endif


////////////////////////////////////////////////////////////////////////////

class IWSModule
    : public IModule
{
public:

	template<typename BaseType>
	bool AddReceiveCallBack(const int msgID, BaseType* pBase, void (BaseType::*handleReceiver)(const NFSOCK, const int, const char*, const uint32_t))
	{
		NET_RECEIVE_FUNCTOR functor = std::bind(handleReceiver, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		NET_RECEIVE_FUNCTOR_PTR functorPtr(new NET_RECEIVE_FUNCTOR(functor));

		return AddReceiveCallBack(msgID, functorPtr);
	}

	template<typename BaseType>
	bool AddReceiveCallBack(BaseType* pBase, void (BaseType::*handleReceiver)(const NFSOCK, const int, const char*, const uint32_t))
	{
		NET_RECEIVE_FUNCTOR functor = std::bind(handleReceiver, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		NET_RECEIVE_FUNCTOR_PTR functorPtr(new NET_RECEIVE_FUNCTOR(functor));

		return AddReceiveCallBack(functorPtr);
	}

	template<typename BaseType>
	bool AddEventCallBack(BaseType* pBase, void (BaseType::*handler)(const NFSOCK, const SQUICK_NET_EVENT, INet*))
	{
		NET_EVENT_FUNCTOR functor = std::bind(handler, pBase, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		NET_EVENT_FUNCTOR_PTR functorPtr(new NET_EVENT_FUNCTOR(functor));

		return AddEventCallBack(functorPtr);
	}

	//as client
	virtual void Initialization(const char* ip, const unsigned short nPort) = 0;

	//as server
	virtual int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4) = 0;
	virtual unsigned int ExpandBufferSize(const unsigned int size = 1024 * 1024 * 20) = 0;

	virtual void RemoveReceiveCallBack(const int msgID) = 0;

	virtual bool AddReceiveCallBack(const int msgID, const NET_RECEIVE_FUNCTOR_PTR& cb) = 0;

	virtual bool AddReceiveCallBack(const NET_RECEIVE_FUNCTOR_PTR& cb) = 0;

	virtual bool AddEventCallBack(const NET_EVENT_FUNCTOR_PTR& cb) = 0;

	virtual bool Execute() = 0;
    virtual bool SendMsgPB(const uint16_t msgID, const google::protobuf::Message& xData, const NFSOCK sockIndex)=0;
	virtual bool SendMsg(const std::string& msg, const NFSOCK sockIndex, const bool text = true) = 0;
	virtual bool SendMsgToAllClient(const std::string& msg, const bool text = true) = 0;

	virtual INet* GetNet() = 0;
};

#endif
