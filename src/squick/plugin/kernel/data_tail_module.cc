
#include "data_tail_module.h"
#include "squick/base/plugin_manager.h"
#include "squick/core/data_list.h"
#include "squick/struct/protocol_define.h"

#if SQUICK_PLATFORM != SQUICK_PLATFORM_WIN
#include <execinfo.h>
#endif

bool NFDataTailModule::Init()
{
	m_pKernelModule = pPluginManager->FindModule<IKernelModule>();
	m_pElementModule = pPluginManager->FindModule<IElementModule>();
	m_pClassModule = pPluginManager->FindModule<IClassModule>();
	m_pLogModule = pPluginManager->FindModule<ILogModule>();

    return true;
}


bool NFDataTailModule::Shut()
{
    return true;
}

bool NFDataTailModule::Execute()
{
    return true;
}

bool NFDataTailModule::AfterInit()
{
#ifdef SQUICK_DEBUG_MODE
    m_pKernelModule->AddClassCallBack(SquickProtocol::Player::ThisName(), this, &NFDataTailModule::OnClassObjectEvent);
#endif
    return true;
}

int NFDataTailModule::OnClassObjectEvent(const Guid& self, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& var)
{
    if (CLASS_OBJECT_EVENT::COE_CREATE_AFTER_ATTACHDATA == classEvent)
	{
	    TrailObjectData(self);
	}

    std::ostringstream stream;
    switch (classEvent)
    {
        case CLASS_OBJECT_EVENT::COE_CREATE_NODATA:
        stream << " " + className + " COE_CREATE_NODATA";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_BEFORE_ATTACHDATA:
        stream << " " + className + " COE_CREATE_BEFORE_ATTACHDATA";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_LOADDATA:
        stream << " " + className + " COE_CREATE_LOADDATA";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_AFTER_ATTACHDATA:
        stream << " " + className + " COE_CREATE_AFTER_ATTACHDATA";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_BEFORE_EFFECT:
        stream << " " + className + " COE_CREATE_BEFORE_EFFECT";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_EFFECTDATA:
        stream << " " + className + " COE_CREATE_EFFECTDATA";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_AFTER_EFFECT:
        stream << " " + className + " COE_CREATE_AFTER_EFFECT";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_HASDATA:
        stream << " " + className + " COE_CREATE_HASDATA";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_FINISH:
        stream << " " + className + " COE_CREATE_FINISH";
        break;
        case CLASS_OBJECT_EVENT::COE_CREATE_CLIENT_FINISH:
        stream << " " + className + " COE_CREATE_CLIENT_FINISH";
        break;
        case CLASS_OBJECT_EVENT::COE_BEFOREDESTROY:
        stream << " " + className + " COE_BEFOREDESTROY";
        break;
        case CLASS_OBJECT_EVENT::COE_DESTROY:
        stream << " " + className + " COE_DESTROY";
        break;
    }

    m_pLogModule->LogDebug(self, stream.str());
    return 0;
}

void NFDataTailModule::StartTrail(const Guid& self)
{
	TrailObjectData(self);


}

void NFDataTailModule::LogObjectData(const Guid& self)
{
    SQUICK_SHARE_PTR<IObject> xObject = m_pKernelModule->GetObject(self);
    if (nullptr == xObject)
    {
        return;
    }

    SQUICK_SHARE_PTR<IPropertyManager> xPropertyManager = xObject->GetPropertyManager();
    if (nullptr != xPropertyManager)
    {
        SQUICK_SHARE_PTR<IProperty> xProperty = xPropertyManager->First();
        while (nullptr != xProperty)
        {
            std::ostringstream stream;

            stream << " Start trail ";
			stream << xProperty->GetKey();
			stream << "==>";
            stream << xProperty->ToString();

            m_pLogModule->LogDebug(self, stream.str(),  __FUNCTION__, __LINE__);

            xProperty = xPropertyManager->Next();
        }
    }

    SQUICK_SHARE_PTR<IRecordManager> xRecordManager = xObject->GetRecordManager();
    if (nullptr != xRecordManager)
    {
        SQUICK_SHARE_PTR<IRecord> xRecord = xRecordManager->First();
        while (nullptr != xRecord)
        {
            for (int i = 0; i < xRecord->GetRows(); ++i)
            {
                DataList xDataList;
                bool bRet = xRecord->QueryRow(i, xDataList);
                if (bRet)
                {
                    std::ostringstream stream;
                    stream << " Start trail Row[" << i << "]";

                    for (int j = 0; j < xDataList.GetCount(); ++j)
                    {
                        stream << " [" << j << "] " << xDataList.ToString(j);
                    }

                    m_pLogModule->LogRecord(ILogModule::SQUICK_LOG_LEVEL::NLL_DEBUG_NORMAL, self, xRecord->GetName(), stream.str(),  __FUNCTION__, __LINE__);
                }
            }

            xRecord = xRecordManager->Next();
        }
    }
}

