#include "Race.h"

#define ts std::to_string


Race::Race() {
	int i = 1;
	while (i == 1) {

		try {
			GetSettings();
			Input();
			GiveUlt();
			GiveSkills();
			GiveParam();
			DefineCategory();
			CheckOnBeta(author);
#ifdef _DEBUG
			Debug();
#else
			Output();
#endif
			std::cout << "Continue (0 or 1): ";
			std::cin >> i;
			std::cout << "\n";
			Clear();

		}
		catch (std::exception& e) {
			std::cout << "Caught exception number: #" << e.what() << std::endl;
			system("pause");
			return;
		}


	}
}

void Race::PushSkill(int start, int add = 0, int skillID = 0, int change = 0, int value2 = 0, double value3 = 0, double value4=0, double value5=0) {
	int amountLvl = Random(skillsLvlMin, skillsLvlMax);
	if (add == 0)
		amountLvl = 1; // TODO FIX
	int* stage = NULL;
	int* stage2 = NULL;
	stage = new int[amountSkills];
	stage2 = new int[amountSkills];

	for (int i = 0; i < amountLvl - 1; i++) {
		if (skillID == 1)
			stage[i] = start - add * (i + 1);
		else if (skillID == 14)
			stage[i] = start + add * (i + 1);
		else if(skillID == 11) {
			stage[i] = start + add * (i + 1);
			stage2[i] = change + value2 * (i + 1);
		}		
		else
			stage[i] = start + add * (i + 1);
		switch (skillID) {
		case 0:
			break;
		case 2: {
			if (stage[i] >= 100)
				stage[i] = 100;
			break;
		}
		default:
			break;
		}
	}

	std::string buffer;

	for (int i = 0; i < amountLvl; i++) {
		if (i == 0 && skillID == 3)
			buffer += ts(start) + " " + ts(change);
		else if (i == 0 && skillID == 14)
			buffer += ts(value3) + " " + ts(start);
		else if(i == 0 && skillID == 11)
			buffer += ts(start) + " " + ts(change);
		else if (i == 0 && skillID == 4)
			buffer += ts(change) + " " + ts(start);
		else if (i == 0)
			buffer += ts(start);
		else if(skillID == 11)
			buffer += ";" + ts(stage[i - 1]) + " " + ts(stage2[i-1]);
		else if (skillID == 3)
			buffer += ";" + ts(stage[i - 1]) + " " + ts(change);
		else if (skillID == 4)
			buffer += ";" + ts(change) + " " + ts(stage[i - 1]);
		else if(skillID == 14)
			buffer += ";" + ts(value3) + " " + ts(stage[i-1]);
		else
			buffer += ";" + ts(stage[i - 1]);
	}
	skillParam.push_back(buffer);

	delete[] stage;
}

void Race::PushSkill(double start, double add=0, int skillID = 0, int change = 0, double value=0) { //#2
	if (skillID == 11) {
		throw std::exception("GrenlauncherPS_Error");
	}
	int amountLvl = Random(skillsLvlMin, skillsLvlMax);
	if (add == 0)
		amountLvl = 1;
	double* stage = new double[amountSkills];
	for (int i = 0; i < amountLvl - 1; i++) {
		if (skillID == 1)
			stage[i] = start - add * (i + 1);
		else if(skillID == 13)
			stage[i] = start + add * (i + 1);
		else if (amountLvl == 1)
			stage[i] = start;
		else if (skillID == 9)
			break;
		else if (skillID == 10)
			break;
		else 
			stage[i] = start + add * (i + 1);
		switch (skillID) {
			case 0:
				break;
			case 1: {
				if (stage[i] < 0.2f)
					stage[i] = 0.2f;
				break;
			}
			case 2: {
				throw std::exception("Case_Error");
				break;
			}
			case 7:
				if (stage[i] > 128)
					stage[i] = 128;
				break;
			case 13:
				if (stage[i] > 1000)
					stage[i] = 1000;
				break;
			default:
				break;
		}
	}

	std::string buffer;
	int type = Random(1, 2);

	for (int i = 0; i < amountLvl; i++) {
		if (i == 0 && skillID == 8)
			buffer += ts(start) + " " + ts(add) + " " + ts(value) + " " + ts(change);
		else if (i == 0 && skillID == 9) {
			buffer += ts(start) + " " + ts(add) + " " + ts(type);
			break;
		}
		else if (i == 0 && skillID == 13)
			buffer += ts(start) + " " + ts(change);
		else if (i == 0 && skillID == 10) {
			buffer += ts(start) + " " + ts(add) + " " + ts(change);
			break;
		}
		else if (i == 0 && skillID == 3)
			buffer += ts(start) + " " + ts(change);
		else if (i == 0 && skillID == 4)
			buffer += ts(change) + " " + ts(start);
		else if (i == 0)
			buffer += ts(start);
		else if(skillID == 13)
			buffer += ";" + ts(stage[i - 1]) + " " + ts(change);
		else if (skillID == 3)
			buffer += ";" + ts(stage[i - 1]) + " " + ts(change);
		else if (skillID == 4)
			buffer += ";" + ts(change) + " " + ts(stage[i - 1]);
		else if (skillID == 8)
			buffer += ";" + ts(stage[i - 1]) + " " + ts(change) + " " + ts(type);
		else if (i != 0)
			buffer += ";" + ts(stage[i - 1]);
		else
			throw std::exception("Data_Error");
	}
	skillParam.push_back(buffer);

	delete[] stage;
}


void Race::PushSkill(double valueF, int valueI=0, int skillID = 0, int change = 0, double value2=0) {
	int amountLvl = Random(skillsLvlMin, skillsLvlMax);
	if (valueI == 0)
		amountLvl = 1;
	double* stage = new double[amountSkills];
	for (int i = 0; i < amountLvl - 1; i++) {
		if (skillID == 12)
			stage[i] = valueI + change * (i + 1);

	}

	std::string buffer;

	for (int i = 0; i < amountLvl; i++) {
		if (skillID == 5) {
			buffer += ts(valueF + valueF) + " " + ts(valueI) + ";" + ts(valueF + valueF) + " " + ts(valueI) + ";" + ts(valueF) + " " + ts(valueI) + ";" + ts(valueF) + " " + ts(valueI);
			break;
		}
		else if (i==0 && skillID == 12)
			buffer += ts(valueI) + " " + ts(valueF) + " " + ts(value2);
		else if (skillID == 12)
			buffer += ";" + ts(stage[i]) + " " + ts(valueF) + " " + ts(value2);
	}
	skillParam.push_back(buffer);

	//delete[] stage;
}

void Race::PushSkill(int valueI, double valueF, int skillID, double valueF2) { // rockets TODO: PLS FIX THIS ISSUE
	std::string buffer;
	if (skillID == 6) {
		buffer += ts(valueI) + " " + ts(valueF) + " " + ts(valueF2);
	}
	skillParam.push_back(buffer);
}

