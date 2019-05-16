#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <cmath>

constexpr auto mapSize = 7;

enum Colors { blue = 1, green, cyan, red, purple, yellow, grey, dgrey, hblue, hgreen, hred, hpurple, hyellow, hwhite, white };

enum MapType { empty = 0 ,border, player1, player2};

struct mapWithUnits {
	char symbol = ' ';
	int type = 0;
};

struct positionVec
{
	int positionX, positionY;
};

//TODO deklaracje wszystkich funkcji

//TODO Dodaæ zapisywanie mapy
struct unit {
	int level,
		costOfUse,
		costOfBuild,
		movment,
		range,
		dmg,
		amount;
	positionVec position;
	//Tylko do wersji ascii
	char symbole = '1';
};

class PlayerPerson {
public:
	bool order;
	std::vector <unit> Army[7];
	mapWithUnits map[mapSize][mapSize];
	void refreshMap();
	void createMap();
	PlayerPerson( int typeOfStart);
	//TODO Ruch jednostek, walka jednostek, budowa jednostek, u¿ycie energii
};

//Ustala kolor tekstu, tylko windows
void coutc(std::string output, int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
	std::cout << output;
	SetConsoleTextAttribute(handle, 15);
}
//Przeci¹¿enie do obs³ugi pojedynczych znaków
void coutc(char output, int color)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, color);
	std::cout << output;
	SetConsoleTextAttribute(handle, 15);
}

//Tylko konsola windows
void cleanScreen() {
	system("cls");
}



void PlayerPerson::refreshMap() {
	cleanScreen();
	positionVec pos;
	for (int x = 0; x < 7; x++)
	{
		for (int y = 0; y < Army[x].size(); y++) {
			pos.positionX = Army[x].at(y).position.positionX;
			pos.positionY = Army[x].at(y).position.positionY;
			map[pos.positionX][pos.positionY].symbol = Army[x].at(y).symbole;
			if (!order) {
				map[pos.positionX][pos.positionY].type = player1;
			}
			else
			{
				map[pos.positionX][pos.positionY].type = player2;
			}
		}
	}

	for (int y = 0; y < mapSize; y++)
	{
		for (int x = 0; x < mapSize; x++)
		{
			switch (map[y][x].type)
			{
			case border:
				coutc(map[y][x].symbol, white);
				break;
			case player1:
				coutc(map[y][x].symbol, red);
				break;
			case player2:
				coutc(map[y][x].symbol, blue);
				break;
			default:
				coutc(map[y][x].symbol, white);
				break;
			}

		}
		std::cout << "\n";
	}
}


void PlayerPerson::createMap() {
	for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{
			if (y == 0 || x == 0 || x == mapSize - 1 || y == mapSize - 1) {
				map[x][y].symbol = '#';
				map[x][y].type = border;
			}
			else
			{
				map[x][y].symbol = ' ';
				map[x][y].type = empty;
			}

		}
	}
}

//TODO Obrócenie mapy dla ka¿dego gracza
PlayerPerson::PlayerPerson( int typeOfStart) {
	Army->resize(1);
	float posit = ceil(mapSize / 2);
	
	Army[0].at(0).position.positionY = posit;
	if (order) {
		Army[0].at(0).position.positionX = mapSize-2;
	}
	else
	{
		Army[0].at(0).position.positionX = 1;
	}
	std::cout << "Posit: " << posit << " OrderLoc: " << mapSize -2;
}

