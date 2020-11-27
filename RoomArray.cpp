#include "RoomArray.h"

RoomArray::RoomArray() {}
RoomArray::~RoomArray() {}

void RoomArray::print() {
	for (int i = 0; i < ROOMCNT; i++) {
		cout << userCnt << " ";
	}
	cout << "\n";
}

int RoomArray::sendUsers() {
	fgets(cMsg, PACKET_SIZE, stdin);
	printf("데이터를 모든 유저에게 보냅니다: %s\n", cMsg);
	int result = send(user[0], cMsg, strlen(cMsg), 0);
	if (result < 0)
		return -1;

	result = send(user[1], cMsg, strlen(cMsg), 0);
	if (result < 0)
		return -1;

	return 1;
}

int RoomArray::recvUser1() {
	int recvResult = recv(user[0], cBuffer, PACKET_SIZE, 0);
	//strcpy_s(cMsg, cBuffer);
	memcpy(cMsg, cBuffer, PACKET_SIZE);
	for (int i = 0; i < PACKET_SIZE; i++) {
		cBuffer[i] = '\0';
	}
	return recvResult;
}
int RoomArray::recvUser2() {
	int recvResult = recv(user[1], cBuffer, PACKET_SIZE, 0);
	//strcpy_s(cMsg, cBuffer);
	memcpy(cMsg, cBuffer, PACKET_SIZE);
	for (int i = 0; i < PACKET_SIZE; i++) {
		cBuffer[i] = '\0';
	}
	return recvResult;
}

void RoomArray::GameStart() {
	// TODO
	// Round turn에 따라서
	// 홀수 라운드: 수사관 잭 잭 수사관
	// 짝수 라운드: 잭 수사관 수사관 잭

	GameData gameData;

	// 처음에 유저0에게는 잭을, 유저1에게는 수사관임을 알려줘야함
	printf("유저에게 역할을 보냅니다.\n");
	int result = send(user[0], "Jack", strlen("Jack"), 0);
	if (result < 0)
		printf("error: send to Jack");

	result = send(user[1], "Police", strlen("Police"), 0);
	if (result < 0)
		printf("error: send to Police");

	// 초기 게임 데이터를 유저에게 전달
	// 게임에 필요한 데이터를 주고 받는다
	while (1) { 
		printf("\n============================\n");
		int sendResult = sendUsers();
		if (sendResult == -1) {
			printf("Send Err\n\n");
			closesocket(user[0]);
			closesocket(user[1]);
			break;
		}
		printf("(시작)두 유저에게 데이터를 보냈습니다.\n");
		while (1) {
			int recvResult = recvUser1();
			printf("\n유저1에게 데이터를 받았습니다: %s\n", cMsg);
			if (recvResult < 0) {
				printf("Recv Err\n\n");
				break;
			}
			else
			{
				int sendResult = sendUsers();
				if (sendResult == -1) {
					printf("Send Err\n\n");
					closesocket(user[0]);
					closesocket(user[1]);
					break;
				}
			}

			recvResult = recvUser2();
			printf("\n유저2에게 데이터를 받았습니다: %s\n", cMsg);
			if (recvResult < 0) {
				printf("Recv Err\n\n");
				break;
			}
			else
			{
				int sendResult = sendUsers();
				if (sendResult == -1) {
					printf("Send Err\n\n");
					closesocket(user[0]);
					closesocket(user[1]);
					break;
				}
			}

			//	for (int i = 0; i < PACKET_SIZE; i++) {
			//		cBuffer[i] = '\0';
			//	}
		}break;
	}

	printf("\n===== Client Disconnected =====\n");
	closesocket(user[0]);
	closesocket(user[1]);
}
