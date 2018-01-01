#include <Windows.h>
#include <iostream>
using namespace std;

// define thread function without parameter
void ThreadFun1()
{
	for (int i = 0; i < 100; ++i) {
		Sleep(1000);
		cout << i << ", This is Thread 1" << endl;
	}
}

// thread handle
HANDLE hThread1;
// thread id
DWORD ThreadID1;

int main(int argc, char *argv[]) {
	// create thread, as ThreadFunc don't have parameter, 
	// so the fourth parameter of CreateThread function is NULL
	hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFun1, NULL, 0, &ThreadID1);
	for (int j = 0; j < 10; ++j) {
		Sleep(1000);
		cout << j << ", This is MainThread!" << endl;
	}
	return 0;
}