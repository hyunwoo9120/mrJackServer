#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include "GameData.h"
#pragma comment(lib, "ws2_32")
#define STRUCT_SIZE 2720

#pragma once
#define ROOMCNT 5
using namespace std;

class RoomArray {
public:
	ofstream recvData;
	ifstream sendData;
	GameData gameData;

	char dataBuffer[STRUCT_SIZE] = ""; // 게임 데이터 받을 버퍼

	int userCnt=0; 
	// user[0]: 잭, user[1]: 수사관
	SOCKET user[2];

	RoomArray();
	~RoomArray();

	void print();
	void saveData();
	int sendUsers();
	int recvUser1();
	int recvUser2();

	void GameStart();
};