#include "Race.h"

//backup https://pastebin.com/iZCF5mu2



Race::Race() {
	std::cout << "Write name and required lvl: ";
	std::getline(std::cin, name);
	std::cin >> requiredLvl;

	try {
		GiveUlt();
		GiveSkills();
		GiveParam();
		DefineCategory();
		#ifdef _DEBUG
		Debug();
		#else
		Output();
		#endif
	}
	catch (std::exception & e) {
		std::cout << "Caught exception number: #" << e.what() << std::endl;
		return;
	}
}

void Race::DefineCategory() {
	if (requiredLvl == 0)
		category = "Дивизион для новичков";
	else if (requiredLvl != 0 && requiredLvl < 2010)
		category = "Первый дивизион";
	else if (4020 > requiredLvl && requiredLvl > 2010)
		category = "Второй дивизион";
	else if (6000 > requiredLvl && requiredLvl > 4020)
		category = "Третий дивизион";
	else if (8020 > requiredLvl && requiredLvl > 6000)
		category = "Четвертый дивизион";
	else if (10030 > requiredLvl && requiredLvl > 8020)
		category = "Пятый дивизион";
	else if (12020 > requiredLvl && requiredLvl > 10030)
		category = "Шестой дивизион";
	else if (21020 > requiredLvl && requiredLvl > 12020)
		category = "Седьмой дивизион";
	else if (30100 > requiredLvl && requiredLvl > 21020)
		category = "Восьмой дивизион";
	else if (45000 > requiredLvl && requiredLvl > 30100)
		category = "Девятый дивизион";
	else if (60000 > requiredLvl && requiredLvl > 45000)
		category = "Десятый дивизион";
	else {
		category = "ERROR";
		throw std::exception("Category_Error");
	}
}

