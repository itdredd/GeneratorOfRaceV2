#include "Race.h"

//backup https://pastebin.com/iZCF5mu2

TCHAR version[MAX_PATH];
TCHAR title[MAX_PATH];
TCHAR build_time[MAX_PATH];

#define VERSION "1.0.4"

Race::Race() {


	int i = 1;
	while (i == 1) {
		std::cout << "Name: ";
		std::getline(std::cin, name);
		std::cout << "Required lvl: ";
		std::cin >> requiredLvl;


		try {
			GetSettings();
			GiveUlt();
			GiveSkills();
			GiveParam();
			DefineCategory();
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
		catch (std::exception & e) {
			std::cout << "Caught exception number: #" << e.what() << std::endl;
			system("pause");
			return;
		}
		
	}
}

void Race::GetSettings() {
	std::fstream config("./config.ini");
	if (!config.is_open()) {
		config.open("./config.ini", std::fstream::out);
		config << "[Settings]" << std::endl << "RiseLevel=1000";
	}
	else if(config.is_open()) {
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("./config.ini", pt);
		riseLvl = pt.get<int>("Settings.RiseLevel");
	}
}

void Race::Clear() {
	std::cin.ignore();
	usedID.clear();
	skillsID.clear();
	skillParam.clear();
	skills.clear();
	skillDesc.clear();

}

void Race::DefineCategory() {
	if (requiredLvl == 0)
		category = "Дивизион для новичков";
	else if (requiredLvl <= 2000)
		category = "Первый дивизион (0-2000)";
	else if (4000 >= requiredLvl && requiredLvl > 2000)
		category = "Второй дивизион (2000-4000)";
	else if (6000 >= requiredLvl && requiredLvl > 4000)
		category = "Третий дивизион (4000-6000)";
	else if (8000 >= requiredLvl && requiredLvl > 6000)
		category = "Четвертый дивизион (6000-8000)";
	else if (10240 >= requiredLvl && requiredLvl > 8000)
		category = "Пятый дивизион (8000-10240)";
	else if (12000 >= requiredLvl && requiredLvl > 10240)
		category = "Шестой дивизион (10240-12000)";
	else if (21000 >= requiredLvl && requiredLvl > 12000)
		category = "Седьмой дивизион (12000-21000)";
	else if (30000 >= requiredLvl && requiredLvl > 21000)
		category = "Восьмой дивизион (21000-30000)";
	else if (40000 >= requiredLvl && requiredLvl > 30000)
		category = "Девятый дивизион (30000-40000)";
	else if (60000 >= requiredLvl && requiredLvl > 40000)
		category = "Десятый дивизион (40000-XXXXX)";
	else {
		category = "ERROR";
		throw std::exception("Category_Error");
	}
}

int Race::Random(int min, int max) {
    // construct a trivial random generator engine from a time-based seed:
	srand(NULL);
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);

    std::uniform_int_distribution<int> distribution(min, max);

    int number = distribution(generator);


    return number;
}

