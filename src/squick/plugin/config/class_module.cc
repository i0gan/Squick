
#include <time.h>
#include <algorithm>
#include "plugin.h"
#include "class_module.h"
#include "squick/plugin/kernel/i_thread_pool_module.h"
#include "third_party/rapidxml/rapidxml.hpp"
#include "third_party/rapidxml/rapidxml_print.hpp"

ClassModule::ClassModule()
{
	mConfigFileName = "config/struct/logic_class.xml";
}

ClassModule::ClassModule(IPluginManager* p)
{
    pPluginManager = p;
	mConfigFileName = "config/struct/logic_class.xml";

    std::cout << "Using [" << pPluginManager->GetConfigPath() + mConfigFileName << "]" << std::endl;

	if (!this->mbBackup)
	{
		//IThreadPoolModule *threadPoolModule = pPluginManager->FindModule<IThreadPoolModule>();
		//const int threadCount = threadPoolModule->GetThreadCount();
		for (int i = 0; i < 10; ++i)
		{
			ThreadClassModule threadElement;
			threadElement.used = false;
			threadElement.classModule = new ClassModule();
			threadElement.classModule->mbBackup = true;
			threadElement.classModule->pPluginManager = pPluginManager;

			threadElement.classModule->Awake();
			threadElement.classModule->Start();
			threadElement.classModule->AfterStart();

			mThreadClasses.push_back(threadElement);
		}
	}
}

ClassModule::~ClassModule()
{
    ClearAll();
}

bool ClassModule::Awake()
{
    for (int i = 0; i < mThreadClasses.size(); ++i)
	{
		mThreadClasses[i].classModule->Awake();
	}

    Load();

	return true;
	
}

bool ClassModule::Start()
{
	for (int i = 0; i < mThreadClasses.size(); ++i)
	{
		mThreadClasses[i].classModule->Start();
	}
    return true;
}

bool ClassModule::Destory()
{
	for (int i = 0; i < mThreadClasses.size(); ++i)
	{
		mThreadClasses[i].classModule->Destory();
	}

    ClearAll();

    return true;
}

IClassModule* ClassModule::GetThreadClassModule()
{
	std::thread::id threadID = std::this_thread::get_id();

	for (int i = 0; i < mThreadClasses.size(); ++i)
	{
		if (mThreadClasses[i].used)
		{
			if (mThreadClasses[i].threadID == threadID)
			{
				return mThreadClasses[i].classModule;
			}
		}
		else
		{
			mThreadClasses[i].used = true;
			mThreadClasses[i].threadID = threadID;
			return mThreadClasses[i].classModule;
		}
	}

	return nullptr;
}

DATA_TYPE ClassModule::ComputerType(const char* pstrTypeName, SquickData& var)
{
    if (0 == strcmp(pstrTypeName, "int"))
    {
        var.SetInt(NULL_INT);
        return var.GetType();
    }
    else if (0 == strcmp(pstrTypeName, "string"))
    {
        var.SetString(NULL_STR);
        return var.GetType();
    }
    else if (0 == strcmp(pstrTypeName, "float"))
    {
        var.SetFloat(NULL_FLOAT);
        return var.GetType();
    }
    else if (0 == strcmp(pstrTypeName, "object"))
    {
        var.SetObject(NULL_OBJECT);
        return var.GetType();
    }
	else if (0 == strcmp(pstrTypeName, "vector2"))
	{
		var.SetVector2(NULL_VECTOR2);
		return var.GetType();
	}
	else if (0 == strcmp(pstrTypeName, "vector3"))
	{
		var.SetVector3(NULL_VECTOR3);
		return var.GetType();
	}

    return TDATA_UNKNOWN;
}

