

#include <squick/struct/protocol_define.h>

#include "create_role_module.h"
#include <server/db/plugin/logic/common_redis_module.h>

bool CreateRoleModule::Start()
{
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pNetModule = pPluginManager->FindModule<INetModule>();
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pGameToDBModule = pPluginManager->FindModule<IGameServerToDBModule>();
	m_pSceneProcessModule = pPluginManager->FindModule<ISceneProcessModule>();
	m_pGameServerNet_ServerModule = pPluginManager->FindModule<IGameServerNet_ServerModule>();
	m_pNetClientModule = pPluginManager->FindModule<INetClientModule>();
	m_pScheduleModule = pPluginManager->FindModule<IScheduleModule>();
	m_pDataTailModule = pPluginManager->FindModule<IDataTailModule>();
	m_pSceneModule = pPluginManager->FindModule<ISceneModule>();
	m_pEventModule = pPluginManager->FindModule<IEventModule>();

    return true;
}

bool CreateRoleModule::AfterStart()
{
	m_pKernelModule->AddClassCallBack(SquickProtocol::Player::ThisName(), this, &CreateRoleModule::OnObjectPlayerEvent);

	return true;
}

bool CreateRoleModule::ReadyUpdate()
{
	m_pNetModule->RemoveReceiveCallBack(SquickStruct::REQ_ROLE_LIST);
	m_pNetModule->RemoveReceiveCallBack(SquickStruct::REQ_CREATE_ROLE);
	m_pNetModule->RemoveReceiveCallBack(SquickStruct::REQ_DELETE_ROLE);
	m_pNetModule->RemoveReceiveCallBack(SquickStruct::REQ_ENTER_GAME);


	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_ROLE_LIST, this, &CreateRoleModule::OnRequireRoleListProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_CREATE_ROLE, this, &CreateRoleModule::OnCreateRoleGameProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_DELETE_ROLE, this, &CreateRoleModule::OnDeleteRoleGameProcess);
	m_pNetModule->AddReceiveCallBack(SquickStruct::REQ_ENTER_GAME, this, &CreateRoleModule::OnClientEnterGameProcess);

	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_DB, SquickStruct::ACK_ROLE_LIST, this, &CreateRoleModule::OnResponseRoleListProcess);
	m_pNetClientModule->AddReceiveCallBack(SQUICK_SERVER_TYPES::SQUICK_ST_DB, SquickStruct::ACK_LOAD_ROLE_DATA, this, &CreateRoleModule::OnDBLoadRoleDataProcess);

	return true;
}

void CreateRoleModule::OnRequireRoleListProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	m_pNetClientModule->SendBySuitWithOutHead(SQUICK_SERVER_TYPES::SQUICK_ST_DB, sockIndex, msgID, std::string(msg, len));
}

void CreateRoleModule::OnResponseRoleListProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	Guid clientID;
	SquickStruct::AckRoleLiteInfoList xData;
	if (!m_pNetModule->ReceivePB(msgID, msg, len, xData, clientID))
	{
		return;
	}

	SQUICK_SHARE_PTR<IGameServerNet_ServerModule::GateServerInfo> xGateInfo = m_pGameServerNet_ServerModule->GetGateServerInfo(clientID.GetHead());
	if (xGateInfo)
	{
		m_pNetModule->SendMsgWithOutHead (msgID, std::string(msg, len), xGateInfo->xServerData.nFD);
	}
}

void CreateRoleModule::OnCreateRoleGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	m_pNetClientModule->SendBySuitWithOutHead(SQUICK_SERVER_TYPES::SQUICK_ST_DB, sockIndex, msgID, std::string(msg, len));
}

void CreateRoleModule::OnDeleteRoleGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	m_pNetClientModule->SendBySuitWithOutHead(SQUICK_SERVER_TYPES::SQUICK_ST_DB, sockIndex, msgID, std::string(msg, len));
}