void Race::GiveSkills() {
    amountSkills = Random(4, 14);
	int random = Random(1, 4);
	if (random != 1)
		usedID.push_back(0); // elevated percent for speed (id=0) 
	else 
		amountSkills = Random(3, 9);
    bool similar = false;
    while(usedID.size() != amountSkills) {
        unsigned int id = Random(0, skillNames.size()-1); //Возможны ошибки, изменил: skillNames.size()-1
		if (id == 0)
			continue;
        else if (usedID.size() != 0) {
            for (unsigned i = 0; i < usedID.size(); i++) {
                if (id == usedID[i]) {
                    break;
                }
                if (i == usedID.size()-1 && similar != true) {
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
	double duration, distance, damage, additionalDamage, common, additionalCommon, minDamage, maxDamage, multiplier, multiplier2, radius, delay, for_level, lvl;
    int hp, change, change2, additionalChange, amount, additionalAmount, maxAmount, stage[3];
	std::string angle, accuracySkill;
	std::vector<std::string> antiSkills = { "antiult", "antiult_ally", "antiaura" , "antiaura_ally" , "antitotem" , "antitotem_ally" , "antilasermine" , "antilasermine_ally" , "antifall" , "antiflash" , "antiflash2" , "antiparalyze" , "antifreeze" , "antibury" , "antifear" , "antipoison" , "antidrug" , "antibeacon" , "antitimebomb" , "antishake" , "antipush" , "antisetangle", "antirockets" , "antihead" , "antiwh" , "antiaim" , "antimirror" , "antipassive" },
		defSkills = { "def_boom", "def_burn", "def_head", "def_knife", "def_bullet", "def_back" },
		protectSkills = { "protectfreeze", "protectburn", "protectslow"};

	lvl = requiredLvl / riseLvl;
	if (requiredLvl < 1000)
		lvl = 1;

    for (unsigned i = 0; i < usedID.size(); i++) {
		switch (usedID[i]) {
		case 0:
			for_level = 0.7; // unit for every thousand lvl
			
			common = Random(80, 120);
			common /= 100;

			additionalCommon = Random(20, 45);
			additionalCommon /= 100;

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl*for_level / 100);

			skillDesc.push_back("Скорость");
			skills.push_back("speed =");
			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common + additionalCommon) + ";" + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(common + additionalCommon * 3));
			break;
		case 1:
			for_level = 1; // unit for every thousand lvl

			common = Random(75, 100);
			common /= 100;
			additionalCommon = Random(80, 130);
			additionalCommon /= 1000;

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			stage[0] = common - additionalCommon;
			stage[1] = common - additionalCommon * 2;
			stage[2] = common - additionalCommon * 3;

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] <= 0.1)
					stage[i] = 0.1;
				else if (stage[i] > 0.1)
					break;
				else 
					throw std::exception("Gravity_Error");
			}

			skillDesc.push_back("Гравитация");
			skills.push_back("gravity =");
			skillParam.push_back(std::to_string(common) + ";" + std::to_string(stage[0]) + ";" + std::to_string(stage[1]) + ";" + std::to_string(stage[2]));
			break;
		case 2:
			for_level = 2; // unit for every thousand lvl

			common = Random(80, 120);
			additionalCommon = Random(3, 20);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Здоровье");
			skills.push_back("hp =");
			skillParam.push_back(std::to_string(int(common)) + ";" + std::to_string(int(common + additionalCommon)) + ";" + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 3:
			for_level = 2; // unit for every thousand lvl

			common = Random(3, 30);
			additionalCommon = Random(3, 10);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			stage[0] = common + additionalCommon;
			stage[1] = common + additionalCommon * 2;
			stage[2] = common + additionalCommon * 3;

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Invis_Error");
			}

			skillDesc.push_back("Невидимость");
			skills.push_back("invis");
			skillParam.push_back(std::to_string(int(common)) + " all" + ";" + std::to_string(int(stage[0])) + " all" + ";" + std::to_string(int(stage[1])) + " all" + ";" + std::to_string(int(stage[2])) + " all");
			break;
		case 4:
			for_level = 1; // unit for every thousand lvl
			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Урон");
			skills.push_back("dmg =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 5:
			for_level = 1; // unit for every thousand lvl

			common = Random(60, 100);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 75);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Заморозка");
			skills.push_back("freeze =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 6:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Поджег");
			skills.push_back("burn =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 7:
			for_level = 1; // unit for every thousand lvl
			
			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 70);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Вампирка");
			skills.push_back("vampire =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 8:
			for_level = 2; // unit for every thousand lvl

			common = Random(3, 10);
			additionalCommon = Random(1, 5);
			distance = Random(100, 400);

			distance += distance * (lvl * for_level / 100);

			skillDesc.push_back("Взрыв после смерти");
			skills.push_back("boom");
			skillParam.push_back(std::to_string(distance) + " " + std::to_string(common) + ";" + std::to_string(distance) + " " + std::to_string(common + additionalCommon) + ";" + std::to_string(distance) + " " + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(distance) + " " + std::to_string(common + additionalCommon * 3));
			break;
		case 9:
			for_level = 2; // unit for every thousand lvl

			duration = Random(1, 5);
			hp = Random(1, 5);

			hp += hp * (lvl * for_level / 100);

			skillDesc.push_back("Регенерация");
			skills.push_back("regen");
			skillParam.push_back(std::to_string(duration + duration) + " " + std::to_string(hp) + ";" + std::to_string(duration + duration) + " " + std::to_string(hp) + ";" + std::to_string(duration) + " " + std::to_string(hp) + ";" + std::to_string(duration) + " " + std::to_string(hp));
			break;
		case 10:
			for_level = 2; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Замедление");
			skills.push_back("slow =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 11:
			for_level = 1; // unit for every thousand lvl

			amount = Random(1, 5);
			minDamage = Random(10, 100);
			maxDamage = Random(70, 150);

			amount += amount * (lvl * for_level / 100);
			minDamage += minDamage * (lvl * for_level / 100);
			maxDamage += maxDamage * (lvl * for_level / 100);

			skillDesc.push_back("Ракеты");
			skills.push_back("rockets =");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage));
			break;
		case 12:
			for_level = 2; // unit for every thousand lvl

			common = Random(80, 120);
			additionalCommon = Random(30, 50);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Длинный прыжок");
			skills.push_back("longjump =");
			skillParam.push_back(std::to_string(float(common)) + ";" + std::to_string(float(common + additionalCommon)) + ";" + std::to_string(float(common + additionalCommon * 2)) + ";" + std::to_string(float(common + additionalCommon * 3)));
			break;
		case 13:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Зеркало");
			skills.push_back("mirror =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 14:
			for_level = 1; // unit for every thousand lvl

			change = Random(1, 30);
			additionalCommon = Random(2, 5);

			change += change * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			stage[0] = change + additionalCommon;
			stage[1] = change + additionalCommon * 2;
			stage[2] = change + additionalCommon * 3;

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 100)
					stage[i] = 98;
				else if (stage[i] <= 100)
					break;
				else
					throw std::exception("Evasion_Error");
			}

			skillDesc.push_back("Уклон");
			skills.push_back("evasion =");
			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(stage[0])) + ";" + std::to_string(int(stage[1])) + ";" + std::to_string(int(stage[2])));
			break;
		case 15:
			for_level = 2; // unit for every thousand lvl

			common = Random(15, 25);
			additionalCommon = Random(3, 7);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			stage[0] = common + additionalCommon;
			stage[1] = common + additionalCommon * 2;
			stage[2] = common + additionalCommon * 3;

			for (int i = 0; i < sizeof(stage); i++) {
				if (stage[i] > 128)
					stage[i] = 128;
				else if (stage[i] <= 128)
					break;
				else
					throw std::exception("Evasion_Error");
			}

			skillDesc.push_back("Высота шага");
			skills.push_back("step");
			skillParam.push_back(std::to_string(int(common)) + ";" + std::to_string(int(common + additionalCommon)) + ";" + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 16:
			for_level = 2; // unit for every thousand lvl

			common = Random(60, 130);
			additionalCommon = Random(3, 33);
			change = Random(1, 99);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Подброс противника");
			skills.push_back("push =");
			skillParam.push_back(std::to_string(int(common)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 2)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 3)) + " " + std::to_string(change));
			break;
		case 17:
			for_level = 3; // unit for every thousand lvl

			common = Random(0, 2);
			additionalCommon = Random(0, 1);
			change = Random(1, 99);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Перевозрождение");
			skills.push_back("respawn");
			skillParam.push_back(std::to_string(int(common)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 2)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 3)) + " " + std::to_string(change));
			break;
		case 18:
			change = Random(1, 99);

			skillDesc.push_back("Выброс оружия");
			skills.push_back("dropweapon");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change) + ";" + std::to_string(change) + ";" + std::to_string(change));
			break;
		case 19:
			for_level = 2; // unit for every thousand lvl

			common = Random(60, 100);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 70);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Паралич");
			skills.push_back("paralyze =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 20:
			for_level = 2; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Ослепление");
			skills.push_back("blind =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 21:
			for_level = 2; // unit for every thousand lvl

			duration = Random(1, 3);
			common = Random(1, 3);
			maxDamage = Random(1, 8);
			change = Random(1, 99);

			maxDamage += maxDamage * (lvl * for_level / 100);
			duration += duration * (lvl * for_level / 100);

			skillDesc.push_back("Яд");
			skills.push_back("poison =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change - change) + ";" + std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change - change) + ";" + std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change));
			break;
		case 22:
			for_level = 2; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Иллюзии");
			skills.push_back("illusion");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 23:
			for_level = 2; // unit for every thousand lvl

			duration = Random(1, 4);
			distance = Random(70, 100);
			change = Random(1, 99);

			change += change * (lvl * for_level / 100);
			if (change > 100)
				change = 100;

			skillDesc.push_back("Закоп");
			skills.push_back("bury");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change));
			break;
		case 24:
			for_level = 2; // unit for every thousand lvl

			amount = Random(0, 2);
			damage = Random(10, 100);
			additionalDamage = Random(10, 20);
			additionalAmount = Random(1, 2);

			amount += amount * (lvl * for_level / 100);
			damage += damage * (lvl * for_level / 100);
			additionalDamage += additionalDamage * (lvl * for_level / 100);
			additionalAmount += additionalAmount * (lvl * for_level / 100);

			skillDesc.push_back("Ружье-гранатомет");
			skills.push_back("grenlauncher =");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(int(damage)) + ";" + std::to_string(amount + additionalAmount) + " " + std::to_string(int(damage+additionalDamage)) + ";" + std::to_string(amount + additionalAmount *2) + " " + std::to_string(int(damage + additionalDamage*2)) + ";" + std::to_string(amount + additionalAmount * 3) + " " + std::to_string(int(damage + additionalDamage * 3)));
			break;
		case 25:
			for_level = 2; // unit for every thousand lvl

			amount = Random(1, 2);
			additionalAmount = Random(0, 1);
			multiplier = Random(80, 180);
			multiplier /= 100;
			radius = Random(80, 210); //radius multiplier
			radius /= 100;

			radius += radius * (lvl * for_level / 100);
			multiplier += multiplier * (lvl * for_level / 100);

			skillDesc.push_back("Усиление гранаты");
			skills.push_back("imbagrenade =");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(multiplier) + " " + std::to_string(radius) + ";" + std::to_string(amount+additionalAmount) + " " + std::to_string(multiplier) + " " + std::to_string(radius) + ";" + std::to_string(amount+additionalAmount*2) + " " + std::to_string(multiplier) + " " + std::to_string(radius) + ";" + std::to_string(amount+additionalAmount*3) + " " + std::to_string(multiplier) + " " + std::to_string(radius));
			break;
		case 26:
			for_level = 2; // unit for every thousand lvl

			common = Random(120, 200);
			additionalCommon = Random(40, 60);
			delay = Random(3, 8);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Длинный прыжок 2");
			skills.push_back("longjump2 =");
			skillParam.push_back(std::to_string(float(common)) + " " + std::to_string(delay) +";" + std::to_string(float(common + additionalCommon)) + " " + std::to_string(delay) + ";" + std::to_string(float(common + additionalCommon * 2)) + " " + std::to_string(delay) + ";" + std::to_string(float(common + additionalCommon * 3)) + " " + std::to_string(delay));
			break;
		case 27:
			for_level = 2; // unit for every thousand lvl

			common = Random(0, 3);
			additionalCommon = Random(0, 2);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Двойной прыжок");
			skills.push_back("doublejumps =");
			skillParam.push_back(std::to_string(int(common)) + ";" + std::to_string(int(common + additionalCommon)) + ";" + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 28:
			for_level = 2; // unit for every thousand lvl

			delay = Random(80, 200);
			delay /= 100;
			common = Random(5, 50);
			additionalCommon = Random(5, 13);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

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
			skillParam.push_back(std::to_string(delay) + " " + std::to_string(int(common)) + ";" + std::to_string(delay) + " " + std::to_string(int(stage[0])) +  ";" + std::to_string(delay) + " " + std::to_string(int(stage[1])) + ";" + std::to_string(delay) + " " + std::to_string(int(stage[2])));
			break;
		case 29:
			for_level = 2; // unit for every thousand lvl

			change = Random(10, 50);
			additionalChange = Random(5, 10);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(stage[0])) + ";" + std::to_string(int(stage[1])) + ";" + std::to_string(int(stage[2])));
			break;
		case 30:
			common = Random(70, 140);
			common /= 100;
			additionalCommon = Random(5, 15);
			additionalCommon /= 100;

			skillDesc.push_back("Скорость атаки");
			skills.push_back("attackspeed =");
			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common + additionalCommon) + ";" + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(common + additionalCommon * 3));
			break;
		case 31:
			for_level = 1; // unit for every thousand lvl

			common = Random(70, 140);
			common /= 100;
			additionalCommon = Random(5, 15);
			additionalCommon /= 100;

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Скорость перезарядки");
			skills.push_back("quickreload =");
			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common + additionalCommon) + ";" + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(common + additionalCommon * 3));
			break;
		case 32:
			for_level = 2; // unit for every thousand lvl

			amount = Random(1, 5);
			additionalAmount = Random(1, 2);
			minDamage = Random(10, 50);
			maxDamage = Random(60, 110);

			amount += amount * (lvl * for_level / 100);
			additionalAmount += additionalAmount * (lvl * for_level / 100);
			minDamage += minDamage * (lvl * for_level / 100);
			maxDamage += maxDamage * (lvl * for_level / 100);

			skillDesc.push_back("Метательные ножи");
			skills.push_back("tknives =");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount + additionalAmount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount+additionalAmount*2) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount+additionalAmount*3) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage));
			break;
		case 33:
			skillDesc.push_back("Бесшумный бегун");
			skills.push_back("catwalk");
			skillParam.push_back("none");
			break;
		case 34:
			skillDesc.push_back("Мерцание");
			change = Random(1, 3);
			if(change == 1)
				skills.push_back("flicker fast");
			else if (change == 2)
				skills.push_back("flicker super");
			else if (change == 3)
				skills.push_back("flicker slow");
			skillParam.push_back("none");
			break;
		case 35:
			for_level = 1; // unit for every thousand lvl

			delay = Random(1, 5);
			amount = Random(2, 10);
			additionalAmount = Random(1, 3);
			maxAmount = Random(70, 99);

			amount += amount * (lvl * for_level / 100);
			additionalAmount += additionalAmount * (lvl * for_level / 100);

			stage[0] = amount + additionalAmount;
			stage[1] = amount + additionalAmount * 2;
			stage[2] = amount + additionalAmount * 3;

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
			for_level = 1; // unit for every thousand lvl

			delay = Random(1, 5);
			amount = Random(2, 10);
			additionalAmount = Random(1, 3);
			maxAmount = Random(70, 99);

			amount += amount * (lvl * for_level / 100);
			additionalAmount += additionalAmount * (lvl * for_level / 100);

			stage[0] = common + additionalCommon;
			stage[1] = common + additionalCommon * 2;
			stage[2] = common + additionalCommon * 3;

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
			skillParam.push_back(std::to_string(delay) + " " + std::to_string(amount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(stage[0]) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(stage[1]) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(stage[2]) + " " + std::to_string(maxAmount));
			break;
		case 37:
			for_level = 1; // unit for every thousand lvl

			multiplier = Random(15, 48); // Damage
			multiplier /= 1000;
			multiplier2 = Random(15, 48); // Speed
			multiplier2 /= 1000;
			amount = Random(5, 15); // HP

			multiplier += multiplier * (lvl * for_level / 100);
			multiplier2 += multiplier2 * (lvl * for_level / 100);
			amount += amount * (lvl * for_level / 100);

			skillDesc.push_back("Зов крови");
			skills.push_back("thirst");
			skillParam.push_back(std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount+Random(1,2)) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount+Random(2,4)) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount+Random(4,6)));
			break;
		case 38:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);
			radius = Random(150, 400);

			additionalCommon += additionalCommon * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);
			radius += radius * (lvl * for_level / 100);

			skillDesc.push_back("Splash Damage");
			skills.push_back("splashdmg =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon)  + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(radius) + " " + std::to_string(change));
			break;
		case 39:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			additionalCommon += additionalCommon * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);

			skillDesc.push_back("Пошатывание");
			skills.push_back("shaker =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 40:
			for_level = 1; // unit for every thousand lvl

			common = Random(200, 400);
			change = Random(10, 30);
			additionalChange = Random(5, 8);

			common += common * (lvl * for_level / 100);
			
			skillDesc.push_back("Притягивание противника");
			skills.push_back("losso =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common) + " " + std::to_string(change+additionalChange) + ";" + std::to_string(common) + " " + std::to_string(change+additionalChange*2) + ";" + std::to_string(common) + " " + std::to_string(change+additionalChange*3));
			break;
		case 41:
			for_level = 2; // unit for every thousand lvl

			common = Random(200, 400);
			change = Random(10, 30);
			additionalChange = Random(5, 8);

			common += common * (lvl * for_level / 100);

			skillDesc.push_back("Отталкивание противника");
			skills.push_back("repel =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 42:
			for_level = 1; // unit for every thousand lvl

			change = Random(2, 5);
			additionalChange = Random(1, 2);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			skillDesc.push_back("Воровство всех патрон при атаке");
			skills.push_back("clip_destroy");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change + additionalChange) + ";" + std::to_string(change + additionalChange * 2) + ";" + std::to_string(change + additionalChange * 3));
			break;
		case 43:
			for_level = 1; // unit for every thousand lvl

			amount = Random(5, 10);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			amount += amount * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			skillDesc.push_back("Воровство патрон при атаке");
			skills.push_back("clip_take");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 44:
			for_level = 1; // unit for every thousand lvl

			amount = Random(2, 8);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			amount += amount * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			skillDesc.push_back("Пополнение обоймы");
			skills.push_back("clip_shot");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 45:
			for_level = 1; // unit for every thousand lvl

			unsigned type;
			type = Random(0, 1);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			skillDesc.push_back("Украсть оружие");
			skills.push_back("takeweapon");
			skillParam.push_back(std::to_string(type) + " " + std::to_string(change) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 46:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 40);
			additionalCommon /= 100;
			change = Random(1, 80);

			change += change * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);

			skillDesc.push_back("Страх");
			skills.push_back("fear =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 47:
			for_level = 1; // unit for every thousand lvl

			change = Random(5, 30); // change of damage
			change2 = Random(10, 50);
			additionalChange = Random(2, 5); // additional for change

			change2 += change2 * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);

			skillDesc.push_back("Убийство танков");
			skills.push_back("dmghealth =");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change+additionalChange) + " " + std::to_string(change2+Random(1,2)) + ";" + std::to_string(change+additionalChange*2) + " " + std::to_string(change2+Random(2,3)) + ";" + std::to_string(change+additionalChange*3) + " " + std::to_string(change2+Random(3,4)));
			break;
		case 48:
			for_level = 1; // unit for every thousand lvl

			duration = Random(1, 4);
			change = Random(10, 30);
			common = Random(80, 120);
			common /= 100;
			additionalChange = Random(3, 8);

			additionalChange += additionalChange * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);

			skillDesc.push_back("Адреналин при попадании");
			skills.push_back("adrenaline_rush =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange*2) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange*3) + " " + std::to_string(common));
			break;
		case 49:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			additionalCommon += additionalCommon * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);

			skillDesc.push_back("Clearance");
			skills.push_back("clearance =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 50:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			additionalCommon += additionalCommon * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);

			skillDesc.push_back("Silence");
			skills.push_back("silence =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 51: 
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			additionalCommon += additionalCommon * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);

			skillDesc.push_back("Заблокировать респавн");
			skills.push_back("blockrespawn =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 52:
			for_level = 1; // unit for every thousand lvl

			radius = Random(100, 200);
			additionalCommon = Random(30, 70);

			radius += radius * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Увеличение радиуса ножа");
			skills.push_back("longknife");
			skillParam.push_back(std::to_string(radius) + ";" + std::to_string(radius+additionalCommon) + ";" + std::to_string(radius + additionalCommon*2) + ";" + std::to_string(radius + additionalCommon*3));
			break;
		case 53:
			for_level = 1; // unit for every thousand lvl

			duration = Random(80, 210);
			duration /= 100;

			float x, y, z;
			x = float(Random(0, 360));
			y = float(Random(0, 360));
			z = float(Random(0, 360));

			angle = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);

			change = Random(5, 10);
			additionalChange = Random(2, 4);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);
			duration += duration * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Применить запрещенные вещества на противнике");
			skills.push_back("drug =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 55:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Beacon");
			skills.push_back("beacon =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 56:
			for_level = 2; // unit for every thousand lvl

			change = Random(1, 2);
			additionalChange = Random(0, 1);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			amount = Random(5, 20);
			change = Random(10, 30);

			amount += amount * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);
			if (change > 100)
				change = 100;

			skillDesc.push_back("Забрать здоровье после смерти");
			skills.push_back("killhp");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount+Random(1,3)) + " " + std::to_string(change) + ";" + std::to_string(amount+ Random(3,4)) + " " + std::to_string(change) + ";" + std::to_string(amount+Random(4,5)) + " " + std::to_string(change));
			break;
		case 59:
			for_level = 1; // unit for every thousand lvl

			change = Random(10, 25);
			additionalChange = Random(5, 15);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 2; // unit for every thousand lvl

			duration = Random(1, 3);
			change = Random(10, 50);
			additionalChange = Random(3, 9);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			change = Random(10, 50); // damage
			change2 = Random(10, 30); // general
			additionalChange = Random(5, 8); // for general

			change += change * (lvl * for_level / 100);
			change2 += change2 * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			if (change2 > 100)
				change2 = 100;

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			duration = Random(1, 4);
			change = Random(10, 30);
			common = Random(80, 120);
			common /= 100;
			additionalChange = Random(3, 8);

			duration += duration * (lvl * for_level / 100);
			common += common * (lvl * for_level / 100);

			skillDesc.push_back("Адреналин");
			skills.push_back("adrenaline =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 2) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 3) + " " + std::to_string(common));
			break;
		case 63:
			for_level = 1; // unit for every thousand lvl

			duration = Random(80, 210);
			duration /= 100;

			x = float(Random(0, 360));
			y = float(Random(0, 360));
			z = float(Random(0, 360));

			angle = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);

			change = Random(5, 10);
			additionalChange = Random(2, 4);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			change = Random(2, 5);
			additionalChange = Random(1, 2);

			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			amount = Random(5, 10);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			amount += amount * (lvl * for_level / 100);
			change += change * (lvl * for_level / 100);
			additionalChange += additionalChange * (lvl * for_level / 100);

			stage[0] = change + additionalChange;
			stage[1] = change + additionalChange * 2;
			stage[2] = change + additionalChange * 3;

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
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Ослепление при попадании по Вам");
			skills.push_back("mirror_blind =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 67:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Поджег при попадании по Вам");
			skills.push_back("mirror_burn =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 68:
			for_level = 1; // unit for every thousand lvl

			common = Random(80, 120);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			common += common * (lvl * for_level / 100);
			additionalCommon += additionalCommon * (lvl * for_level / 100);

			skillDesc.push_back("Пошатывание при попадании по Вам");
			skills.push_back("mirror_shaker =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 69:
			change = Random(0, antiSkills.size()-1);
			skillDesc.push_back("Игнорирование " + antiSkills[change]);
			skills.push_back(antiSkills[change]);
			skillParam.push_back("none");
			break;
		case 70:
			type = Random(0, antiSkills.size()-1);
			skillDesc.push_back("Игнорирование " + antiSkills[type]);
			skills.push_back(antiSkills[type]);
			skillParam.push_back("none");
			break;
		case 71:
			type = Random(0, defSkills.size()-1);
			change = Random(10, 30); // of skill
			additionalChange = Random(5, 8);
			change2 = Random(20, 50); // general

			skillDesc.push_back("Снижение урона от " + defSkills[type]);
			skills.push_back(defSkills[type] + " =");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change + additionalChange) + " " + std::to_string(change2 + Random(1, 2)) + ";" + std::to_string(change + additionalChange * 2) + " " + std::to_string(change2 + Random(2, 3)) + ";" + std::to_string(change + additionalChange * 3) + " " + std::to_string(change2 + Random(3, 4)));
			break;
		case 72:
			type = Random(0, protectSkills.size()-1); 
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
			change = Random(1, 44);
			additionalCommon = Random(5, 8);

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
			change = Random(1, 44);
			additionalCommon = Random(5, 8);

			skillDesc.push_back("Mole");
			skills.push_back("mole");
			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(change + additionalCommon)) + ";" + std::to_string(int(change + additionalCommon * 2)) + ";" + std::to_string(int(change + additionalCommon * 3)));
			break;
		default:
			throw std::exception("Skill_Error");
		}
    }
}

