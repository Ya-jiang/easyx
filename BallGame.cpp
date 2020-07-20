#ifndef EASYX_H
#define EASYX_H
#include<graphics.h>
#include<conio.h>
#endif
#ifndef STL_H
#define STL_H
#include<vector>
#include<deque>
#endif
#ifndef MATH_H
#define MATH_H
#include<ctime>
#include<math.h>
#endif
#ifndef WINDOWS_H
#define WINDOWS_H
#include<Windows.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
#endif
//#include<stdlib.h>

const double pi = acos(-1);
const double gen2 = sqrt(2);

const int size = 16;
const int buttonRX = size * 6;
const int buttonRY = int(size / 3);
const int buttonOneX = size * 50;
const int buttonOneY = size * 15;
const int buttonTwoX = size * 50;
const int buttonTwoY = size * 22;
const int buttonThreeX = size * 50;
const int buttonThreeY = size * 29;
const int textHeight = size * 3;

#define areaX 60
#define areaY 40
#define radiusRect 10

enum class Action{NONE,LINE,CURVE,EXPLODE,ACCELERATE};

DWORD lastTime = 0;

MOUSEMSG m;
IMAGE img;

wchar_t str[128];

const int hp = 20;
const int speed = 10;

COLORREF searcher = GREEN, attacker = YELLOW, bleeder = MAGENTA, destoryer = BROWN, exploder = RED, hider = 0x1DAE95;

class basic
{
public:
	int x;
	int y;
	int hp;
	int speed;
	int r;
	COLORREF color;
};

class player :public basic
{
public:
	bool alive;
	player(int h, int s, COLORREF color, bool alive=true)
	{
		hp = h;
		speed = s;
		this->color = color;
		r = int(round(size / 1.5));
		x = areaX * size / 2;
		y = areaY * size / 2;
		this->alive = alive;
	}
};

class ai :public basic
{
public:
	bool player2;
	enum Action aiAction;
	ai(int posx, int posy, int h, int s, int r, COLORREF c, bool p2 = false)
	{
		x = posx;
		y = posy;
		hp = h;
		speed = s;
		this->r = r;
		color = c;
		player2 = p2;
		aiAction = Action::NONE;
	}
};


class death
{
public:
	int x;
	int y;
	int r;
	int time;
	COLORREF color;
	death(int posx, int posy, int r, COLORREF c)
	{
		x = posx;
		y = posy;
		this->r = r;
		time = 10;
		color = c;
	}
};

class buff
{
public:
	int x;
	int y;
	int buffTime;
	int hp;
	int speed;
	int score;
	int aiSpeed;
	bool aiStop;
	COLORREF color;
	buff(int x,int y,int h, int sp, int sc, int aisp, bool stop,COLORREF c)
	{
		this->x = x;
		this->y = y;
		buffTime = 5;
		hp = h;
		speed = sp;
		score = sc;
		aiSpeed = aisp;
		aiStop = stop;
		color = c;
	}
};

void welcome();
void showMenu();
void choosePlayerNum();
void playMusic(bool welcome);
void stopMusic();
void survivalMode(bool twoPlayer);

//attackmode
int position[1000][650];
int winner = 0;

class bullet
{
public:
	int x;
	int y;
	int time;
	int dx;
	int dy;
	int anamy;
	bullet(int posx, int posy, int t, int speedx, int speedy, int a)
	{
		x = posx;
		y = posy;
		time = t;
		dx = speedx;
		dy = speedy;
		anamy = a;
	}
};

struct node {
	int x, y;
}pos[25];

class attackplayer :public basic
{
public:
	bool alive;
	attackplayer(int a, int b, int h, int s, COLORREF color, bool alive = true)
	{
		hp = h;
		speed = s;
		this->color = color;
		r = 10;
		x = a;
		y = b;
		this->alive = alive;
	}
};

std::vector<bullet> bullett;

bool Judge2(int a, int b);
int getRandData(int a, int b);
void attackmode();
void inline attackmoveP2(attackplayer& p1, attackplayer& p2);

int main()
{
	srand(int(time(0)));
	initgraph(size * areaX, size * areaY);
	loadimage(&img, _T("bk.jpg"), size * areaX, size * areaY);
	BeginBatchDraw();
	welcome();
	showMenu();
	closegraph();
	return 0;
}

void inline showLogo(bool welcome)
{
	int FirstCX = size*7;
	int SecondCX = size*15;
	int ThirdCX = size*7;
	int FourthCX = size*15;
	int roundX = int(size * 14.5);
	if (welcome)
	{
		FirstCX = size * 20;
		SecondCX = size * 28;
		ThirdCX = size * 20;
		FourthCX = size * 28;
		roundX = int(size * 27.5);
	}
	const int FirstCY = size*11;
	const int SecondCY = size*11;
	const int ThirdCY = size*20;
	const int FourthCY = size*20;
	const int textHeight = size * 8;
	const int roundY = size*20;
	const int roundR = size*2;
	setbkmode(TRANSPARENT);
	settextstyle(textHeight, 0, _T("黑体"));
	settextcolor(WHITE);
	outtextxy(FirstCX, FirstCY, _T("生"));
	settextcolor(LIGHTRED);
	outtextxy(SecondCX, SecondCY, _T("存"));
	settextcolor(LIGHTBLUE);
	outtextxy(ThirdCX, ThirdCY, _T("小"));
	settextcolor(WHITE);
	outtextxy(FourthCX, FourthCY, _T("球"));
	setfillcolor(0x0061eb);
	fillcircle(roundX, roundY, roundR);
	settextstyle(roundR, 0, _T("黑体"));
	settextcolor(WHITE);
	outtextxy(roundX - roundR +size, roundY - roundR +size, _T("de"));
	int borderR = size * 40;
	int borderX = size * areaX + int(borderR / 2);
	int borderY = size * areaY / 2;
	int thickness = 5;
	if (welcome)
	{
		borderX = roundX+int(size*0.4);
		borderY = roundY-int(size*0.3);
		borderR = size * 13;
		thickness = 4;
	}
	setlinestyle(PS_SOLID, thickness);
	setlinecolor(WHITE);
	circle(borderX, borderY, borderR);
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
}

void welcome()
{
	//游戏欢迎界面
	setbkcolor(BLACK);
	cleardevice();
	setlinecolor(WHITE);
	while (!_kbhit())
	{
		putimage(0, 0, &img);
		showLogo(true);
		settextstyle(size * 2, 0, _T("宋体"));
		outtextxy(areaX * size / 11*4+int(size*0.5), areaY * size / 7 * 6 , _T("按任意键继续"));
		FlushBatchDraw();
	}
	setlinecolor(0x1CAE95);
	for (int i = 0; i < areaY * size; i++)
	{
		line(0, i, areaX * size, i);
		Sleep(0.6);
		FlushBatchDraw();
	}
	setlinecolor(0x1CAE95);
}