int Race::Random(int min, int max) {

    // construct a trivial random generator engine from a time-based seed:

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
		usedID.push_back(0);
	else 
		amountSkills = Random(3, 9);
    bool similar = false;
    while(usedID.size() != amountSkills) {
        unsigned int id = Random(0, skillNames.size()); //Возможны ошибки, изменил: skillNames.size()-1
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
    float duration, distance, damage, additionalDamage, common, additionalCommon, minDamage, maxDamage, multiplier, multiplier2, radius, delay;
    int hp, change, change2, additionalChange, amount, additionalAmount, maxAmount;
	std::string angle, accuracySkill;
	std::vector<std::string> antiSkills = { "antiult", "antiult_ally", "antiaura" , "antiaura_ally" , "antitotem" , "antitotem_ally" , "antilasermine" , "antilasermine_ally" , "antifall" , "antiflash" , "antiflash2" , "antiparalyze" , "antifreeze" , "antibury" , "antifear" , "antipoison" , "antidrug" , "antibeacon" , "antitimebomb" , "antishake" , "antipush" , "antisetangle", "antirockets" , "antihead" , "antiwh" , "antiaim" , "antimirror" , "antipassive" },
		defSkills = { "def_boom", "def_burn", "def_head", "def_knife", "def_bullet", "def_back" },
		protectSkills = { "protectfreeze", "protectburn", "protectslow"};

    for (unsigned i = 0; i < usedID.size(); i++) {
		switch (usedID[i]) {
		case 0:
			common = float(Random(80, 200));
			common /= 100;
			additionalCommon = float(Random(20, 45));
			additionalCommon /= 100;

			skillDesc.push_back("Скорость");
			skills.push_back("speed =");
			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common + additionalCommon) + ";" + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(common + additionalCommon * 3));
			break;
		case 1:
			skillDesc.push_back("Гравитация");
			skills.push_back("gravity =");
			common = Random(75, 100);
			common /= 100;
			additionalCommon = Random(80, 130);
			additionalCommon /= 1000;


			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common - additionalCommon) + ";" + std::to_string(common - additionalCommon * 2) + ";" + std::to_string(common - additionalCommon * 3));
			break;
		case 2:
			skillDesc.push_back("Здоровье");
			skills.push_back("hp =");
			common = Random(80, 150);
			additionalCommon = Random(3, 33);


			skillParam.push_back(std::to_string(int(common)) + ";" + std::to_string(int(common + additionalCommon)) + ";" + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 3:
			skillDesc.push_back("Невидимость");
			skills.push_back("invis");
			common = Random(5, 50);
			additionalCommon = Random(5, 13);


			skillParam.push_back(std::to_string(int(common)) + " all" + ";" + std::to_string(int(common + additionalCommon)) + " all" + ";" + std::to_string(int(common + additionalCommon * 2)) + " all" + ";" + std::to_string(int(common + additionalCommon * 3)) + " all");
			break;
		case 4:
			skillDesc.push_back("Урон");
			skills.push_back("dmg =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 5:
			skillDesc.push_back("Заморозка");
			skills.push_back("freeze =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 6:
			skillDesc.push_back("Поджег");
			skills.push_back("burn =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 7:
			skillDesc.push_back("Вампирка");
			skills.push_back("vampire =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 70);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 8:
			skillDesc.push_back("Взрыв после смерти");
			skills.push_back("boom");
			common = Random(3, 10);
			additionalCommon = Random(1, 5);
			distance = Random(100, 400);


			skillParam.push_back(std::to_string(distance) + " " + std::to_string(common) + ";" + std::to_string(distance) + " " + std::to_string(common + additionalCommon) + ";" + std::to_string(distance) + " " + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(distance) + " " + std::to_string(common + additionalCommon * 3));
			break;
		case 9:
			skillDesc.push_back("Регенерация");
			skills.push_back("regen");
			duration = Random(1, 5);
			hp = Random(1, 5);


			skillParam.push_back(std::to_string(duration + duration) + " " + std::to_string(hp) + ";" + std::to_string(duration + duration) + " " + std::to_string(hp) + ";" + std::to_string(duration) + " " + std::to_string(hp) + ";" + std::to_string(duration) + " " + std::to_string(hp));
			break;
		case 10:
			skillDesc.push_back("Замедление");
			skills.push_back("slow =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 11:
			skillDesc.push_back("Ракеты");
			skills.push_back("rockets =");
			amount = Random(1, 5);
			minDamage = Random(10, 100);
			maxDamage = Random(70, 150);


			skillParam.push_back(std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage));
			break;
		case 12:
			skillDesc.push_back("Длинный прыжок");
			skills.push_back("longjump =");
			common = Random(80, 150);
			additionalCommon = Random(30, 50);


			skillParam.push_back(std::to_string(float(common)) + ";" + std::to_string(float(common + additionalCommon)) + ";" + std::to_string(float(common + additionalCommon * 2)) + ";" + std::to_string(float(common + additionalCommon * 3)));
			break;
		case 13:
			skillDesc.push_back("Зеркало");
			skills.push_back("mirror =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 14:
			skillDesc.push_back("Уклон");
			skills.push_back("evasion =");
			change = Random(1, 44);
			additionalCommon = Random(5, 8);


			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(change + additionalCommon)) + ";" + std::to_string(int(change + additionalCommon * 2)) + ";" + std::to_string(int(change + additionalCommon * 3)));
		case 15:
			skillDesc.push_back("Высота шага");
			skills.push_back("step");
			common = Random(15, 100);
			additionalCommon = Random(3, 7);


			skillParam.push_back(std::to_string(int(common)) + ";" + std::to_string(int(common + additionalCommon)) + ";" + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 16:
			skillDesc.push_back("Подброс противника");
			skills.push_back("push =");
			common = Random(60, 130);
			additionalCommon = Random(3, 33);
			change = Random(1, 99);


			skillParam.push_back(std::to_string(int(common)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 2)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 3)) + " " + std::to_string(change));
			break;
		case 17:
			skillDesc.push_back("Перевозрождение");
			skills.push_back("respawn");
			common = Random(0, 2);
			additionalCommon = Random(1, 2);
			change = Random(1, 99);


			skillParam.push_back(std::to_string(int(common)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 2)) + " " + std::to_string(change) + ";" + std::to_string(int(common + additionalCommon * 3)) + " " + std::to_string(change));
			break;
		case 18:
			skillDesc.push_back("Выброс оружия");
			skills.push_back("dropweapon");
			change = Random(1, 99);


			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change) + ";" + std::to_string(change) + ";" + std::to_string(change));
			break;
		case 19:
			skillDesc.push_back("Паралич");
			skills.push_back("paralyze =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 20:
			skillDesc.push_back("Ослепление");
			skills.push_back("blind =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 21:
			skillDesc.push_back("Яд");
			skills.push_back("poison =");
			duration = Random(1, 3);
			common = Random(1, 3);
			maxDamage = Random(1, 8);
			change = Random(1, 99);


			skillParam.push_back(std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change - change) + ";" + std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change - change) + ";" + std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(common) + " " + std::to_string(maxDamage) + " " + std::to_string(change));
			break;
		case 22:
			skillDesc.push_back("Иллюзии");
			skills.push_back("illusion");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 23:
			skillDesc.push_back("Закоп");
			skills.push_back("bury");
			duration = Random(1, 4);
			distance = Random(70, 100);
			change = Random(1, 99);


			skillParam.push_back(std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(distance) + " " + std::to_string(change));
			break;
		case 24:
			skillDesc.push_back("Ружье-гранатомет");
			skills.push_back("grenlauncher =");
			amount = Random(0, 2);
			damage = Random(10, 100);
			additionalDamage = Random(10, 20);
			additionalAmount = Random(1, 2);
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(int(damage)) + ";" + std::to_string(amount + additionalAmount) + " " + std::to_string(int(damage+additionalDamage)) + ";" + std::to_string(amount + additionalAmount *2) + " " + std::to_string(int(damage + additionalDamage*2)) + ";" + std::to_string(amount + additionalAmount * 3) + " " + std::to_string(int(damage + additionalDamage * 3)));
			break;
		case 25:
			skillDesc.push_back("Усиление гранаты");
			skills.push_back("imbagrenade =");
			amount = Random(1, 2);
			additionalAmount = Random(0, 1);
			multiplier = Random(80, 180);
			multiplier /= 100;
			radius = Random(80, 210); //radius multiplier
			radius /= 100;
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(multiplier) + " " + std::to_string(radius) + ";" + std::to_string(amount+additionalAmount) + " " + std::to_string(multiplier) + " " + std::to_string(radius) + ";" + std::to_string(amount+additionalAmount*2) + " " + std::to_string(multiplier) + " " + std::to_string(radius) + ";" + std::to_string(amount+additionalAmount*3) + " " + std::to_string(multiplier) + " " + std::to_string(radius));
			break;
		case 26:
			skillDesc.push_back("Длинный прыжок 2");
			skills.push_back("longjump2 =");
			common = Random(80, 150);
			additionalCommon = Random(30, 50);
			delay = Random(3, 8);

			skillParam.push_back(std::to_string(float(common)) + " " + std::to_string(delay) +";" + std::to_string(float(common + additionalCommon)) + " " + std::to_string(delay) + ";" + std::to_string(float(common + additionalCommon * 2)) + " " + std::to_string(delay) + ";" + std::to_string(float(common + additionalCommon * 3)) + " " + std::to_string(delay));
			break;
		case 27:
			skillDesc.push_back("Двойной прыжок");
			skills.push_back("doublejumps =");
			common = Random(0, 3);
			additionalCommon = Random(0, 2);

			skillParam.push_back(std::to_string(int(common)) + ";" + std::to_string(int(common + additionalCommon)) + ";" + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 28:
			skillDesc.push_back("Динамическая невидимость");
			skills.push_back("glow");
			delay = Random(80, 200);
			delay /= 100;
			common = Random(5, 50);
			additionalCommon = Random(5, 13);


			skillParam.push_back(std::to_string(delay) + " " + std::to_string(int(common)) + ";" + std::to_string(delay) + " " + std::to_string(int(common + additionalCommon)) +  ";" + std::to_string(delay) + " " + std::to_string(int(common + additionalCommon * 2)) + ";" + std::to_string(delay) + " " + std::to_string(int(common + additionalCommon * 3)));
			break;
		case 29:
			skillDesc.push_back("Хамелеон");
			skills.push_back("chameleon");
			change = Random(10, 50);
			additionalChange = Random(5, 10);
			skillParam.push_back(std::to_string(int(change)) + ";" + std::to_string(int(change + additionalChange)) + ";" + std::to_string(int(change + additionalChange * 2)) + ";" + std::to_string(int(change + additionalChange * 3)));
			break;
		case 30:
			skillDesc.push_back("Скорость атаки");
			skills.push_back("attackspeed =");
			common = Random(70, 140);
			common /= 100;
			additionalCommon = Random(5, 15);
			additionalCommon /= 100;
			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common + additionalCommon) + ";" + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(common + additionalCommon * 3));
			break;
		case 31:
			skillDesc.push_back("Скорость перезарядки");
			skills.push_back("quickreload =");
			common = Random(70, 140);
			common /= 100;
			additionalCommon = Random(5, 15);
			additionalCommon /= 100;

			skillParam.push_back(std::to_string(common) + ";" + std::to_string(common + additionalCommon) + ";" + std::to_string(common + additionalCommon * 2) + ";" + std::to_string(common + additionalCommon * 3));
			break;
		case 32:
			skillDesc.push_back("Метательные ножи");
			skills.push_back("tknives =");
			amount = Random(1, 5);
			additionalAmount = Random(1, 2);
			minDamage = Random(10, 50);
			maxDamage = Random(60, 110);
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
			skillDesc.push_back("Стоячая невидимость");
			skills.push_back("obscurity");
			delay = Random(1, 5);
			amount = Random(2, 10);
			additionalAmount = Random(1, 3);
			maxAmount = Random(70, 99);
			skillParam.push_back(std::to_string(delay) + " " + std::to_string(amount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(amount+additionalAmount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(amount + additionalAmount*2) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(amount + additionalAmount*3) + " " + std::to_string(maxAmount));
			break;
		case 36:
			skillDesc.push_back("Сидячая невидимость");
			skills.push_back("obscurity_duck");
			delay = Random(1, 5);
			amount = Random(2, 10);
			additionalAmount = Random(1, 3);
			maxAmount = Random(70, 99);
			skillParam.push_back(std::to_string(delay) + " " + std::to_string(amount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(amount + additionalAmount) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(amount + additionalAmount * 2) + " " + std::to_string(maxAmount) + ";" + std::to_string(delay) + " " + std::to_string(amount + additionalAmount * 3) + " " + std::to_string(maxAmount));
			break;
		case 37:
			skillDesc.push_back("Зов крови");
			skills.push_back("thirst");
			multiplier = Random(15, 48); // Damage
			multiplier /= 1000;
			multiplier2 = Random(15, 48); // Speed
			multiplier2 /= 1000;
			amount = Random(5, 15); // HP
			skillParam.push_back(std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount+Random(1,2)) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount+Random(2,4)) + ";" + std::to_string(multiplier) + " " + std::to_string(multiplier2) + " " + std::to_string(amount+Random(4,6)));
			break;
		case 38:
			skillDesc.push_back("Splash Damage");
			skills.push_back("splashdmg =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);
			radius = Random(150, 400);

			skillParam.push_back(std::to_string(common) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon)  + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(radius) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(radius) + " " + std::to_string(change));
			break;
		case 39:
			skillDesc.push_back("Пошатывание");
			skills.push_back("shaker =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 40:
			skillDesc.push_back("Притягивание противника");
			skills.push_back("losso =");
			common = Random(200, 400);
			change = Random(10, 30);
			additionalChange = Random(5, 8);
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common) + " " + std::to_string(change+additionalChange) + ";" + std::to_string(common) + " " + std::to_string(change+additionalChange*2) + ";" + std::to_string(common) + " " + std::to_string(change+additionalChange*3));
			break;
		case 41:
			skillDesc.push_back("Отталкивание противника");
			skills.push_back("repel =");
			common = Random(200, 400);
			change = Random(10, 30);
			additionalChange = Random(5, 8);
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(common) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 42:
			skillDesc.push_back("Воровство всех патрон при атаке");
			skills.push_back("clip_destroy");
			change = Random(2, 5);
			additionalChange = Random(1, 2);
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change + additionalChange) + ";" + std::to_string(change + additionalChange * 2) + ";" + std::to_string(change + additionalChange * 3));
			break;
		case 43:
			skillDesc.push_back("Воровство патрон при атаке");
			skills.push_back("clip_take");
			amount = Random(5, 10);
			change = Random(2, 5);
			additionalChange = Random(1, 2);
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 44:
			skillDesc.push_back("Пополнение обоймы");
			skills.push_back("clip_shot");
			amount = Random(2, 8);
			change = Random(2, 5);
			additionalChange = Random(1, 2);
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 45:
			skillDesc.push_back("Украсть оружие");
			skills.push_back("takeweapon");
			unsigned type;
			type = Random(0, 1);
			change = Random(2, 5);
			additionalChange = Random(1, 2);
			skillParam.push_back(std::to_string(type) + " " + std::to_string(change) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(type) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 46:
			skillDesc.push_back("Страх");
			skills.push_back("fear =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);


			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 47:
			skillDesc.push_back("Убийство танков");
			skills.push_back("dmghealth =");
			change = Random(5, 30); // change of damage
			change2 = Random(10, 50);
			additionalChange = Random(2, 5); // additional for change
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change+additionalChange) + " " + std::to_string(change2+Random(1,2)) + ";" + std::to_string(change+additionalChange*2) + " " + std::to_string(change2+Random(2,3)) + ";" + std::to_string(change+additionalChange*3) + " " + std::to_string(change2+Random(3,4)));
			break;
		case 48:
			skillDesc.push_back("Адреналин при попадании");
			skills.push_back("adrenaline_rush =");
			duration = Random(1, 4);
			change = Random(10, 30);
			common = Random(80, 150);
			common /= 100;
			additionalChange = Random(3, 8);
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange*2) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange*3) + " " + std::to_string(common));
			break;
		case 49:
			skillDesc.push_back("Clearance");
			skills.push_back("clearance =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 50:
			skillDesc.push_back("Silence");
			skills.push_back("silence =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 51:
			skillDesc.push_back("Заблокировать респавн");
			skills.push_back("blockrespawn =");
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 52:
			skillDesc.push_back("Увеличение радиуса ножа");
			skills.push_back("longknife");
			radius = Random(100, 200);
			additionalCommon = Random(30, 70);
			skillParam.push_back(std::to_string(radius) + ";" + std::to_string(radius+additionalCommon) + ";" + std::to_string(radius + additionalCommon*2) + ";" + std::to_string(radius + additionalCommon*3));
			break;
		case 53:
			duration = Random(80, 210);
			duration /= 100;

			float x, y, z;
			x = Random(0, 360);
			y = Random(0, 360);
			z = Random(0, 360);

			angle = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);

			change = Random(5, 10);
			additionalChange = Random(2, 4);

			skillParam.push_back(std::to_string(duration) + " " + angle + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(change+additionalChange) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(change+additionalChange*2) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(change+additionalChange*3));
			skillDesc.push_back("Развернуть противника при атаке");
			skills.push_back("setangle");
			break;
		case 54:
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillDesc.push_back("Применить запрещенные вещества на противнике");
			skills.push_back("drug =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 55:
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillDesc.push_back("Beacon");
			skills.push_back("beacon =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 56:
			change = Random(1, 2);
			additionalChange = Random(0, 1);

			skillDesc.push_back("Временная бомба");
			skills.push_back("timebomb =");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change+additionalChange) + ";" + std::to_string(change + additionalChange*2) + ";" + std::to_string(change + additionalChange*3));
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
			amount = Random(5, 20);
			change = Random(10, 30);


			skillDesc.push_back("Забрать здоровье после смерти");
			skills.push_back("killhp");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount+Random(1,3)) + " " + std::to_string(change) + ";" + std::to_string(amount+ Random(3,4)) + " " + std::to_string(change) + ";" + std::to_string(amount+Random(4,5)) + " " + std::to_string(change));
			break;
		case 59:
			change = Random(10, 25);
			additionalChange = Random(5, 15);

			skillDesc.push_back("Забрать невидимость после смерти");
			skills.push_back("kill_invis");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change+additionalChange) + ";" + std::to_string(change+additionalChange*2) + ";" + std::to_string(change+additionalChange*3));
			break;
		case 60:
			duration = Random(1, 3);
			change = Random(10, 50);
			additionalChange = Random(3, 9);

			skillDesc.push_back("Сокращение отката ульты при убийстве");
			skills.push_back("arcanum =");
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange*2) + ";" + std::to_string(duration) + " " + std::to_string(change+additionalChange*3));
			break;
		case 61:
			change = Random(10, 50); // damage
			change2 = Random(10, 30); // general
			additionalChange = Random(5, 8); // for general

			skillDesc.push_back("Снижение урона");
			skills.push_back("armor %");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change + additionalChange) + " " + std::to_string(change2 + Random(1, 2)) + ";" + std::to_string(change + additionalChange * 2) + " " + std::to_string(change2 + Random(2, 3)) + ";" + std::to_string(change + additionalChange * 3) + " " + std::to_string(change2 + Random(3, 4)));
			break;
		case 62:
			skillDesc.push_back("Адреналин");
			skills.push_back("adrenaline =");
			duration = Random(1, 4);
			change = Random(10, 30);
			common = Random(80, 150);
			common /= 100;
			additionalChange = Random(3, 8);
			skillParam.push_back(std::to_string(duration) + " " + std::to_string(change) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 2) + " " + std::to_string(common) + ";" + std::to_string(duration) + " " + std::to_string(change + additionalChange * 3) + " " + std::to_string(common));
			break;
		case 63:
			duration = Random(80, 210);
			duration /= 100;

			x = Random(0, 360);
			y = Random(0, 360);
			z = Random(0, 360);

			angle = std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);

			change = Random(5, 10);
			additionalChange = Random(2, 4);

			skillParam.push_back(std::to_string(duration) + " " + angle + " " + std::to_string(change) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(change + additionalChange) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(duration) + " " + angle + " " + std::to_string(change + additionalChange * 3));
			skillDesc.push_back("Развернуть противника при попадании по Вам");
			skills.push_back("mirror_setangle");
			break;
		case 64:
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			skillDesc.push_back("Воровство всех патрон при попадании по Вам");
			skills.push_back("mirror_clip_destroy");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change + additionalChange) + ";" + std::to_string(change + additionalChange * 2) + ";" + std::to_string(change + additionalChange * 3));
			break;
		case 65:
			amount = Random(5, 10);
			change = Random(2, 5);
			additionalChange = Random(1, 2);

			skillDesc.push_back("Воровство патрон при попадании по Вам");
			skills.push_back("mirror_clip_take");
			skillParam.push_back(std::to_string(amount) + " " + std::to_string(change) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 2) + ";" + std::to_string(amount) + " " + std::to_string(change + additionalChange * 3));
			break;
		case 66:
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillDesc.push_back("Ослепление при попадании по Вам");
			skills.push_back("mirror_blind =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 67:
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillDesc.push_back("Поджег при попадании по Вам");
			skills.push_back("mirror_burn =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 68:
			common = Random(80, 150);
			common /= 100;
			additionalCommon = Random(10, 80);
			additionalCommon /= 100;
			change = Random(1, 80);

			skillDesc.push_back("Пошатывание при попадании по Вам");
			skills.push_back("mirror_shaker =");
			skillParam.push_back(std::to_string(common) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 2) + " " + std::to_string(change) + ";" + std::to_string(common + additionalCommon * 3) + " " + std::to_string(change));
			break;
		case 69:
			change = Random(0, antiSkills.size());
			skillDesc.push_back("Игнорирование " + antiSkills[change]);
			skills.push_back(antiSkills[change]);
			skillParam.push_back("none");
			break;
		case 70:
			type = Random(0, antiSkills.size());
			skillDesc.push_back("Игнорирование " + antiSkills[type]);
			skills.push_back(antiSkills[type]);
			skillParam.push_back("none");
			break;
		case 71:
			type = Random(0, defSkills.size());
			change = Random(10, 30); // of skill
			additionalChange = Random(5, 8);
			change2 = Random(20, 50); // general

			skillDesc.push_back("Снижение урона от " + defSkills[type]);
			skills.push_back(defSkills[type] + " =");
			skillParam.push_back(std::to_string(change) + " " + std::to_string(change2) + ";" + std::to_string(change + additionalChange) + " " + std::to_string(change2 + Random(1, 2)) + ";" + std::to_string(change + additionalChange * 2) + " " + std::to_string(change2 + Random(2, 3)) + ";" + std::to_string(change + additionalChange * 3) + " " + std::to_string(change2 + Random(3, 4)));
			break;
		case 72:
			type = Random(0, protectSkills.size()); 
			change = Random(5, 20);
			additionalChange = Random(3, 8);

			skillDesc.push_back("Снижение шанса " + protectSkills[type]);
			skills.push_back(protectSkills[type] + " =");
			skillParam.push_back(std::to_string(change) + ";" + std::to_string(change + additionalChange) + ";" + std::to_string(change + additionalChange * 2) + ";" + std::to_string(change + additionalChange * 3));
			break;
		default:
			throw std::exception("Skill_Error");
		}
    }
}

