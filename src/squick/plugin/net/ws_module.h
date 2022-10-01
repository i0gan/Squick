
#ifndef SQUICK_WS_SERVER_MODULE_H
#define SQUICK_WS_SERVER_MODULE_H

#include <iostream>
#include "net_module.h"
#include "squick/base/ws.h"

class WSModule: public IWSModule
{
public:
    WSModule(IPluginManager* p);

    virtual ~WSModule();

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

    virtual bool SendMsg(const std::string& msg, const NFSOCK sockIndex, const bool text = true);
    virtual bool SendMsgToAllClient(const std::string& msg, const bool text = true);
    virtual bool SendMsgWithOutHead(const int16_t msgID, const char* msg, const size_t len, const NFSOCK sockIndex /*= 0*/);
    virtual bool SendMsgPB(const uint16_t msgID, const google::protobuf::Message& xData, const NFSOCK sockIndex);
    int EnCode(const uint16_t umsgID, const char* strData, const uint32_t unDataLen, std::string& strOutData);
    virtual INet* GetNet();

    virtual void OnError(const NFSOCK sockIndex, const std::error_code& e);
protected:
    bool SendRawMsg(const std::string& msg, const NFSOCK sockIndex);

    void OnReceiveNetPack(const NFSOCK sockIndex, const int msgID, const char* msg, const uint32_t len);

    void OnSocketNetEvent(const NFSOCK sockIndex, const SQUICK_NET_EVENT eEvent, INet* pNet);

    void KeepAlive();

    std::error_code HandShake(const NFSOCK sockIndex, const char* msg, const uint32_t len);

    std::error_code DecodeFrame(const NFSOCK sockIndex,NetObject* pNetObject);
    int DeCode(const char* strData, const uint32_t unAllLen, SquickStructHead& xHead);

    std::string EncodeFrame(const char* data, size_t size, bool text);
    

    std::string HashKey(const char* key, size_t len);
private:

    unsigned int mnBufferSize;
    INet* m_pNet;
    INT64 mLastTime;
	std::map<int, std::list<NET_RECEIVE_FUNCTOR_PTR>> mxReceiveCallBack;
    std::list<NET_EVENT_FUNCTOR_PTR> mxEventCallBackList;
    std::list<NET_RECEIVE_FUNCTOR_PTR> mxCallBackList;

	ILogModule* m_pLogModule;
};

#endif
