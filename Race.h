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


class Race {
public:
	Race();
	int Random(int min, int max);
	void GiveSkills();
	void GiveParam();
	void DefineCategory();
	void Output();
	void Debug();
	void GetSettings();
	void GiveUlt();
	void Clear();
	//void ExceptionHandler();
private:
	std::string name, category, author = "GOR", ultimate, ability;
	int requiredLvl = 0, maxLvl = 501, amountSkills = 0, riseLvl = 1000;
	unsigned int ultCooldown = 0;
	std::vector<int> skillsID, usedID;
	std::vector<std::string> skillNames = { "speed", "gravity", "hp", "invis", "dmg", "freeze", "burn",
		"vampire", "boom", "regen", "slow", "rockets", "longjump", "mirror", "evasion", "step", "push",
"respawn", "dropweapon", "paralyze", "blind", "poison", "illusion", "bury", "grenlauncher", "imbagrenade",
"longjump2", "doublejumps", "glow", "chameleon", "attackspeed", "quickreload", "tknives",
"catwalk", "flicker", "obscurity", "obscurity_duck", "thirst", "splashdmg", "shaker", "losso", "repel",
"clip_destroy", "takeweapon", "fear", "dmghealth", "adrenaline_rush", "clearance", "silence", "blockrespawn",
"setangle", "drug", "beacon", "accuracy", "killhp", "kill_invis", "armor", "adrenaline", "mirror_setangle",
"mirror_clip_destroy", "mirror_clip_take", "mirror_blind", "mirror_burn", "mirror_shaker",
	"antiskill", "antiskill2", "def_", "protect", "backjump", "radarinvis", "selfdiet", "mole" },
		ultimates = { "teleport", "jetpack", "explode", "ultfreeze", "CreateProp", "ultgod", "webshot", "ultburn","speedbuf", "heal", "ultblind","ultremove", "ultburyme",
"fatality", "blink", "ultswap", "ultmatrix", "chaos", "teleportator", "portals", "leap", "ult_kamikaze", "ultgod_ally", "rapidfire", "ultnorecoil", "ultaim", "ultwh", "ultrandweapon", "ultsilence",
	"hook", "stun", "disarm", "dmgbuf", "eclipse", "ultsteal", "cashheal", "saw", "ultblind", "satanic", "mirror_shield", "diet", "locust_swarm", "locust_swarm2", "ultstealcash", "ultchain",
		"ultchain2", "ultstomp", "ultrecline", "telekinez", "ultclearance", "rupture", "doom", "ult_takeoff", "sphere", "freezetele" },
		enemyPart = { "head", "body" },
		typeUlt = { "aim","random","radius" },
		skillParam, skills, skillDesc;
};