void Race::Output() {
	std::ofstream file("C://Users/dredd/Desktop/Races.txt", std::ios::app);
	if (!file)
		exit(1);
	file << "\n\"" + name + "\"\n{";
	file << "\n\t\"required\"\t\"" + std::to_string(requiredLvl) + "\"";
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
	file << "\n}";
}

void Race::Debug() {
	std::cout << "\n\"" + name + "\"\n{";
	std::cout << "\n\t\"required\"\t\"" + std::to_string(requiredLvl) + "\"";
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
	std::cout << "\n}";
}

void Race::GiveUlt() {
	float distance, damage, damage2, duration, duration2, speed, freezeTime, radius, amountF, height;
	int hp, idUlt = Random(0, ultimates.size()), type, change, amount;
	ultCooldown;
	switch (idUlt) {
	case 0:
		ultimate = "teleport";
		ultCooldown = Random(0, 5);
		break;
	case 1:
		ultimate = "jetpack";
		ultCooldown = Random(0, 5);
		break;
	case 2:
		distance = Random(300, 1500);
		damage = Random(10, 30);
		ultimate = "explode radius " + std::to_string(distance) + " " + std::to_string(damage);
		ultCooldown = Random(15, 20);
		break;
	case 3:
		distance = Random(300, 800);
		duration = Random(10, 40);
		ultimate = "ultfreeze radius " + std::to_string(distance) + " " + std::to_string(duration);
		ultCooldown = Random(7, 12);
		break;
	case 4: 
		ultimate = "CreateProp models/props/cs_office/vending_machine.mdl";
		ultCooldown = Random(0, 2);
		break;
	case 5:
		duration = Random(3, 8);
		ultimate = "ultgod " + std::to_string(duration);
		ultCooldown = int(duration)*2;
		break;
	case 6:
		ultimate = "webshot";
		ultCooldown = Random(0, 2);
		break;
	case 7:
		distance = Random(250, 500);
		duration = Random(10, 40);
		ultimate = "ultburn radius " + std::to_string(distance) + " " + std::to_string(duration);
		ultCooldown = Random(7, 12);
		break;
	case 8: 
		speed = Random(9, 25);
		speed /= 10;
		duration = Random(1, 5);
		ultimate = "speedbuf" + std::to_string(speed) + " " + std::to_string(duration);
		ultCooldown = Random(7, 15);
		break;
	case 9:
		hp = Random(150, 250);
		ultimate = "heal " + std::to_string(hp);
		ultCooldown = Random(14, 25);
		break;
	case 10:
		distance = Random(250, 500);
		duration = Random(10, 40);
		ultimate = "ultblind radius " + std::to_string(distance) + " " + std::to_string(duration);
		ultCooldown = Random(8, 13);
		break;
	case 11:
		ultimate = "ultremove";
		ultCooldown = Random(15, 20);
		break;
	case 12: 
		distance = Random(30, 100);
		ultimate = "ultburyme " + std::to_string(distance);
		ultCooldown = Random(0, 3);
		break;
	case 13:
		ultimate = "fatality";
		ultCooldown = Random(30, 50);
		break;
	case 14:
		ultimate = "blink";
		ultCooldown = Random(30, 50);
		break;
	case 15:
		ultimate = "ultswap";
		ultCooldown = Random(30, 50);
		break;
	case 16:
		freezeTime = Random(25, 100);
		freezeTime /= 100;
		duration = Random(50, 200);
		duration /= 100;
		ultimate = "ultmatrix " + std::to_string(freezeTime) + " " + std::to_string(duration);
		ultCooldown = Random(20, 50);
		break;
	case 17:
		damage = Random(5, 15);
		duration = Random(15, 25);
		duration /= 10;
		duration2 = Random(15, 25);
		duration2 /= 10;
		radius = Random(100, 250);
		ultimate = "chaos " + std::to_string(damage) + " " + std::to_string(duration) + " " + std::to_string(duration2) + " " + std::to_string(radius);
		ultCooldown = Random(10, 15);
		break;
	case 18:
		ultimate = "teleportator";
		ultCooldown = Random(1, 4);
		break;
	case 19:
		ultimate = "portals";
		ultCooldown = Random(0, 3);
		break;
	case 20:
		ultimate = "leap";
		ultCooldown = Random(2, 5);
		break;
	case 21:
		distance = Random(200, 1000);
		damage = Random(5, 20);
		ultimate = "ult_kamikaze " + std::to_string(distance) + " " + std::to_string(damage);
		ultCooldown = Random(15, 20);
		break;
	case 22:
		duration = Random(2, 5);
		ultimate = "ultgod_ally " + std::to_string(duration);
		ultCooldown = Random(20, 25);
		break;
	case 23:
		duration = Random(2, 5);
		ultimate = "rapidfire " + std::to_string(duration);
		ultCooldown = Random(10, 15);
		break;
	case 24:
		duration = Random(1, 4);
		ultimate = "ultnorecoil " + std::to_string(duration);
		ultCooldown = Random(15, 18);
		break;
	case 25:
		type = Random(0, enemyPart.size());
		duration = Random(1, 4);
		ultimate = "ultaim " + enemyPart[type] + " " + std::to_string(duration);
		ultCooldown = Random(15, 18);
		break;
	case 26:
		duration = Random(2, 5);
		ultimate = "ultwh " + std::to_string(duration);
		ultCooldown = Random(15, 18);
		break;
	case 27:
		ultimate = "ultrandweapon";
		ultCooldown = Random(1, 4);
		break;
	case 28:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "ultsilence " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 29:
		radius = Random(200, 500);
		damage = Random(10, 30);
		ultimate = "hook " + std::to_string(radius) + " " + std::to_string(damage);
		ultCooldown = Random(15, 18);
		break;
	case 30:
		type = Random(0, typeUlt.size());
		radius = Random(300, 800);
		duration = Random(2, 5);
		ultimate = "stun " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(10, 15);
		break;
	case 31:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "disarm " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 32:
		damage = Random(80, 180);
		damage /= 100;
		change = Random(20, 60);
		duration = Random(4, 8);

		ultimate = "dmgbuf " + std::to_string(damage) + " " + std::to_string(duration);
		ultCooldown = Random(10, 15);
		break;
	case 33:
		radius = Random(300, 1500);
		damage = Random(1, 4);
		amount = Random(2, 10);
		ultimate = "eclipse " + std::to_string(radius) + " " + std::to_string(damage) + " " + std::to_string(amount);
		ultCooldown = Random(15, 20);
		break;
	case 34:
		radius = Random(200, 800);
		ultimate = "ultsteal " + std::to_string(radius);
		ultCooldown = Random(20, 25);
		break;
	case 35:
		amount = Random(500, 2000);
		hp = Random(10, 50);
		ultimate = "cashheal " + std::to_string(amount) + " " + std::to_string(hp);
		ultCooldown = Random(1, 20);
		break;
	case 36:
		duration = Random(2, 5);
		damage = Random(1, 4);
		speed = Random(80, 120);
		speed /= 100;
		radius = Random(200, 800);
		ultimate = "saw " + std::to_string(duration) + " " + std::to_string(damage) + " " + std::to_string(speed) + " " + std::to_string(radius);
		ultCooldown = Random(10, 20);
		break;
	case 37:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "ultblind " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 38:
		amountF = Random(80, 220);
		amountF /= 100;
		change = Random(30, 80);
		duration = Random(5, 8);

		ultimate = "satanic " + std::to_string(amountF) + " " + std::to_string(change) + " " + std::to_string(duration);
		ultCooldown = Random(20, 30);
		break;
	case 39:
		amountF = Random(80, 220);
		amountF /= 100;
		change = Random(30, 80);
		duration = Random(5, 8);

		ultimate = "mirror_shield " + std::to_string(amountF) + " " + std::to_string(change) + " " + std::to_string(duration);
		ultCooldown = Random(20, 30);
		break;
	case 40:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "diet " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 41:
		damage = Random(10, 40);
		amount = Random(10, 40);
		ultimate = "locust_swarm " + std::to_string(damage) + " " + std::to_string(amount);
		ultCooldown = Random(15, 20);
		break;
	case 42:
		damage = Random(10, 40);
		amount = Random(10, 40);
		ultimate = "locust_swarm2 " + std::to_string(damage) + " " + std::to_string(amount);
		ultCooldown = Random(20, 25);
		break;
	case 43:
		amount = Random(500, 3000);
		ultimate = "ultstealcash " + std::to_string(amount);
		ultCooldown = Random(20, 30);
		break;;
	case 44:
		damage = Random(20, 40);
		change = Random(1, 20);
		radius = Random(300, 1200);
		
		ultimate = "ultchain " + std::to_string(damage) + " " + std::to_string(change) + " " + std::to_string(radius);
		ultCooldown = Random(20, 30);
		break;
	case 45:
		damage = Random(5, 20);
		change = Random(1, 20);
		radius = Random(300, 1200);

		ultimate = "ultchain2 " + std::to_string(damage) + " " + std::to_string(change) + " " + std::to_string(radius);
		ultCooldown = Random(20, 30);
		break;
	case 46:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(2, 5);
		height = Random(100, 300);
		ultimate = "ultstomp " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(height) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 47:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(2, 5);
		height = Random(100, 300);
		ultimate = "ultrecline " + typeUlt[type] + " " + std::to_string(radius) + " " + std::to_string(height) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 48:
		radius = Random(300, 1500);
		duration = Random(2, 5);
		ultimate = "telekinez "  + std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 49:
		type = Random(0, typeUlt.size());
		radius = Random(300, 1500);
		duration = Random(5, 15);
		ultimate = "ultclearance " + typeUlt[type] + " " +  std::to_string(radius) + " " + std::to_string(duration);
		ultCooldown = Random(15, 20);
		break;
	case 50:
		type = Random(0, typeUlt.size());
		radius = Random(200, 600);
		damage = Random(5, 13); // instant
		damage2 = Random(1, 10);
		damage2 /= 100;
		duration = Random(3, 8);
		ultimate = "rupture " + typeUlt[type] + " " + std::to_string(damage) + " " + std::to_string(damage2) + " " + std::to_string(duration);
		ultCooldown = Random(10, 25);
		break;
	default:
		throw std::exception("Ultimate_Error");
	}
	

}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Race New;



	return 0;
}


