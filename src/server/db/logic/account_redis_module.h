#pragma once

#include <squick/struct/struct.h>
#include <squick/struct/protocol_define.h>
#include <squick/plugin/config/i_class_module.h>
#include <squick/plugin/config/i_element_module.h>
#include <squick/plugin/log/i_log_module.h>
#include <squick/plugin/no_sql/i_no_sql_module.h>
#include <squick/core/i_plugin_manager.h>
#include <squick/plugin/kernel/i_kernel_module.h>


#include "i_player_redis_module.h"
#include "i_account_redis_module.h"
#include "i_common_redis_module.h"

class AccountRedisModule : public IAccountRedisModule
{
public:

	AccountRedisModule(IPluginManager* p)
	{
		pPluginManager = p;
	}

	virtual bool Start();
	virtual bool Destory();
	virtual bool Update();

	virtual bool AfterStart();

	virtual bool VerifyAccount(const std::string& account, const std::string& strPwd);
	virtual bool AddAccount(const std::string& account, const std::string& strPwd);
	virtual bool ExistAccount(const std::string& account);


protected:

private:
	IClassModule* m_pLogicClassModule;
	INoSqlModule* m_pNoSqlModule;
	ICommonRedisModule* m_pCommonRedisModule;
	IKernelModule* m_pKernelModule;
};

