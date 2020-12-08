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

	// �����͸� ���������� �޾Ҵµ� Ȧ�� ���忡 ù��° ���� ��� �������� 4�� �̱�
	if (this->gameData.RoundTurn[1] == 1 && this->gameData.RoundTurn[0] % 2 != 0)
		this->gameData.randomCard();

	// ¦�� ���忡 ù���� ���� ��� ���� ī�� 4�� ����ϱ�
	else if (this->gameData.RoundTurn[1] == 1 && this->gameData.RoundTurn[0] % 2 == 0)
		this->gameData.remainCard();

	// �ϴ� ��ü�� ���Ϸ� �ٽ� �����ϴ� �۾��� �ʿ���
	saveData();

	// ���� ����
	sendData.open("../data.txt", ios::in);

	// ���� ũ�⸸ŭ�� dataBuffer�� ����
	sendData.read(dataBuffer, STRUCT_SIZE);
	sendData.close();

	// data�� ������ �������� ����
	printf("�����͸� ��� �������� �����ϴ�\n");
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

	// ���� �����͸� �� ���� �����ͷ� �̽�
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

	// ���� �����͸� ���� �����ͷ� �����ϱ� ���� �� ���� �����ͷ� �̽�
	sendData.open("../data.txt", ios::in);
	sendData.seekg(0);
	sendData.read((char*)&this->gameData, sizeof(this->gameData));
	sendData.close();

	return recvResult;
}

void RoomArray::GameStart() {
	printf("�������� ������ �����ϴ�.\n");
	int result = send(user[0], "Jack", strlen("Jack"), 0);
	printf("Jack�� �����Ͽ����ϴ�.\n");
	if (result < 0)
		printf("error: send to Jack");

	result = send(user[1], "Police", strlen("Police"), 0);
	printf("������� �����Ͽ����ϴ�.\n");
	if (result < 0)
		printf("error: send to Police");

	// ���ӿ� �ʿ��� �����͸� �ְ� �޴´�
	printf("\n=========================================\n");
	printf("(����) �� �������� ������ �����߽��ϴ�.\n");

	printf("8 ĳ���� ī�� �� �� ������ ĳ���͸� �����߽��ϴ�..\n");
	this->gameData.set_Jack();

	// �������� �ʱ� �����͸� ����
	int sendResult = sendUsers();
	if (sendResult == -1) {
		printf("Send Err\n\n");
		closesocket(user[0]);
		closesocket(user[1]);
	}

	while(this->gameData.whoWin == -1){

		if (this->gameData.check_user() == 0) {
			//�� ������ ����
			int recvResult = recvUser1();
			printf("\n\'��\' �������� �����͸� �޾ҽ��ϴ�\n");
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
			//����� ������ ����
			int recvResult = recvUser2();
			printf("\n\'�����\' �������� �����͸� �޾ҽ��ϴ�\n");
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