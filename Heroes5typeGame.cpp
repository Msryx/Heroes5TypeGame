// Heroes5typeGame.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <C:\Users\matiz\source\repos\Heroes5typeGame\FuncHandling.h>





int main()
{
	PlayerPerson playerP(0);
	playerP.order = 0;
	playerP.createMap();
	positionVec unitP;
	unitP.positionX = playerP.Army[0].at(0).position.positionY;
	unitP.positionY = playerP.Army[0].at(0).position.positionX;
	std::cout << "\nPozycjaX: " << unitP.positionX << " PozycjaY: " << unitP.positionY << std::endl;
	playerP.refreshMap();
	playerP.Army[0].at(0).position.positionY = 2;
	playerP.Army[0].at(0).position.positionX = 2;
	playerP.refreshMap();
	/*for (int x = 0; x < mapSize; x++)
	{
		for (int y = 0; y < mapSize; y++)
		{	
			switch (map[x][y].type)
			{
			case 1:
				coutc(map[x][y].symbol, red);
				break;
			default:
				coutc(map[x][y].symbol, white);
				break;
			}
			
		}
		std::cout << "\n";
	}
	 player1.Army[0].push_back(1);
	player1.Army[1].push_back(2);
	std::cout << "\n" << player1.Army[0][0] << " " << player1.Army[1][0] << "\n"; 
	*/
	coutc("A", red);
	coutc("B", blue);
	std::cout << "A";
	int a;
	std::cin >> a;
	return 0;
}

