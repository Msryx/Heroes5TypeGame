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
	bool movmentLeft;
	positionVec position;
	//Tylko do wersji ascii
	char symbole = '1';
};

class PlayerPerson {
public:
	int pointsOfAction;
	bool order;
	std::vector <unit> Army;
	mapWithUnits map[mapSize][mapSize];
	void refreshMap();
	void createMap();
	PlayerPerson( int typeOfStart, bool start, int actionPoints);
	void moveUnit(unit &oneUnit);
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
		for (int y = 0; y < Army.size(); y++) {
			pos.positionX = Army.at(y).position.positionX;
			pos.positionY = Army.at(y).position.positionY;
			map[pos.positionX][pos.positionY].symbol = Army.at(y).symbole;
			if (!order) {
				map[pos.positionX][pos.positionY].type = player1;
			}
			else
			{
				map[pos.positionX][pos.positionY].type = player2;
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
PlayerPerson::PlayerPerson( int typeOfStart, bool start, int actionPoints) {
	Army.resize(1);
	order = start;
	pointsOfAction = actionPoints;
	float posit = ceil(mapSize / 2);
	
	Army.at(0).position.positionY = posit;
	if (order) {
		Army.at(0).position.positionX = mapSize-2;
	}
	else
	{
		Army.at(0).position.positionX = 1;
	}
	//TODO Deklracja jednostki, testowe, przesun¹æ do osobnej funkcji
	Army.at(0).amount = 2;
	Army.at(0).costOfBuild = 1;
	Army.at(0).costOfUse = 1;
	Army.at(0).dmg = 1;
	Army.at(0).level = 0;
	Army.at(0).movment = 2;
	Army.at(0).range = 1;
	std::cout << "Posit: " << posit << " OrderLoc: " << mapSize -2;
}

void PlayerPerson::moveUnit(unit& oneUnit)
{
	const int move = oneUnit.movment;
	positionVec startPosit = oneUnit.position;
	positionVec endPosit = oneUnit.position;
	//Sprawdza czy nie wyjdzie poza tablicê map

	if (startPosit.positionX - move < 1) {
		startPosit.positionX = 1;
	}
	else
	{
		startPosit.positionX -= move;
	}
	if (startPosit.positionY - move < 1)
	{
		startPosit.positionY = 1;
	}
	else
	{
		startPosit.positionY -= move;
	}

	if (endPosit.positionX + move > mapSize - 2) {
		endPosit.positionX = mapSize-2;
	}
	else
	{
		endPosit.positionX += move;
	}
	if (endPosit.positionY + move > mapSize -2)
	{
		endPosit.positionY = mapSize-2;
	}
	else
	{
		endPosit.positionY += move;
	}
	std::vector <positionVec> freeToMove;
	for (int y = startPosit.positionX; y <= endPosit.positionX; y++) {
		for (int x = startPosit.positionY; x <= endPosit.positionY; x++) {
			if (map[y][x].type == empty) {
				positionVec emptyPlace;
				emptyPlace.positionX = x;
				emptyPlace.positionY = y;
				freeToMove.push_back(emptyPlace);
			}
		}
	}
	std::cout << "Dostepne ruch:\n";
	for (int x = 0; x < freeToMove.size(); x++) {
		std::cout << "Ruch nr. " << x+1 << " ## X: " << freeToMove.at(x).positionX << " Y: " << freeToMove.at(x).positionY << " ##\n";

	}
	int moveNumber;
	map[oneUnit.position.positionX][oneUnit.position.positionY].type = empty;
	map[oneUnit.position.positionX][oneUnit.position.positionY].symbol = ' ';
	std::cin >> moveNumber;
	oneUnit.position.positionY = freeToMove.at(moveNumber - 1).positionX;
	oneUnit.position.positionX = freeToMove.at(moveNumber - 1).positionY;
	oneUnit.movmentLeft = false;
	refreshMap();
		//testowe
	std::cout << "\nStartPositX: " << startPosit.positionX << "StartPositY: " << startPosit.positionY << "\n";
	std::cout << "EndPositX: " << endPosit.positionX << "EndPositY: " << endPosit.positionY << "\n";
	std::cout << "NewPositX: " << oneUnit.position.positionX << "NewPositY: " << oneUnit.position.positionY << "\n";
	

}