void CreateRoleModule::OnClientEnterGameProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	Guid clientID;
	SquickStruct::ReqEnterGameServer xMsg;
	if (!m_pNetModule->ReceivePB( msgID, msg, len, xMsg, clientID))
	{
		return;
	}

	Guid roleID = INetModule::ProtobufToStruct(xMsg.id());

	if (m_pKernelModule->GetObject(roleID))
	{
		m_pKernelModule->DestroyObject(roleID);
	}

	//////////////////////////////////////////////////////////////////////////

	SQUICK_SHARE_PTR<IGameServerNet_ServerModule::GateBaseInfo>  pGateInfo = m_pGameServerNet_ServerModule->GetPlayerGateInfo(roleID);
	if (nullptr != pGateInfo)
	{
		if (pGateInfo->eStatus == IGameServerNet_ServerModule::GateBaseInfo::E_LOADING)
		{
			return;
		}

		m_pGameServerNet_ServerModule->RemovePlayerGateInfo(roleID);
	}

	SQUICK_SHARE_PTR<IGameServerNet_ServerModule::GateServerInfo> pGateServerinfo = m_pGameServerNet_ServerModule->GetGateServerInfoBySockIndex(sockIndex);
	if (nullptr == pGateServerinfo)
	{
		return;
	}

	int gateID = -1;
	if (pGateServerinfo->xServerData.pData)
	{
		gateID = pGateServerinfo->xServerData.pData->server_id();
	}

	if (gateID < 0)
	{
		return;
	}

	if (!m_pGameServerNet_ServerModule->AddPlayerGateInfo(roleID, clientID, gateID))
	{
		return;
	}

	m_pNetClientModule->SendBySuitWithOutHead(SQUICK_SERVER_TYPES::SQUICK_ST_DB, sockIndex, SquickStruct::REQ_LOAD_ROLE_DATA, std::string(msg, len));

}

void CreateRoleModule::OnDBLoadRoleDataProcess(const SQUICK_SOCKET sockIndex, const int msgID, const char * msg, const uint32_t len)
{
	Guid clientID;
	SquickStruct::RoleDataPack xMsg;
	if (!m_pNetModule->ReceivePB(msgID, msg, len, xMsg, clientID))
	{
		//releasing all the resource that allow when the user login, then kick off the user
		// TODO

		//m_pGameServerNet_ServerModule->RemovePlayerGateInfo();

		//Avtually, the developer may not know the user id in this situation, therefore the developer must record the login-time when the user coming
		//and check the time per min to kick off the user who are not active.

		return;
	}

	Guid roleID = INetModule::ProtobufToStruct(xMsg.id());
	if (m_pKernelModule->GetObject(roleID))
	{
		//it should be rebind with proxy's netobject
		m_pKernelModule->DestroyObject(roleID);
	}

	mxObjectDataCache[roleID] = xMsg;

	SQUICK_SHARE_PTR<IGameServerNet_ServerModule::GateBaseInfo>  pGateInfo = m_pGameServerNet_ServerModule->GetPlayerGateInfo(roleID);
	if (nullptr != pGateInfo)
	{
		if (pGateInfo->eStatus == IGameServerNet_ServerModule::GateBaseInfo::E_LOADING)
		{
			pGateInfo->eStatus = IGameServerNet_ServerModule::GateBaseInfo::E_LOADED;
		}


		DataList var;

		var.AddString(SquickProtocol::Player::GateID());
		var.AddInt(pGateInfo->gateID);

		var.AddString(SquickProtocol::Player::GameID());
		var.AddInt(pPluginManager->GetAppID());

		var.AddString(SquickProtocol::Player::Connection());
		var.AddInt(1);

		/*
		var.AddString(SquickProtocol::Player::HomeSceneID());
		var.AddInt(1);

		var.AddString(SquickProtocol::Player::SceneID());
		var.AddInt(1);
		*/

		SQUICK_SHARE_PTR<IObject> pObject = m_pKernelModule->CreateObject(roleID, defaultSceneID, 0, SquickProtocol::Player::ThisName(), "", var);
		if (nullptr == pObject)
		{
			//mRoleBaseData
			//mRoleFDData
			mxObjectDataCache.erase(roleID);
			return;
		}

		/////other modules may move the player to other scene or group at ON_FINISHED event by require
		/////if other modules moved the player, the group id > 0
		const int group = m_pKernelModule->GetPropertyInt(pObject->Self(), SquickProtocol::IObject::GroupID());
		if (group <= 0)
		{
			/////////////////////////////
			//sometimes, the player might disconnected from game server and want to reconnect.
			//Basic on this reason, developer could move this kinds of players into the specific scene or group to avoid players move to the default scene.
			//If developers move that kinds of players into the specific scene or group, which means the group value will NOT ZERO!
			//COE_CREATE_FINISH

			/////////////////////////////
			const Vector3& pos = m_pSceneModule->GetRelivePosition(defaultSceneID, 0);
			const int sceneType = m_pElementModule->GetPropertyInt(std::to_string(defaultSceneID), SquickProtocol::Scene::Type());
			if (sceneType == SquickStruct::SINGLE_CLONE_SCENE)
			{
				const int groupID = m_pKernelModule->RequestGroupScene(defaultSceneID);
				m_pSceneModule->SetPropertyObject(defaultSceneID, groupID, SquickProtocol::Group::MasterID(), pObject->Self());

				m_pSceneProcessModule->RequestEnterScene(pObject->Self(), defaultSceneID, groupID, 0, pos, DataList::Empty());
			}
			else if (sceneType == SquickStruct::NORMAL_SCENE)
			{
				m_pSceneProcessModule->RequestEnterScene(pObject->Self(), defaultSceneID, 1, 0, pos, DataList::Empty());
			}
		}
	}
}

