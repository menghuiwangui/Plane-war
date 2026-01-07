#pragma once 
//玩家飞机大小
#define PLAYER_WIDTH 40
#define PLAYER_HEIGTH 50
//敌机
#define ENEMYCOUNT 10
#define ENEMY_WIDTH 30
#define ENEMY_HEIGTH 40
//游戏失败提示窗
#define END_WIDTH 180
#define END_HEIGTH 300
//游戏失败选项
#define END_selection_WIDTH 100
#define END_selection_HEIGHT 30
struct Player //玩家
{
	int x, y;
	int width, height;
	int speed;
	bool isAlive;
	int live;
};
struct Bullet//子弹
{
	int x, y;
	int speed;
	bool isAlive;
};
struct Enemy//敌机
{
	int x, y;
	int speed;
	bool isAlive;
};

void InitGame();//游戏初始化
void DrawGame();//游戏绘制
void HandleInput();//处理用户输入
bool IsCollide(int x1, int y1, int w1, int h1,
	int x2, int y2, int w2, int h2);//检测两个矩形是否碰撞
void UpdateGame();//用来实现游戏运动逻辑（移动碰撞重生）
void start();//开始游戏
void end();//游戏失败的结束界面 