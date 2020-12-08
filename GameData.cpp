#include "GameData.h"

GameData::GameData()
{

}

GameData::~GameData()
{
}

void GameData::randomCard() {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 8; i++) {
		this->selectedCard[i] = 0;
	}
	while (1) {
		int n = rand() % 8;
		this->selectedCard[n] = 1;
		int cnt = 0;
		for (int i = 0; i < 8; i++) {
			if (this->selectedCard[i] == 1)
				cnt++;
		}
		if (cnt == 4) {
			break;
		}
	}
}

void GameData::remainCard() {
	for (int i = 0; i < 8; i++) {
		if (this->selectedCard[i] == 1) {
			this->selectedCard[i] = 0;
		}
		else {
			this->selectedCard[i] = 1;
		}
	}
}

void GameData::InfoGameRound() {

	if (this->RoundTurn[1] == 4) {
		this->RoundTurn[0]++;
		this->RoundTurn[1] = 1;
	}
	else {
		this->RoundTurn[1]++;
	}

}int GameData::check_user() {
	int oddround[4] = { 1, 0, 0, 1 };
	int evenround[4] = { 0, 1, 1, 0 };

	if (this->RoundTurn[0] % 2 == 0) {
		return evenround[this->RoundTurn[1] - 1];
	}
	else {
		return oddround[this->RoundTurn[1] - 1];
	}
}

void GameData::set_Jack() {
	srand((unsigned int)time(NULL));
	this->jack = (Characters)(rand() % 8);
}