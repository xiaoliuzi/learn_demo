// TestProject.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#define N 100000

int ThreadF0(LPVOID lpParam)
{
	long *a = (long*)lpParam;
	for (int i = 0; i < N; ++i) {
		//InterlockedExchangeAdd(a, 1);
		(*a) +=1;
		//Sleep(3);
		//printf("0: %d\n", *a);
	}
	printf("0: %d\n", *a);
	return 0;
}

int ThreadF2(LPVOID lpParam)
{
	long *b = (long*)lpParam;
	for (int i = 0; i < N; ++i) {
		(*b) += 1;
		//InterlockedExchangeAdd(b, 1);
		//Sleep(2);
		//printf("   1: %d\n", *b);
	}
	printf("2: %d\n", *b);
	return 0;
}

int main(int argc, char *argv[])
{
	int t = 0;
	HANDLE htd0, htd1, htd2;
	DWORD thrdID0, thrdID2;
	htd0 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadF0, (void*)&t, 0, &thrdID0);
	htd1 = 0;
	//htd1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadF1, (void*)&t, 0, &thrdID1);
	htd2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadF2, (void*)&t, 0, &thrdID2);
	Sleep(1000);
	printf("t:%d\n", t);
	printf("hello, world\n");
		return 0;
	}

