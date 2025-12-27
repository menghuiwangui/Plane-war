#include<graphics.h>
#include<iostream>
#include<string>
#include"MainInterface.h"
#include"Player.h"
int Load_Music()
{
	MCIERROR err = mciSendString("open \"assets/1.mp3\" alias bgm", NULL, 0, NULL);
	if (err != 0) {
		char errorMsg[128];
		mciGetErrorString(err, errorMsg, sizeof(errorMsg));
		std::cerr << "打开文件失败: " << errorMsg << std::endl;
		return 1;
	}
	mciSendString("play bgm repeat", NULL, 0, NULL);// 循环播放音频
}
void Load_MainInterface()
{
	Load_Music();
	IMAGE img;
	loadimage(&img, _T("images/background.png"), WINDOWS_WIDTH, WINDOWS_HEIGTH, true);//背景
	putimage(0, 0, &img);
	std::string text = "开始游戏";
	int text_height = textheight(text.c_str());
	int text_width = textwidth(text.c_str());
	outtextxy((WINDOWS_WIDTH-text_width)/2, (WINDOWS_HEIGTH-text_height)/2, text.c_str());
	ExMessage msg;
	while (1)
	{
		if (peekmessage(&msg, EX_MOUSE))
		{
			if (msg.message == WM_LBUTTONDOWN && msg.x >= (WINDOWS_WIDTH - text_width) / 2 && msg.x <= (WINDOWS_WIDTH - text_width) / 2 + text_width
				&& msg.y >= (WINDOWS_HEIGTH - text_height) / 2 && msg.y <= (WINDOWS_HEIGTH - text_height) / 2 + text_height)
			{
				start();//点击开始游戏后进入游玩界面
			}
		}
		
	}
}