void showMenu()
{
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	playMusic(true);
	while (true)
	{
		setbkcolor(TRANSPARENT);
		cleardevice();

		putimage(0, 0, &img);
		//展示Logo
		showLogo(false);

		settextstyle(textHeight, 0, _T("黑体"));
		//初始化三个Button
		if (m.x >= buttonOneX - buttonRX && m.x <= buttonOneX + buttonRX && m.y >= buttonOneY - buttonRY -textHeight && m.y <= buttonOneY - buttonRY)
			setfillcolor(LIGHTRED);
		else
			setfillcolor(0x1CAE95);
		solidrectangle(buttonOneX - buttonRX, buttonOneY - buttonRY, buttonOneX + buttonRX, buttonOneY + buttonRY);
		outtextxy(buttonOneX - buttonRX, buttonOneY - buttonRY- textHeight, L"生存模式");
		if (m.x >= buttonTwoX - buttonRX && m.x <= buttonTwoX + buttonRX && m.y >= buttonTwoY - buttonRY -textHeight && m.y <= buttonTwoY - buttonRY )
			setfillcolor(LIGHTBLUE);
		else
			setfillcolor(0x1CAE95);
		solidrectangle(buttonTwoX - buttonRX, buttonTwoY - buttonRY, buttonTwoX + buttonRX, buttonTwoY + buttonRY);
		outtextxy(buttonTwoX - buttonRX, buttonTwoY - buttonRY - textHeight, L"对战模式");
		if (m.x >= buttonThreeX - buttonRX && m.x <= buttonThreeX + buttonRX && m.y >= buttonThreeY - buttonRY -textHeight && m.y <= buttonThreeY - buttonRY)
			setfillcolor(LIGHTGRAY);
		else
			setfillcolor(0x1CAE95);
		solidrectangle(buttonThreeX - buttonRX, buttonThreeY - buttonRY, buttonThreeX + buttonRX, buttonThreeY + buttonRY);
		outtextxy(buttonThreeX - buttonRX, buttonThreeY - buttonRY - textHeight, L"退出游戏");

		FlushBatchDraw();
		fflush(stdin);
		FlushMouseMsgBuffer();

		//利用鼠标左键点击实现功能
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{

			if (m.x >= buttonOneX - buttonRX && m.x <= buttonOneX + buttonRX && m.y >= buttonOneY - buttonRY - textHeight && m.y <= buttonOneY - buttonRY)
			{
				choosePlayerNum();
			}

			else if (m.x >= buttonTwoX - buttonRX && m.x <= buttonTwoX + buttonRX && m.y >= buttonTwoY - buttonRY - textHeight && m.y <= buttonTwoY - buttonRY)
			{
				attackmode();
			}

			else if (m.x >= buttonThreeX - buttonRX && m.x <= buttonThreeX + buttonRX && m.y >= buttonThreeY - buttonRY - textHeight && m.y <= buttonThreeY - buttonRY)
			{
				break;
			}
		}
	}
	EndBatchDraw();
}

void inline choosePlayerNum()
{
	const int buttonRX = size * 3;
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	while (true)
	{
		//此函数与上个函数类似，不作额外注释
		cleardevice();
		putimage(0, 0, &img);
		showLogo(false);

		settextstyle(textHeight, 0, _T("黑体"));
		if (m.x >= buttonOneX - buttonRX && m.x <= buttonOneX + buttonRX && m.y >= buttonOneY - buttonRY - textHeight && m.y <= buttonOneY - buttonRY)
			setfillcolor(LIGHTRED);
		else
			setfillcolor(0x1CAE95);
		solidrectangle(buttonOneX - buttonRX, buttonOneY - buttonRY, buttonOneX + buttonRX, buttonOneY + buttonRY);
		outtextxy(buttonOneX - buttonRX, buttonOneY - buttonRY - textHeight, L"单人");
		if (m.x >= buttonTwoX - buttonRX && m.x <= buttonTwoX + buttonRX && m.y >= buttonTwoY - buttonRY - textHeight && m.y <= buttonTwoY - buttonRY)
			setfillcolor(LIGHTBLUE);
		else
			setfillcolor(0x1CAE95);
		solidrectangle(buttonTwoX - buttonRX, buttonTwoY - buttonRY, buttonTwoX + buttonRX, buttonTwoY + buttonRY);
		outtextxy(buttonTwoX - buttonRX, buttonTwoY - buttonRY - textHeight, L"双人");
		if (m.x >= buttonThreeX - buttonRX && m.x <= buttonThreeX + buttonRX && m.y >= buttonThreeY - buttonRY - textHeight && m.y <= buttonThreeY - buttonRY)
			setfillcolor(LIGHTGRAY);
		else
			setfillcolor(0x1CAE95);
		solidrectangle(buttonThreeX - buttonRX, buttonThreeY - buttonRY, buttonThreeX + buttonRX, buttonThreeY + buttonRY);
		outtextxy(buttonThreeX - buttonRX, buttonThreeY - buttonRY - textHeight, L"返回");

		FlushBatchDraw();

		fflush(stdin);
		FlushMouseMsgBuffer();
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN)
		{

			if (m.x >= buttonOneX - buttonRX && m.x <= buttonOneX + buttonRX && m.y >= buttonOneY - buttonRY - textHeight && m.y <= buttonOneY - buttonRY)
			{
				survivalMode(false);
				break;
			}

			else if (m.x >= buttonTwoX - buttonRX && m.x <= buttonTwoX + buttonRX && m.y >= buttonTwoY - buttonRY - textHeight && m.y <= buttonTwoY - buttonRY)
			{
				survivalMode(true);
				break;
			}

			else if (m.x >= buttonThreeX - buttonRX && m.x <= buttonThreeX + buttonRX && m.y >= buttonThreeY - buttonRY - textHeight && m.y <= buttonThreeY - buttonRY)
			{
				break;
			}
		}
	}
}

