#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <set>
#include <Windows.h>
#include <fstream>



class Race {
public:
	std::string name,category;
	int amountskill = 0, maxLvl, required;
	std::vector <int> skillID;
	std::vector <std::string> params, skillnames, skills;

	std::vector<std::string> availableskills = { "speed", "gravity", "hp", "invis", "dmg", "freeze", "burn", "vampire", "boom", "regen", "slow", "rockets", "longjump", "mirror", "evasion", "step", "push",
"respawn", "dropweapon", "paralyze", "blind", "poison", "illusion", "bury" }; 

	Race() {
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		printf("Write name and required lvl: ");
		std::cin >> name >> required;
		//Временное решение
		category = "none";
		maxLvl = 500;
	}

	int Random(int min, int max) {
		if (min > max) {
			printf("[DEBUG]\nmin = %i, max = %i", min, max);
		}
		std::random_device rd;  //Will be used to obtain a seed for the random number engine
		std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
		std::uniform_int_distribution<> dis(min, max);

		return dis(gen);
	}

	void GenerationSkill() {
		amountskill = Random(3, 10);
		float startValue;
		float distance;
		int amount;
		float minDamage;
		float maxDamage;
		int hp;
		float time;
		float additionalValue;
		int change;

		printf("[DEBUG]\n");
		while (amountskill != skillID.size()) {
			
			int buffer = Random(0, availableskills.size()-1);

			skillID.push_back(buffer);

			printf("skillID = %i\n", buffer);

			switch (buffer) {
				case 0:
					skillnames.push_back("Скорость");
					skills.push_back("speed =");
					startValue = Random(80, 250);
					startValue /= 100;
					additionalValue = Random(20, 50);
					additionalValue /= 100;
					
					
					params.push_back(std::to_string(startValue) + ";" + std::to_string(startValue+additionalValue) + ";" + std::to_string(startValue+additionalValue*2) + ";" + std::to_string(startValue + additionalValue * 3));
					break;
				case 1: 
					skillnames.push_back("Гравитация");
					skills.push_back("gravity =");
					startValue = Random(75, 100);
					startValue /= 100;
					additionalValue = Random(800, 1300);
					additionalValue /= 1000;
					
					
					params.push_back(std::to_string(startValue) + ";" + std::to_string(startValue - additionalValue) + ";" + std::to_string(startValue - additionalValue * 2) + ";" + std::to_string(startValue - additionalValue * 3));
					break;
				case 2: 
					skillnames.push_back("Здоровье");
					skills.push_back("hp =");
					startValue = Random(80, 150);
					additionalValue = Random(3, 33);
					
					
					params.push_back(std::to_string(int(startValue)) + ";" + std::to_string(int(startValue + additionalValue)) + ";" + std::to_string(int(startValue + additionalValue * 2)) + ";" + std::to_string(int(startValue + additionalValue * 3)));
					break;
				case 3: 
					skillnames.push_back("Невидимость");
					skills.push_back("invis");
					startValue = Random(5, 50);
					additionalValue = Random(5, 13);
					
					
					params.push_back(std::to_string(int(startValue)) + ";" + std::to_string(int(startValue + additionalValue)) + ";" + std::to_string(int(startValue + additionalValue * 2)) + ";" + std::to_string(int(startValue + additionalValue * 3)));
					break;
				case 4: 
					skillnames.push_back("Урон");
					skills.push_back("dmg =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 5:
					skillnames.push_back("Заморозка");
					skills.push_back("freeze =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					

					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 6:
					skillnames.push_back("Поджег");
					skills.push_back("burn =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 7: 
					skillnames.push_back("Вампирка");
					skills.push_back("vampire =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 8:
					skillnames.push_back("Взрыв после смерти");
					skills.push_back("boom");
					startValue = Random(3, 10);
					additionalValue = Random(1, 5);
					distance = Random(100, 400);
					
					
					params.push_back(std::to_string(distance) + " " + std::to_string(startValue) + ";" + std::to_string(distance) + " " + std::to_string(startValue + additionalValue) + ";" + std::to_string(distance) + " " + std::to_string(startValue + additionalValue * 2) + ";" + std::to_string(distance) + " " + std::to_string(startValue + additionalValue * 3));
					break;
				case 9: 
					skillnames.push_back("Регенирация");
					skills.push_back("regen");
					time = Random(1, 5);
					hp = Random(1, 5);
					
					
					params.push_back(std::to_string(time+time) + " " + std::to_string(hp) + ";" + std::to_string(time + time) + " " + std::to_string(hp) + ";" + std::to_string(time) + " " + std::to_string(hp) + ";" + std::to_string(time) + " " + std::to_string(hp) + ";");
					break;
				case 10:
					skillnames.push_back("Замедление");
					skills.push_back("slow =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 11:
					skillnames.push_back("Ракеты");
					skills.push_back("rockets =");
					amount = Random(1, 5);
					minDamage = Random(10, 100);
					maxDamage = Random(70, 150);
					
					
					params.push_back(std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";" + std::to_string(amount) + " " + std::to_string(minDamage) + " " + std::to_string(maxDamage) + ";");
					break;
				case 12:
					skillnames.push_back("Длинный прыжок");
					skills.push_back("longjump =");
					startValue = Random(80, 150);
					additionalValue = Random(30, 50);
					
					
					params.push_back(std::to_string(int(startValue)) + ";" + std::to_string(int(startValue + additionalValue)) + ";" + std::to_string(int(startValue + additionalValue * 2)) + ";" + std::to_string(int(startValue + additionalValue * 3)));
					break;
				case 13:
					skillnames.push_back("Зеркало");
					skills.push_back("mirror =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 14:
					skillnames.push_back("Уклон");
					skills.push_back("evasion");
					change = Random(1, 44);
					additionalValue = Random(5, 8);
					
					
					params.push_back(std::to_string(int(change)) + ";" + std::to_string(int(change + additionalValue)) + ";" + std::to_string(int(change + additionalValue * 2)) + ";" + std::to_string(int(change + additionalValue * 3)));
				case 15:
					skillnames.push_back("Высота шага");
					skills.push_back("step");
					startValue = Random(100, 180);
					additionalValue = Random(3, 33);
					
					
					params.push_back(std::to_string(int(startValue)) + ";" + std::to_string(int(startValue + additionalValue)) + ";" + std::to_string(int(startValue + additionalValue * 2)) + ";" + std::to_string(int(startValue + additionalValue * 3)));
					break;
				case 16:
					skillnames.push_back("Подброс противника");
					skills.push_back("push =");
					startValue = Random(60, 130);
					additionalValue = Random(3, 33);
					change = Random(1, 99);
					
					
					params.push_back(std::to_string(int(startValue)) + " " + std::to_string(change) + ";" + std::to_string(int(startValue + additionalValue)) + " " + std::to_string(change) + ";" + std::to_string(int(startValue + additionalValue * 2)) + " " + std::to_string(change) + ";" + std::to_string(int(startValue + additionalValue * 3)) + " " + std::to_string(change));
					break;
				case 17:
					skillnames.push_back("Перевозрождение");
					skills.push_back("respawn");
					startValue = Random(0, 2);
					additionalValue = Random(1, 2);
					change = Random(1, 99);
					
					
					params.push_back(std::to_string(int(startValue)) + " " + std::to_string(change) + ";" + std::to_string(int(startValue + additionalValue)) + " " + std::to_string(change) + ";" + std::to_string(int(startValue + additionalValue * 2)) + " " + std::to_string(change) + ";" + std::to_string(int(startValue + additionalValue * 3)) + " " + std::to_string(change));
					break;
				case 18:
					skillnames.push_back("Выброс оружия");
					skills.push_back("dropweapon");
					change = Random(1, 99);
					
					
					params.push_back(std::to_string(change) + ";" + std::to_string(change) + ";" + std::to_string(change) + ";" + std::to_string(change));
					break;
				case 19:
					skillnames.push_back("Паралич");
					skills.push_back("paralyze =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 20:
					skillnames.push_back("Ослепление");
					skills.push_back("blind =");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 21:
					skillnames.push_back("Яд");
					skills.push_back("poison =");
					time = Random(1, 3);
					startValue = Random(1, 3);
					maxDamage = Random(1, 8);
					change = Random(1, 99);


					params.push_back(std::to_string(time) + " " + std::to_string(startValue) + " " + std::to_string(maxDamage) + " " + std::to_string(change-change) + std::to_string(time) + " " + std::to_string(startValue) + " " + std::to_string(maxDamage) + " " + std::to_string(change - change) + std::to_string(time) + " " + std::to_string(startValue) + " " + std::to_string(maxDamage) + " " + std::to_string(change) + std::to_string(time) + " " + std::to_string(startValue) + " " + std::to_string(maxDamage) + " " + std::to_string(change ));
					break;
				case 22:
					skillnames.push_back("Иллюзии");
					skills.push_back("illusion");
					startValue = Random(80, 150);
					startValue /= 100;
					additionalValue = Random(10, 80);
					additionalValue /= 100;
					change = Random(1, 80);
					
					
					params.push_back(std::to_string(startValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 2) + " " + std::to_string(change) + ";" + std::to_string(startValue + additionalValue * 3) + " " + std::to_string(change));
					break;
				case 23:
					skillnames.push_back("Закоп");
					skills.push_back("bury");
					time = Random(1, 4);
					distance = Random(70, 100);
					change = Random(1, 99);
					
					
					params.push_back(std::to_string(time) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(time) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(time) + " " + std::to_string(distance) + " " + std::to_string(change) + ";" + std::to_string(time) + " " + std::to_string(distance) + " " + std::to_string(change));
					break;
			}

		}

	}
	void Output() {
		std::ofstream file("C://Users/dredd/Desktop/Races.txt", std::ios::app);
		if (!file)
			exit(1);
		file << "\n\"" + name + "\"\n\{\n\t\"name\"\t\"" + name + "\"";
		file << "\n\t\"required\"\t\"" + std::to_string(required) + "\"";
		file << "\n\t\"category\"\t\"" + category + "\"";
		file << "\n\t\"maxlvl\"\t\"" + std::to_string(maxLvl) + "\"";
		file << "\n\t\"teamlimit\"\t\"0\"";
		file << "\n\t\"skillamount\"\t\"" + std::to_string(amountskill) + "\"";
		file << "\n\t\"skilllvls\"\t\"0\"";
		file << "\n\t\"skillsets\"\t\"4\"";
		file << "\n\t\"skillnames\"\t\"";
		for (int i = 0; i < amountskill; i++) {
			if(i != amountskill-1)
				file << skillnames[i] + ";";
			else {
				file << skillnames[i] + "\"";
			}
		}
		file << "\n\t\"skilldesc\"\t\"";
		for (int i = 0; i < amountskill; i++) {
			if (i != amountskill - 1)
				file << skillnames[i] + ";";
			else {
				file << skillnames[i] + "\"";
			}
		}
		for (int i = 0; i < amountskill; i++) {
			file << "\n\t\"skill" + std::to_string(i+1) + "\"\t\"" + skills[i] + "\"";
			file << "\n\t\"setting" + std::to_string(i+1) + "\"\t\"" + params[i] + "\"";
		}
		file << "\n}";

	}

};