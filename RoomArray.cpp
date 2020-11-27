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
	printf("�����͸� ��� �������� �����ϴ�: %s\n", cMsg);
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
	// Round turn�� ����
	// Ȧ�� ����: ����� �� �� �����
	// ¦�� ����: �� ����� ����� ��

	GameData gameData;

	// ó���� ����0���Դ� ����, ����1���Դ� ��������� �˷������
	printf("�������� ������ �����ϴ�.\n");
	int result = send(user[0], "Jack", strlen("Jack"), 0);
	if (result < 0)
		printf("error: send to Jack");

	result = send(user[1], "Police", strlen("Police"), 0);
	if (result < 0)
		printf("error: send to Police");

	// �ʱ� ���� �����͸� �������� ����
	// ���ӿ� �ʿ��� �����͸� �ְ� �޴´�
	while (1) { 
		printf("\n============================\n");
		int sendResult = sendUsers();
		if (sendResult == -1) {
			printf("Send Err\n\n");
			closesocket(user[0]);
			closesocket(user[1]);
			break;
		}
		printf("(����)�� �������� �����͸� ���½��ϴ�.\n");
		while (1) {
			int recvResult = recvUser1();
			printf("\n����1���� �����͸� �޾ҽ��ϴ�: %s\n", cMsg);
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
			printf("\n����2���� �����͸� �޾ҽ��ϴ�: %s\n", cMsg);
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
