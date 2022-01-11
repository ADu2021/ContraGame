#pragma once

#pragma region 头文件引用

// Windows 头文件: 
#include <windows.h>
#include <conio.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// 资源头文件
#include "resource.h"
#pragma comment(lib, "Msimg32.lib")			//图象处理的函数接口，例如：透明色的位图的绘制TransparentBlt函数


// TODO:  在此处引用程序需要的其他头文件
#include <vector>
#include <math.h>


#pragma endregion


#pragma region 宏定义

#define WINDOW_TITLEBARHEIGHT	32			//标题栏高度
#define WINDOW_WIDTH			1024		//游戏窗口宽度
#define WINDOW_HEIGHT			768			//游戏窗口高度


#define STAGE_STARTMENU			0		//开始画面的ID
#define STAGE_1					1		//第一个游戏场景的ID
#define STAGE_2					2
#define STAGE_CNT				2
#define STAGE_PAUSE				-1		//暂停界面
#define STAGE_HELP				-2
#define STAGE_SUCCESS			-3		


#define UNIT_SIZE_X				64		//单位的宽度
#define UNIT_SIZE_Y				64		//单位的高度
#define UNIT_LAST_FRAME			11		//单位的动画帧最大值

//单位阵营定义
#define UNIT_SIDE_RED			10000	//红方
#define UNIT_SIDE_BLUE			10001	//蓝方
#define UNIT_SIDE_MARINE		10002   //主角
#define UNIT_SIDE_ALLY			0
#define UNIT_SIDE_ENEMY			1


//单位类型定义
#define UNIT_TYPE_REAPER		0		//收割者
#define UNIT_TYPE_CASTER		1		//魔术师
#define UNIT_TYPE_SABER			2		//剑士
#define UNIT_TYPE_SHIELDER		3		//盾卫
#define UNIT_TYPE_HOPLITE		4		//重装步兵
#define UNIT_TYPE_MARINE        5		
#define UNIT_TYPE_PLAYER		6
#define UNIT_TYPE_BEE			7
#define UNIT_TYPE_BEE2			8
#define UNIT_TYPE_BOSS			9

//单位状态定义
#define UNIT_STATE_HOLD			0		//静止
#define UNIT_STATE_WALK			1		//行走
#define UNIT_STATE_ATTACK		2		//攻击
#define UNIT_STATE_FLY			3		//飞行

//单位方向定义
#define UNIT_DIRECT_RIGHT		0		//向右
#define UNIT_DIRECT_LEFT		1		//向左
#define UNIT_DIRECT_UPPER_LEFT	1		//左上
#define UNIT_DIRECT_LOWER_LEFT	3		//左下
#define UNIT_DIRECT_UPPER_RIGHT 0		//右上
#define UNIT_DIRECT_LOWER_RIGHT 2		//右下


//背景
#define BG_SRC_COUNT			6		//背景资源数量
#define BG_COLUMNS				16		//背景列数
#define BG_ROWS					12		//背景行数
#define BG_ROWS_SKY				3		//背景天空行数
#define BG_ROWS_LAND			9		//背景地面行数
#define BG_CELL_WIDTH			64		//背景单格宽度
#define BG_CELL_HEIGHT			64		//背景单格高度
#define BG_CITY_WIDTH			2816	
#define BG_CITY_SINGLE_WIDTH    702
#define BG_CITY_HEIGHT			1200
#define BG_STARTMENU_WIDTH		1208
#define BG_STARTMENU_HEIGHT		1208
#define BG_PAUSE_WIDTH			1024
#define BG_PAUSE_HEIGHT			768
#define BG_CASTLE_WIDTH			3072
#define BG_CASTLE_HEIGHT		768
#define BG_CASTLE_SINGLE_WIDTH	1536
#define BG_CASTLE_SINGLE_HEIGHT	768
#define BG_TUTORIAL_WIDTH		3996
#define BG_TUTORIAL_HEIGHT		768
#define BG_TUTORIAL_SINGLE_WIDTH	1998
#define BG_TUTORIAL_SINGLE_HEIGHT	768
#define BG_HELP_WIDTH			1024
#define BG_HELP_HEIGHT			768
#define BG_SUCCESS_WIDTH			1024
#define BG_SUCCESS_HEIGHT			768

//UI
#define UI_HP_WIDTH				264
#define UI_HP_HEIGHT			68
#define UI_HP_X					43
#define UI_HP_Y					9
#define UI_HP_CX				179
#define UI_HP_CY				30
#define UI_HP					1
#define UI_MP					2

//其它定义
#define BUTTON_DEFAULT_WIDTH		334		//默认按钮宽度
#define BUTTON_DEFAULT_HEIGHT		100		//默认按钮高度
#define BUTTON_STARTGAME			1001	//开始游戏按钮ID
#define BUTTON_QUITGAME				1002	//结束游戏按钮ID
#define BUTTON_RESUMEGAME			1003	//继续游戏按钮ID
#define BUTTON_HELP					1004	//帮助按钮ID
#define BUTTON_MAINMENU				1005	//返回主菜单按钮ID
#define BUTTON_RESTART				1006	//重新开始
#define BUTTON_HELPBACK				1007	//帮助界面返回主菜单