//void Race::PushSkill(int value = 0, int value2 = 0, int skillID = 0, int value3 = 0, double value4 = 0, double value5 = 0, double value6 = 0) {
//	int amountLvl = Random(skillsLvlMin, skillsLvlMax);
//
//	double* stageD = new double[amountSkills];
//	int* stageI = new int[amountSkills];
//	for (int i = 0; i < amountLvl - 1; i++) {
//
//	}
//}

void Race::Clear() {
	std::cin.ignore();
	usedID.clear();
	skillParam.clear();
	skills.clear();
	skillDesc.clear();

}

void Race::CheckOnBeta(std::string &author) {
	if (BETA == 1) {
		author = "GOR Beta";
	}
}

void Race::Output() {
	std::ofstream file;
	file.open("C://Users/dredd/Desktop/Races.txt", std::ios::app); // TODO: Fix this shit
	if (!file)
		exit(1);
	file.imbue(std::locale(""));
	file << "\n\"" + name + "\"\n{";
	file << "\n\t\"required\"\t\"" + std::to_string(requiredLvl) + "\"";
	file << "\n\t\"author\"\t\"" + author + " " + VERSION + " | " + __DATE__ + "\"";
	file << "\n\t\"category\"\t\"" + category + "\"";
	file << "\n\t\"maxlvl\"\t\"" + std::to_string(maxLvl) + "\"";
	file << "\n\t\"teamlimit\"\t\"0\"";
	file << "\n\t\"skillamount\"\t\"" + std::to_string(amountSkills) + "\"";
	file << "\n\t\"skilllvls\"\t\"0\"";
	file << "\n\t\"skillnames\"\t\"";
	for (int i = 0; i < amountSkills; i++) {
		if (i != amountSkills - 1)
			file << skillDesc[i] + ";";
		else {
			file << skillDesc[i] + "\"";
		}
	}
	file << "\n\t\"skillDesc\"\t\"";
	for (int i = 0; i < amountSkills; i++) {
		if (i != amountSkills - 1)
			file << skillDesc[i] + ";";
		else {
			file << skillDesc[i] + "\"";
		}
	}
	for (int i = 0; i < amountSkills; i++) {
		file << "\n\t\"skill" + std::to_string(i + 1) + "\"\t\"" + skills[i] + "\"";
		if (skillParam[i] != "none")
			file << "\n\t\"setting" + std::to_string(i + 1) + "\"\t\"" + skillParam[i] + "\"";
	}
	file << "\n\t\"ultimate\"\t\"" + ultimate + "\"";
	file << "\n\t\"cooldown\"\t\"" + std::to_string(ultCooldown) + "\"";
	if (ability.length() != 0)
	{
		file << "\n\t\"ability\"\t\"" + ability + "\"";
	}
	file << "\n}";
	file.close();
}

void Race::Debug() {
	std::cout << "\n\"" + name + "\"\n{";
	std::cout << "\n\t\"required\"\t\"" + std::to_string(requiredLvl) + "\"";
	std::cout << "\n\t\"author\"\t\"" + author + " " + VERSION + " | Build " + __DATE__ + "\"";
	std::cout << "\n\t\"category\"\t\"" + category + "\"";
	std::cout << "\n\t\"maxlvl\"\t\"" + std::to_string(maxLvl) + "\"";
	std::cout << "\n\t\"teamlimit\"\t\"0\"";
	std::cout << "\n\t\"skillamount\"\t\"" + std::to_string(amountSkills) + "\"";
	std::cout << "\n\t\"skilllvls\"\t\"0\"";
	std::cout << "\n\t\"skillnames\"\t\"";
	for (int i = 0; i < amountSkills; i++) {
		if (i != amountSkills - 1)
			std::cout << skillDesc[i] + ";";
		else {
			std::cout << skillDesc[i] + "\"";
		}
	}
	std::cout << "\n\t\"skilldesc\"\t\"";
	for (int i = 0; i < amountSkills; i++) {
		if (i != amountSkills - 1)
			std::cout << skillDesc[i] + ";";
		else {
			std::cout << skillDesc[i] + "\"";
		}
	}
	for (int i = 0; i < amountSkills; i++) {
		std::cout << "\n\t\"skill" + std::to_string(i + 1) + "\"\t\"" + skills[i] + "\"";
		if (skillParam[i] != "none")
			std::cout << "\n\t\"setting" + std::to_string(i + 1) + "\"\t\"" + skillParam[i] + "\"";
	}
	std::cout << "\n\t\"ultimate\"\t\"" + ultimate + "\"";
	std::cout << "\n\t\"cooldown\"\t\"" + std::to_string(ultCooldown) + "\"";
	if (ability.length() != 0)
	{
		std::cout << "\n\t\"ability\"\t\"" + ability + "\"";
	}
	std::cout << "\n}\n";
}


