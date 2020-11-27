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

	// 여기부터 데이터 송수신

	SOCKADDR_IN tClntAddr = {};

	// 룸 배열 생성
	RoomArray roomList[ROOMCNT];
	printf("\n----- server using thread -----\n");
	while (1) { // 여러 클라이언트 접속허용
		printf("Waiting...\n");

		int iClntSize = sizeof(tClntAddr);
		hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);

		// accept 오류확인
		if (hClient == -1) {
			closesocket(hClient);
			printf("accept error\n");
			break;
		}

		// 클라이언트 연결이 확인됨.
		else printf("\n----- Connection Established -----\n");
		// roomList room의 인원수를 확인. 이론상 인원수가 2일리는 없음
		for (int i = 0; i < ROOMCNT; i++) {
			bool escapeLoop = false;
			switch (roomList[i].userCnt) {
				// room 안에 아무도 없는 경우
			case 0:
			{
				roomList[i].userCnt++;
				roomList[i].user[0] = hClient;
				escapeLoop = true;
				break;
			}

			// room 안에 한 명 있는 경우
			case 1:
			{
				roomList[i].userCnt++;
				roomList[i].user[1] = hClient;
				escapeLoop = true;
				// 스레드를 만들어서 게임을 시작하려고함
				std::thread procStart(proc_start, roomList[i]);
				procStart.detach();
				// roomList[i].GameStart();
				break;
			}


			// room 안에 두 명 있는 경우 
			default: break;
			}

			if (escapeLoop) break;
		}

	} // 전체 while 종료
	closesocket(hListen);

	WSACleanup();
	return 0;
}