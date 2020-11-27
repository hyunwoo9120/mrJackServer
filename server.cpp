#include "RoomArray.h"
#include <stdio.h>
#include <WinSock2.h>
#include <thread>
#pragma comment(lib, "ws2_32")

#define PORT 18363
#define PACKET_SIZE 1024

void proc_start(RoomArray room) {
	room.GameStart();
}

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	SOCKET hClient;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = PF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr)) == SOCKET_ERROR) {
		printf("Err bind\n");
		closesocket(hListen);
		WSACleanup();
		return 0;

	}
	if (listen(hListen, SOMAXCONN) == SOCKET_ERROR) {
		printf("Err listen\n");
		closesocket(hListen);
		WSACleanup();
		return 0;
	}

	// ������� ������ �ۼ���

	SOCKADDR_IN tClntAddr = {};

	// �� �迭 ����
	RoomArray roomList[ROOMCNT];
	printf("\n----- server using thread -----\n");
	while (1) { // ���� Ŭ���̾�Ʈ �������
		printf("Waiting...\n");

		int iClntSize = sizeof(tClntAddr);
		hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

		// accept ����Ȯ��
		if (hClient == -1) {
			closesocket(hClient);
			printf("accept error\n");
			break;
		}

		// Ŭ���̾�Ʈ ������ Ȯ�ε�.
		else printf("\n----- Connection Established -----\n");
		// roomList room�� �ο����� Ȯ��. �̷л� �ο����� 2�ϸ��� ����
		for (int i = 0; i < ROOMCNT; i++) {
			bool escapeLoop = false;
			switch (roomList[i].userCnt) {
				// room �ȿ� �ƹ��� ���� ���
			case 0:
			{
				roomList[i].userCnt++;
				roomList[i].user[0] = hClient;
				escapeLoop = true;
				break;
			}

			// room �ȿ� �� �� �ִ� ���
			case 1:
			{
				roomList[i].userCnt++;
				roomList[i].user[1] = hClient;
				escapeLoop = true;
				// �����带 ���� ������ �����Ϸ�����
				std::thread procStart(proc_start, roomList[i]);
				procStart.detach();
				// roomList[i].GameStart();
				break;
			}


			// room �ȿ� �� �� �ִ� ��� 
			default: break;
			}

			if (escapeLoop) break;
		}

	} // ��ü while ����
	closesocket(hListen);

	WSACleanup();
	return 0;
}