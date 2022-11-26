#pragma once


#include "config_generator_data.h"
#include "config_generator_help.h"
namespace squick::tools::file_process {
class IGenerator
{
public:

	void SetConfigPath(const std::string &configPath) {
		this->configPath = configPath;
		strExcelIniPath = configPath + "/excel/";
		strXMLStructPath = configPath + "/struct/";
		strXMLIniPath = configPath + "/ini/";
		
	}

	virtual bool Generate(const std::map<std::string, ClassData*>& classData) = 0;

	std::string strExcelIniPath;
	std::string strXMLStructPath;
	std::string strXMLIniPath;
	std::string configPath;

};

}
