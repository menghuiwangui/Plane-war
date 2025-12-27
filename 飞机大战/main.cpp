#include<iostream>
#include<graphics.h>
#include"Player.h"
#include"MainInterface.h"
#include <chrono>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
using namespace std;
int main()
{
	initgraph(WINDOWS_WIDTH, WINDOWS_HEIGTH);//打开一个窗口
	Load_MainInterface();//主界面

	//点击开始游戏后运行这部分内容

	//游戏开始运行
	start();


	mciSendString("close bgm", NULL, 0, NULL);
	closegraph();
	return 0;
}
