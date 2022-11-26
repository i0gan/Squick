#include "config_generator.h"
#include <iostream>
#include <chrono>
#include <string>

#include <squick/core/platform.h>

using namespace squick::tools::file_process;

int main(int argc, const char *argv[])
{
	if(argc < 2) {
		std::cout << "Usague: ./gen_config [config path]\n";
		return 1;
	}

	std::string configPath = argv[1];
	std::cout << "configPath: " << configPath << std::endl;
	auto t1 = SquickGetTimeMS();

	ConfigGenerator fp(configPath);
	fp.SetUTF8(false);//set it true to convert UTF8 to GBK which is to show Chinese words in Squick
	fp.LoadDataFromExcel();

	fp.PrintData();

	fp.GenerateData();

	auto t2 = SquickGetTimeMS();
	std::cout << "Timespan: "  << (t2 - t1) << " ms" << std::endl;

	return 0;
}
