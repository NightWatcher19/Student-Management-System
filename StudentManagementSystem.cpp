#include"Database.h"
#include<stdlib.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

int main()
{
	mciSendString("open GoingOut.mp3 alias music", 0, 0, 0);
	mciSendString("play music repeat", 0, 0, 0);
	while (true)
	{
		InitWindow();
	}
	return 1;
}
