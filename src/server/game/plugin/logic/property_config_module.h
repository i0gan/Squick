

#ifndef SQUICK_PROPERTY_CONFIG_MODULE_H
#define SQUICK_PROPERTY_CONFIG_MODULE_H

#include "third_party/RapidXML/rapidxml.hpp"
#include "third_party/RapidXML/rapidxml_print.hpp"
#include "third_party/RapidXML/rapidxml_utils.hpp"
#include "squick/base/class.h"
#include "squick/base/element.h"
#include "squick/struct/protocol_define.h"

#include "if_property_config_module.h"
class PropertyConfigModule
    : public IPropertyConfigModule
{
public:
    PropertyConfigModule(IPluginManager* p)
    {
        pPluginManager = p;
    }
    virtual ~PropertyConfigModule() {};

    virtual bool Init();
    virtual bool Shut();
    virtual bool Execute();
    virtual bool AfterInit();

    virtual bool LegalLevel(const int nJob, const int nLevel);

    virtual const std::string& GetInitPropertyID(const int nJob,  const int nLevel);

    virtual void ClearInitPropertyData();

    virtual void AddInitPropertyID(const int nJob, const int nLevel, const std::string& data);

    virtual void SetEx(const bool b);

protected:
    void Load();

    std::map<Guid, std::string>& GetData();

private:
    bool mbExtra = false;

	//[job,Level]->ConfigID
    std::map<Guid, std::string> mhtCoefficientData;

    IClassModule* m_pClassModule;
    IElementModule* m_pElementModule;
};


#endif
