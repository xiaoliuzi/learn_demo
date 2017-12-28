//#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define PORT 65432
#pragma comment(lib, "Ws2_32.lib")
using namespace std;
//#if 0
int main(int argc, char *argv[])
{
	// define listening socket and established socket
	SOCKET sock_client;
	// to store server address
	struct sockaddr_in server_addr;
	int addr_len = sizeof(struct sockaddr_in);
	// to receive message content from client
	char msgbuffer[1000];
	
	// initial winsock dll
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		cout << "load winsock.dll failed." << endl;
		return 0;
	}

	// create socket
	if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "create socket failed. error code:" << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}
	// set server address
	char IP[20];
	cout << "Input server ip(like 192.168.23.154):" << endl;
	cin >> IP;
	// clear server addr_in
	memset((void*)&server_addr, 0, addr_len);
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, (PVOID)&server_addr.sin_addr.S_un.S_addr);
	// connect with server
	if (connect(sock_client, (struct sockaddr*)&server_addr, addr_len) != 0) {
		cout << "connnected failed. error code:" << WSAGetLastError() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}

	// receive message and print
	int size;
	if ((size = recv(sock_client, msgbuffer, sizeof(msgbuffer), 0)) < 0) {
		cout << "receive message failed. error code:" << WSAGetLastError() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	else if (size == 0) {
		cout << "server has close socket" << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	else {
		cout << "The message from Server:" << msgbuffer << endl;
	}

	// input a message from keyboard and send to server
	cout << "Input message:(size less than 1000 Bytes)" << endl;
	cin >> msgbuffer;
	if ((size = send(sock_client, msgbuffer, sizeof(msgbuffer), 0)) < 0) {
		cout << "send message to server failed. error code:" << WSAGetLastError() << endl;
	}
	else if (size == 0) {
		cout << "server has closed socket" << endl;
	}
	else {
		cout << "message send success" << endl;
	}

	// final process
	// close socket
	closesocket(sock_client);
	WSACleanup();
	cout << "hello world" << endl;
	return 0;
}

//#endif