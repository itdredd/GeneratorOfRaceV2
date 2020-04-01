#include "Race.h"

TCHAR version[MAX_PATH];
TCHAR title[MAX_PATH];
TCHAR build_time[MAX_PATH];

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	StringCchPrintf(version, MAX_PATH, TEXT(VERSION));
	StringCchPrintf(build_time, MAX_PATH, TEXT(__DATE__));
	StringCchPrintf(title, MAX_PATH, TEXT("GOR ver. %s | Build %s"), version, build_time);
	SetConsoleTitle(title);

    Race race;


    return 0;
}