void inline moveP1(player& p1)
{

	if (GetKeyState('W') < 0 && GetKeyState('S') >= 0 && GetKeyState('A') < 0 && GetKeyState('D') >= 0)
	{
		p1.y -= int(round(p1.speed * size / 32 / gen2));
		p1.x -= int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') < 0 && GetKeyState('S') >= 0 && GetKeyState('A') >= 0 && GetKeyState('D') < 0)
	{
		p1.y -= int(round(p1.speed * size / 32 / gen2));
		p1.x += int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') >= 0 && GetKeyState('S') < 0 && GetKeyState('A') < 0 && GetKeyState('D') >= 0)
	{
		p1.y += int(round(p1.speed * size / 32 / gen2));
		p1.x -= int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') >= 0 && GetKeyState('S') < 0 && GetKeyState('A') >= 0 && GetKeyState('D') < 0)
	{
		p1.y += int(round(p1.speed * size / 32 / gen2));
		p1.x += int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') < 0 && GetKeyState('A') * GetKeyState('D') >= 0 && GetKeyState('S') >= 0)
	{
		p1.y -= p1.speed * size / 32;
	}
	else if (GetKeyState('S') < 0 && GetKeyState('A') * GetKeyState('D') >= 0 && GetKeyState('W') >= 0)
	{
		p1.y += p1.speed * size / 32;
	}
	else if (GetKeyState('A') < 0 && GetKeyState('W') * GetKeyState('S') >= 0 && GetKeyState('D') >= 0)
	{
		p1.x -= p1.speed * size / 32;
	}
	else if (GetKeyState('D') < 0 && GetKeyState('W') * GetKeyState('S') >= 0 && GetKeyState('A') >= 0)
	{
		p1.x += p1.speed * size / 32;
	}
}

void inline moveP2(player &p1,player& p2)
{
	//判断仅P1移动的情况
	if (GetKeyState('W') < 0 && GetKeyState('S') >= 0 && GetKeyState('A') < 0 && GetKeyState('D') >= 0)
	{
		p1.y -= int(round(p1.speed * size / 32 / gen2));
		p1.x -= int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') < 0 && GetKeyState('S') >= 0 && GetKeyState('A') >= 0 && GetKeyState('D') < 0)
	{
		p1.y -= int(round(p1.speed * size / 32 / gen2));
		p1.x += int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') >= 0 && GetKeyState('S') < 0 && GetKeyState('A') < 0 && GetKeyState('D') >= 0)
	{
		p1.y += int(round(p1.speed * size / 32 / gen2));
		p1.x -= int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') >= 0 && GetKeyState('S') < 0 && GetKeyState('A') >= 0 && GetKeyState('D') < 0)
	{
		p1.y += int(round(p1.speed * size / 32 / gen2));
		p1.x += int(round(p1.speed * size / 32 / gen2));
	}
	else if (GetKeyState('W') < 0 && GetKeyState('A') * GetKeyState('D') >= 0 && GetKeyState('S') >= 0)
	{
		p1.y -= p1.speed * size / 32;
	}
	else if (GetKeyState('S') < 0 && GetKeyState('A') * GetKeyState('D') >= 0 && GetKeyState('W') >= 0)
	{
		p1.y += p1.speed * size / 32;
	}
	else if (GetKeyState('A') < 0 && GetKeyState('W') * GetKeyState('S') >= 0 && GetKeyState('D') >= 0)
	{
		p1.x -= p1.speed * size / 32;
	}
	else if (GetKeyState('D') < 0 && GetKeyState('W') * GetKeyState('S') >= 0 && GetKeyState('A') >= 0)
	{
		p1.x += p1.speed * size / 32;
	}
	//判断仅P2移动的情况
	if (GetKeyState(VK_UP) < 0 && GetKeyState(VK_DOWN) >= 0 && GetKeyState(VK_LEFT) < 0 && GetKeyState(VK_RIGHT) >= 0)
	{
		p2.y -= int(round(p2.speed * size / 32 / gen2));
		p2.x -= int(round(p2.speed * size / 32 / gen2));
	}
	else if (GetKeyState(VK_UP) < 0 && GetKeyState(VK_DOWN) >= 0 && GetKeyState(VK_LEFT) >= 0 && GetKeyState(VK_RIGHT) < 0)
	{
		p2.y -= int(round(p2.speed * size / 32 / gen2));
		p2.x += int(round(p2.speed * size / 32 / gen2));
	}
	else if (GetKeyState(VK_UP) >= 0 && GetKeyState(VK_DOWN) < 0 && GetKeyState(VK_LEFT) < 0 && GetKeyState(VK_RIGHT) >= 0)
	{
		p2.y += int(round(p2.speed * size / 32 / gen2));
		p2.x -= int(round(p2.speed * size / 32 / gen2));
	}
	else if (GetKeyState(VK_UP) >= 0 && GetKeyState(VK_DOWN) < 0 && GetKeyState(VK_LEFT) >= 0 && GetKeyState(VK_RIGHT) < 0)
	{
		p2.y += int(round(p2.speed * size / 32 / gen2));
		p2.x += int(round(p2.speed * size / 32 / gen2));
	}
	else if (GetKeyState(VK_UP) < 0 && GetKeyState(VK_LEFT) * GetKeyState(VK_RIGHT) >= 0 && GetKeyState(VK_DOWN) >= 0)
	{
		p2.y -= p2.speed * size / 32;
	}
	else if (GetKeyState(VK_DOWN) < 0 && GetKeyState(VK_LEFT) * GetKeyState(VK_RIGHT) >= 0 && GetKeyState(VK_UP) >= 0)
	{
		p2.y += p2.speed * size / 32;
	}
	else if (GetKeyState(VK_LEFT) < 0 && GetKeyState(VK_UP) * GetKeyState(VK_DOWN) >= 0 && GetKeyState(VK_RIGHT) >= 0)
	{
		p2.x -= p2.speed * size / 32;
	}
	else if (GetKeyState(VK_RIGHT) < 0 && GetKeyState(VK_UP) * GetKeyState(VK_DOWN) >= 0 && GetKeyState(VK_LEFT) >= 0)
	{
		p2.x += p2.speed * size / 32;
	}
}

void inline printInf(player& p1, player& p2,int aiSize , DWORD time, int scoreP1, int scoreP2,int score, bool twoPlayer)
{
	const int buttonRX = size * 6;
	const int buttonRY = int(size / 3);
	const int desOneX = size * 25;
	const int desOneY = size * 6;
	const int desTwoX = size * 25;
	const int desTwoY = size * 16;
	const int desThreeX = size * 25;
	const int desThreeY = size * 26;
	const int desHeight = textHeight - size;
	settextstyle(desHeight, 0, _T("黑体"));
	setlinestyle(PS_SOLID, 1);
	setlinecolor(WHITE);
	while (GetKeyState(VK_RETURN)>=0)
	{
		cleardevice();
		putimage(0, 0, &img);
		if ((twoPlayer && (p1.alive || p2.alive)) || (!twoPlayer && p1.alive))
		{
			wsprintf(str, _T("游戏暂停"));
			outtextxy(int(areaX * size / 3 + size*3), int(areaY * size / 15 * 1), str);
		}
		else
		{
			wsprintf(str, _T("游戏结束"));
			outtextxy(int(areaX * size / 3 + size*3), int(areaY * size / 15 * 1), str);
		}
		if (twoPlayer)
		{
			//玩家1
			if (p1.alive)
			{
				setfillcolor(0x189280);
				solidroundrect(desOneX - 5 * desHeight, int(desOneY - 0.5 * desHeight), desThreeX + 7 * desHeight, int(desOneY + 3.7 * desHeight), radiusRect, radiusRect);
				setfillcolor(p1.color);
				solidcircle(desOneX-2*desHeight, int(desOneY+1.5*desHeight), desHeight);
				wsprintf(str, _T("HP：%d"), p1.hp);
				outtextxy(desOneX, desOneY, str);
				wsprintf(str, _T("速度：%d"), p1.speed);
				outtextxy(desOneX, desOneY + desHeight, str);
				wsprintf(str, _T("分数：%d"), scoreP1);
				outtextxy(desOneX, desOneY + desHeight * 2, str);
			}
			else
			{
				setfillcolor(0x189280);
				solidroundrect(desOneX - 5 * desHeight, int(desOneY - 0.5 * desHeight), desThreeX + 7 * desHeight, int(desOneY + 3.7 * desHeight), radiusRect, radiusRect);
				setfillcolor(DARKGRAY);
				solidcircle(desOneX - 2 * desHeight,int( desOneY + 1.5*desHeight), desHeight);
				wsprintf(str, _T("玩家1已阵亡"));
				outtextxy(desOneX, desOneY + desHeight, str);
			}
			setfillcolor(LIGHTRED);
			solidrectangle(desOneX-4*desHeight, desOneY + desHeight * 3, desOneX + 2 * buttonRX, desOneY + desHeight * 3 + 2 * buttonRY);
			//玩家2
			if (p2.alive)
			{
				setfillcolor(0x189280);
				solidroundrect(desTwoX - 5 * desHeight, int(desTwoY - 0.5 * desHeight), desTwoX + 7 * desHeight, int(desTwoY + 3.7 * desHeight), radiusRect, radiusRect);
				setfillcolor(p2.color);
				solidrectangle(desTwoX - 3 * desHeight, int(desTwoY + 0.5 * desHeight), desTwoX - 1 * desHeight, int(desTwoY + 2.5 * desHeight));
				wsprintf(str, _T("HP：%d"), p2.hp);
				outtextxy(desTwoX, desTwoY, str);
				wsprintf(str, _T("速度：%d"), p2.speed);
				outtextxy(desTwoX, desTwoY + desHeight, str);
				wsprintf(str, _T("分数：%d"), scoreP2);
				outtextxy(desTwoX, desTwoY + desHeight * 2, str);
			}
			else
			{
				setfillcolor(0x189280);
				solidroundrect(desTwoX - 5 * desHeight, int(desTwoY - 0.5 * desHeight), desTwoX + 7 * desHeight, int(desTwoY + 3.7 * desHeight), radiusRect, radiusRect);
				setfillcolor(DARKGRAY);
				solidrectangle(desTwoX - 3 * desHeight, int(desTwoY + 0.5 * desHeight), desTwoX - 1 * desHeight, int(desTwoY + 2.5 * desHeight));
				wsprintf(str, _T("玩家2已阵亡"));
				outtextxy(desTwoX, desTwoY + desHeight, str);
			}
			setfillcolor(LIGHTBLUE);
			solidrectangle(desTwoX - 4 * desHeight, desTwoY + desHeight * 3, desTwoX + 2 * buttonRX, desTwoY + desHeight * 3 + 2 * buttonRY);
			//模式信息
			setfillcolor(0x189280);
			solidroundrect(desThreeX - 5 * desHeight, int(desThreeY - 0.5 * desHeight), desThreeX + 7 * desHeight, int(desThreeY + 3.7 * desHeight), radiusRect, radiusRect);
			setfillcolor(LIGHTGREEN);
			solidroundrect(desThreeX - 3 * desHeight, int(desThreeY + 0.5 * desHeight), desThreeX - 1 * desHeight, int(desThreeY + 2.5 * desHeight), radiusRect, radiusRect);
			wsprintf(str, _T("敌人数量：%d"), aiSize);
			outtextxy(desThreeX, desThreeY, str);
			wsprintf(str, _T("游戏时间：%ds"), time/1000);
			outtextxy(desThreeX, desThreeY + desHeight, str);
			wsprintf(str, _T("总分数：%d"), score+scoreP1+scoreP2);
			outtextxy(desThreeX, desThreeY + desHeight * 2, str);
			setfillcolor(LIGHTGRAY);
			solidrectangle(desThreeX - 4 * desHeight, desThreeY + desHeight * 3, desThreeX + 2 * buttonRX, desThreeY + desHeight * 3 + 2 * buttonRY);
		}
		else
		{
			//玩家状态
			setfillcolor(0x189280);
			solidroundrect(desOneX - 5 * desHeight, int(desOneY - 0.5 * desHeight), desThreeX + 7 * desHeight, int(desOneY + 3.7 * desHeight), radiusRect, radiusRect);
			setfillcolor(p1.color);
			solidcircle(desOneX - 2 * desHeight, int(desOneY + 1.5 * desHeight), desHeight);
			wsprintf(str, _T("HP：%d"), p1.hp);
			outtextxy(desOneX, desOneY, str);
			wsprintf(str, _T("速度：%d"), p1.speed);
			outtextxy(desOneX, desOneY + desHeight, str);
			wsprintf(str, _T("分数：%d"), scoreP1);
			outtextxy(desOneX, desOneY + desHeight * 2, str);
			setfillcolor(LIGHTRED);
			solidrectangle(desOneX - 4 * desHeight, desOneY + desHeight * 3, desOneX + 2 * buttonRX, desOneY + desHeight * 3 + 2 * buttonRY);
			//模式信息
			setfillcolor(0x189280);
			solidroundrect(desThreeX - 5 * desHeight, int(desThreeY - 0.5 * desHeight), desThreeX + 7 * desHeight, int(desThreeY + 3.7 * desHeight), radiusRect, radiusRect);
			setfillcolor(LIGHTGREEN);
			solidroundrect(desThreeX - 3 * desHeight, int(desThreeY+0.5*desHeight) , desThreeX - 1 * desHeight, int(desThreeY + 2.5*desHeight), radiusRect, radiusRect);
			wsprintf(str, _T("敌人数量：%d"), aiSize);
			outtextxy(desThreeX, desThreeY, str);
			wsprintf(str, _T("游戏时间：%ds"), time/1000);
			outtextxy(desThreeX, desThreeY + desHeight, str);
			wsprintf(str, _T("总分数：%d"), score + scoreP1 + scoreP2);
			outtextxy(desThreeX, desThreeY + desHeight * 2, str);
			setfillcolor(LIGHTGRAY);
			solidrectangle(desThreeX - 4 * desHeight, desThreeY + desHeight * 3, desThreeX + 2 * buttonRX, desThreeY + desHeight * 3 + 2 * buttonRY);
		}
		wsprintf(str, _T("按Enter键继续"));
		outtextxy(areaX * size / 3 + size, areaY * size / 7 * 6, str);
		FlushBatchDraw();
	}
	_getch();
}

//随机并循环播放音乐
void playMusic(bool welcome)
{
	if (!welcome)
	{
		int choice = rand() % 5;
		switch (choice)
		{
		case 0:
			::mciSendString(_T("open game0.mp3 alias start"), NULL, 0, NULL);
			::mciSendString(_T("play start repeat"), NULL, 0, NULL);
		case 1:
			::mciSendString(_T("open game1.mp3 alias start"), NULL, 0, NULL);
			::mciSendString(_T("play start repeat"), NULL, 0, NULL);
		case 2:
			::mciSendString(_T("open game2.mp3 alias start"), NULL, 0, NULL);
			::mciSendString(_T("play start repeat"), NULL, 0, NULL);
		case 3:
			::mciSendString(_T("open game3.mp3 alias start"), NULL, 0, NULL);
			::mciSendString(_T("play start repeat"), NULL, 0, NULL);
		case 4:
			::mciSendString(_T("open game4.mp3 alias start"), NULL, 0, NULL);
			::mciSendString(_T("play start repeat"), NULL, 0, NULL);
		}
	}
	else
	{
		::mciSendString(_T("open game.mp3 alias start"), NULL, 0, NULL);
		::mciSendString(_T("play start repeat"), NULL, 0, NULL);
	}
}

void stopMusic()
{
	::mciSendString(_T("close start"), NULL, 0, NULL);
}

void survivalMode(bool twoPlayer)
{
	//计时开始
	DWORD startTime = GetTickCount();
	DWORD buffTime = 0; 
	DWORD pauseTime = 0;
	//初始化信息
	player p1(hp, speed, RED);
	player p2(hp + 5, speed - 1, BLUE);
	p1.hp = hp;
	p1.speed = speed;
	p1.alive = true;
	stopMusic();
	playMusic(false);
	if (twoPlayer)
	{
		p2.hp = hp + 5;
		p2.speed = speed - 1;
		p1.x = size * areaX / 2 + 2 * size;
		p1.y = size * areaY / 2;
		p2.x = size * areaX / 2 - 2 * size;
		p2.y = size * areaY / 2;
		p2.alive = true;
	}
	else
	{
		p1.x = size * areaX / 2;
		p1.y = size * areaY / 2;
	}
	std::vector<ai> a;
	std::deque<death> d;
	std::vector<buff> b;
	std::vector<ai> aX;
	int score = 0;
	int scoreP1 = 0;
	int scoreP2 = 0;
	player* pX = 0;
	//
	while (true)
	{
		//循环初始化参数
		setbkcolor(BLACK);
		cleardevice();
		putimage(0, 0, &img);
		setlinestyle(PS_SOLID, 1);
		setlinecolor(WHITE);
		DWORD currentTime = GetTickCount() - startTime; 
		pauseTime = 0;
		settextstyle(size / 2, size / 2, _T("黑体"));
		if (twoPlayer)
			//双人模式下玩家移动
			moveP2(p1, p2);
		else
			//单人玩家移动
			moveP1(p1);

		//校正玩家坐标
		if (p1.x < 0)
			p1.x = 0;
		else if (p1.x > size * areaX)
			p1.x = size * areaX;
		if (p1.y < 0)
			p1.y = 0;
		else if (p1.y > areaY * size)
			p1.y = areaY * size;
		if (twoPlayer)
		{
			if (p2.x < 0)
				p2.x = 0;
			else if (p2.x > size * areaX)
				p2.x = size * areaX;
			if (p2.y < 0)
				p2.y = 0;
			else if (p2.y > areaY * size)
				p2.y = areaY * size;
		}

		//画出玩家
		if (p1.alive)
		{
			setfillcolor(p1.color);
			fillcircle(p1.x, p1.y, p1.r);
		}
		if (twoPlayer && p2.alive)
		{
			setfillcolor(p2.color);
			fillrectangle(p2.x - p2.r, p2.y - p2.r, p2.x + p2.r, p2.y + p2.r);
		}

		//判断玩家存活状态，便于部分敌人及时调整属性
		if (p1.alive&&!twoPlayer)
			pX = &p1;
		else if (p1.alive && p2.alive && twoPlayer)
		{
			if(p1.speed>p2.speed)
				pX = &p1;
			else
				pX = &p2;
		}
		else if(p1.alive&&!p2.alive&&twoPlayer)
			pX = &p1;
		else
			pX = &p2;

		//随机产生普通敌人
		if(a.size()<=17)//限制同屏普通敌人数量
		if (rand() % (2000 - (currentTime) / 1000) < 30)//随着玩家存活时间增加，敌人出现的可能性也会提升
		{
			int posx = rand() % areaX * size;
			int X1 = p1.x - posx;
			int X2 = p2.x - posx;
			double dis1 = pow(X1, 2) + pow(p1.y, 2);
			double dis2 = pow(X2, 2) + pow(p2.y, 2);
			//控制不同敌人出现的可能性
			int choice = rand() % 10;
			switch (choice)
			{
			case 0:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, 3, 3, int(size / 3 * 2), hider, true));
				else if(twoPlayer && p2.alive&&!p1.alive)
					a.push_back(ai(posx, -size, 3, 3, int(size / 3 * 2), hider,true));
				else
					a.push_back(ai(posx, -size, 3, 3, int(size / 3 * 2), hider, true));
				break;
			case 1:
			case 2:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 75 + 2, score / 75 + 4, size / 2, searcher, true));
				else if (twoPlayer && p2.alive && !p1.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 75 + 2, score / 75 + 4, size / 2, searcher,true));
				else
					a.push_back(ai(posx, -size, currentTime / 1000 / 75 + 2, score / 75 + 4, size / 2, searcher));
				break;
			case 3:
			case 4:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 50 + 5, pX->speed/2 - 1, size / 2, searcher, true));
				else if (twoPlayer && p2.alive && !p1.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 50 + 5, pX->speed / 2 - 1, size / 2, searcher, true));
				else
					a.push_back(ai(posx, -size, currentTime / 1000 / 50 + 5, pX->speed/2 - 1, size / 2, searcher));
				break;
			case 5:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 75 + 3, score / 50 + 4, int(round(size / 1.5)), attacker, true));
				else if (twoPlayer && p2.alive && !p1.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 75 + 3, score / 50 + 4, int(round(size / 1.5)), attacker, true));
				else
					a.push_back(ai(posx, -size, currentTime / 1000 / 75 + 3, score / 50 + 4, int(round(size / 1.5)), attacker));
				break;
			case 6:
			case 7:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 30 + 1, currentTime / 1000 / 60 + 4, size, bleeder, true));
				else if (twoPlayer && p2.alive && !p1.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 30 + 1, currentTime / 1000 / 60 + 4, size, bleeder, true));
				else
					a.push_back(ai(posx, -size, currentTime / 1000 / 30 + 1, currentTime / 1000 / 60 + 4, size, bleeder));
				break;
			case 8:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 50 + 5, score / 100 + 4, size, destoryer, true));
				else if (twoPlayer && p2.alive && !p1.alive)
					a.push_back(ai(posx, -size, currentTime / 1000 / 50 + 5, score / 100 + 4, size, destoryer, true));
				else
					a.push_back(ai(posx, -size, currentTime / 1000 / 50 + 5, score / 100 + 4, size, destoryer));
				break;
			case 9:
				if (twoPlayer && dis2 < dis1 && p2.alive)
					a.push_back(ai(posx, -size, 1, currentTime / 1000 / 40 + 5, size / 2, exploder, true));
				else if (twoPlayer && p2.alive && !p1.alive)
					a.push_back(ai(posx, -size, 1, currentTime / 1000 / 40 + 5, size / 2, exploder, true));
				else
					a.push_back(ai(posx, -size, 1, currentTime / 1000 / 40 + 5, size / 2, exploder));
				break;
			}
		}

		//随着游戏的进行，将有更大几率产生特殊敌人
		if (rand() % (2000 - (score) / 10) < 20)
		{
			int posx = rand() % areaX * size;
			int posy = rand() % areaY * size;
			int X1 = p1.x - posx;
			int X2 = p2.x - posx;
			int Y1 = p1.y - posy;
			int Y2 = p2.y - posy;
			int choice = rand() % 10;
			switch (choice)
			{
			case 0:
				aX.push_back(ai(-size, posy, 10, 5, size / 2, searcher));
				break;
			case 1:
			case 2:
				aX.push_back(ai(posx, size * areaY + size, 10, 4, size / 2, attacker));
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				aX.push_back(ai(size * areaX + size, posy, 10, 4, size / 2, bleeder));
				break;
			case 7:
			case 8:
			case 9:
				if (score >= 10)
				{
					if (sqrt(pow(X1, 2)) + sqrt(pow(Y1, 2)) >= p1.r)
					{
						if (twoPlayer)
						{
							if (sqrt(pow(X2, 2)) + sqrt(pow(Y2, 2)) >= p2.r)
								aX.push_back(ai(posx, posy, 4, 5, size / 2, exploder));
							else
								break;
						}
						else
							aX.push_back(ai(posx, posy, 5, 5, size / 2, exploder));
					}
					else
						break;
				}
				break;
			}

		}

		//定义特殊敌人行为
		for (int i = 0; i < int(aX.size()); ++i)
		{
			if (aX[i].aiAction == Action::NONE)
			{
				int choice = rand() % 10;
				switch (choice)
				{
				case 0:
				case 1:
				case 2:
					aX[i].aiAction = Action::LINE;
					break;
				case 3:
				case 4:
					aX[i].aiAction = Action::ACCELERATE;
					break;
				case 5:
				case 6:
				case 7:
				case 8:
					aX[i].aiAction = Action::CURVE;
					break;
				case 9:
					aX[i].aiAction = Action::EXPLODE;
					break;
				}
			}
		}

		//判断特殊敌人是否对玩家造成伤害
		for (int i = 0; i < int(aX.size()); ++i)
		{
			if (p1.alive)
			{
				int dx1 = aX[i].x - p1.x;
				int dy1 = aX[i].y - p1.y;
				int dis1 = aX[i].r + p1.r;
				if (dx1 * dx1 + dy1 * dy1 < dis1 * dis1 && p1.alive)
				{
					p1.hp -= int(aX[i].hp * aX[i].speed * 0.5);
					death tmp(aX[i].x, aX[i].y, aX[i].r, aX[i].color);
					d.push_back(tmp);
					aX.erase(aX.begin() + i);
					i--;
					continue;
				}
			}
			if (twoPlayer && p2.alive)
			{
				int dx2 = aX[i].x - p2.x;
				int dy2 = aX[i].y - p2.y;
				int dis2 = aX[i].r + p2.r;
				if (dx2 * dx2 + dy2 * dy2 < dis2 * dis2)
				{
					p2.hp -= int(aX[i].hp * aX[i].speed *0.5);
					death tmp(aX[i].x, aX[i].y, aX[i].r, aX[i].color);
					d.push_back(tmp);
					aX.erase(aX.begin() + i);
					--i;
					continue;
				}
			}
		}

		//随机产生Buff
		if(b.size()<=10)//限制同屏Buff数量
		if (rand() % (2000 - (currentTime) / 1000) < 15)//随着玩家的游戏时间，Buff出现的可能性也会提升
		{
			int choice = rand() % 10;
			switch (choice)//所有Buff产生的几率为debuff的两倍
			{
			case 0:
			case 1:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, 2, 0, 1, 0, false, LIGHTGREEN));
				break;
			case 2:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, -1, 0, -1, 0, false, LIGHTRED));
				break;
			case 3:
			case 4:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, 0, 1, 1, 0, false, LIGHTGREEN));
				break;
			case 5:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, 0, -1, -1, 0, false, LIGHTRED));
				break;
			case 6:
			case 7:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, 0, 0, 1, -1, false, LIGHTGREEN));
				break;
			case 8:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, 0, 0, -1, 1, false, LIGHTRED));
				break;
			case 9:
				b.push_back(buff(rand() % areaX * size, rand() % areaY * size, 0, 0, 1, 0, true, CYAN));
				break;
			}
		}

		//判断Buff是否被玩家拾起
		for (int i = 0; i < int(b.size()); i++)
		{
			int dx1 = b[i].x - p1.x + size / 2;
			int dy1 = b[i].y - p1.y + size / 2;
			int dis1 = size / 2 + p1.r;
			if (dx1 * dx1 + dy1 * dy1 < dis1 * dis1 && p1.alive)
			{
				p1.hp += b[i].hp;
				p1.speed += b[i].speed;
				for (int j = 0; j < int(a.size()); ++j)
				{
					a[j].speed += b[i].aiSpeed;
				}
				if (b[i].aiStop)
				{
					buffTime = GetTickCount() + 1500 - startTime;
				}
				scoreP1++;
				death tmp(b[i].x, b[i].y, size / 2, b[i].color);
				d.push_back(tmp);
				b.erase(b.begin() + i);
				i--;
				continue;
			}
			if (twoPlayer && p2.alive)
			{
				int dx2 = b[i].x - p2.x + size / 2;
				int dy2 = b[i].y - p2.y + size / 2;
				int dis2 = size / 2 + p2.r;
				if (dx2 * dx2 + dy2 * dy2 < dis2 * dis2)
				{
					p2.hp += b[i].hp;
					p2.speed += b[i].speed;
					for (int j = 0; j < int(a.size()); ++j)
					{
						a[j].speed += b[i].aiSpeed;
					}
					if (b[i].aiStop)
					{
						buffTime = GetTickCount() + 1500 - startTime;
					}
					scoreP2++;
					death tmp(b[i].x, b[i].y, size / 2, b[i].color);
					d.push_back(tmp);
					b.erase(b.begin() + i);
					i--;
					continue;
				}
			}
		}

		//Buff存在一定的出现时间
		for (int i = 0; i < int(b.size()); ++i)
		{
			if (currentTime % 2000 == 0)
			{
				b[i].buffTime -= 1;
				if (b[i].buffTime <= 0)
				{
					death tmp(b[i].x + size / 2, b[i].y + size / 2, size / 2, b[i].color);
					d.push_back(tmp);
					b.erase(b.begin() + i);
				}
			}
		}

		//判断普通敌人是否与玩家接触并根据条件移动普通敌人
		for (int i = 0; i < int(a.size()); ++i)
		{
			if (p1.alive)
			{
				int dx1 = a[i].x - p1.x;
				int dy1 = a[i].y - p1.y;
				int dis1 = a[i].r + p1.r;
				if (dx1 * dx1 + dy1 * dy1 < dis1 * dis1 && p1.alive)
				{
					p1.hp -= int(a[i].hp * a[i].speed * 0.5);
					death tmp(a[i].x, a[i].y, a[i].r, a[i].color);
					d.push_back(tmp);
					a.erase(a.begin() + i);
					i--;
					continue;
				}
			}
			double rad = 0;
			if (twoPlayer)
			{
				if (p2.alive)
				{
					int dx2 = a[i].x - p2.x;
					int dy2 = a[i].y - p2.y;
					int dis2 = a[i].r + p2.r;
					if (dx2 * dx2 + dy2 * dy2 < dis2 * dis2)
					{
						p2.hp -= int(a[i].hp * a[i].speed * 0.5);
						death tmp(a[i].x, a[i].y, a[i].r, a[i].color);
						d.push_back(tmp);
						a.erase(a.begin() + i);
						--i;
						continue;
					}
				}
				if (a[i].player2 && p2.alive)
				{
					if (a[i].x == p2.x)
					{
						if (a[i].x > p2.x)
						{
							rad = -pi / 2;
						}
						else
						{
							rad = pi / 2;
						}
					}
					else
					{
						rad = atan((1.0 * a[i].y - 1.0 * p2.y) / (1.0 * a[i].x - 1.0 * p2.x));
						if (p2.x < a[i].x)
						{
							rad += pi;
						}
					}
					goto P2;
				}
			}
			if (p1.alive)
			{
				if (a[i].x == p1.x)
				{
					if (a[i].x > p1.x)
					{
						rad = -pi / 2;
					}
					else
					{
						rad = pi / 2;
					}
				}
				else
				{
					rad = atan((1.0 * a[i].y - 1.0 * p1.y) / (1.0 * a[i].x - 1.0 * p1.x));
					if (p1.x < a[i].x)
					{
					rad += pi;
					}
				}
			}
			else
			{
				for (int i = 0; i<int(a.size()); ++i)
				{
					a[i].player2 = true;
				}
			}
P2:			if (currentTime >= buffTime)
			{
				a[i].x += int(round(a[i].speed * 0.8 * cos(rad)));
				a[i].y += int(round(a[i].speed * 0.8 * sin(rad)));
			}
		}

		//生存模式下，敌人HP随着时间的减少而减少
		for (int i = 0; i < int(a.size()); ++i)
		{
			if (currentTime % 2000 == 0)
			{
				a[i].hp -= 1;
				if (a[i].hp <= 0)
				{
					death tmp(a[i].x, a[i].y, a[i].r, a[i].color);
					d.push_back(tmp);
					a.erase(a.begin() + i);
					score++;
				}
			}
		}
		for (int i = 0; i < int(aX.size()); ++i)
		{
			if (currentTime % 2000 == 0)
			{
				aX[i].hp -= 1;
				if (aX[i].hp <= 0)
				{
					death tmp(aX[i].x, aX[i].y, aX[i].r, aX[i].color);
					d.push_back(tmp);
					aX.erase(aX.begin() + i);
					score++;
				}
			}
		}

		//在游戏到一定进程之后，玩家拥有自动回复HP的能力
		if (currentTime / 1000 >= 400 && score >= 250)
		{
			if (currentTime % 1000 == 0)
			{
				if (p1.alive)
					p1.hp += 10;
				if (twoPlayer && p2.alive)
				{
					p2.hp += 10;
				}
			}
		}
		else if (currentTime / 1000 >= 300 && score >= 150)
		{
			if (currentTime % 2000 == 0)
			{
				if (p1.alive)
					p1.hp += 5;
				if (twoPlayer && p2.alive)
				{
					p2.hp += 5;
				}
			}
		}
		else if (currentTime / 1000 >= 170 && score >= 70)
		{
			if (currentTime % 2000 == 0)
			{
				if (p1.alive)
					p1.hp += 3;
				if (twoPlayer && p2.alive)
				{
					p2.hp += 3;
				}
			}
		}
		else if (currentTime / 1000 >= 80 && score >= 30)
		{
			if (currentTime % 2000 == 0)
			{
				if (p1.alive)
					p1.hp += 1;
				if (twoPlayer && p2.alive)
				{
					p2.hp += 1;
				}
			}
		}

		//单一玩家死亡判定
		if (p1.hp <= 0 && p1.alive && !twoPlayer)
		{
			p1.hp = 0;
			p1.alive = false;
		}
		if (p1.hp <= 0 && p1.alive && twoPlayer)
		{
			death temp(p1.x, p1.y, p1.r, p1.color);
			d.push_back(temp);
			p1.hp = 0;
			p1.alive = false;
		}
		if (twoPlayer && p2.hp <= 0 && p2.alive)
		{
			death temp(p2.x, p2.y, p2.r, p2.color);
			d.push_back(temp);
			p2.hp = 0;
			p2.alive = false;
		}

		//死亡动画
		for (int i = 0; i < int(d.size()); ++i)
		{
			d[i].time--;
			if (d[i].time == 0)
			{
				d.pop_front();
				i--;
			}
			else
			{
				setfillcolor(d[i].color);
				fillcircle(d[i].x, d[i].y, d[i].r * d[i].time / 10);
			}
		}


		//画出每一个普通敌人
		for (int i = 0; i < int(a.size()); ++i)
		{
			setfillcolor(a[i].color);
			if (a[i].color == attacker || a[i].color == exploder)
				fillrectangle(a[i].x - a[i].r, a[i].y - a[i].r, a[i].x + a[i].r, a[i].y + a[i].r);
			else if (a[i].color == hider && score <= 70)
			{
				POINT pts[] = { {a[i].x - a[i].r, a[i].y}, {a[i].x, a[i].y - a[i].r}, {a[i].x + a[i].r, a[i].y},{a[i].x,a[i].y + a[i].r} };
				fillpolygon(pts, 4);
				DeleteObject(pts);
			}
			else if (a[i].color == hider)//随着游戏的进行，hider将变得更难可见
			{
				POINT pts[] = { {a[i].x - a[i].r, a[i].y}, {a[i].x, a[i].y - a[i].r}, {a[i].x + a[i].r, a[i].y},{a[i].x,a[i].y + a[i].r} };
				solidpolygon(pts, 4);
				DeleteObject(pts);
			}
			else
				fillcircle(a[i].x, a[i].y, a[i].r);
		}

		//定义每一个特殊敌人的轨迹
		if(currentTime>=buffTime)
		for (int i = 0; i<int(aX.size()); ++i)
		{
			switch (aX[i].aiAction)
			{
			case Action::LINE:
				if (aX[i].color == searcher)
				{
					aX[i].x += aX[i].speed;
					break;
				}
				else if (aX[i].color == attacker)
				{
					aX[i].y -= aX[i].speed;
					break;
				}
				else if (aX[i].color == bleeder)
				{
					aX[i].x -= aX[i].speed;
					break;
				}
				else if (aX[i].color == exploder)
				{
					aX[i].aiAction = Action::EXPLODE;
					break;
				}
			case Action::ACCELERATE:
				if (aX[i].color == searcher)
				{
					if (currentTime % 200 == 0)
						aX[i].speed += 1;
					aX[i].x += int(aX[i].speed);
					break;
				}
				else if (aX[i].color == attacker)
				{
					if (currentTime % 200 == 0)
						aX[i].speed += 1;
					aX[i].y -= int(aX[i].speed);
					break;
				}
				else if (aX[i].color == bleeder)
				{
					if (currentTime % 200 == 0)
						aX[i].speed += 1;
					aX[i].x -= int(aX[i].speed);
					break;
				}
				else if (aX[i].color == exploder)
				{
					aX[i].aiAction = Action::EXPLODE;
					break;
				}
			case Action::CURVE:
				if (aX[i].color == searcher)
				{
					aX[i].x += aX[i].speed;
					aX[i].y += int(aX[i].speed * 10 * sin(currentTime / 100));
					break;
				}
				else if (aX[i].color == attacker)
				{
					aX[i].y -= aX[i].speed;
					aX[i].x += int(aX[i].speed *10 * sin(currentTime / 100));
					break;
				}
				else if (aX[i].color == bleeder)
				{
					aX[i].x -= aX[i].speed;
					aX[i].y += int(aX[i].speed * 10 * sin(currentTime / 100));
					break;
				}
				else if (aX[i].color == exploder)
				{
					aX[i].aiAction = Action::EXPLODE;
					break;
				}
			case Action::EXPLODE:
				break;
			}
		}

		//画出每一个特殊敌人
		for (int i = 0; i < int(aX.size()); ++i)
		{
			setfillcolor(aX[i].color);
			if (aX[i].color == exploder)
			{
				POINT pts[] = { {aX[i].x - aX[i].r, aX[i].y+int(aX[i].r/2)}, {aX[i].x, aX[i].y - aX[i].r}, {aX[i].x + aX[i].r, aX[i].y+int(aX[i].r/2)}};
				fillpolygon(pts, 3);
				DeleteObject(pts);
			}
			else if (aX[i].color == bleeder)
			{
				POINT pts[] = { {aX[i].x - aX[i].r, aX[i].y}, {aX[i].x, aX[i].y - aX[i].r}, {aX[i].x + aX[i].r, aX[i].y},{aX[i].x,aX[i].y + aX[i].r} };
				fillpolygon(pts, 4);
				DeleteObject(pts);
			}
			else
				fillcircle(aX[i].x, aX[i].y, aX[i].r);
		}

		//画出每一个Buff
		for (int i = 0; i < int(b.size()); ++i)
		{
			setfillcolor(b[i].color);
			if (b[i].hp != 0)
			{
				fillroundrect(b[i].x, b[i].y, b[i].x + size, b[i].y + size, radiusRect, radiusRect);
				outtextxy(b[i].x, b[i].y, _T("HP"));
			}
			else if (b[i].speed != 0)
			{
				fillroundrect(b[i].x, b[i].y, b[i].x + size, b[i].y + size, radiusRect, radiusRect);
				outtextxy(b[i].x, b[i].y, _T("SP"));
			}
			else if (b[i].aiSpeed != 0)
			{
				fillroundrect(b[i].x, b[i].y, b[i].x + size, b[i].y + size, radiusRect, radiusRect);
				outtextxy(b[i].x, b[i].y, _T("AP"));
			}
			else if (b[i].aiStop != 0)
			{
				fillroundrect(b[i].x, b[i].y, b[i].x + size, b[i].y + size, radiusRect, radiusRect);
				outtextxy(b[i].x, b[i].y, _T("AS"));
			}
		}

		FlushBatchDraw();
		//按ESC键暂停游戏,并显示情况
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			pauseTime = GetTickCount();
			printInf(p1, p2, a.size() + aX.size(), currentTime, scoreP1, scoreP2,score,  twoPlayer);
			pauseTime = GetTickCount() - pauseTime;
			startTime += pauseTime;
		}

		FlushMouseMsgBuffer();
		fflush(stdin);

		Sleep(40);
		//如果玩家生命值不足,将结束游戏,计时结束
		if (twoPlayer && p1.hp <= 0 && p2.hp <= 0)
		{
			DWORD endTime = GetTickCount();
			lastTime = endTime - startTime;
			break;
		}
		if (!twoPlayer && p1.hp <= 0)
		{
			DWORD endTime = GetTickCount();
			lastTime = endTime - startTime;
			break;
		}
	}
	setlinecolor(0x1CAE95);
	for (int i = 0; i < areaY * size; i++)
	{
		line(0, i, areaX * size, i);
		Sleep(0.9);
		FlushBatchDraw();
	}
	FlushBatchDraw();
	stopMusic();
	printInf(p1, p2, a.size() + aX.size(), lastTime, scoreP1, scoreP2,score, twoPlayer);
	_getch();
	setlinecolor(0x1CAE95);
	playMusic(true);
	//退场动画
	for (int i = 0; i < areaY * size; i++)
	{
		line(0, i, areaX * size, i);
		Sleep(0.9);
		FlushBatchDraw();
	}
	setlinecolor(0x1CAE95);
}

