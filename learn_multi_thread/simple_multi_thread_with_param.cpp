#include <Windows.h>
#include <iostream>
using namespace std;

// define thread function without parameter
int ThreadF0(LPVOID a)
{
	for (int i = 0; i < 10; ++i) {
		Sleep(1000);
		cout << "I am Thread0, the nubmer main thread give me is" << ((int)a) << endl;
	}
	return 0;
}

int ThreadF1(LPVOID lpParam) {
	char *p = (char*)lpParam;
	Sleep(1000);
	cout << "This is Thread1, the string main thread give me is:" << p << endl;
	return 0;
}

int ThreadF2(LPVOID lpParam) {
	string *p = (string*)lpParam;
	Sleep(1000);
	cout << "This is ThreadF2, the stirng main thread give me is:" << p << endl;
	return 0;
}
// thread handle
HANDLE hThrd0, hThrd1, hThrd2;
// thread id
DWORD ThrdID0, ThrdID1, ThrdID2;

int main(int argc, char *argv[]) {
	int a = 888;
	char s1[] = "ABCDEFGH";
	string s2("abcdefgh");
	cout << "This is MainThread!" << endl;
	// create thread, as ThreadFunc don't have parameter, 
	// so the fourth parameter of CreateThread function is NULL
	hThrd0 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadF0, (void*)a, 0, &ThrdID0);
	hThrd0 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadF1, s1, 0, &ThrdID1);
	hThrd0 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadF2, (void*)&s2, 0, &ThrdID2);
	Sleep(1000);
	cout << "MainThread Exit" << endl;
	return 0;
}