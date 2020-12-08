#include "RoomArray.h"

RoomArray::RoomArray() {}
RoomArray::~RoomArray() {}

void RoomArray::print() {
	for (int i = 0; i < ROOMCNT; i++) {
		cout << userCnt << " ";
	}
	cout << "\n";
}

void RoomArray::saveData()
{
	recvData.open("../data.txt", ios::out);
	recvData.write((char*)&this->gameData, sizeof(this->gameData));
	recvData.close();
}


int RoomArray::sendUsers() {

	// 데이터를 성공적으로 받았는데 홀수 라운드에 첫번째 턴일 경우 랜덤으로 4장 뽑기
	if (this->gameData.RoundTurn[1] == 1 && this->gameData.RoundTurn[0] % 2 != 0)
		this->gameData.randomCard();

	// 짝수 라운드에 첫번재 턴일 경우 남은 카드 4장 사용하기
	else if (this->gameData.RoundTurn[1] == 1 && this->gameData.RoundTurn[0] % 2 == 0)
		this->gameData.remainCard();

	// 일단 객체를 파일로 다시 저장하는 작업이 필요함
	saveData();

	// 파일 열기
	sendData.open("../data.txt", ios::in);

	// 파일 크기만큼을 dataBuffer에 저장
	sendData.read(dataBuffer, STRUCT_SIZE);
	sendData.close();

	// data의 내용을 유저에게 보냄
	printf("데이터를 모든 유저에게 보냅니다\n");
	int result = send(user[0], dataBuffer, sizeof(dataBuffer), 0);
	if (result < 0)
	{
		return -1;
	}
	result = send(user[1], dataBuffer, sizeof(dataBuffer), 0);
	if (result < 0)
	{
		return -1;
	}
	return 1;
}

int RoomArray::recvUser1() {
	int recvResult;

	recvResult = recv(user[0], dataBuffer, sizeof(dataBuffer), 0);
	if (recvResult == -1) return recvResult;

	recvData.open("../data.txt", ios::out);
	recvData.write(dataBuffer, recvResult);
	recvData.close();

	// 받은 데이터를 내 게임 데이터로 이식
	sendData.open("../data.txt", ios::in);
	sendData.seekg(0);
	sendData.read((char*)&this->gameData, sizeof(this->gameData));
	sendData.close();

	return recvResult;
}

int RoomArray::recvUser2() {
	int recvResult;

	recvResult = recv(user[1], dataBuffer, sizeof(dataBuffer), 0);
	if (recvResult == -1) return recvResult;

	recvData.open("../data.txt", ios::out);
	recvData.write(dataBuffer, recvResult);
	recvData.close();

	// 받은 데이터를 보낼 데이터로 가공하기 위해 내 게임 데이터로 이식
	sendData.open("../data.txt", ios::in);
	sendData.seekg(0);
	sendData.read((char*)&this->gameData, sizeof(this->gameData));
	sendData.close();

	return recvResult;
}

void RoomArray::GameStart() {
	printf("유저에게 역할을 보냅니다.\n");
	int result = send(user[0], "Jack", strlen("Jack"), 0);
	printf("Jack을 결정하였습니다.\n");
	if (result < 0)
		printf("error: send to Jack");

	result = send(user[1], "Police", strlen("Police"), 0);
	printf("수사관을 결정하였습니다.\n");
	if (result < 0)
		printf("error: send to Police");

	// 게임에 필요한 데이터를 주고 받는다
	printf("\n=========================================\n");
	printf("(시작) 두 유저에게 역할을 전달했습니다.\n");

	printf("8 캐릭터 카드 중 잭 역할의 캐릭터를 선정했습니다..\n");
	this->gameData.set_Jack();

	// 유저에게 초기 데이터를 보냄
	int sendResult = sendUsers();
	if (sendResult == -1) {
		printf("Send Err\n\n");
		closesocket(user[0]);
		closesocket(user[1]);
	}

	while(this->gameData.whoWin == -1){

		if (this->gameData.check_user() == 0) {
			//잭 유저의 차례
			int recvResult = recvUser1();
			printf("\n\'잭\' 유저에게 데이터를 받았습니다\n");
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
		}
		if (this->gameData.check_user() == 1) {
			//수사관 유저의 차례
			int recvResult = recvUser2();
			printf("\n\'수사관\' 유저에게 데이터를 받았습니다\n");
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
		}
	}

	printf("\n========== Client Disconnected ==========\n");
	closesocket(user[0]);
	closesocket(user[1]);
}