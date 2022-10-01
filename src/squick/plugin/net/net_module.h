

#ifndef SQUICK_NET_MODULE_H
#define SQUICK_NET_MODULE_H

#include "net.h"
#include <iostream>
#include <iosfwd>
#include "squick/struct/struct.h"
#include "squick/core/queue.h"
#include "squick/core/performance.h"
#include "squick/base/net.h"
#include "squick/base/log.h"
#include "squick/base/plugin_manager.h"


#ifdef _MSC_VER
#pragma warning(disable: 4244 4267)
#endif

#include "squick/struct/define.pb.h"

#ifdef _MSC_VER
#pragma warning(default: 4244 4267)
#endif

#if SQUICK_PLATFORM != SQUICK_PLATFORM_WIN
#include "squick/core/exception.h"
#endif

class NetModule : public INetModule
{
public:
    NetModule(IPluginManager* p);

    virtual ~NetModule();

	virtual bool Init();
	virtual bool AfterInit();

    //as client
    virtual void Initialization(const char* ip, const unsigned short nPort);

    //as server
    virtual int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4);

    virtual unsigned int ExpandBufferSize(const unsigned int size = 1024 * 1024 * 20) override;

    virtual void RemoveReceiveCallBack(const int msgID);

    virtual bool AddReceiveCallBack(const int msgID, const NET_RECEIVE_FUNCTOR_PTR& cb);

    virtual bool AddReceiveCallBack(const NET_RECEIVE_FUNCTOR_PTR& cb);

    virtual bool AddEventCallBack(const NET_EVENT_FUNCTOR_PTR& cb);

    virtual bool Execute();


    virtual bool SendMsgWithOutHead(const int msgID, const std::string& msg, const NFSOCK sockIndex);
    virtual bool SendMsgToAllClientWithOutHead(const int msgID, const std::string& msg);

	virtual bool SendMsgPB(const uint16_t msgID, const google::protobuf::Message& xData, const NFSOCK sockIndex);
	virtual bool SendMsgPB(const uint16_t msgID, const google::protobuf::Message& xData, const NFSOCK sockIndex, const Guid id);
	virtual bool SendMsg(const uint16_t msgID, const std::string& xData, const NFSOCK sockIndex);
	virtual bool SendMsg(const uint16_t msgID, const std::string& xData, const NFSOCK sockIndex, const Guid id);

    virtual bool SendMsgPBToAllClient(const uint16_t msgID, const google::protobuf::Message& xData);

    virtual bool SendMsgPB(const uint16_t msgID, const google::protobuf::Message& xData, const NFSOCK sockIndex, const std::vector<Guid>* pClientIDList);
    virtual bool SendMsgPB(const uint16_t msgID, const std::string& strData, const NFSOCK sockIndex,  const std::vector<Guid>* pClientIDList);

    virtual INet* GetNet();

protected:
    void OnReceiveNetPack(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    void OnSocketNetEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void KeepAlive();

private:

    unsigned int mnBufferSize;
    INet* m_pNet;
    INT64 nLastTime;
	std::map<int, std::list<NET_RECEIVE_FUNCTOR_PTR>> mxReceiveCallBack;
    std::list<NET_EVENT_FUNCTOR_PTR> mxEventCallBackList;
    std::list<NET_RECEIVE_FUNCTOR_PTR> mxCallBackList;

	ILogModule* m_pLogModule;
};

#endif