void Race::GiveUlt() {
	double distance, damage, damage2, duration, duration2, speed, freezeTime, radius, amountF, height, buffer, lvl;
	int hp, idUlt = Random(0, ultimates.size() - 1), type, change, amount;

	lvl = double(requiredLvl / riseLvl);
	if (requiredLvl < riseLvl)
		lvl = 1.0;

	switch (idUlt) {
	case 0:
		ultCooldown = Random(5, 10);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "teleport";
		break;
	case 1:
		ultCooldown = Random(5, 10);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "jetpack";
		break;
	case 2:
		ultCooldown = Random(30, 55);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		distance = Random(300.0, 1500.0);
		damage = Random(10.0, 30.0);
		ultimate = "explode radius " + std::to_string(distance) + " " + std::to_string(damage);
		break;
	case 3:
		ultCooldown = Random(25, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		distance = Random(300.0, 800.0);
		duration = Random(1, 8);
		ultimate = "ultfreeze radius " + std::to_string(distance) + " " + std::to_string(duration);
		ultCooldown = Random(7, 12);
		break;
	case 4:
		ultCooldown = Random(4, 12);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "CreateProp models/props/cs_office/vending_machine.mdl";
		ability = "del";
		break;
	case 5:
		ultCooldown = Random(15, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		duration = Random(3, 8);
		ultimate = "ultgod " + std::to_string(duration);
		break;
	case 6:
		ultCooldown = Random(6, 12);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "webshot";
		break;
	case 7:
		ultCooldown = Random(20, 35);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		distance = Random(250, 50);
		duration = Random(1, 4);
		ultimate = "ultburn radius " + std::to_string(distance) + " " + std::to_string(duration);
		break;
	case 8:
		ultCooldown = Random(15, 25);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		speed = Random(9, 25);
		speed /= 10;
		duration = Random(1, 5);
		ultimate = "speedbuf " + std::to_string(speed) + " " + std::to_string(duration);
		break;
	case 9:
		ultCooldown = Random(40, 60);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		hp = Random(150, 250);
		ultimate = "heal " + std::to_string(hp);
		break;
	case 10:
		ultCooldown = Random(15, 25);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		distance = Random(250, 500);
		duration = Random(1, 4);
		ultimate = "ultblind radius " + std::to_string(distance) + " " + std::to_string(duration);
		break;
	case 11:
		ultCooldown = Random(20, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "ultremove";
		break;
	case 12:
		ultCooldown = Random(10, 15);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		distance = Random(30, 100);
		ultimate = "ultburyme " + std::to_string(distance);
		break;
	case 13:
		ultCooldown = Random(50, 70);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "fatality";
		break;
	case 14:
		ultCooldown = Random(40, 60);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "blink";
		break;
	case 15:
		ultCooldown = Random(40, 70);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "ultswap";
		break;
	case 16:
		ultCooldown = Random(40, 80);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		freezeTime = Random(25, 100);
		freezeTime /= 100;
		duration = Random(50, 200);
		duration /= 100;
		ultimate = "ultmatrix " + std::to_string(freezeTime) + " " + std::to_string(duration);
		break;
	case 17:
		ultCooldown = Random(30, 55);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, enemyPart.size() - 1);
		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		duration2 = Random(15, 25);
		duration2 /= 10;
		radius = Random(100, 250);
		ultimate = "chaos " + typeUlt[type] + " " + std::to_string(damage) + " " + std::to_string(duration) + " " + std::to_string(duration2) + " " + std::to_string(radius);
		break;
	case 18:
		ultCooldown = Random(10, 25);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "teleportator";
		break;
	case 19:
		ultCooldown = Random(10, 20);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "portals";
		break;
	case 20:
		ultCooldown = Random(10, 20);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "leap";
		break;
	case 21:
		ultCooldown = Random(25, 40);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		distance = Random(200, 1000);
		damage = Random(15, 35);
		ultimate = "ult_kamikaze " + std::to_string(distance) + " " + std::to_string(damage);
		break;
	case 22:
		ultCooldown = Random(30, 65);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		duration = Random(2, 5);
		ultimate = "ultgod_ally " + std::to_string(duration);
		break;
	case 23:
		ultCooldown = Random(15, 25);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		duration = Random(2, 5);
		ultimate = "rapidfire " + std::to_string(duration);
		break;
	case 24:
		ultCooldown = Random(25, 40);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		duration = Random(2, 7);
		ultimate = "ultnorecoil " + std::to_string(duration);
		break;
	case 25:
		ultCooldown = Random(40, 70);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, enemyPart.size() - 1);
		duration = Random(1, 4);
		ultimate = "ultaim " + enemyPart[type] + " " + std::to_string(duration);
		break;
	case 26:
		ultCooldown = Random(50, 70);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		duration = Random(2, 5);
		ultimate = "ultwh " + std::to_string(duration);
		break;
	case 27:
		ultCooldown = Random(7, 22);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "ultrandweapon";
		break;
	case 28:
		ultCooldown = Random(25, 33);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "ultsilence " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 29:
		ultCooldown = Random(22, 33);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		radius = Random(200, 500);
		damage = Random(10, 30);
		ultimate = "hook " + std::to_string(radius) + " " + std::to_string(damage);
		break;
	case 30:
		ultCooldown = Random(20, 35);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 800);
		duration = Random(2, 5);
		ultimate = "stun " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 31:
		ultCooldown = Random(35, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "disarm " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 32:
		ultCooldown = Random(20, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		damage = Random(80, 180);
		damage /= 100;
		change = Random(20, 60);
		duration = Random(4, 8);

		ultimate = "dmgbuf " + std::to_string(damage) + " " + std::to_string(duration);
		break;
	case 33:
		ultCooldown = Random(20, 25);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		radius = Random(300, 1500);
		damage = Random(1, 4);
		amount = Random(2, 10);
		ultimate = "eclipse " + std::to_string(radius) + " " + std::to_string(damage) + " " + std::to_string(amount);
		break;
	case 34:
		ultCooldown = Random(25, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		radius = Random(200, 800);
		ultimate = "ultsteal " + std::to_string(radius);
		break;
	case 35:
		ultCooldown = Random(15, 20);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		amount = Random(500, 2000);
		hp = Random(10, 50);
		ultimate = "cashheal " + std::to_string(amount) + " " + std::to_string(hp);
		break;
	case 36:
		ultCooldown = Random(20, 28);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		duration = Random(2, 5);
		damage = Random(1, 4);
		speed = Random(80, 120);
		speed /= 100;
		radius = Random(200, 800);
		ultimate = "saw " + std::to_string(duration) + " " + std::to_string(damage) + " " + std::to_string(speed) + " " + std::to_string(radius);
		break;
	case 37:
		ultCooldown = Random(15, 25);
		radius = Random(300, 1500);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		radius += buffer;

		type = Random(0, typeUlt.size() - 1);
		duration = Random(2, 5);
		ultimate = "ultblind " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 38:
		ultCooldown = Random(35, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		amountF = Random(80, 220);
		amountF /= 100;
		change = Random(30, 80);
		duration = Random(5, 8);

		ultimate = "satanic " + std::to_string(amountF) + " " + std::to_string(change) + " " + std::to_string(duration);
		break;
	case 39:
		ultCooldown = Random(30, 35);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		amountF = Random(80, 220);
		amountF /= 100;
		change = Random(30, 80);
		duration = Random(5, 8);
		ultimate = "mirror_shield " + std::to_string(amountF) + " " + std::to_string(change) + " " + std::to_string(duration);
		break;
	case 40:
		ultCooldown = Random(25, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);


		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "diet " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 41:
		ultCooldown = Random(20, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		damage = Random(10, 40);
		amount = Random(10, 40);
		ultimate = "locust_swarm " + std::to_string(damage) + " " + std::to_string(amount);
		break;
	case 42:
		ultCooldown = Random(25, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		damage = Random(10, 40);
		amount = Random(10, 40);
		ultimate = "locust_swarm2 " + std::to_string(damage) + " " + std::to_string(amount);
		break;
	case 43:
		ultCooldown = Random(30, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		amount = Random(500, 3000);
		ultimate = "ultstealcash " + std::to_string(amount);
		break;;
	case 44:
		ultCooldown = Random(30, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		damage = Random(20, 40);
		change = Random(1, 20);
		radius = Random(300, 1200);

		ultimate = "ultchain " + std::to_string(damage) + " " + std::to_string(change) + " " + std::to_string(radius);
		break;
	case 45:
		ultCooldown = Random(30, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		damage = Random(5, 20);
		change = Random(1, 20);
		radius = Random(300, 1200);

		ultimate = "ultchain2 " + std::to_string(damage) + " " + std::to_string(change) + " " + std::to_string(radius);
		break;
	case 46:
		ultCooldown = Random(25, 35);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		height = Random(100, 300);
		ultimate = "ultstomp " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(height) + " " + std::to_string(duration);
		break;
	case 47:
		ultCooldown = Random(20, 28);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		height = Random(100, 300);
		ultimate = "ultrecline " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(height) + " " + std::to_string(duration);
		break;
	case 48:
		ultCooldown = Random(20, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "telekinez " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 49:
		ultCooldown = Random(20, 25);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(300, 1500);
		duration = Random(5, 15);
		ultimate = "ultclearance " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 50:
		ultCooldown = Random(30, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, typeUlt.size() - 1);
		radius = Random(200, 600);
		damage = Random(5, 13); // instant
		damage2 = Random(1, 10);
		damage2 /= 100;
		duration = Random(3, 8);
		ultimate = "rupture " + typeUlt[type] + " " + std::to_string(damage) + " " + std::to_string(damage2) + " " + std::to_string(duration);
		break;
	case 51:
		ultCooldown = Random(20, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, enemyPart.size() - 1);
		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		duration2 = Random(15, 25);
		duration2 /= 10;
		radius = Random(100, 250);

		ultimate = "doom " + typeUlt[type] + " " + std::to_string(duration) + " " + std::to_string(damage) + " " + std::to_string(duration2) + " " + std::to_string(radius);
		break;
	case 52:
		ultCooldown = Random(30, 40);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		type = Random(0, enemyPart.size() - 1);
		radius = Random(100, 250);
		ultimate = "ult_takeoff " + enemyPart[type] + " " + std::to_string(radius);
		break;
	case 53:
		ultCooldown = Random(15, 25);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		amount = Random(1, 3);
		radius = Random(150, 350);
		ultimate = "sphere " + std::to_string(duration) + " " + std::to_string(radius) + " " + std::to_string(amount);
		break;
	case 54:
		ultCooldown = Random(10, 30);


		buffer = double(ultCooldown * (lvl * percent_rise / 100.0f));
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= int(buffer);

		ultimate = "freezetele";
		break;
	default:
		throw std::exception("Ultimate_Error");
	}

}

void Race::GiveSkills() {
	amountSkills = Random(minSkills, maxSkills);

	int random = Random(1, 4);
	if (random != 1)
		usedID.push_back(0); // elevated percent for speed (id=0) 
	else
		amountSkills = Random(minSkills_Exep, maxSkills_Exep);

	bool similar = false;
	while (usedID.size() != amountSkills) {
		unsigned int id = Random(0, skillNames.size() - 1); //Возможны ошибки, изменил: skillNames.size()-1
		while (id == 0)
			id = Random(0, skillNames.size() - 1);
		if (usedID.size() != 0) {
			for (unsigned i = 0; i < usedID.size(); i++) {
				if (id == usedID[i]) {
					break;
				}
				if (i == usedID.size() - 1 && similar != true) {
					//skills.push_back(skillNames[id]);
					usedID.push_back(id);
					similar = false;
				}
			}
		}
		else {
			// skills.push_back(skillNames[id]);
			usedID.push_back(id);
		}
	}
}

void Race::GiveParam() {
	int hp=0, addHp = 0, change = 0, change2 = 0, additionalChange = 0, amount = 0, additionalAmount = 0, maxAmount = 0, lvl = 0, type = 0;
	double stage[3] = {0,0,0}, common = 0, additionalCommon = 0, radius = 0, duration = 0, distance = 0, damage = 0, additionalDamage = 0, minDamage = 0, maxDamage = 0, multiplier = 0, multiplier2 = 0, delay = 0;
	std::string angle, accuracySkill;
	std::vector<std::string> antiSkills = { "antiult", "antiult_ally", "antiaura" , "antiaura_ally" , "antitotem" , "antitotem_ally" , "antilasermine" , "antilasermine_ally" , "antifall" , "antiflash" , "antiflash2" , "antiparalyze" , "antifreeze" , "antibury" , "antifear" , "antipoison" , "antidrug" , "antibeacon" , "antitimebomb" , "antishake" , "antipush" , "antisetangle", "antirockets" , "antihead" , "antiwh" , "antiaim" , "antimirror" , "antipassive" },
		defSkills = { "def_boom", "def_burn", "def_head", "def_knife", "def_bullet", "def_back" },
		protectSkills = { "protectfreeze", "protectburn", "protectslow" };

	lvl = requiredLvl / riseLvl;
	if (requiredLvl < riseLvl)
		lvl = 1;

	/* Выборка скилла
	usedID.clear();
	usedID.push_back(0);
	usedID.push_back(3);
	usedID.push_back(2);
	usedID.push_back(4);
	amountSkills = 4;*/

	for (unsigned i = 0; i < usedID.size(); i++) {
		switch (usedID[i]) {
		case 0:
			common = Random(0.8, 1.2);


			additionalCommon = Random(0.08, 0.1);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Скорость");
			skills.push_back("speed =");
			PushSkill(common, additionalCommon);
			break;
		case 1:
			common = Random(0.75, 1.00);
			additionalCommon = Random(0.08, 0.130);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Гравитация");
			skills.push_back("gravity =");
			PushSkill(common, additionalCommon, 1);
			break;
		case 2:
			hp = Random(80, 120);
			addHp = Random(3, 20);

			hp += hp * (lvl * (int)percent_rise / 100);
			addHp += addHp * (lvl * (int)percent_rise / 100);

			skillDesc.push_back("Здоровье");
			skills.push_back("hp =");
			PushSkill(hp, addHp);
			break;
		case 3:
			amount = Random(1, 15);
			additionalAmount = Random(1, 6);

			amount += amount * (lvl * (int)percent_rise / 100);
			additionalAmount += additionalAmount * (lvl * (int)percent_rise / 100);

			skillDesc.push_back("Невидимость");
			skills.push_back("invis");
			PushSkill(amount, additionalAmount, 2);
			break;
		case 4:
			common = Random(0.80, 1.20);
			additionalCommon = Random(0.10, 0.25);
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;


			skillDesc.push_back("Урон");
			skills.push_back("dmg =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 5:
			common = Random(0.60, 1.00);
			additionalCommon = Random(0.10, 0.40);
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Заморозка");
			skills.push_back("freeze =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 6:
			common = Random(0.80, 1.20);
			additionalCommon = Random(0.10, 0.40);
			change = Random(1, 10);


			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Поджег");
			skills.push_back("burn =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 7:
			common = Random(0.80, 1.20);
			additionalCommon = Random(0.10, 0.40);
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Вампирка");
			skills.push_back("vampire =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 8:
			// unit for every thousand lvl

			common = Random(3.0, 10.0);
			additionalCommon = Random(1.0, 5.0);
			distance = Random(100.0, 400.0);

			distance += distance * (lvl * percent_rise / 100);

			skillDesc.push_back("Взрыв после смерти");
			skills.push_back("boom");
			PushSkill(common, additionalCommon, 4, (int)distance); // MAY BE ERROR
			break;
		case 9:
			// unit for every thousand lvl

			duration = Random(1.0, 5.0);
			hp = Random(1, 5);

			hp += int(hp * (lvl * percent_rise / 100));

			skillDesc.push_back("Регенерация");
			skills.push_back("regen");
			PushSkill(duration, hp, 5);
			break;
		case 10:
			// unit for every thousand lvl

			common = Random(0.80, 1.20);
			additionalCommon = Random(0.10, 0.40);
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Замедление");
			skills.push_back("slow =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 11:
			// unit for every thousand lvl

			amount = Random(1, 5);
			minDamage = Random(10, 100);
			maxDamage = Random(70, 150);

			amount += int(amount * (lvl * percent_rise / 100));
			minDamage += minDamage * (lvl * percent_rise / 100);
			maxDamage += maxDamage * (lvl * percent_rise / 100);

			skillDesc.push_back("Ракеты");
			skills.push_back("rockets =");
			PushSkill(amount, minDamage, 6, maxDamage);
			break;
		case 12:
			// unit for every thousand lvl

			common = Random(80.0, 120.0);
			additionalCommon = Random(30.0, 50.0);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Длинный прыжок");
			skills.push_back("longjump =");
			PushSkill(common, additionalCommon);
			break;
		case 13:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Зеркало");
			skills.push_back("mirror =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 14:
			// unit for every thousand lvl

			change = Random(1, 10);
			additionalChange = Random(1, 4);

			change += int(change * (lvl * (int)percent_rise / 100));
			additionalChange += additionalChange * (lvl * (int)percent_rise / 100);

			skillDesc.push_back("Уклон");
			skills.push_back("evasion =");
			PushSkill(change, additionalChange, 2);
			break;
		case 15:
			// unit for every thousand lvl

			common = Random(18, 25);
			additionalCommon = Random(3, 7);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Высота шага");
			skills.push_back("step");
			PushSkill(common, additionalCommon, 7);
			break;
		case 16:
			// unit for every thousand lvl

			common = Random(60.0, 130.0);
			additionalCommon = Random(3.0, 33.0);
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Подброс противника");
			skills.push_back("push =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 17:
			// unit for every thousand lvl

			amount = Random(0, 2);
			additionalAmount = Random(0, 1);
			change = Random(1, 10);

			amount += amount * (lvl * (int)percent_rise / 100);
			additionalAmount += additionalAmount * (lvl * (int)percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Перевозрождение");
			skills.push_back("respawn");
			PushSkill(amount, additionalAmount, 0, change);
			break;
		case 18:
			change = Random(1, 7);

			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Выброс оружия");
			skills.push_back("dropweapon");
			PushSkill(change, 0);
			break;
		case 19:
			// unit for every thousand lvl

			common = Random(0.60, 1.00);
			additionalCommon = Random(0.10, 0.40);
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Паралич");
			skills.push_back("paralyze =");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 20:
			// unit for every thousand lvl
			type = Random(1, 2);
			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Ослепление");
			skills.push_back("blind =");
			PushSkill(common, additionalCommon, 8, change);
			break;
		case 21:
			// unit for every thousand lvl

			duration = Random(1, 2);
			common = Random(1, 2);
			maxDamage = Random(1, 6);
			change = Random(1, 5);

			maxDamage += maxDamage * (lvl * percent_rise / 100);
			duration += duration * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Яд");
			skills.push_back("poison =");
			PushSkill(duration, common, 9, change, maxDamage);
			break;
		case 22:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Иллюзии");
			skills.push_back("illusion");
			PushSkill(common, additionalCommon, 3, change);
			break;
		case 23:
			// unit for every thousand lvl

			duration = Random(1, 4);
			distance = Random(70, 100);
			change = Random(1, 10);

			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Закоп");
			skills.push_back("bury");
			PushSkill(duration, distance, 10, change);
			break;
		case 24:
			// unit for every thousand lvl

			amount = Random(0, 2);
			change = Random(10, 100);
			additionalDamage = Random(10, 20);
			additionalChange = Random(1, 2);

			amount += int(amount * (lvl * percent_rise / 100));
			damage += damage * (lvl * percent_rise / 100);
			additionalDamage += additionalDamage * (lvl * percent_rise / 100);
			additionalAmount += int(additionalAmount * (lvl * percent_rise / 100));

			skillDesc.push_back("Ружье-гранатомет");
			skills.push_back("grenlauncher =");
			PushSkill(amount, change, additionalAmount, 11, additionalChange);
			break;
		case 25:
			// unit for every thousand lvl

			amount = Random(1, 2);
			additionalAmount = Random(0, 1);
			multiplier = Random(80, 180);
			multiplier /= 100;
			radius = Random(80, 210); //radius multiplier
			radius /= 100;

			radius += radius * (lvl * percent_rise / 100);
			multiplier += multiplier * (lvl * percent_rise / 100);

			skillDesc.push_back("Усиление гранаты");
			skills.push_back("imbagrenade =");
			PushSkill(multiplier, amount, 12, additionalAmount, radius);
			break;
		case 26:
			// unit for every thousand lvl

			common = Random(120, 200);
			additionalCommon = Random(40, 60);
			change = Random(3, 8);

			change += change * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Длинный прыжок 2");
			skills.push_back("longjump2 =");
			PushSkill(common, additionalCommon, 13, change);
			break;
		case 27:
			// unit for every thousand lvl

			amount = Random(0, 3);
			additionalAmount = Random(0, 2);

			amount += amount * (lvl * percent_rise / 100);
			additionalAmount += additionalAmount * (lvl * percent_rise / 100);

			skillDesc.push_back("Двойной прыжок");
			skills.push_back("doublejumps =");
			PushSkill(amount, additionalAmount);
			break;
		case 28:
			// unit for every thousand lvl

			delay = Random(80, 200);
			delay /= 100;
			amount = Random(5, 50);
			additionalAmount = Random(5, 13);

			amount += amount * (lvl * percent_rise / 100);
			additionalAmount += additionalAmount * (lvl * percent_rise / 100);

			stage[0] = common + additionalCommon;
			stage[1] = common + additionalCommon * 2;
			stage[2] = common + additionalCommon * 3;

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Glow_Error");
			}

			skillDesc.push_back("Динамическая невидимость");
			skills.push_back("glow");
			PushSkill(amount, additionalAmount, 14, 0, 0, delay);
			break;
		case 29:
			change = Random(10, 50);
			additionalChange = Random(5, 10);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			stage[0] = int(change + additionalChange * 1.0);
			stage[1] = int(change + additionalChange * 2.0);
			stage[2] = int(change + additionalChange * 3.0);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Glow_Error");
			}

			skillDesc.push_back("Хамелеон");
			skills.push_back("chameleon");
			PushSkill(change, additionalChange, 2);
			break;
		case 30:
			common = Random(70, 140);
			common /= 100;
			additionalCommon = Random(5, 15);
			additionalCommon /= 100;

			skillDesc.push_back("Скорость атаки");
			skills.push_back("attackspeed =");
			PushSkill(common, additionalCommon, 15);
			break;
		case 31:
			// unit for every thousand lvl

			common = Random(70, 140);
			common /= 100;
			additionalCommon = Random(5, 15);
			additionalCommon /= 100;

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Скорость перезарядки");
			skills.push_back("quickreload =");
			PushSkill(common, additionalCommon, 15);
			break;
		case 32: // TODO Continue point
			// unit for every thousand lvl

			amount = Random(1, 5);
			additionalAmount = Random(1, 2);
			minDamage = Random(10, 50);
			maxDamage = Random(60, 110);

			amount += int(amount * (lvl * percent_rise / 100));
			additionalAmount += int(additionalAmount * (lvl * percent_rise / 100));
			minDamage += minDamage * (lvl * percent_rise / 100);
			maxDamage += maxDamage * (lvl * percent_rise / 100);

			skillDesc.push_back("Метательные ножи");
			skills.push_back("tknives =");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount + additionalAmount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount + additionalAmount * 2) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount + additionalAmount * 3) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage));
			break;
		case 33:
			skillDesc.push_back("Бесшумный бегун");
			skills.push_back("catwalk");
			skillParam.push_back("none");
			break;
		case 34:
			skillDesc.push_back("Мерцание");
			change = Random(1, 3);
			if (change == 1)
				skills.push_back("flicker fast");
			else if (change == 2)
				skills.push_back("flicker super");
			else if (change == 3)
				skills.push_back("flicker slow");
			skillParam.push_back("none");
			break;
		case 35:
			// unit for every thousand lvl

			delay = Random(1, 5);
			amount = Random(2, 10);
			additionalAmount = Random(1, 3);
			maxAmount = Random(70, 99);

			amount += int(amount * (lvl * percent_rise / 100));
			additionalAmount += int(additionalAmount * (lvl * percent_rise / 100));

			stage[0] = double(amount + additionalAmount);
			stage[1] = double(amount + additionalAmount * 2);
			stage[2] = double(amount + additionalAmount * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Obscurity_Error");
			}

			skillDesc.push_back("Стоячая невидимость");
			skills.push_back("obscurity");
			skillParam.push_back(std::to_string(delay) + " " + std::to_string(amount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(stage[0]) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(stage[1]) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(stage[2]) + " " + std::to_string(maxAmount));
			break;
		case 36:
			// unit for every thousand lvl

			delay = Random(1, 5);
			amount = Random(2, 10);
			additionalAmount = Random(1, 3);
			maxAmount = Random(70, 99);

			amount += int(amount * (lvl * percent_rise / 100));
			additionalAmount += int(additionalAmount * (lvl * percent_rise / 100));

			stage[0] = double(amount + additionalAmount);
			stage[1] = double(amount + additionalAmount * 2);
			stage[2] = double(amount + additionalAmount * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Obscurity_Error");
			}

			skillDesc.push_back("Сидячая невидимость");
			skills.push_back("obscurity_duck");
			skillParam.push_back(std::to_string(delay) + " " + std::to_string(amount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(int(stage[0])) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(int(stage[1])) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(int(stage[2])) + " " + std::to_string(maxAmount));
			break;
		case 37:
			// unit for every thousand lvl

			multiplier = Random(15, 48); // Damage
			multiplier /= 1000;
			multiplier2 = Random(15, 48); // Speed
			multiplier2 /= 1000;
			amount = Random(5, 15); // HP

			multiplier += multiplier * (lvl * percent_rise / 100);
			multiplier2 += multiplier2 * (lvl * percent_rise / 100);
			amount += int(amount * (lvl * percent_rise / 100));

			skillDesc.push_back("Зов крови");
			skills.push_back("thirst");
			skillParam.push_back(std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount + Random(1, 2)) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount + Random(2, 4)) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount + Random(4, 6)));
			break;
		case 38:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 10);
			radius = Random(150, 400);

			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			common += common * (lvl * percent_rise / 100);
			radius += radius * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Splash Damage");
			skills.push_back("splashdmg =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(radius) + " " + std::to_string(change));
			break;
		case 39:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 10);

			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			common += common * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Пошатывание");
			skills.push_back("shaker =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 40:
			// unit for every thousand lvl

			common = Random(200, 400);
			change = Random(1, 10);
			additionalChange = Random(5, 8);

			common += common * (lvl * percent_rise / 100);


			skillDesc.push_back("Притягивание противника");
			skills.push_back("losso =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 41:
			// unit for every thousand lvl

			common = Random(200, 400);
			change = Random(10, 30);
			additionalChange = Random(5, 8);

			common += common * (lvl * percent_rise / 100);

			skillDesc.push_back("Отталкивание противника");
			skills.push_back("repel =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 42:
			// unit for every thousand lvl

			change = Random(2, 5);
			additionalChange = Random(1, 2);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			skillDesc.push_back("Воровство всех патрон при атаке");
			skills.push_back("clip_destroy");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change + additionalChange) + ";" + std::to_string(change + additionalChange * 2) + ";" + std::to_string(change + additionalChange * 3));
			break;
		case 43:
			// unit for every thousand lvl

			amount = Random(5, 10);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			amount += int(amount * (lvl * percent_rise / 100));
			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			skillDesc.push_back("Воровство патрон при атаке");
			skills.push_back("clip_take");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 44:
			// unit for every thousand lvl

			amount = Random(2, 8);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			amount += int(amount * (lvl * percent_rise / 100));
			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			skillDesc.push_back("Пополнение обоймы");
			skills.push_back("clip_shot");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 45:
			// unit for every thousand lvl

			unsigned type;
			type = Random(0, 1);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			skillDesc.push_back("Украсть оружие");
			skills.push_back("takeweapon");
			skillParam.push_back(std::to_string(type) + " " + std::to_string(change) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 46:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 10);

			change += int(change * (lvl * percent_rise / 100));
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Страх");
			skills.push_back("fear =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 47:
			// unit for every thousand lvl

			change = Random(10, 30); // change of damage
			change2 = Random(10, 50);
			additionalChange = Random(2, 5); // additional for change

			change2 += int(change2 * (lvl * percent_rise / 100));
			change += int(change * (lvl * percent_rise / 100));

			skillDesc.push_back("Убийство танков");
			skills.push_back("dmghealth =");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change + additionalChange) + " " + std::to_string(change2 + Random(1, 2)) + ";" + std::to_string(change + additionalChange * 2) + " " + std::to_string(change2 + Random(2, 3)) + ";" + std::to_string(change + additionalChange * 3) + " " + std::to_string(change2 + Random(3, 4)));
			break;
		case 48:
			// unit for every thousand lvl

			duration = Random(1, 4);
			change = Random(10, 30);
			common = Random(80, 120);
			common /= 100;
			additionalChange = Random(3, 8);

			additionalChange += int(additionalChange * (lvl * percent_rise / 100));
			common += common * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			skillDesc.push_back("Адреналин при попадании");
			skills.push_back("adrenaline_rush =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 2) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 3) + " " + std::to_string(common));
			break;
		case 49:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			common += common * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Clearance");
			skills.push_back("clearance =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 50:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			common += common * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Silence");
			skills.push_back("silence =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 51:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			common += common * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Заблокировать респавн");
			skills.push_back("blockrespawn =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 52:
			// unit for every thousand lvl

			radius = Random(100, 200);
			additionalCommon = Random(30, 70);

			radius += radius * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);

			skillDesc.push_back("Увеличение радиуса ножа");
			skills.push_back("longknife");
			skillParam.push_back(std::to_string(radius) + ";" + std::to_string(radius + additionalCommon) + ";" + std::to_string(radius + additionalCommon * 2) + ";" + std::to_string(radius + additionalCommon * 3));
			break;
		case 53:
			// unit for every thousand lvl

			duration = Random(80, 210);
			duration /= 100;

			double x, y, z;
			x = Random(0, 360);
			y = Random(0, 360);
			z = Random(0, 360);

			angle = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);

			change = Random(5, 10);
			additionalChange = Random(2, 4);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));
			duration += duration * (lvl * percent_rise / 100);

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("SetAngle_Error");
			}

			skillParam.push_back(std::to_string(duration) + " " + angle + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(stage[0]) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(stage[1]) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(stage[2]));
			skillDesc.push_back("Развернуть противника при атаке");
			skills.push_back("setangle");
			break;
		case 54:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Применить запрещенные вещества на противнике");
			skills.push_back("drug =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 55:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Beacon");
			skills.push_back("beacon =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 56:
			// unit for every thousand lvl

			change = Random(1, 2);
			additionalChange = Random(0, 1);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("TimeBomb_Error");
			}

			skillDesc.push_back("Временная бомба");
			skills.push_back("timebomb =");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(stage[0]) + ";" + std::to_string(stage[1]) + ";" + std::to_string(stage[2]));
			break;
		case 57:
			type = Random(1, 3);
			if (type == 1)
				accuracySkill = "evasion";
			else if (type == 2)
				accuracySkill = "armor";
			else if (type == 3)
				accuracySkill = "antihead";
			else
				throw std::exception("Accuracy_Error");

			skillDesc.push_back("Игнорирование скилла");
			skills.push_back("accuracy");
			skillParam.push_back(accuracySkill + ";" + accuracySkill + ";" + accuracySkill + ";" + accuracySkill);
			break;
		case 58:
			// unit for every thousand lvl

			amount = Random(5, 20);
			change = Random(10, 30);

			amount += int(amount * (lvl * percent_rise / 100));
			change += int(change * (lvl * percent_rise / 100));
			if (change > 100)
				change = 100;

			skillDesc.push_back("Забрать здоровье после смерти");
			skills.push_back("killhp");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount + Random(1, 3)) + " " + std::to_string(change) + ";" + std::to_string(amount + Random(3, 4)) + " " + std::to_string(change) + ";" + std::to_string(amount + Random(4, 5)) + " " + std::to_string(change));
			break;
		case 59:
			// unit for every thousand lvl

			change = Random(10, 25);
			additionalChange = Random(5, 15);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("KillInvis_Error");
			}

			skillDesc.push_back("Забрать невидимость после смерти");
			skills.push_back("kill_invis");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(stage[0]) + ";" + std::to_string(stage[1]) + ";" + std::to_string(stage[2]));
			break;
		case 60:
			// unit for every thousand lvl

			duration = Random(1, 3);
			change = Random(10, 50);
			additionalChange = Random(3, 9);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Arcanum_Error");
			}

			skillDesc.push_back("Сокращение отката ульты при убийстве");
			skills.push_back("arcanum =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(stage[0]) + ";" + std::to_string(duration) + " " + std::to_string(stage[1]) + ";" + std::to_string(duration) + " " + std::to_string(stage[2]));
			break;
		case 61:
			// unit for every thousand lvl

			change = Random(10, 50); // damage
			change2 = Random(10, 30); // general
			additionalChange = Random(5, 8); // for general

			change += int(change * (lvl * percent_rise / 100));
			change2 += int(change2 * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			if (change2 > 100)
				change2 = 100;

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 100;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Armor_Error");
			}

			skillDesc.push_back("Снижение урона");
			skills.push_back("armor %");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(stage[0]) + " " + std::to_string(change2 + Random(1, 2)) + ";" + std::to_string(stage[1]) + " " + std::to_string(change2 + Random(2, 3)) + ";" + std::to_string(stage[2]) + " " + std::to_string(change2 + Random(3, 4)));
			break;
		case 62:
			// unit for every thousand lvl

			duration = Random(1, 4);
			change = Random(10, 30);
			common = Random(80, 120);
			common /= 100;
			additionalChange = Random(3, 8);

			duration += duration * (lvl * percent_rise / 100);
			common += common * (lvl * percent_rise / 100);

			skillDesc.push_back("Адреналин");
			skills.push_back("adrenaline =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 2) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 3) + " " + std::to_string(common));
			break;
		case 63:
			// unit for every thousand lvl

			duration = Random(80, 210);
			duration /= 100;

			x = Random(0, 360);
			y = Random(0, 360);
			z = Random(0, 360);

			angle = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);

			change = Random(5, 10);
			additionalChange = Random(2, 4);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 100;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("MirrorSetAngle_Error");
			}

			skillParam.push_back(std::to_string(duration) + " " + angle + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(stage[0]) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(stage[1]) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(stage[2]));
			skillDesc.push_back("Развернуть противника при попадании по Вам");
			skills.push_back("mirror_setangle");
			break;
		case 64:
			// unit for every thousand lvl

			change = Random(2, 5);
			additionalChange = Random(1, 2);

			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 100;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("MirrorClipDestroy_Error");
			}

			skillDesc.push_back("Воровство всех патрон при попадании по Вам");
			skills.push_back("mirror_clip_destroy");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(stage[0]) + ";" + std::to_string(stage[1]) + ";" + std::to_string(stage[2]));
			break;
		case 65:
			// unit for every thousand lvl

			amount = Random(5, 10);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			amount += int(amount * (lvl * percent_rise / 100));
			change += int(change * (lvl * percent_rise / 100));
			additionalChange += int(additionalChange * (lvl * percent_rise / 100));

			stage[0] = double(change + additionalChange);
			stage[1] = double(change + additionalChange * 2);
			stage[2] = double(change + additionalChange * 3);

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 100;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("MirrorClipDestroy_Error");
			}

			skillDesc.push_back("Воровство патрон при попадании по Вам");
			skills.push_back("mirror_clip_take");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(stage[0]) + ";" + std::to_string(amount) + " " + std::to_string(stage[1]) + ";" + std::to_string(amount) + " " + std::to_string(stage[2]));
			break;
		case 66:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Ослепление при попадании по Вам");
			skills.push_back("mirror_blind =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 67:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Поджег при попадании по Вам");
			skills.push_back("mirror_burn =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 68:
			// unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 10);

			common += common * (lvl * percent_rise / 100);
			additionalCommon += additionalCommon * (lvl * percent_rise / 100);
			change += int(change * (lvl * percent_rise / 100));

			if (change > 100)
				change = 100;

			skillDesc.push_back("Пошатывание при попадании по Вам");
			skills.push_back("mirror_shaker =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 69:
			change = Random(0, antiSkills.size() - 1);
			skillDesc.push_back("Игнорирование " + antiSkills[change]);
			skills.push_back(antiSkills[change]);
			skillParam.push_back("none");
			break;
		case 70:
			type = Random(0, antiSkills.size() - 1);
			skillDesc.push_back("Игнорирование " + antiSkills[type]);
			skills.push_back(antiSkills[type]);
			skillParam.push_back("none");
			break;
		case 71:
			type = Random(0, defSkills.size() - 1); //_def
			change = Random(10, 30); // of skill
			additionalChange = Random(5, 8);
			change2 = Random(20, 50); // general

			skillDesc.push_back("Снижение урона от " + defSkills[type]);
			skills.push_back(defSkills[type] + " =");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change + additionalChange) + " " + std::to_string(change2 + Random(1, 2)) + ";" + std::to_string(change + additionalChange * 2) + " " + std::to_string(change2 + Random(2, 3)) + ";" + std::to_string(change + additionalChange * 3) + " " + std::to_string(change2 + Random(3, 4)));
			break;
		case 72:
			type = Random(0, protectSkills.size() - 1); // protect
			change = Random(5, 20);
			additionalChange = Random(3, 8);

			skillDesc.push_back("Снижение шанса " + protectSkills[type]);
			skills.push_back(protectSkills[type] + " =");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change + additionalChange) + ";" + std::to_string(change + additionalChange * 2) + ";" + std::to_string(change + additionalChange * 3));
			break;
		case 73:
			skillDesc.push_back("Обратный прыжок");
			skills.push_back("backjump");
			skillParam.push_back("none");
			break;
		case 74:
			change = Random(1, 10);
			additionalCommon = Random(5, 8);

			change += int(change * (lvl * percent_rise / 100));

			if (change > 70)
				change = 70;

			skillDesc.push_back("Радар инвис");
			skills.push_back("radarinvis");
			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(change + additionalCommon)) + ";" + std::to_string(int(change + additionalCommon * 2)) + ";" + std::to_string(int(change + additionalCommon * 3)));
			break;
		case 75:
			skillDesc.push_back("Selfdiet");
			skills.push_back("selfdiet");
			skillParam.push_back("none");
			break;
		case 76:
			change = Random(1, 10);
			additionalCommon = Random(5, 8);

			change += int(change * (lvl * percent_rise / 100));

			if (change > 70)
				change = 70;

			skillDesc.push_back("Mole");
			skills.push_back("mole");
			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(change + additionalCommon)) + ";" + std::to_string(int(change + additionalCommon * 2)) + ";" + std::to_string(int(change + additionalCommon * 3)));
			break;
		default:
			throw std::exception("Skill_Error");
		}
	}
}



