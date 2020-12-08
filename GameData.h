#include <iostream>
#include <ctime>
#pragma once

class Chara
{
public:
	int x;
	int y;
	bool inno;
};

class Map
{
public:
	bool b_lamp_on;
	bool b_checkpoint_on;
	bool b_manhole_on;
	int x, y;
	int i_Item_on;
	int i_default_item;
};

enum Characters :int
{
	Shelock = 0,
	Watson,
	Smith,
	Lestrade,
	Stealthy,
	Goodley,
	William,
	Jeremy
};

class GameData
{
public:
	int whoWin = -1;
	int selectedCard[8] = { 0, 0 };
	int RoundTurn[2] = { 1, 1 };

	int usedCard[8] = { 0,0 };
	bool JackState = true;
	Characters jack;

	Chara charaInfo[8];

	GameData();
	~GameData();

	void randomCard();
	void remainCard();
	void set_Jack();

	void InfoGameRound();
	int check_user();

	Map tile[113];
	Map manhole[8];
	Map lamp[6];
};