bool ClassModule::AddProperties(rapidxml::xml_node<>* pPropertyRootNode, SQUICK_SHARE_PTR<IClass> pClass)
{
    for (rapidxml::xml_node<>* pPropertyNode = pPropertyRootNode->first_node(); pPropertyNode; pPropertyNode = pPropertyNode->next_sibling())
    {
        if (pPropertyNode)
        {
            const char* propertyName = pPropertyNode->first_attribute("Id")->value();
            if (pClass->GetPropertyManager()->GetElement(propertyName))
            {
                //error
                NFASSERT(0, propertyName, __FILE__, __FUNCTION__);
                continue;
            }

            const char* pstrType = pPropertyNode->first_attribute("Type")->value();
            const char* pstrPublic = pPropertyNode->first_attribute("Public")->value();
            const char* pstrPrivate = pPropertyNode->first_attribute("Private")->value();
            const char* pstrSave = pPropertyNode->first_attribute("Save")->value();
            const char* pstrCache = pPropertyNode->first_attribute("Cache")->value();
			const char* pstrRef = pPropertyNode->first_attribute("Ref")->value();
			const char* pstrForce = pPropertyNode->first_attribute("Force")->value();
			const char* pstrUpload = pPropertyNode->first_attribute("Upload")->value();

            bool bPublic = lexical_cast<bool>(pstrPublic);
            bool bPrivate = lexical_cast<bool>(pstrPrivate);
            bool bSave = lexical_cast<bool>(pstrSave);
            bool bCache = lexical_cast<bool>(pstrCache);
			bool bRef = lexical_cast<bool>(pstrRef);
			bool bForce = lexical_cast<bool>(pstrForce);
			bool bUpload = lexical_cast<bool>(pstrUpload);

            SquickData varProperty;
            if (TDATA_UNKNOWN == ComputerType(pstrType, varProperty))
            {
                //std::cout << "error:" << pClass->GetTypeName() << "  " << pClass->GetInstancePath() << ": " << propertyName << " type error!!!" << std::endl;

                NFASSERT(0, propertyName, __FILE__, __FUNCTION__);
            }

            //printf( " Property:%s[%s]\n", propertyName, pstrType );

            SQUICK_SHARE_PTR<IProperty> xProperty = pClass->GetPropertyManager()->AddProperty(Guid(), propertyName, varProperty.GetType());
            xProperty->SetPublic(bPublic);
            xProperty->SetPrivate(bPrivate);
            xProperty->SetSave(bSave);
            xProperty->SetCache(bCache);
			xProperty->SetRef(bRef);
			xProperty->SetForce(bForce);
			xProperty->SetUpload(bUpload);

        }
    }

    return true;
}

bool ClassModule::AddRecords(rapidxml::xml_node<>* pRecordRootNode, SQUICK_SHARE_PTR<IClass> pClass)
{
    for (rapidxml::xml_node<>* pRecordNode = pRecordRootNode->first_node(); pRecordNode;  pRecordNode = pRecordNode->next_sibling())
    {
        if (pRecordNode)
        {
            const char* pstrRecordName = pRecordNode->first_attribute("Id")->value();

            if (pClass->GetRecordManager()->GetElement(pstrRecordName))
            {
                //error
                //file << pClass->mstrType << ":" << pstrRecordName << std::endl;
                //assert(0);
                NFASSERT(0, pstrRecordName, __FILE__, __FUNCTION__);
                continue;
            }

            const char* pstrRow = pRecordNode->first_attribute("Row")->value();
            const char* pstrCol = pRecordNode->first_attribute("Col")->value();

            const char* pstrPublic = pRecordNode->first_attribute("Public")->value();
            const char* pstrPrivate = pRecordNode->first_attribute("Private")->value();
            const char* pstrSave = pRecordNode->first_attribute("Save")->value();
			const char* pstrCache = pRecordNode->first_attribute("Cache")->value();
			const char* pstrRef = pRecordNode->first_attribute("Ref")->value();
			const char* pstrForce = pRecordNode->first_attribute("Force")->value();
			const char* pstrUpload = pRecordNode->first_attribute("Upload")->value();

            std::string strView;
            if (pRecordNode->first_attribute("View") != NULL)
            {
                strView = pRecordNode->first_attribute("View")->value();
            }

            bool bPublic = lexical_cast<bool>(pstrPublic);
            bool bPrivate = lexical_cast<bool>(pstrPrivate);
            bool bSave = lexical_cast<bool>(pstrSave);
			bool bCache = lexical_cast<bool>(pstrCache);
			bool bRef = lexical_cast<bool>(pstrCache);
			bool bForce = lexical_cast<bool>(pstrCache);
			bool bUpload = lexical_cast<bool>(pstrUpload);

			SQUICK_SHARE_PTR<DataList> recordVar(SQUICK_NEW DataList());
			SQUICK_SHARE_PTR<DataList> recordTag(SQUICK_NEW DataList());

            for (rapidxml::xml_node<>* recordColNode = pRecordNode->first_node(); recordColNode;  recordColNode = recordColNode->next_sibling())
            {
                //const char* pstrColName = recordColNode->first_attribute( "Id" )->value();
                SquickData TData;
                const char* pstrColType = recordColNode->first_attribute("Type")->value();
                if (TDATA_UNKNOWN == ComputerType(pstrColType, TData))
                {
                    //assert(0);
                    NFASSERT(0, pstrRecordName, __FILE__, __FUNCTION__);
                }

                recordVar->Append(TData);
                //////////////////////////////////////////////////////////////////////////
                if (recordColNode->first_attribute("Tag") != NULL)
                {
                    const char* pstrTag = recordColNode->first_attribute("Tag")->value();
                    recordTag->Add(pstrTag);
                }
                else
                {
                    recordTag->Add("");
                }
            }

            SQUICK_SHARE_PTR<IRecord> xRecord = pClass->GetRecordManager()->AddRecord(Guid(), pstrRecordName, recordVar, recordTag, atoi(pstrRow));

			xRecord->SetPublic(bPublic);
            xRecord->SetPrivate(bPrivate);
            xRecord->SetSave(bSave);
            xRecord->SetCache(bCache);
			xRecord->SetRef(bRef);
			xRecord->SetForce(bForce);
			xRecord->SetUpload(bUpload);
        }
    }

    return true;
}

