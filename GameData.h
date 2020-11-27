#include <iostream>
#include <ctime>
#pragma once
class GameData
{
public:
	GameData();
	~GameData();

	void randomCard();
	int selectedCard[8] = { 0, };
	int round = 0;
	int turn = 0;
};