#define BULLET_WIDTH				26
#define BULLET_HEIGHT				26

#define TIMER_GAMETIMER				1		//游戏的默认计时器ID
#define TIMER_GAMETIMER_ELAPSE		30		//默认计时器刷新间隔的毫秒数
#define UNIT_SPEED					3.0		//单位行走速度	

//碰撞体类型
#define CL_RECT						1		//矩形碰撞体
#define CL_CIRCLE					2		//圆形碰撞体

//地形Terrain类型
#define TR_VISIBLE					0x1		//可见
#define TR_GROUND					0x2		//地面（与Unit.hover）有关
#define TR_TOUCH_AND_DIE			0x4		//碰到直接死的机关
#define TR_BLOCK_2					0x8		//第2种砖块地形
#define TR_SPIKE					0x10	
#define TR_NO_COLLISION				0x20	//不参与位置碰撞
#define TR_MOVING					0x40	//移动砖块
#define TR_GATE						0x80

//地形
#define TR_BLOCK1_WIDTH				36
#define TR_BLOCK1_HEIGHT			36
#define TR_BLOCK2_0_WIDTH			64
#define TR_BLOCK2_0_HEIGHT			64
#define TR_BLOCK2_1_WIDTH			64
#define TR_BLOCK2_1_HEIGHT			33
#define TR_SPIKE_WIDTH				40
#define TR_SPIKE_HEIGHT				38
#define TR_GATE_WIDTH				84
#define TR_GATE_HEIGHT				180

#define TR_SPIKE_DAMAGE				200
#define TR_SPIKE_CD					30


//武器类型
#define WP_MEELEE					0x1		//近战
#define WP_RANGED					0x2		//远程
#define WP_BULLET					0x4		//发射子弹

//主角状态
#define PLAYER_MANA_RECOVER_TIME	100
#define PLAYER_MANA_MAX				100
#define PLAYER_HP_MAX				100

#define BEE_HP_MAX					20
#define BEE2_HP_MAX					10

//速度
#define SPEED_BEE				5.0
#define SPEED_BEE2				2.5
#define SPEED_PLAYER_WALK		4.0
#define SPEED_PLAYER_RUN		7.0
#define SPEED_PLAYER_JUMP		13.0

//攻击参数
#define AT_RANGE_UNIT			125
#define AT_DAMEGE_UNIT			10

#define AT_RANGE_BEE			250
#define AT_EYESIGHT_BEE			600
#define AT_CD_BEE				50
#define AT_SPEED_BEE			13.0
#define AT_ACC_BEE				0.5
#define AT_DMG_BEE				10

#define AT_RANGE_BEE2			700
#define AT_EYESIGHT_BEE2		1000
#define AT_ESCAPE_BEE2			125
#define AT_APPROACH_BEE2		250
#define AT_CD_BEE2				100
#define AT_ACC_BEE2				0.5
#define AT_DMG_BEE2				10

#define BULLET_SPEED			5

#define BOSS_WIDTH				305
#define BOSS_HEIGHT				371
#define BOSS_HP_MAX				400
#define BOSS_SUMMON_CD			150
#define BOSS_MOVE_CD			300
#define BOSS_EYESIGHT			500

#pragma endregion


#pragma region 结构体声明

// 场景结构体
struct Stage
{
	int stageID;		//场景编号
	HBITMAP bg;			//背景图片
	int timeCountDown;	//游戏时间倒计时
	bool timerOn;		//计时器是否运行（游戏是否被暂停）

	//物理信息
	double g;			//重力加速度
	int time;			//时间（帧）
};
//UI
class UI
{
public:
	HBITMAP img;
	int x;
	int y;
	int cx;
	int cy;
	int type;
};


//碰撞体
class Collider
{
public:
	int ColliderType;
};
class RectCollider : public Collider
{
public:
	double x;
	double y;
	int cx;
	int cy;
public:
	RectCollider()
	{
		ColliderType = CL_RECT;
	}
};
class CircleCollider : public Collider
{
public:
	int x;
	int y;
	int r;
public:
	CircleCollider()
	{
		ColliderType = CL_CIRCLE;
	}
};

// 按钮结构体
struct Button
{
	int buttonID;	//按钮编号
	bool visible;	//按钮是否可见
	HBITMAP img;	//图片
	int x;			//坐标x
	int y;			//坐标y
	int width;		//宽度
	int height;		//高度
	bool pause;
};

// 单位结构体
struct Unit : public RectCollider
{
	HBITMAP img;	//图片

	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;		//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个

	int* frame_x;
	int* frame_y;
	int* frame_xb;
	int* frame_yb;
	int* frame_xc;
	int* frame_yc;


	int side;		//单位阵营
	int type;		//单位类型
	int state;		//单位状态
	int direction;	//单位方向

	double g;		//所受重力加速度

	/*
	int x;			//坐标x
	int y;			//坐标y
	int cx;			//单位的宽度
	int cy;			//单位的高度
	*/
	double vx;		//速度x
	double vy;		//速度y
	double vx_limit;//速度x上限
	double vy_limit;//速度y上限
	double ax;      //加速度x
	double ay;		//加速度y
	int health;		//生命值
	int mana;
	int maxHealth;
	int maxMana;

