#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "fileMessage.h"
#include <fstream>
#include "string.h"

#define PORT 65432

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(int argc, char *argv[])
{
	// define socket variable
	// define listenning socket and established socket
	SOCKET sock_server, newsock;
	// store binding address structure
	struct sockaddr_in addr;
	// store client address
	struct sockaddr_in client_addr;
	// buffer to receive message content from client
	char msgbuffer[256];
	char msg[] = "Connect succeed.\n";
	// initialize winsock2.dll
	WSADATA wsaData;
	// generate version 2.2
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		cout << "load winsock.dll failed" << endl;
		return 0;
	}
	// create socket
	if ((sock_server = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR) {
		cout << "create socket failed error code:" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	// binding local address
	int addr_len = sizeof(struct sockaddr_in);
	memset((void*)&addr, 0, addr_len);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	// allow to use any ip of localhost
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	// binding listenning socket with localhost ip
	if (bind(sock_server, (struct sockaddr*)&addr, sizeof(addr)) != 0) {
		cout << "address bind failed. error code:" << WSAGetLastError() << endl;
		closesocket(sock_server);
		WSACleanup();
		return 0;
	}
	// set socket listenning
	if (listen(sock_server, 0) != 0) {
		cout << "listen function called failed. error code:" << WSAGetLastError() << endl;
		closesocket(sock_server);
		WSACleanup();
		return 0;
	}
	else {
		cout << "listenning..." << endl;
	}
	char filename[500];
	cout << "Input the directory:(less than 500 bytes)" << endl;
	char IP[20] = { 0 };
	cin.getline(filename, 500);
	// loop: accept connect request, send and receive data
	
	while (true) 
	{
		if ((newsock = accept(sock_server, (struct sockaddr*)&client_addr, &addr_len)) == INVALID_SOCKET) {
			cout << "accept() function called failed error code:" << WSAGetLastError() << endl;
			// break loop
			break;
		}
		else {
			cout << "Accept a connection request succeed!" << endl;
		}
		// after succeed in receiving a connection  and send or receive message
		inet_pton(AF_INET, IP, (PVOID)&client_addr.sin_addr.S_un.S_addr);
		cout << "connect from:" << IP << endl;
		//define file transfer variable
		char OK[3];
		char fileBuffer[1000];
		struct fileMessage fileMsg;
		int size = strlen(filename);
		while (filename[size] != '\\' && size > 0) {
			size--;
		}
		strcpy_s(fileMsg.fileName, filename + size);
		ifstream inFile(filename, ios::in | ios::binary);
		if (!inFile.is_open()) {
			cout << "can not open " << filename << endl;
			closesocket(newsock);
			closesocket(sock_server);
			WSACleanup();
			return 0;
		}

		inFile.seekg(0, ios::end);
		streampos possize = inFile.tellg();
		size = (int)possize;
		inFile.seekg(0, ios::beg);

		fileMsg.fileSize = htonl(size);
		// send filename and size to client
		send(newsock, (char*)&fileMsg, sizeof(fileMsg), 0);
		

		if ((size = recv(newsock, OK, sizeof(OK), 0)) < 0) {
			cout << "receive OK failed error coed:" << WSAGetLastError() << endl;
			closesocket(newsock);
			continue;
		}
		else if (size == 0) {
			cout << "client has closed the socket" << endl;
			closesocket(newsock);
			continue;
		}
		else {
			cout << "receive message:" << msgbuffer << endl;
		}
		// send file content
		if (strcmp(OK, "OK") == 0) {
			while (!inFile.eof()) {
				inFile.read(fileBuffer, sizeof(fileBuffer));
				size = (int)inFile.gcount();
				send(newsock, fileBuffer, size, 0);
			}
			cout << "file transfer finished.";
			inFile.close();
		}
		else {
			cout << "client can not receive file" << endl;
		}
		closesocket(newsock);

	}
	// release resource
	// close listenning socket
	closesocket(sock_server);
	// release winsock dll
	WSACleanup();
	cout << "hello world" << endl;
	return 0;
}


