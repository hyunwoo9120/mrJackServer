#include <iostream>
#include <ctime>
#pragma once
class GameData
{
public:
	
	int selectedCard[8] = { 0, 0};				// 뽑힌 카드는 1로 표현
	int RoundTurn[2] = { 1,0 };				// round, turn 알려주는 배열( [0] : round, [1] : turn )

	int selectedCard[8] = { 0,0 };				// 선택된 카드(1) 알려줌. 
	bool JackState = true;					// 잭의 상태,  우선 '빛에 있다' 가정하고 시작


	GameData();
	~GameData();

	void randomCard();					// 홀수라운드마다 캐릭터 카드 4장 뽑는 함수 
	void remainCard();					//	짝수라운드일 때 나머지 카드 4장 뽑는 함수

	int* InfoGameRound();					// turn 시작마다 round, turn 알려주는 함수(전체 게임 시작시에도 실행)
	int check_user();					// 잭 차례인지 수사관 차례인지 알려주는 함수
	bool update_Jack();					// 잭이 빛에 있는지, 어둠에 있는지 알려주는 함수


	/*	
	추가로 구현해야 할 것
	캐릭터, 가로등, 맨홀, 손전등 위치(+ 왓슨 손전등 방향)
	캐릭터 innocent
	*/
};
