#include"Player.h"
#include"ImageFileProcessing.h"//解决png图片透明背景变黑问题
#include"MainInterface.h"//主界面
#include"Collision.h"//判断是否碰撞
#include<graphics.h>
#include<string>
//#include<conio.h>//检测键盘输入->控制台
#include<cstdlib>
#include <vector>
#include<iostream>
#include<fstream>//文件读写
#include<stdlib.h>//引入atoi(str.c_str()) 转化成整型
using namespace std;


char s[] = "Game Over!";
int score = 0;
int HightScore = 0;
string HighRecord="0";
Player player;
Bullet playerBullet;
std::vector<Bullet> playerBullets;
//Bullet playerBullets[BULLETCOUNT];
Enemy enemies[ENEMYCOUNT];
bool Playing = true;


void InitGame()//游戏初始化
{
	player.x = WINDOWS_WIDTH / 2;
	player.y = WINDOWS_HEIGTH - 50;//位于居中底部
	player.width = PLAYER_WIDTH;
	player.height= PLAYER_HEIGTH;
	player.speed = 5;
	player.isAlive = true;
	player.live = 100;
	/*for (int i = 0; i < playerBullets.size(); i++)
	{
		playerBullet.isAlive = false;
		playerBullet.speed = 8;
		playerBullets.push_back(playerBullet);
	}*/
	for (int i = 0; i < ENEMYCOUNT; i++)
	{
		enemies[i].x = rand() % (WINDOWS_WIDTH - ENEMY_WIDTH);//避免超出窗口
		enemies[i].y = rand() % 200-200;
		enemies[i].speed = rand() % 3 + 2;
		enemies[i].isAlive = true;
	}
	//读取文件信息更改HightScore值
	fstream file;
	file.open("record.dat", ios::out | ios::in);
	if (file.is_open())
	{
		getline(file, HighRecord);
		string HighRecords;
		/*while (getline(file, HighRecords))//找到保存的数据中最大值
		{
			if (atoi(HighRecord.c_str()) < atoi(HighRecords.c_str()))
				HighRecord = HighRecords;
		}*/
		file.close();
	}
	else
	{
		cout << "打开文件失败" << endl;
		cout << "创建文件record.dat" << endl;
		file.open("record.dat", ios::out);
		file.close();
	}
}


void DrawGame()//游戏绘制
{
	setbkcolor(BLACK);
	cleardevice();
	IMAGE img[10];
	loadimage(&img[0], _T("images/background.png"), WINDOWS_WIDTH, WINDOWS_HEIGTH, true);//背景
	loadimage(&img[1], _T("images/me1.png"), PLAYER_WIDTH, PLAYER_HEIGTH, true);//玩家
	loadimage(&img[2], _T("images/bullet1.png"), 4, 4, true);//子弹
	loadimage(&img[3], _T("images/enemy1.png"), ENEMY_WIDTH, ENEMY_HEIGTH, true);//敌机1
	loadimage(&img[4], _T("images/enemy2.png"), ENEMY_WIDTH, ENEMY_HEIGTH, true);//敌机2
	loadimage(&img[5], _T("images/enemy3.png"), ENEMY_WIDTH, ENEMY_HEIGTH, true);//敌机3
	putimage(0, 0, &img[0]);
	if (player.isAlive)//玩家
	{
		setfillcolor(BLUE);
		drawAlpha(&img[1], player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGTH / 2);
		/*putimage(player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGTH / 2,&img[1]);
		fillrectangle(player.x - player.width / 2, player.y - player.height / 2,
			player.x + player.width / 2, player.y + player.height / 2);*/
	}
	setfillcolor(WHITE);
	for (int i = 0; i < playerBullets.size(); i++)//子弹
	{
		if (playerBullets[i].isAlive)
		{
			drawAlpha(&img[2], playerBullets[i].x - 2, playerBullets[i].y - 2);
			/*fillcircle(playerBullets[i].x, playerBullets[i].y, 3);
			putimage(playerBullets[i].x-2, playerBullets[i].y-2, &img[2]);*/
		}
	}
	setfillcolor(RED);
	for (int i = 0; i < ENEMYCOUNT; i++)//敌机
	{
		if (enemies[i].isAlive)
		{
			drawAlpha(&img[3], enemies[i].x, enemies[i].y);
			/*fillrectangle(enemies[i].x, enemies[i].y, enemies[i].x + ENEMY_WIDTH, enemies[i].y + ENEMY_HEIGTH);
			putimage(enemies[i].x, enemies[i].y, &img[3]);*/
		}
	}
	settextcolor(RED);
	string text = "历史最高记录: " + HighRecord;
	outtextxy(10, 10, text.c_str());//绘制历史最高记录
	text = "目前得分: " + std::to_string(score);
	outtextxy(10, 25, text.c_str());//绘制目前得分
	text = "生命：" + std::to_string(player.live);
	outtextxy(10, 40, text.c_str());//绘制目前的生命值
	FlushBatchDraw();
}