void Race::Output() {
	std::wstring buffer = version;
	std::string sVersion(buffer.begin(), buffer.end());

	std::ofstream file;
	file.open("C://Users/dredd/Desktop/Races.txt", std::ios::app);
	if (!file)
		exit(1);
	file << "\n\"" + name + "\"\n{";
	file << "\n\t\"required\"\t\"" + std::to_string(requiredLvl) + "\"";
	file << "\n\t\"author\"\t\"" + author + " " + sVersion + " | " + __DATE__ + "\"";
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
	file << "\n\t\"cooldown\"\t\"" + std::to_string(ultCooldown) +"\"";
	if (ability.length() != 0)
	{	
		file << "\n\t\"ability\"\t\"" + ability + "\"";
	}
	file << "\n}";
	file.close();
}

void Race::Debug() {
	std::wstring buffer = version;
	std::string sVersion(buffer.begin(), buffer.end());

	std::cout << "\n\"" + name + "\"\n{";
	std::cout << "\n\t\"required\"\t\"" + std::to_string(requiredLvl) + "\"";
	std::cout << "\n\t\"author\"\t\"" + author + " " + sVersion + " | Build " + __DATE__ + "\"";
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
	float distance, damage, damage2, duration, duration2, speed, freezeTime, radius, amountF, height;
	int hp, idUlt = Random(0, ultimates.size() - 1), type, change, amount;
	double buffer, for_level, lvl;

	lvl = requiredLvl / riseLvl;
	if (requiredLvl < 1000)
		lvl = 1;

	switch (idUlt) {
	case 0:
		ultCooldown = Random(5, 10);

		for_level = 3.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else 
			ultCooldown -= buffer;

		ultimate = "teleport";
		break;
	case 1:
		ultCooldown = Random(5, 10);

		for_level = 3.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "jetpack";
		break;
	case 2:
		ultCooldown = Random(30, 55);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		distance = float(Random(300, 1500));
		damage = float(Random(10, 30));
		ultimate = "explode radius " + std::to_string(distance) + " " + std::to_string(damage);
		break;
	case 3:
		ultCooldown = Random(20, 30);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		distance = float(Random(300, 800));
		duration = float(Random(10, 40));
		ultimate = "ultfreeze radius " + std::to_string(distance) + " " + std::to_string(duration);
		ultCooldown = Random(7, 12);
		break;
	case 4: 
		ultCooldown = Random(4, 12);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "CreateProp models/props/cs_office/vending_machine.mdl";
		ability = "del";
		break;
	case 5:
		ultCooldown = Random(15, 30);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		duration = float(Random(3, 8));
		ultimate = "ultgod " + std::to_string(duration);
		break;
	case 6:
		ultCooldown = Random(6, 12);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "webshot";
		break;
	case 7:
		ultCooldown = Random(20, 35);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		distance = Random(250, 500);
		duration = Random(10, 40);
		ultimate = "ultburn radius " + std::to_string(distance) + " " + std::to_string(duration);
		break;
	case 8: 
		ultCooldown = Random(15, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		speed = Random(9, 25);
		speed /= 10;
		duration = Random(1, 5);
		ultimate = "speedbuf " + std::to_string(speed) + " " + std::to_string(duration);
		break;
	case 9:
		ultCooldown = Random(40, 60);

		for_level = 1.5;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		hp = Random(150, 250);
		ultimate = "heal " + std::to_string(hp);
		break;
	case 10:
		ultCooldown = Random(15, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		distance = Random(250, 500);
		duration = Random(10, 40);
		ultimate = "ultblind radius " + std::to_string(distance) + " " + std::to_string(duration);
		break;
	case 11:
		ultCooldown = Random(20, 28);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "ultremove";
		break;
	case 12: 
		ultCooldown = Random(10, 15);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		distance = Random(30, 100);
		ultimate = "ultburyme " + std::to_string(distance);
		break;
	case 13:
		ultCooldown = Random(50, 70);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "fatality";
		break;
	case 14:
		ultCooldown = Random(40, 60);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "blink";
		break;
	case 15:
		ultCooldown = Random(40, 70);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "ultswap";
		break;
	case 16:
		ultCooldown = Random(40, 80);

		for_level = 1.5;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		freezeTime = Random(25, 100);
		freezeTime /= 100;
		duration = Random(50, 200);
		duration /= 100;
		ultimate = "ultmatrix " + std::to_string(freezeTime) + " " + std::to_string(duration);
		break;
	case 17:
		ultCooldown = Random(30, 55);

		for_level = 1.3;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, enemyPart.size()-1);
		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		duration2 = Random(15, 25);
		duration2 /= 10;
		radius = Random(100, 250);
		ultimate = "chaos " + enemyPart[type] + " " + std::to_string(damage) + " " + std::to_string(duration) + " " + std::to_string(duration2) + " " + std::to_string(radius);
		break;
	case 18:
		ultCooldown = Random(10, 25);

		for_level = 2.3;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "teleportator";
		break;
	case 19:
		ultCooldown = Random(10, 20);

		for_level = 1.3;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "portals";
		break;
	case 20:
		ultCooldown = Random(10, 20);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "leap";
		break;
	case 21:
		ultCooldown = Random(25, 40);

		for_level = 1.3;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		distance = Random(200, 1000);
		damage = Random(5, 20);
		ultimate = "ult_kamikaze " + std::to_string(distance) + " " + std::to_string(damage);
		break;
	case 22:
		ultCooldown = Random(30, 65);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		duration = Random(2, 5);
		ultimate = "ultgod_ally " + std::to_string(duration);
		break;
	case 23:
		ultCooldown = Random(15, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		duration = Random(2, 5);
		ultimate = "rapidfire " + std::to_string(duration);
		break;
	case 24:
		ultCooldown = Random(25, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		duration = Random(2, 7);
		ultimate = "ultnorecoil " + std::to_string(duration);
		break;
	case 25:
		ultCooldown = Random(40, 70);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, enemyPart.size()-1);
		duration = Random(1, 4);
		ultimate = "ultaim " + enemyPart[type] + " " + std::to_string(duration);
		break;
	case 26:
		ultCooldown = Random(50, 70);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		duration = Random(2, 5);
		ultimate = "ultwh " + std::to_string(duration);
		break;
	case 27:
		ultCooldown = Random(7, 22);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "ultrandweapon";
		break;
	case 28:
		ultCooldown = Random(25, 33);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "ultsilence " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 29:
		ultCooldown = Random(22, 33);

		for_level = 2.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		radius = Random(200, 500);
		damage = Random(10, 30);
		ultimate = "hook " + std::to_string(radius) + " " + std::to_string(damage);
		break;
	case 30:
		ultCooldown = Random(20, 35);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 800);
		duration = Random(2, 5);
		ultimate = "stun " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 31:
		ultCooldown = Random(35, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "disarm " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 32:
		ultCooldown = Random(20, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		damage = Random(80, 180);
		damage /= 100;
		change = Random(20, 60);
		duration = Random(4, 8);

		ultimate = "dmgbuf " + std::to_string(damage) + " " + std::to_string(duration);
		break;
	case 33:
		ultCooldown = Random(20, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		radius = Random(300, 1500);
		damage = Random(1, 4);
		amount = Random(2, 10);
		ultimate = "eclipse " + std::to_string(radius) + " " + std::to_string(damage) + " " + std::to_string(amount);
		break;
	case 34:
		ultCooldown = Random(25, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		radius = Random(200, 800);
		ultimate = "ultsteal " + std::to_string(radius);
		break;
	case 35:
		ultCooldown = Random(15, 20);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		amount = Random(500, 2000);
		hp = Random(10, 50);
		ultimate = "cashheal " + std::to_string(amount) + " " + std::to_string(hp);
		break;
	case 36:
		ultCooldown = Random(20, 28);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		duration = Random(2, 5);
		damage = Random(1, 4);
		speed = Random(80, 120);
		speed /= 100;
		radius = Random(200, 800);
		ultimate = "saw " + std::to_string(duration) + " " + std::to_string(damage) + " " + std::to_string(speed) + " " + std::to_string(radius);
		break;
	case 37:
		ultCooldown = Random(15, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "ultblind " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 38:
		ultCooldown = Random(35, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		amountF = Random(80, 220);
		amountF /= 100;
		change = Random(30, 80);
		duration = Random(5, 8);

		ultimate = "satanic " + std::to_string(amountF) + " " + std::to_string(change) + " " + std::to_string(duration);
		break;
	case 39:
		ultCooldown = Random(30, 35);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		amountF = Random(80, 220);
		amountF /= 100;
		change = Random(30, 80);
		duration = Random(5, 8);
		ultimate = "mirror_shield " + std::to_string(amountF) + " " + std::to_string(change) + " " + std::to_string(duration);
		break;
	case 40:
		ultCooldown = Random(25, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;


		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "diet " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 41:
		ultCooldown = Random(20, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		damage = Random(10, 40);
		amount = Random(10, 40);
		ultimate = "locust_swarm " + std::to_string(damage) + " " + std::to_string(amount);
		break;
	case 42:
		ultCooldown = Random(25, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		damage = Random(10, 40);
		amount = Random(10, 40);
		ultimate = "locust_swarm2 " + std::to_string(damage) + " " + std::to_string(amount);
		break;
	case 43:
		ultCooldown = Random(30, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		amount = Random(500, 3000);
		ultimate = "ultstealcash " + std::to_string(amount);
		break;;
	case 44:
		ultCooldown = Random(30, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		damage = Random(20, 40);
		change = Random(1, 20);
		radius = Random(300, 1200);
		
		ultimate = "ultchain " + std::to_string(damage) + " " + std::to_string(change) + " " + std::to_string(radius);
		break;
	case 45:
		ultCooldown = Random(30, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		damage = Random(5, 20);
		change = Random(1, 20);
		radius = Random(300, 1200);

		ultimate = "ultchain2 " + std::to_string(damage) + " " + std::to_string(change) + " " + std::to_string(radius);
		break;
	case 46:
		ultCooldown = Random(25, 35);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		height = Random(100, 300);
		ultimate = "ultstomp " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(height) + " " + std::to_string(duration);
		break;
	case 47:
		ultCooldown = Random(20, 28);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(2, 5);
		height = Random(100, 300);
		ultimate = "ultrecline " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(height) + " " + std::to_string(duration);
		break;
	case 48:
		ultCooldown = Random(20, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "telekinez "  + std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 49:
		ultCooldown = Random(20, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(300, 1500);
		duration = Random(5, 15);
		ultimate = "ultclearance " + typeUlt[type] + " " +  std::to_string(radius) + " " + std::to_string(duration);
		break;
	case 50:
		ultCooldown = Random(30, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, typeUlt.size()-1);
		radius = Random(200, 600);
		damage = Random(5, 13); // instant
		damage2 = Random(1, 10);
		damage2 /= 100;
		duration = Random(3, 8);
		ultimate = "rupture " + typeUlt[type] + " " + std::to_string(damage) + " " + std::to_string(damage2) + " " + std::to_string(duration);
		break;
	case 51:
		ultCooldown = Random(20, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, enemyPart.size()-1);
		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		duration2 = Random(15, 25);
		duration2 /= 10;
		radius = Random(100, 250);

		ultimate = "doom " + enemyPart[type] + " " + std::to_string(duration) + " " + std::to_string(damage) + " " + std::to_string(duration2) + " " + std::to_string(radius);
		break;
	case 52:
		ultCooldown = Random(30, 40);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		type = Random(0, enemyPart.size()-1);
		radius = Random(100, 250);
		ultimate = "ult_takeoff " + enemyPart[type] + " " + std::to_string(radius);
		break;
	case 53:
		ultCooldown = Random(15, 25);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		amount = Random(1, 3);
		radius = Random(150, 350);
		ultimate = "sphere " + std::to_string(duration) + " " + std::to_string(radius) + " " + std::to_string(amount);
		break;
	case 54:
		ultCooldown = Random(10, 30);

		for_level = 1.0;
		buffer = ultCooldown * (lvl * for_level / 100.0);
		if (buffer > ultCooldown)
			ultCooldown = 0;
		else
			ultCooldown -= buffer;

		ultimate = "freezetele";
		break;
	default:
		throw std::exception("Ultimate_Error");
	}

}
	
int main() {
	
	StringCchPrintf(version, MAX_PATH, TEXT(VERSION));
	StringCchPrintf(build_time, MAX_PATH, TEXT(__DATE__));
	StringCchPrintf(title, MAX_PATH, TEXT("GOR ver. %s | Build %s"), version, build_time);
	SetConsoleTitle(title);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Race New;

	return 0;
}


