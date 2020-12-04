#include "GameData.h"

GameData::GameData()
{
	// 8캐릭터의 위치를 초기화
	this->characterPosition[Shelock][0]=6;
	this->characterPosition[Shelock][1]=5;

	this->characterPosition[Watson][0]=0;
	this->characterPosition[Watson][1]=2;

	this->characterPosition[Smith][0]=6;
	this->characterPosition[Smith][1]=2;

	this->characterPosition[Lestrade][0]=4;
	this->characterPosition[Lestrade][1]=4;

	this->characterPosition[Stealthy][0]=8;
	this->characterPosition[Stealthy][1]=7;

	this->characterPosition[Goodley][0]=12;
	this->characterPosition[Goodley][1]=3;

	this->characterPosition[William][0]=4;
	this->characterPosition[William][1]=0;

	this->characterPosition[Jeremy][0]=8;
	this->characterPosition[Jeremy][1]=3;

}

GameData::~GameData()
{
}


/// <summary>
/// 홀수 라운드 시작할 때, 8개의 카드 중 랜덤으로 4개를 뽑는 함수
/// </summary>
void GameData::randomCard() {
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 8; i++) {					// 홀수 라운드마다 모두 0으로 초기화
		this->selectedCard[i] = 0;
	}
	while (1) {
		int n = rand() % 8;
		this->selectedCard[n] = 1;				// 뽑힌 카드는 1로 표시
		int cnt = 0;
		for (int i = 0; i < 8; i++) {
			if (this->selectedCard[i] == 1)
				cnt++;
		}
		if (cnt == 4) {						// 뽑힌 카드 4개 될 때 종료
			break;
		}
	}
}


/// <summary>
/// 홀수 라운드에서 짝수 라운드로 바뀔 때,
/// 전 라운드에서 사용하지 않은 카드를 세팅해주는 함수
/// </summary>
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

/// <summary>
/// 유저의 순서를 확인하는 함수
/// </summary>
/// <returns>0이면 잭의 차례, 1이면 수사관의 차례</returns>
int GameData::check_user() {
	int oddround[4] = { 1, 0, 0, 1 };				// 홀수 : 수사관(1)부터
	int evenround[4] = { 0, 1, 1, 0 };				// 짝수 : 잭(0)부터

	if (this->RoundTurn[0] % 2 == 0) {				// 짝수 라운드인 경우
		return evenround[this->RoundTurn[1]];
	}
	else {											// 홀수 라운드인 경우
		return oddround[this->RoundTurn[1]];
	}
}


/// <summary>
/// 잭이 빛에 있는지, 어둠에 있는지 확인해서 JackState를 세팅하는 함수
/// 빛에 있으면 JackState는 true
/// </summary>
/// <returns>없음</returns>
void GameData::update_Jack() {
	if (this->characterState[this->jack])
	{
		this->JackState = true;
	}
	else {
		this->JackState = false;
	}
}


/// <summary>
/// 각 캐릭터가 빛에 있는지 확인하는 함수
/// </summary>
/// <returns>밝은 곳에 있으면 true, 어두운 곳에 있으면 false</returns>
void GameData::light_character() {
	// TODO: 가로등 범위, 왓슨 손전등 범위, 주위 사람 유무 확인
	for (int name = Shelock; name < 8; name++) {
		if (/*가로등 옆 || 주위 캐릭터 옆 || 왓슨 손전등 범위 안*/0) {
			this->characterState[name]=true; }
		else this->characterState[name] = false;
	
	}
}


/// <summary>
/// 8개의 카드 중 잭 역할의 캐릭터를 고르고 세팅하는 함수
/// </summary>
void GameData::set_Jack() {
	srand((unsigned int)time(NULL));
	this->jack = (Characters)(rand() % 8);
	this->isJack[this->jack] = true;
}