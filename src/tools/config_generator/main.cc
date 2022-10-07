#include "config_generator.h"
#include <iostream>
#include <chrono>

#include "squick/base/platform.h"

using namespace squick::tools::file_process;
int main(int argc, const char *argv[])
{
	auto t1 = SquickGetTimeMS();

	ConfigGenerator fp;
	fp.SetUTF8(false);//set it true to convert UTF8 to GBK which is to show Chinese words in NF
	fp.LoadDataFromExcel();

	fp.PrintData();

	fp.GenerateData();

	auto t2 = SquickGetTimeMS();
	std::cout << "Timespan: "  << (t2 - t1) << " ms" << std::endl;

	return 0;
}
