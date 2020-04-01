#pragma once


#include <iostream>
#include <string>
#include <windows.h>
#include <random>
#include <chrono>
#include <fstream>
#include <set>
#include <strsafe.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <winbase.h>

#define VERSION "1.0.5 Patch 4"
#define BETA 1

class Race
{
	std::vector<int> usedID;
	int maxLvl = 500, startCat[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }, endCat[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	std::string cats[16];
	std::string category, name, author = "GOR";
	double percent_rise = 0.0;
	int riseLvl = 1000, minSkills = 4, maxSkills = 14, minSkills_Exep = 3, maxSkills_Exep = 9, amountSkills = 5, requiredLvl = 0, ultCooldown = 0, skillsLvlMin = 2, skillsLvlMax = 10;
	std::vector<std::string> skillDesc, skills, skillParam, enemyPart = { "head", "body" },
		typeUlt = { "aim","random","radius" }, skillNames = { "speed", "gravity", "hp", "invis", "dmg", "freeze", "burn",
		"vampire", "boom", "regen", "slow", "rockets", "longjump", "mirror", "evasion", "step", "push",
"respawn", "dropweapon", "paralyze", "blind", "poison", "illusion", "bury", "grenlauncher", "imbagrenade",
"longjump2", "doublejumps", "glow", "chameleon", "attackspeed", "quickreload", "tknives",
"catwalk", "flicker", "obscurity", "obscurity_duck", "thirst", "splashdmg", "shaker", "losso", "repel",
"clip_destroy", "clip_take", "clip_shot", "takeweapon", "fear", "dmghealth", "adrenaline_rush", "clearance", "silence", "blockrespawn", "longknife",
"setangle", "drug", "beacon", "timebomb", "accuracy", "killhp", "kill_invis", "arcanum", "armor", "adrenaline", "mirror_setangle",
"mirror_clip_destroy", "mirror_clip_take", "mirror_blind", "mirror_burn", "mirror_shaker",
	"antiskill", "antiskill2", "def_", "protect", "backjump", "radarinvis", "selfdiet", "mole" }, ultimates = { "teleport", "jetpack", "explode", "ultfreeze", "CreateProp", "ultgod", "webshot", "ultburn","speedbuf", "heal", "ultblind","ultremove", "ultburyme",
"fatality", "blink", "ultswap", "ultmatrix", "chaos", "teleportator", "portals", "leap", "ult_kamikaze", "ultgod_ally", "rapidfire", "ultnorecoil", "ultaim", "ultwh", "ultrandweapon", "ultsilence",
	"hook", "stun", "disarm", "dmgbuf", "eclipse", "ultsteal", "cashheal", "saw", "ultblind", "satanic", "mirror_shield", "diet", "locust_swarm", "locust_swarm2", "ultstealcash", "ultchain",
		"ultchain2", "ultstomp", "ultrecline", "telekinez", "ultclearance", "rupture", "doom", "ult_takeoff", "sphere", "freezetele" };
	std::string ultimate, ability;


public:
	Race();
	inline int Random(int min, int max);
	inline double Random(double min, double max);
	void Input();
	void CheckOnBeta(std::string& author);
	void PushSkill(int start, int add, int skillID, int change, int value2, double value3, double value4, double value5);
	void PushSkill(double start, double add, int skillID, int change, double value);
	void PushSkill(double valueF, int valueI, int skillID, int change, double value2);
	void PushSkill(int valueI, double valueF, int skillID, double valueF2);
	//void PushSkill(int value = 0, int value2 = 0, int skillID = 0, int value3 = 0, double value4 = 0, double value5 = 0, double value6 = 0);
	void GetSettings();
	void Output();
	void Debug();
	void GiveSkills();
	void GiveParam();
	void GiveUlt();
	void Clear();
	void DefineCategory();


};

