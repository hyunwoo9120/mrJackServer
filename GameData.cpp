#include "GameData.h"

GameData::GameData()
{
}

GameData::~GameData()
{
}

void GameData::randomCard() {
	srand((unsigned int)time(NULL));
	
	for (int i = 0; i < 8; i++) {					// 홀수 라운드마다 모두 0으로 초기화
		this->selectedCard[i] = 0;
	}

	while (1) {
		int n = rand() % 8;
		this->selectedCard[n] = 1;			// 뽑힌 카드는 1로 표시
		int cnt = 0;
		for (int i = 0; i < 8; i++) {
			if (this->selectedCard[i] == 1)	
				cnt++;
		}
		if (cnt == 4) {								// 뽑힌 카드 4개 될 때 종료
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
	// 홀수일때 1인 카드를 0으로, 0인 카드를 1로 바꿈!
}



int* GameData::InfoGameRound() {

	if (turn < 4) {
		this->RoundTurn[2]++;
	}
	else {
		this->RoundTurn[0]++;
		this->RoundTurn[2] = 1;
	}
}


int GameData::check_user() {
	int oddround[4] = { 1, 0, 0, 1 };		// 홀수 : 수사관(1)부터
	int evenround[4] = { 0, 1, 1, 0 };		// 짝수 : 잭(0)부터

	if (round % 2 == 0) {						// 짝수 라운드인 경우
		return evenround[turn - 1];
	}
	else {												// 홀수 라운드인 경우
		return oddround[turn - 1];
	}
	// return 값이 1이면 수사관 차례, 0이면 잭 차례
}

bool GameData::update_Jack() {

	if (/*잭이 밝은 곳에 존재함*/) {		// 가로등 범위, 왓슨 손전등 범위, 주위 사람 유무 확인
		JackState = true;
	}
	else {
		JackState = false;
	}
	return JackState;
}
