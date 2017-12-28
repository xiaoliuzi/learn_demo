//#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>

#define PORT 65432
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
//#if 0
int main(int argc, char *argv[])
{
	// define listening socket and established socket
	SOCKET sock_server, newsock;
	// binding address struct variable
	struct sockaddr_in addr;
	// to store client address
	struct sockaddr_in client_addr;
	// to receive message content from client
	char msgbuffer[256];
	char msg[] = "Connect succeed.\n";

	// initial winsock2.dll
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		cout << "load winsock.dll failed" << endl;
		return 0;
	}

	// create socket
	if ((sock_server = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
		cout << "create socket failed. error code:" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	// to set binding local address
	int addr_len = sizeof(struct sockaddr_in);
	// clear addr_in
	memset((void*)&addr, 0, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	// allow to use any ip of localhost
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// binding address for socket
	if (bind(sock_server, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
		cout << "address bind failed error code:" << WSAGetLastError() << endl;
		closesocket(sock_server);
		WSACleanup();
		return 0;
	}
	// set socket_server to listening
	if (listen(sock_server, 0) != 0) {
		cout << "listen function call failed. error code:" << WSAGetLastError() << endl;
		closesocket(sock_server);
		WSACleanup();
		return 0;
	}
	else
		cout << "lisntenning...." << endl;

	// loop accept connect request and send & recv message
	int size;
	while (true) {
		if ((newsock = accept(sock_server, (struct sockaddr *)&client_addr, &addr_len)) == INVALID_SOCKET) {
			cout << "accept() function call failed. error code:" << WSAGetLastError() << endl;
			break;  // loop exit
		}
		else
			cout << "success accept a connection request" << endl;
		// success recv a connection and send message then recv message
		// send a message to client.
		size = send(newsock, msg, sizeof(msg), 0);
		if (size == SOCKET_ERROR) {
			cout << "send message failed error code:" << WSAGetLastError() << endl;
			// close socket had connected.
			closesocket(sock_server);
			// continue to accept other connection request
			continue;
		}
		else if (size == 0) {
			cout << "dest closed socket" << endl;
			// close socket had connected
			closesocket(newsock);
			// continue to accept other connection request
			continue;
		}
		else {
			cout << "success send message" << endl;
		}
		// receive message
		if ((size = recv(newsock, msgbuffer, sizeof(msgbuffer), 0)) < 0) {
			cout << "recv message failed error code:" << WSAGetLastError() << endl;
			closesocket(newsock);
			continue;
		}
		else if (size == 0) {
			cout << "dest closed socket" << endl;
			closesocket(newsock);
			continue;
		}
		else {
			cout << "newsock:" << newsock << endl;
			cout << "recv msg:" << msgbuffer << endl;
		}
			
		closesocket(newsock);
	}

	// final process
	// close socket
	closesocket(sock_server);
	WSACleanup();
	cout << "hello world" << endl;
	return 0;
}


//#endif