//attackModeFunction
bool Judge2(int a, int b) {
	if (position[a][b])
		return 1;
	if (position[a + 100][b])
		return 1;
	if (position[a][b + 100])
		return 1;
	if (position[a + 100][b + 100])
		return 1;
	return 0;
}

int getRandData(int a, int b)
{
	return (rand() % (b - a + 1)) + a;
}

void attackmode()
{
	//初始化信息
	attackplayer p1(20, 20, hp, speed, YELLOW);
	attackplayer p2(940, 620, hp, speed, BLUE);
	winner = 0;
	bullett.clear();

	//生成地图
	memset(position, 0, sizeof(position));
	srand((unsigned)time(NULL));
	int aa, bb;
	for (int i = 1; i <= 20; i++) {
		aa = getRandData(40, 820);
		bb = getRandData(40, 500);
		while (Judge2(aa, bb)) {
			aa = getRandData(40, 800);
			bb = getRandData(40, 500);
		}
		pos[i].x = aa;
		pos[i].y = bb;
		for (int j = aa; j <= aa + 100; j++)
			for (int k = bb; k <= bb + 100; k++) {
				position[j][k] = 1;
			}
	}

	//开始游戏
	while (true)
	{
		//清空画布
		setbkcolor(BLACK);
		cleardevice();

		//双人模式下玩家移动
		attackmoveP2(p1, p2);

		//修正P1坐标
		if (p1.x < 0)
			p1.x = 0;
		else if (p1.x > size * areaX)
			p1.x = size * areaX;
		if (p1.y < 0)
			p1.y = 0;
		else if (p1.y > areaY * size)
			p1.y = areaY * size;

		//修正P2坐标
		if (p2.x < 0)
			p2.x = 0;
		else if (p2.x > size * areaX)
			p2.x = size * areaX;
		if (p2.y < 0)
			p2.y = 0;
		else if (p2.y > areaY * size)
			p2.y = areaY * size;

		//判断子弹运动情况
		for (int i = 0; i < int(bullett.size()); i++)
		{
			bullett[i].x += bullett[i].dx;
			bullett[i].y += bullett[i].dy;

			if (bullett[i].x >= 0 && bullett[i].y >= 0 && bullett[i].x <= 960 && bullett[i].y <= 640 && position[bullett[i].x][bullett[i].y]) {
				bullett.erase(bullett.begin() + i);
				i--;
				continue;
			}

			//判断是否打中玩家1
			int dx, dy;
			dx = bullett[i].x - p1.x;
			dy = bullett[i].y - p1.y;
			if (dx < 0) dx = -dx;
			if (dy < 0) dy = -dy;
			if (dx <= 12 && dy <= 12 && bullett[i].anamy == 1) {
				p1.hp -= 2;
				if (p1.hp == 0)
					winner = 2;
				bullett.erase(bullett.begin() + i);
				i--;
				continue;
			}
			//判断是否打中玩家2
			dx = bullett[i].x - p2.x;
			dy = bullett[i].y - p2.y;
			if (dx < 0) dx = -dx;
			if (dy < 0) dy = -dy;
			if (dx <= 12 && dy <= 12 && bullett[i].anamy == 2) {
				p2.hp -= 2;
				if (p2.hp == 0)
					winner = 1;
				bullett.erase(bullett.begin() + i);
				i--;
				continue;
			}

			bullett[i].time--;
			if (bullett[i].time <= 0 || bullett[i].x > 960 || bullett[i].y > 640 || bullett[i].x < 0 || bullett[i].y < 0)
			{
				bullett.erase(bullett.begin() + i);
				i--;
				continue;
			}
		}

		//显示玩家
		setfillcolor(p1.color);
		fillcircle(p1.x, p1.y, p1.r);
		setfillcolor(p2.color);
		fillcircle(p2.x, p2.y, p2.r);

		//画出地图
		setfillcolor(GREEN);
		for (int i = 1; i <= 20; i++) {
			fillrectangle(pos[i].x, pos[i].y, pos[i].x + 100, pos[i].y + 100);
		}

		//画出子弹
		setfillcolor(RED);
		for (int i = 0; i < int(bullett.size()); i++)
		{
			fillcircle(bullett[i].x, bullett[i].y, 2);
		}


		//实时显示情况
		setbkmode(TRANSPARENT);
		setbkmode(OPAQUE);

		//按ESC键exit游戏
		if (GetKeyState(VK_ESCAPE) < 0)
		{
			break;
		}

		FlushBatchDraw();
		fflush(stdin);

		Sleep(50);

		//如果玩家生命值不足，将结束游戏,计时结束
		if (p1.hp <= 0 || p2.hp <= 0)
		{
			IMAGE img;
			if (winner == 1)
			{
				loadimage(&img, _T("win1.png"), 960, 640);
			}
			else
			{
				loadimage(&img, _T("win2.png"), 960, 640);
			}
			putimage(0, 0, &img);
			break;
		}
	}//end while

	FlushBatchDraw();
	Sleep(2000);
	setlinecolor(BLACK);
	for (int i = 0; i < areaY * size; i++)
	{
		line(0, i, areaX * size, i);
		Sleep(0.9);
		FlushBatchDraw();
	}

}