bool ClassModule::AddComponents(rapidxml::xml_node<>* pComponentRootNode, SQUICK_SHARE_PTR<IClass> pClass)
{
	/*
    for (rapidxml::xml_node<>* pComponentNode = pComponentRootNode->first_node(); pComponentNode; pComponentNode = pComponentNode->next_sibling())
    {
        if (pComponentNode)
        {
            const char* componentName = pComponentNode->first_attribute("Name")->value();
            const char* strLanguage = pComponentNode->first_attribute("Language")->value();
            const char* strEnable = pComponentNode->first_attribute("Enable")->value();
            bool bEnable = lexical_cast<bool>(strEnable);
            if (bEnable)
            {
                if (pClass->GetComponentManager()->GetElement(componentName))
                {
                    //error
                    NFASSERT(0, componentName, __FILE__, __FUNCTION__);
                    continue;
                }
                SQUICK_SHARE_PTR<IComponent> xComponent(SQUICK_NEW IComponent(Guid(), componentName));
                pClass->GetComponentManager()->AddComponent(componentName, xComponent);
            }
        }
    }
	*/
    return true;
}

bool ClassModule::AddClassInclude(const char* pstrClassFilePath, SQUICK_SHARE_PTR<IClass> pClass)
{
    if (pClass->Find(pstrClassFilePath))
    {
        return false;
    }

    //////////////////////////////////////////////////////////////////////////
    std::string strFile = pPluginManager->GetConfigPath() + pstrClassFilePath;
	std::string content;
	pPluginManager->GetFileContent(strFile, content);

	rapidxml::xml_document<> xDoc;
    xDoc.parse<0>((char*)content.c_str());
    //////////////////////////////////////////////////////////////////////////

    //support for unlimited layer class inherits
    rapidxml::xml_node<>* root = xDoc.first_node();

    rapidxml::xml_node<>* pRropertyRootNode = root->first_node("Propertys");
    if (pRropertyRootNode)
    {
		AddProperties(pRropertyRootNode, pClass);
    }

    //////////////////////////////////////////////////////////////////////////
    //and record
    rapidxml::xml_node<>* pRecordRootNode = root->first_node("Records");
    if (pRecordRootNode)
    {
        AddRecords(pRecordRootNode, pClass);
    }

    rapidxml::xml_node<>* pComponentRootNode = root->first_node("Components");
    if (pComponentRootNode)
    {
        AddComponents(pComponentRootNode, pClass);
    }

    //pClass->mvIncludeFile.push_back( pstrClassFilePath );
    //and include file
    rapidxml::xml_node<>* pIncludeRootNode = root->first_node("Includes");
    if (pIncludeRootNode)
    {
        for (rapidxml::xml_node<>* includeNode = pIncludeRootNode->first_node(); includeNode; includeNode = includeNode->next_sibling())
        {
            const char* pstrIncludeFile = includeNode->first_attribute("Id")->value();
            //std::vector<std::string>::iterator it = std::find( pClass->mvIncludeFile.begin(), pClass->mvIncludeFile..end(), pstrIncludeFile );

            if (AddClassInclude(pstrIncludeFile, pClass))
            {
                pClass->Add(pstrIncludeFile);
            }
        }
    }

    return true;
}

bool ClassModule::AddClass(const char* pstrClassFilePath, SQUICK_SHARE_PTR<IClass> pClass)
{
    SQUICK_SHARE_PTR<IClass> pParent = pClass->GetParent();
    while (pParent)
    {
        //inherited some properties form class of parent
        std::string fileName = "";
        pParent->First(fileName);
        while (!fileName.empty())
        {
            if (pClass->Find(fileName))
            {
                fileName.clear();
                continue;
            }

            if (AddClassInclude(fileName.c_str(), pClass))
            {
                pClass->Add(fileName);
            }

            fileName.clear();
            pParent->Next(fileName);
        }

        pParent = pParent->GetParent();
    }

    //////////////////////////////////////////////////////////////////////////
    if (AddClassInclude(pstrClassFilePath, pClass))
    {
        pClass->Add(pstrClassFilePath);
    }

    //file.close();

    return true;
}