	bool hover;     //是否悬空

	int JumpStage;
	int JumpCount;

	int time;
	int mana_recover_time;

	int attack_range;
	int attack_damage;
	
	//敌方单位attack
	int attack;
	int attack_cd;
	int attack_x;
	int attack_y;

	bool FX1;

	int death_cnt;
	bool visible;

	bool del;
};

struct Terrain : public RectCollider
{
	HBITMAP img;	//图片 
	int img_width;
	int img_height;
	bool visible;
	
	/*以下只有背景图变化才会用到
	int frame_row;			//当前显示的是图像的第几行
	int frame_column;		//当前显示的是图像的第几列

	int* frame_sequence;		//当前的帧序列
	int frame_count;		//帧序列的长度
	int frame_id;			//当前显示的是帧序列的第几个
	*/
	int id;
	int type;

	int timestamp;
	int dx;
	int dy;
	int vx;
	int vy;
	/*
	int x;			//坐标x
	int y;			//坐标y
	int cx;			//x方向上长
	int cy;			//y方向上长
	*/

	Terrain* pre;
};

class Bullet : public RectCollider
{
public:
	int BulletType;
	int damage;
	int tarx;
	int tary;
	double vx;
	double vy;
	bool del;
};

class Weapon
{
	int WeaponType;

	Bullet* bullet;

	int price;		//价格
	bool inf_ammo;	//是否无限弹药
	int ammo;		//弹药

	Weapon(int type = 0, Bullet* weapon_bullet = NULL, int weapon_price = 0, bool weapon_inf_ammo = true, int weapon_ammo = 0x3f3f3f3f)
	{
		WeaponType = type;
		bullet = weapon_bullet;
		price = weapon_price;
		inf_ammo = weapon_inf_ammo;
		ammo = weapon_ammo;
	}
};

struct Camera		//镜头
{
	int x;
	int y;
	int cx;
	int cy;
	int limit_x;
	int limit_y;
	int limit_cx;
	int limit_cy;
	int follow_id; // 跟随的id(unit[Camera.follow_id])
	Camera(int X, int Y, int CX, int CY, int lim_x, int lim_y, int lim_cx, int lim_cy)
	{
		x = X;
		y = Y;
		cx = CX;
		cy = CY;
		limit_x = lim_x;
		limit_y = lim_y;
		limit_cx = lim_cx;
		limit_cy = lim_cy;
	}
	void move();
};

//TODO: 添加游戏需要的更多种数据（地物、砖块等）


#pragma endregion


#pragma region 事件处理函数声明


// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam);
void InitUI();

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam);

// 暂停函数
void MyPause(HWND hWnd);

#pragma endregion


#pragma region 其它游戏状态处理函数声明

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int x, int y, bool is_pause = false, int width = BUTTON_DEFAULT_WIDTH, int height = BUTTON_DEFAULT_HEIGHT);

// 添加单位函数
Unit* CreateUnit(int side, int type, int x, int y, int health, double gravity, int cx, int cy, int mana);

//	添加地形函数
Terrain* CreateTerrain(int id, int type, int x, int y, int cx, int cy, bool vis, HBITMAP bitmap, int bmp_cx, int bmp_cy, Terrain* pre);

Bullet* CreateBullet(int x, int y, int tarx, int tary, double v, int damage);

// 添加子弹函数

//  删除地形函数
void DeleteTerrain(Terrain* terrain);

//碰撞检测函数：单位和地形的碰撞检测（AABB包围盒）
int CollisionDetectionForRectAndRect(Unit* unit, std::vector<Terrain*> &Terrains, int start_id);
int CollisionDetectionForRectAndRect(Unit* unit, std::vector<Terrain*>& Bullets, int start_id);
int CollisionDetectionForRectAndRect(Bullet* unit, std::vector<Terrain*>& Terrains, int start_id);
int CollisionDetectionForRectAndRect(Unit* unit, Unit* x);

// 初始化场景函数
void InitStage(HWND hWnd, int stageID);

// 刷新单位状态函数
void UpdateUnits(HWND hWnd);
void UpdateTerrains(HWND hWnd);
void UpdateBullets(HWND hWnd);


//单位行为函数
void UnitBehaviour_Bee(Unit* unit);
void UnitBehaviour_Bee2(Unit* unit);
void UnitBehaviour_Boss(Unit* unit);
void UnitBehaviour_Player(Unit* unit);
void UnitBehaviour_1(Unit* unit);
void MyUnitBehaviour_2(Unit* unit);
void UnitBehaviour_2(Unit* unit);
void UnitBehaviour_marine(Unit* unit);
void Attack(Unit* unit);
void Death(Unit* unit);


//TODO: 添加游戏需要的更多函数
double Dist(double x1, double y1, double x2, double y2);

#pragma endregion 


#pragma region 绘图函数声明

// 绘图函数
void Paint(HWND hWnd);

// 初始化背景函数
HBITMAP GetBackGround(HWND hWnd, HBITMAP bmp_src);
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src);

#pragma endregion