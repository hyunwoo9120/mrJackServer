#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string.h>
#include "GameData.h"
#pragma comment(lib, "ws2_32")
#define PACKET_SIZE 1024

#pragma once
#define ROOMCNT 5
using namespace std;

class RoomArray {
public:
	char cBuffer[PACKET_SIZE] = {}; // ���� ������
	char cMsg[PACKET_SIZE] = "GameStart"; // ������ ������(�������� ���� ��)

	int userCnt=0; 
	// user[0]: ��, user[1]: �����
	SOCKET user[2];
	GameData gameData;

	RoomArray();
	~RoomArray();

	void print();
	int sendUsers();
	int recvUser1();
	int recvUser2();

	void GameStart();
	void initGameDate();
};