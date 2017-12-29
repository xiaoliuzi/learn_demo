#include "stdafx.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include "fileMessage.h"
#include "direct.h"
#include "string.h"
#include <fstream>

#define PORT 65432

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main(int argc, char *argv[])
{
	// define socket variable
	// define client socket
	SOCKET sock_client;
	// store server address
	struct sockaddr_in server_addr;
	int addr_len = sizeof(struct sockaddr_in);
	// send or receive buffer
	//char msgbuffer[1000];

	// initialize winsock2.dll
	WSADATA wsaData;
	// generate version 2.2
	WORD wVersionRequested = MAKEWORD(2, 2);
	if (WSAStartup(wVersionRequested, &wsaData) != 0) {
		cout << "load winsock.dll failed" << endl;
		return 0;
	}

	// create socket
	if ((sock_client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		cout << "create socket failed" << endl;
		WSACleanup();
		return 0;
	}

	// store server ip
	char IP[20];
	cout << "Input server ip:(192.168.0.224)" << endl;
	cin >> IP;
	memset((void*)&server_addr, 0, addr_len);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	// set server ip
	inet_pton(AF_INET, IP, (PVOID)&server_addr.sin_addr.S_un.S_addr);

	// connect with server
	if (connect(sock_client, (struct sockaddr*)&server_addr, addr_len) != 0) {
		cout << "connection failed error code:" << WSAGetLastError() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}

	// define file transfer variable
	struct fileMessage fileMsg;
	long int filelen;
	// set the directory for the receive file
	//char filename[500] = "C:\\Users\\liuqp\\source\\repos\\Test
	string filename("D:\\");
	char ok[3] = "OK";
	// reveive message buffer
	char fileBuffer[1000];

	// create file directory included by "direct.h"
	_mkdir(filename.c_str());

	// receive filename and length info of file
	if((filelen = recv(sock_client, (char*)&fileMsg, sizeof(fileMsg), 0)) <= 0) {
		cout << "do not receive filename and file length" << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}
	filelen = ntohl(fileMsg.fileSize);
	filename += fileMsg.fileName;
	cout << "file name:" << filename.c_str() << endl;
	//strcat(filename, fileMsg.fileName);
	// create file and prepare receive file content
	ofstream outFile;
	outFile.open(filename, ios::out | ios::binary);
	if (!outFile.is_open()) {
		cout << "Cannot open " << filename.c_str() << endl;
		closesocket(sock_client);
		WSACleanup();
		return 0;
	}

	// inform server has been already to receive message
	int size = 0;
	if ((size = send(sock_client, ok, sizeof(ok), 0)) < 0) {
		cout << "send message failed error code:" << WSAGetLastError() << endl;
	}
	else if (size == 0) {
		cout << "server closed socket" << endl;
	}
	else {
		cout << "message send success" << endl;
	}

	// receive and write to file
	do {
		size = recv(sock_client, fileBuffer, sizeof(fileBuffer), 0);
		outFile.write(fileBuffer, size);
		filelen -= size;
	} while (size != 0 && filelen > 0);
	
	// transfer finished.
	cout << "Transfer finished" << endl;
	outFile.close();
	// release resource
	// close connect socket
	closesocket(sock_client);
	// release winsock dll
	WSACleanup();
	cout << "hello world" << endl;
	return 0;
}


