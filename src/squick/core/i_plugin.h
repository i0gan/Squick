
#ifndef SQUICK_INTF_PLUGIN_H
#define SQUICK_INTF_PLUGIN_H

#include <iostream>
#include <assert.h>
#include "i_module.h"
#include "i_plugin_manager.h"

#define REGISTER_MODULE(pManager, classBaseName, className)  \
	assert((TIsDerived<classBaseName, IModule>::Result));	\
	assert((TIsDerived<className, classBaseName>::Result));	\
	IModule* pRegisterModule##className= new className(pManager); \
    pRegisterModule##className->name = (#classBaseName); \
    pManager->AddModule( typeid(classBaseName).name(), pRegisterModule##className );\
    this->AddElement( typeid(classBaseName).name(), pRegisterModule##className );

#define UNREGISTER_MODULE(pManager, classBaseName, className) \
    IModule* pUnRegisterModule##className = dynamic_cast<IModule*>( pManager->FindModule( typeid(classBaseName).name() )); \
	pManager->RemoveModule( typeid(classBaseName).name() ); \
    this->RemoveElement( typeid(classBaseName).name() ); \
    delete pUnRegisterModule##className;


#define CREATE_PLUGIN(pManager, className)  IPlugin* pCreatePlugin##className = new className(pManager); pManager->Registered( pCreatePlugin##className );

#define DESTROY_PLUGIN(pManager, className) pManager->UnRegistered( pManager->FindPlugin((#className)) );

class IPluginManager;

class IPlugin : public IModule
{

public:
	IPlugin()
	{
	}
    virtual ~IPlugin()
	{
	}
    virtual const int GetPluginVersion() = 0;
    virtual const std::string GetPluginName() = 0;

    virtual void Install() = 0;

	virtual void Uninstall() = 0;


	void AddElement(const std::string& name, IModule* module)
	{
		mModules[name] = module;
	}

	IModule* GetElement(const std::string& name)
	{
		auto it = mModules.find(name);
		if (it != mModules.end())
		{
			return it->second;
		}

		return nullptr;
	}

	void RemoveElement(const std::string& name)
	{
		auto it = mModules.find(name);
		if (it != mModules.end())
		{
			mModules.erase(it);
		}
	}

	virtual bool Awake()
	{
		for (const auto& it : mModules)
		{
			IModule* pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);

			bool bRet = pModule->Awake();
			if (!bRet)
			{
				std::cout << pModule->name << std::endl;
				assert(0);
			}
		}

		return true;
	}

    virtual bool Start()
	{
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
			bool bRet = pModule->Start();
			if (!bRet)
			{
				std::cout << pModule->name << std::endl;
				assert(0);
			}
		}

        return true;
    }

    virtual bool AfterStart()
    {
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
            bool bRet = pModule->AfterStart();
            if (!bRet)
            {
				std::cout << pModule->name << std::endl;
                assert(0);
            }
        }
        return true;
    }

    virtual bool CheckConfig()
    {
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
            pModule->CheckConfig();

        }

        return true;
    }

	virtual bool ReadyUpdate()
	{
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
			pModule->ReadyUpdate();
		}

		return true;
	}

    virtual bool Update()
    {
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
            pModule->Update();

        }

        return true;
    }

    virtual bool BeforeDestory()
    {
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
            pModule->BeforeDestory();
        }

        return true;
    }

    virtual bool Destory()
    {
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
            pModule->Destory();
        }

        return true;
    }

    virtual bool Finalize()
    {
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
            pModule->Finalize();

        }

        return true;
    }

	virtual bool OnReloadPlugin()
	{
		for (const auto& it : mModules)
		{
			IModule *pModule = it.second;

			pPluginManager->SetCurrentModule(pModule);
			pModule->OnReloadPlugin();
		}

		return true;
	}

private:
	std::map<std::string, IModule*> mModules;
};

#endif
