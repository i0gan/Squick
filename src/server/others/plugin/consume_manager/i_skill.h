

#ifndef SQUICK_INTF_SKILL_MODULE_H
#define SQUICK_INTF_SKILL_MODULE_H

#include <iostream>
#include <squick/base/module.h>

class ISkillModule
    : public IModule
{

public:
	virtual int UseSkill(const Guid& self, const std::string& strSkillName, const Guid& target, const int64_t index = 0) = 0;
	virtual int UseSkill(const Guid& self, const std::string& strSkillName, const DataList& target, const int64_t index = 0) = 0;

	/*
	std::cout << "100, -10: " << CalDamage(100, -10) << std::endl;
	std::cout << "100, 5: " << CalDamage(100, 5) << std::endl;
	std::cout << "100, 10: " << CalDamage(100, 10) << std::endl;
	std::cout << "100, 20: " << CalDamage(100, 20) << std::endl;
	std::cout << "100, 30: " << CalDamage(100, 30) << std::endl;
	std::cout << "-100, 30: " << CalDamage(-100, 30) << std::endl;
	std::cout << "-100, -30: " << CalDamage(-100, -30) << std::endl;

	 	100, -10: 250
		100, 5: 76
		100, 10: 62
		100, 20: 45
		100, 30: 35
		-100, 30: 0
		-100, -30: 0
	 */
	virtual int CalDamage(const int atk, const int def) = 0;

	//virtual int CalSkillDamage(const Guid& self, const int def) = 0;
};

#endif