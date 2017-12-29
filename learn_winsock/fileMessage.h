#pragma once
#ifndef __FILE_TRANSFER_SERVER_H__
#define __FILE_TRANSFER_SERVER_H__
// define struct to store file infomation.
struct fileMessage {
	char fileName[256];
	long int fileSize;
};
#endif