void inline attackmoveP2(attackplayer& p1, attackplayer& p2)
{
	int t = 50;
	//判断仅P1移动的情况
	if (GetKeyState('W') < 0 && GetKeyState('S') >= 0 && GetKeyState('A') < 0 && GetKeyState('D') >= 0)//左上
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p1.x - d >= 0 && p1.y - d >= 0 && position[p1.x - d][p1.y - d] == 0) {
			p1.y -= d;
			p1.x -= d;
		}
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, -15, -15, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('W') < 0 && GetKeyState('S') >= 0 && GetKeyState('A') >= 0 && GetKeyState('D') < 0)//右上
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p1.x + d <= 960 && p1.y - d >= 0 && position[p1.x + d][p1.y - d] == 0) {
			p1.y -= d;
			p1.x += d;
		}
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, 15, -15, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('W') >= 0 && GetKeyState('S') < 0 && GetKeyState('A') < 0 && GetKeyState('D') >= 0)//左下
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p1.x - d >= 0 && p1.y + d <= 640 && position[p1.x - d][p1.y + d] == 0) {
			p1.y += d;
			p1.x -= d;
		}
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, -15, 15, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('W') >= 0 && GetKeyState('S') < 0 && GetKeyState('A') >= 0 && GetKeyState('D') < 0)//右下
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p1.x + d <= 960 && p1.y + d <= 640 && position[p1.x + d][p1.y + d] == 0) {
			p1.y += d;
			p1.x += d;
		}
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, 15, 15, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('W') < 0 && GetKeyState('A') * GetKeyState('D') >= 0 && GetKeyState('S') >= 0)//上
	{
		int d = speed * size / 16;
		if (p1.y - d >= 0 && position[p1.x][p1.y - d] == 0)
			p1.y -= d;
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, 0, -20, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('S') < 0 && GetKeyState('A') * GetKeyState('D') >= 0 && GetKeyState('W') >= 0)//下
	{
		int d = speed * size / 16;
		if (p1.y + d <= 640 && position[p1.x][p1.y + d] == 0)
			p1.y += d;
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, 0, 20, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('A') < 0 && GetKeyState('W') * GetKeyState('S') >= 0 && GetKeyState('D') >= 0)//左
	{
		int d = speed * size / 16;
		if (p1.x - d >= 0 && position[p1.x - d][p1.y] == 0)
			p1.x -= d;
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, -20, 0, 2);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState('D') < 0 && GetKeyState('W') * GetKeyState('S') >= 0 && GetKeyState('A') >= 0)//右
	{
		int d = speed * size / 16;
		if (p1.x + d <= 960 && position[p1.x + d][p1.y] == 0)
			p1.x += d;
		//判断攻击
		if (GetKeyState('G') < 0) {
			bullet tmpb(p1.x, p1.y, t, 20, 0, 2);
			bullett.push_back(tmpb);
		}
	}
	
	
	//判断仅P2移动的情况
	if (GetKeyState(VK_NUMPAD5) < 0 && GetKeyState(VK_NUMPAD2) >= 0 && GetKeyState(VK_NUMPAD1) < 0 && GetKeyState(VK_NUMPAD3) >= 0)//左上
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p2.x - d >= 0 && p2.y - d >= 0 && position[p2.x - d][p2.y - d] == 0) {
			p2.y -= d;
			p2.x -= d;
		}
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, -15, -15, 1);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState(VK_NUMPAD5) < 0 && GetKeyState(VK_NUMPAD2) >= 0 && GetKeyState(VK_NUMPAD1) >= 0 && GetKeyState(VK_NUMPAD3) < 0)//右上
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p2.x + d <= 960 && p2.y - d >= 0 && position[p2.x + d][p2.y - d] == 0) {
			p2.y -= d;
			p2.x += d;
		}
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, 15, -15, 1);
			bullett.push_back(tmpb);
			//exit(0);
		}
	}
	else if (GetKeyState(VK_NUMPAD5) >= 0 && GetKeyState(VK_NUMPAD2) < 0 && GetKeyState(VK_NUMPAD1) < 0 && GetKeyState(VK_NUMPAD3) >= 0)//左下
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p2.x - d >= 0 && p2.y + d <= 640 && position[p2.x - d][p2.y + d] == 0) {
			p2.y += d;
			p2.x -= d;
		}
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, -15, 15, 1);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState(VK_NUMPAD5) >= 0 && GetKeyState(VK_NUMPAD2) < 0 && GetKeyState(VK_NUMPAD1) >= 0 && GetKeyState(VK_NUMPAD3) < 0)//右下
	{
		int d = int(round(speed * size / 16 / gen2));
		if (p2.x + d <= 960 && p2.y + d <= 640 && position[p2.x + d][p2.y + d] == 0) {
			p2.y += d;
			p2.x += d;
		}
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, 15, 15, 1);
			bullett.push_back(tmpb);
			//exit(0);
		}
	}
	else if (GetKeyState(VK_NUMPAD5) < 0 && GetKeyState(VK_NUMPAD1) * GetKeyState(VK_NUMPAD3) >= 0 && GetKeyState(VK_NUMPAD2) >= 0)//上
	{
		int d = speed * size / 16;
		if (p2.y - d >= 0 && position[p2.x][p2.y - d] == 0)
			p2.y -= d;
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, 0, -20, 1);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState(VK_NUMPAD2) < 0 && GetKeyState(VK_NUMPAD1) * GetKeyState(VK_NUMPAD3) >= 0 && GetKeyState(VK_NUMPAD5) >= 0)//下
	{
		int d = speed * size / 16;
		if (p2.y + d <= 640 && position[p2.x][p2.y + d] == 0)
			p2.y += d;
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, 0, 20, 1);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState(VK_NUMPAD1) < 0 && GetKeyState(VK_NUMPAD5) * GetKeyState(VK_NUMPAD2) >= 0 && GetKeyState(VK_NUMPAD3) >= 0)//左
	{
		int d = speed * size / 16;
		if (p2.x - d >= 0 && position[p2.x - d][p2.y] == 0)
			p2.x -= d;
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, -20, 0, 1);
			bullett.push_back(tmpb);
		}
	}
	else if (GetKeyState(VK_NUMPAD3) < 0 && GetKeyState(VK_NUMPAD5) * GetKeyState(VK_NUMPAD2) >= 0 && GetKeyState(VK_NUMPAD1) >= 0)//右
	{
		int d = speed * size / 16;
		if (p2.x + d <= 960 && position[p2.x + d][p2.y] == 0)
			p2.x += d;
		//判断攻击
		if (GetKeyState(VK_ADD) < 0) {
			bullet tmpb(p2.x, p2.y, t, 20, 0, 1);
			bullett.push_back(tmpb);
		}
	}
}
