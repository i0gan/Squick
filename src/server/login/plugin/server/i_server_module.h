#include <squick/base/guid.h>
#include <squick/base/module.h>
#include <string>

class ILoginNet_ServerModule
    : public IModule
{
public:

    virtual int OnSelectWorldResultsProcess(const int nWorldID, const Guid xSenderID, const int nLoginID, const std::string& account, const std::string& strWorldIP, const int nWorldPort, const std::string& strKey) = 0;
    //virtual INetModule* GetNetModule() = 0;
};

