

#ifndef SQUICK_HELLO_WORLD_H
#define SQUICK_HELLO_WORLD_H

#include "squick/base/plugin.h"
#include "squick/base/plugin_manager.h"
#include "squick/base/navigation.h"
#include "squick/plugin/no_sql/redis_client.h"
#include "squick/core/performance.h"


class IHelloWorld7
	: public IModule
{

};

class HelloWorld7
    : public IHelloWorld7
{
public:
    HelloWorld7(IPluginManager* p)
    {
        m_bIsUpdate = true;
        pPluginManager = p;
    }

    virtual bool Start();
    virtual bool AfterStart();

    virtual bool Update();

    virtual bool BeforeDestory();
    virtual bool Destory();

protected:

	bool Test_1();
	bool TestPerformance();

    void TestHash();
    void TestKey();
    void TestList();
    void TestSet();
    void TestSort();
    void TestString();
	void TestPubSub();

protected:
    RedisClient mxRedisClient;
};

#endif