inline int Race::Random(int min, int max) {
	// construct a trivial random generator engine from a time-based seed:
	srand(NULL);
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> distribution(min, max);

	int number = distribution(generator);


	return number;
}

inline double Race::Random(double min, double max) {
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(min, max);

	double buffer = round(dis(gen) * 1000) / 1000;
	return buffer;
}

void Race::Input() {
	std::cout << "Name: ";
	std::getline(std::cin, name);
	std::cout << "Required lvl: ";
	std::cin >> requiredLvl;
}



void Race::GetSettings() {
	std::fstream config("./config.ini");
	if (!config.is_open()) {
		config.open("./config.ini", std::fstream::out);
		config << "[Settings]" << std::endl << "Max Level = 500" << std::endl << "Rise Level = 1000\nPercent for level = 1.0" << std::endl << "Minimal Skills = 4" << std::endl
			<< "Maximum Skills = 14" << std::endl << "Minimal Skills[25%] = 3" << std::endl << "Maximum Skills[25%] = 9" << std::endl << "Minimal lvls of skill = 4\nMaximum lvls of skill = 4\n";
		config << "[Cats Settings]" << std::endl;
		for (int i = 0; i < 16; i++) {
			config << "Cat[" << i << "] = " << std::endl << "Start of Cat[" << i << "] = " << i * 500 << std::endl << "End of Cat[" << i << "] = " << 500 * (i + 1) << std::endl;
		}
	}
	else if (config.is_open()) {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("./config.ini", pt);
		maxLvl = pt.get <int>("Settings.Max Level");
		riseLvl = pt.get<int>("Settings.Rise Level");
		percent_rise = pt.get<double>("Settings.Percent for level");
		minSkills = pt.get<int>("Settings.Minimal Skills");
		maxSkills = pt.get<int>("Settings.Maximum Skills");
		minSkills_Exep = pt.get<int>("Settings.Minimal Skills[25%]");
		maxSkills_Exep = pt.get<int>("Settings.Maximum Skills[25%]");
		skillsLvlMin = pt.get<int>("Settings.Minimal lvls of skill");
		skillsLvlMax = pt.get<int>("Settings.Maximum lvls of skill");
		for (int i = 0; i < 16; i++) {
			cats[i] = pt.get<std::string>("Cats Settings.Cat[" + std::to_string(i) + "]");
			startCat[i] = pt.get<int>("Cats Settings.Start of Cat[" + std::to_string(i) + "]");
			endCat[i] = pt.get<int>("Cats Settings.End of Cat[" + std::to_string(i) + "]");
		}
	}
	else
		throw std::exception("Config_Error");
}

void Race::DefineCategory() {
	for (int i = 0; i < 16; i++) {
		if (endCat[i] >= requiredLvl && requiredLvl > startCat[i]) {
			category = cats[i];
			break;
		}
		else if (cats[i] == "" || endCat[i] < requiredLvl || requiredLvl <= startCat[i])
			continue;
		else
			throw std::exception("Category_Error");
	}

}