int NFDataTailModule::OnObjectPropertyEvent(const Guid& self, const std::string& propertyName, const NFData& oldVar, const NFData& newVar, const INT64 reason)
{
    std::ostringstream stream;

    stream << propertyName;
    stream << ":";
    stream << oldVar.ToString();
    stream << "==>";
    stream << newVar.ToString();

    //m_pLogModule->LogDebug(self, stream.str());

    PrintStackTrace();

    return 0;
}

int NFDataTailModule::OnObjectRecordEvent(const Guid& self, const RECORD_EVENT_DATA& eventData, const NFData& oldVar, const NFData& newVar)
{
    std::ostringstream stream;
    SQUICK_SHARE_PTR<IRecord> xRecord = m_pKernelModule->FindRecord(self, eventData.recordName);
    if (nullptr == xRecord)
    {
        return 0;
    }

    switch (eventData.nOpType)
    {
        case RECORD_EVENT_DATA::Add:
        {
            DataList xDataList;
            bool bRet = xRecord->QueryRow(eventData.row, xDataList);
            if (bRet)
            {
                stream << xRecord->GetName();
                stream << " Add Row[" << eventData.row << "]";

                for (int j = 0; j < xDataList.GetCount(); ++j)
                {
                    stream << " [" << j << "] " << xDataList.ToString(j);
                }

                //m_pLogModule->LogDebug(self, stream.str());

                PrintStackTrace();
            }
        }
        break;
        case RECORD_EVENT_DATA::Del:
        {
            stream << xRecord->GetName();
            stream << " Del Row[" << eventData.row << "]";
            //m_pLogModule->LogDebug(self, stream.str());

            PrintStackTrace();
        }
        break;
        case RECORD_EVENT_DATA::Swap:
        {
            stream << xRecord->GetName();
            stream << " Swap Row[" << eventData.row << "] Row[" << eventData.col << "]";
            //m_pLogModule->LogDebug(self, stream.str());
        }
        break;
        case RECORD_EVENT_DATA::Create:
            break;
        case RECORD_EVENT_DATA::Update:
        {
            stream << xRecord->GetName();
            stream << " UpData Row[" << eventData.row << "] Col[" << eventData.col << "]";
            stream << oldVar.ToString();
            stream << "==>" << newVar.ToString();
            //m_pLogModule->LogDebug(self, stream.str());

            PrintStackTrace();
        }
        break;
        case RECORD_EVENT_DATA::Cleared:
            break;
        case RECORD_EVENT_DATA::Sort:
            break;
        default:
            break;
    }

    return 0;
}

int NFDataTailModule::TrailObjectData(const Guid& self)
{
    SQUICK_SHARE_PTR<IObject> xObject = m_pKernelModule->GetObject(self);
    if (nullptr == xObject)
    {
        return -1;
    }

    SQUICK_SHARE_PTR<IPropertyManager> xPropertyManager = xObject->GetPropertyManager();
    if (nullptr != xPropertyManager)
    {
        SQUICK_SHARE_PTR<IProperty> xProperty = xPropertyManager->First();
        while (nullptr != xProperty)
        {
            m_pKernelModule->AddPropertyCallBack(self, xProperty->GetKey(), this, &NFDataTailModule::OnObjectPropertyEvent);

            xProperty = xPropertyManager->Next();
        }
    }

    SQUICK_SHARE_PTR<IRecordManager> xRecordManager = xObject->GetRecordManager();
    if (nullptr != xRecordManager)
    {
        SQUICK_SHARE_PTR<IRecord> xRecord = xRecordManager->First();
        while (nullptr != xRecord)
        {
            m_pKernelModule->AddRecordCallBack(self, xRecord->GetName(), this, &NFDataTailModule::OnObjectRecordEvent);


            xRecord = xRecordManager->Next();
        }
    }

    return 0;
}

void NFDataTailModule::PrintStackTrace()
{
    return;

}