int CreateRoleModule::OnObjectPlayerEvent(const Guid & self, const std::string & className, const CLASS_OBJECT_EVENT classEvent, const DataList & var)
{
	if (CLASS_OBJECT_EVENT::COE_DESTROY == classEvent)
	{
		//m_pDataTailModule->LogObjectData(self);

		m_pKernelModule->SetPropertyInt(self, SquickProtocol::Player::LastOfflineTime(), NFGetTimeS());
		SaveData(self);
	}
	else if (CLASS_OBJECT_EVENT::COE_CREATE_LOADDATA == classEvent)
	{
		//m_pDataTailModule->StartTrail(self);
		//m_pDataTailModule->LogObjectData(self);

		AttachData(self);

		m_pKernelModule->SetPropertyInt(self, SquickProtocol::Player::OnlineTime(), NFGetTimeS());
	}
	else if (CLASS_OBJECT_EVENT::COE_CREATE_FINISH == classEvent)
	{
		auto it = mxObjectDataCache.find(self);
		if (it != mxObjectDataCache.end())
		{
			mxObjectDataCache.erase(it);
		}


		m_pScheduleModule->AddSchedule(self, "SaveDataOnTime", this, &CreateRoleModule::SaveDataOnTime, 180.0f, -1);
	}

	return 0;
}

void CreateRoleModule::AttachData(const Guid & self)
{
	auto it = mxObjectDataCache.find(self);
	if (it != mxObjectDataCache.end())
	{
		SQUICK_SHARE_PTR<IObject> xObject = m_pKernelModule->GetObject(self);
		if (xObject)
		{
			SQUICK_SHARE_PTR<IPropertyManager> xPropManager = xObject->GetPropertyManager();
			SQUICK_SHARE_PTR<IRecordManager> xRecordManager = xObject->GetRecordManager();

			if (xPropManager)
			{
				CommonRedisModule::ConvertPBToPropertyManager(it->second.property(), xPropManager);
			}

			if (xRecordManager)
			{
				CommonRedisModule::ConvertPBToRecordManager(it->second.record(), xRecordManager);
			}

			mxObjectDataCache.erase(it);

			xObject->SetPropertyInt(SquickProtocol::Player::GateID(), pPluginManager->GetAppID());

			auto playerGateInfo = m_pGameServerNet_ServerModule->GetPlayerGateInfo(self);
			if (playerGateInfo)
			{
				xObject->SetPropertyInt(SquickProtocol::Player::GateID(), playerGateInfo->gateID);
			}
		}
	}
}

void CreateRoleModule::SaveData(const Guid & self)
{
	SQUICK_SHARE_PTR<IObject> xObject = m_pKernelModule->GetObject(self);
	if (xObject)
	{
		SQUICK_SHARE_PTR<IPropertyManager> xPropManager = xObject->GetPropertyManager();
		SQUICK_SHARE_PTR<IRecordManager> xRecordManager = xObject->GetRecordManager();
		SquickStruct::RoleDataPack xDataPack;

		*xDataPack.mutable_id() = INetModule::StructToProtobuf(self);

		*(xDataPack.mutable_property()->mutable_player_id()) = INetModule::StructToProtobuf(self);
		*(xDataPack.mutable_record()->mutable_player_id()) = INetModule::StructToProtobuf(self);

		if (xPropManager)
		{
			CommonRedisModule::ConvertPropertyManagerToPB(xPropManager, xDataPack.mutable_property(), false, true);
		}

		if (xRecordManager)
		{
			CommonRedisModule::ConvertRecordManagerToPB(xRecordManager, xDataPack.mutable_record(), false, true);
		}

		m_pNetClientModule->SendSuitByPB(SQUICK_SERVER_TYPES::SQUICK_ST_DB, self.GetData(), SquickStruct::REQ_SAVE_ROLE_DATA, xDataPack);
	}
}

int CreateRoleModule::SaveDataOnTime(const Guid & self, const std::string & name, const float fIntervalTime, const int count)
{
	SaveData(self);
	return 0;
}

bool CreateRoleModule::Destory()
{
    return true;
}

bool CreateRoleModule::Update()
{
    return true;
}

void CreateRoleModule::SetDefaultSceneID(const int sceneID)
{
	defaultSceneID = sceneID;
}

