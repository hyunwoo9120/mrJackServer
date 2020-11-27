#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
}

void GameData::randomCard() {
	srand((unsigned int)time(NULL));
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