bool ClassModule::AddClass(const std::string& className, const std::string& strParentName)
{
    SQUICK_SHARE_PTR<IClass> pParentClass = GetElement(strParentName);
    SQUICK_SHARE_PTR<IClass> pChildClass = GetElement(className);
    if (!pChildClass)
    {
        pChildClass = SQUICK_SHARE_PTR<IClass>(SQUICK_NEW Class(className));
        AddElement(className, pChildClass);
        //pChildClass = CreateElement( className );

        pChildClass->SetTypeName("");
        pChildClass->SetInstancePath("");

        if (pParentClass)
        {
            pChildClass->SetParent(pParentClass);
        }
    }

    return true;
}

bool ClassModule::Load(rapidxml::xml_node<>* attrNode, SQUICK_SHARE_PTR<IClass> pParentClass)
{
    const char* pstrLogicClassName = attrNode->first_attribute("Id")->value();
    const char* pstrPath = attrNode->first_attribute("Path")->value();
    const char* pstrInstancePath = attrNode->first_attribute("InstancePath")->value();

    //printf( "-----------------------------------------------------\n");
    //printf( "%s:\n", pstrLogicClassName );

    SQUICK_SHARE_PTR<IClass> pClass(SQUICK_NEW Class(pstrLogicClassName));
    AddElement(pstrLogicClassName, pClass);
    pClass->SetParent(pParentClass);
    pClass->SetInstancePath(pstrInstancePath);

    AddClass(pstrPath, pClass);

    for (rapidxml::xml_node<>* pDataNode = attrNode->first_node(); pDataNode; pDataNode = pDataNode->next_sibling())
    {
        //her children
        Load(pDataNode, pClass);
    }
    //printf( "-----------------------------------------------------\n");
    return true;
}

bool ClassModule::Load()
{
    //////////////////////////////////////////////////////////////////////////
	std::string strFile = pPluginManager->GetConfigPath() + mConfigFileName;
	std::string content;
	pPluginManager->GetFileContent(strFile, content);

	rapidxml::xml_document<> xDoc;
	xDoc.parse<0>((char*)content.c_str());
    //////////////////////////////////////////////////////////////////////////
    //support for unlimited layer class inherits
    rapidxml::xml_node<>* root = xDoc.first_node();
    for (rapidxml::xml_node<>* attrNode = root->first_node(); attrNode; attrNode = attrNode->next_sibling())
    {
        Load(attrNode, NULL);
    }

	for (int i = 0; i < mThreadClasses.size(); ++i)
	{
		mThreadClasses[i].classModule->Load();
	}

    return true;
}

bool ClassModule::Save()
{
    return true;
}

SQUICK_SHARE_PTR<IPropertyManager> ClassModule::GetClassPropertyManager(const std::string& className)
{
    SQUICK_SHARE_PTR<IClass> pClass = GetElement(className);
    if (pClass)
    {
        return pClass->GetPropertyManager();
    }

    return NULL;
}

SQUICK_SHARE_PTR<IRecordManager> ClassModule::GetClassRecordManager(const std::string& className)
{
    SQUICK_SHARE_PTR<IClass> pClass = GetElement(className);
    if (pClass)
    {
        return pClass->GetRecordManager();
    }

    return NULL;
}

bool ClassModule::Clear()
{
    return true;
}

bool ClassModule::AddClassCallBack(const std::string& className, const CLASS_EVENT_FUNCTOR_PTR& cb)
{
    SQUICK_SHARE_PTR<IClass> pClass = GetElement(className);
    if (nullptr == pClass)
    {
        return false;
    }

    return pClass->AddClassCallBack(cb);
}

bool ClassModule::DoEvent(const Guid& objectID, const std::string& className, const CLASS_OBJECT_EVENT classEvent, const DataList& valueList)
{
    SQUICK_SHARE_PTR<IClass> pClass = GetElement(className);
    if (nullptr == pClass)
    {
        return false;
    }

    return pClass->DoEvent(objectID, classEvent, valueList);
}

bool ClassModule::AfterStart()
{


	return true;
}

IClassModule *ClassModule::GetThreadClassModule(const int index)
{
	return mThreadClasses[index].classModule;
}