void HandleInput()//处理用户输入
{
	ExMessage msg;
		if (peekmessage(&msg, EX_KEY))
		{
			if (msg.message == WM_KEYDOWN)
			{ 
				if (msg.vkcode == VK_ESCAPE)
				{
					Playing = (Playing==TRUE)?FALSE:TRUE;
					if(Playing)mciSendString("play bgm repeat", NULL, 0, NULL);
					else mciSendString("pause bgm", NULL, 0, NULL);
					return;
				}
				if (!Playing)return;
				switch (msg.vkcode)
				{
				case VK_UP:
					if (player.y - player.height / 2 > 0)player.y -= player.speed;
					break;
				case VK_DOWN:
					if (player.y + player.height / 2 < WINDOWS_HEIGTH)player.y += player.speed;
					break;
				case VK_LEFT:
					if (player.x - player.width / 2 > 0)player.x -= player.speed;
					break;
				case VK_RIGHT:
					if (player.x + player.height / 2 < WINDOWS_WIDTH)player.x += player.speed;
					break;
				case 'W':
					if (player.y - player.height / 2 > 0)player.y -= player.speed;
					break;
				case 'S':
					if (player.y + player.height / 2 < WINDOWS_HEIGTH)player.y += player.speed;
					break;
				case 'A':
					if (player.x - player.width / 2 > 0)player.x -= player.speed;
					break;
				case 'D':
					if (player.x + player.height / 2 < WINDOWS_WIDTH)player.x += player.speed;
					break;
				//case VK_ESCAPE:
				//	while (peekmessage(&msg, EX_KEY))
				//	{
				//		if (msg.vkcode == VK_SPACE)
				//			break;
				//	}
				//	/*Sleep(10000);  //结束游戏
				//	mciSendString("close bgm", NULL, 0, NULL);
				//	closegraph();*/
				//	break;
				case VK_SPACE:
					/*BULLETCOUNT++;*/
					playerBullet.x = player.x;
					playerBullet.y = player.y - player.height / 2;
					playerBullet.isAlive = true;
					playerBullet.speed = 8;
					playerBullets.push_back(playerBullet);
					/*for (int i = 0; i < BULLETCOUNT; i++)
					{
						if (!playerBullets[i].isAlive)
						{
							playerBullets[i].x = player.x;
							playerBullets[i].y = player.y- player.height / 2;
							playerBullets[i].isAlive = true;
							break;
						}
					}*/
					break;
				default:break;
				}
			}
		}
}


void UpdateGame()//用来实现游戏运动逻辑（移动碰撞重生）
{
	if (Playing)
	{
		for (int i = 0; i < playerBullets.size(); i++)//子弹
		{
			if (playerBullets[i].isAlive)
			{
				playerBullets[i].y -= playerBullets[i].speed;
				if (playerBullets[i].y < 0)//超出屏幕的子弹
					playerBullets.erase(playerBullets.begin() + i);
			}
		}
		for (int i = 0; i < ENEMYCOUNT; i++)//敌机
		{
			if (enemies[i].isAlive)
			{
				enemies[i].y += enemies[i].speed;
				if (enemies[i].y > WINDOWS_HEIGTH)//敌机超出屏幕时
				{
					enemies[i].x = rand() % (WINDOWS_WIDTH - ENEMY_WIDTH);//重新生成敌机
					enemies[i].y = rand() % 200 - 200;
					enemies[i].speed = rand() % 3 + 2;
				}
			}
		}
		//子弹与敌机碰撞
		for (int i = 0; i < playerBullets.size(); i++)//子弹
		{
			for (int j = 0; j < ENEMYCOUNT; j++)//敌机
			{
				if (playerBullets[i].isAlive && IsCollide(playerBullets[i].x - 1, playerBullets[i].y - 1, 2, 2,
					enemies[j].x, enemies[j].y, ENEMY_WIDTH, ENEMY_HEIGTH) && enemies[j].isAlive)
				{
					//playerBullets[i].isAlive = false;
					playerBullets.erase(playerBullets.begin() + i);//碰撞过的子弹删除
					enemies[j].isAlive = false;
					score++;
					enemies[j].x = rand() % (WINDOWS_WIDTH - ENEMY_WIDTH);//重新生成敌机
					enemies[j].y = rand() % 200 - 200;
					enemies[i].speed = rand() % 3 + 2;
					enemies[j].isAlive = true;
					break;
				}
			}
		}
		//玩家与敌机碰撞
		if (player.isAlive)
		{
			for (int j = 0; j < ENEMYCOUNT; j++)//敌机
			{
				if (enemies[j].isAlive)
				{
					if (IsCollide(player.x - player.width / 2, player.y - player.height / 2, player.width, player.height,
						enemies[j].x, enemies[j].y, ENEMY_WIDTH, ENEMY_HEIGTH))
					{
						enemies[j].isAlive = false;
						player.live -= 50;
						if (player.live <= 0)
						{
							player.isAlive = false;
							settextcolor(RED);
							outtextxy(180, 100, s);
							FlushBatchDraw();
							Sleep(2000);
							//保存历史最高纪录
							if (score > atoi(HighRecord.c_str()))
							{
								fstream file;
								file.open("record.dat", ios::out);  //会覆盖原本的记录
								if (file.is_open())
								{
									file << score << endl;
								}
								file.close();
							}
							Load_MainInterface();
							/*exit(0);*/
						}
					}
				}
			}
		}
	}
}

void start()//开始游戏
{
	InitGame();
	BeginBatchDraw();
	while (1)
	{
		HandleInput();
		UpdateGame();
		DrawGame();
		Sleep(1000 / 60);
	}
	EndBatchDraw();
}

void end()
{
	DrawGame();
	IMAGE img[2];
	loadimage(&img[0], _T("images/again.png"), WINDOWS_WIDTH, WINDOWS_HEIGTH, true);
	loadimage(&img[1], _T("images/gameover.png"), WINDOWS_WIDTH, WINDOWS_HEIGTH, true);
}