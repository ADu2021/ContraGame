// ContraGame.cpp : 定义应用程序的入口点。
//

#include "ContraGame.h"

using namespace std;


#pragma region 全局变量

#define MAX_LOADSTRING			100	
#define MAX_HELPSTRING			1000

// 全局变量: 
HINSTANCE hInst; // 当前窗体实例
WCHAR szTitle[MAX_LOADSTRING]; // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING]; // 主窗口类名
WCHAR help[MAX_HELPSTRING];



HBITMAP bmp_Grass;			//背景图像资源
HBITMAP bmp_StartMenu;
HBITMAP bmp_City;			//第二关背景
HBITMAP bmp_Castle;
HBITMAP bmp_Tutorial;		//新手教程（第一关）背景
HBITMAP bmp_Help;
HBITMAP bmp_Help0;
HBITMAP bmp_Success;

//地形
HBITMAP bmp_block1;
HBITMAP bmp_block2_0;
HBITMAP bmp_block2_1;
HBITMAP bmp_spike;
HBITMAP bmp_gate;

//按钮
HBITMAP bmp_Pause;
HBITMAP bmp_StartButton;	//开始按钮图像资源
HBITMAP bmp_QuitButton;
HBITMAP bmp_ResumeButton;
HBITMAP bmp_MainMenuButton;
HBITMAP bmp_RestartButton;
HBITMAP bmp_HelpButton;

HBITMAP bmp_bullet;

HBITMAP bmp_Unit_Red;		//红方主角图像资源
HBITMAP bmp_Unit_Blue;		//蓝方主角图像资源
HBITMAP bmp_Unit_Marine;

HBITMAP bmp_UI_HpBar;
HBITMAP bmp_UI_HP;
HBITMAP bmp_UI_MP;
HBITMAP bmp_UI_GREY;

HBITMAP bmp_Unit_Player;
HBITMAP bmp_Unit_Bee;
HBITMAP bmp_Unit_Boss;

HBITMAP bmp_FX1;

HBITMAP bmp_Background;		//生成的背景图像



Stage* currentStage = NULL; //当前场景状态
vector<Unit*> units;		//单位
vector<Button*> buttons;	//按钮
vector<Terrain*> terrains;  //地形
vector<UI*> UIs;			//UI
vector<Bullet*> bullets;	//子弹
Camera* cam = NULL;

int frame = 0;

int mouseX = 0;
int mouseY = 0;
bool mouseDown = false;
bool keyUpDown = false;
bool keyDownDown = false;
bool keyLeftDown = false;
bool keyRightDown = false;
bool keyShiftDown = false;
bool keySpaceDown = false;
bool keyJDown = false;
bool keySpaceHasUp = false;
bool keyADown = false;
bool keyDDown = false;
bool keySDown = false;
bool keyWDown = false;
bool keyTabDown = false;
bool keyFDown = false;
bool keyHDown = false;

bool attack = false;



//帧
int FRAMES_HOLD[] = { 0 };
int FRAMES_HOLD_COUNT = 1;
int FRAMES_WALK[] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2 };
int FRAMES_WALK_COUNT = 16;
int FRAMES_RUN[] = { 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2 };
int FRAMES_RUN_COUNT = 12;
int FRAMES_ATTACK[] = { 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 };
int FRAMES_ATTACK_COUNT = 24;

int FRAMES_MARINE_WALK[] = { 0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7};
int FRAMES_MARINE_WALK_COUNT = 32;
int FRAMES_MARINE_WALK_X[] = {0, 111, 226, 316, 413, 0, 90, 226};
int FRAMES_MARINE_WALK_XB[] = {110 ,225, 315, 412, 522, 89, 199, 344};
int FRAMES_MARINE_WALK_Y[] = { 0,0,0,0,0, 135, 135, 135};
int FRAMES_MARINE_WALK_YB[] = { 135, 135, 135, 135, 135, 273, 267, 273 };

int FRAMES_PLAYER_WALK[] = { 0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7 };
int FRAMES_PLAYER_WALK_COUNT = 32;
int FRAMES_PLAYER_RUN[] = { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7 };
int FRAMES_PLAYER_RUN_COUNT = 16;

int FRAMES_PLAYER_HOLD[] = { 0 };
int FRAMES_PLAYER_HOLD_COUNT = 1;
int FRAMES_PLAYER_HOLD_RIGHT_X[] = { 228 };
int FRAMES_PLAYER_HOLD_RIGHT_XC[] = { 72 };
int FRAMES_PLAYER_HOLD_RIGHT_Y[] = { 4 };
int FRAMES_PLAYER_HOLD_RIGHT_YC[] = { 59 };
int FRAMES_PLAYER_HOLD_LEFT_X[] = { 600 };
int FRAMES_PLAYER_HOLD_LEFT_XC[] = { 73 };
int FRAMES_PLAYER_HOLD_LEFT_Y[] = { 1 };
int FRAMES_PLAYER_HOLD_LEFT_YC[] = { 62 };



int FRAMES_PLAYER_WALK_RIGHT_X[] = { 27, 127, 228, 327, 27, 127, 228, 327 };
int FRAMES_PLAYER_WALK_RIGHT_XC[] = { 73, 73, 72, 73, 73, 73, 72, 73 };
int FRAMES_PLAYER_WALK_RIGHT_Y[] = { 2, 1, 4, 0, 122, 121, 121, 121 };
int FRAMES_PLAYER_WALK_RIGHT_YC[] = { 61, 62, 59, 63, 61, 62, 59, 63 };
int FRAMES_PLAYER_WALK_LEFT_X[] = { 400,500,600,700,400,500,600,700 };
int FRAMES_PLAYER_WALK_LEFT_XC[] = { 73,72,73,73,73,72,73,73 };
int FRAMES_PLAYER_WALK_LEFT_Y[] = { 0,4,1,2,121,121,121,122 };
int FRAMES_PLAYER_WALK_LEFT_YC[] = { 63,59,62,61,63,59,62,61 };

//int FRAMES_PLAYER_ATTACK[] = { 0, 0, 0, 0,0, 0,1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2};
//int FRAMES_PLAYER_ATTACK_COUNT = 18;
int FRAMES_PLAYER_ATTACK[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2 };
int FRAMES_PLAYER_ATTACK_COUNT = 9;
int FRAMES_PLAYER_ATTACK_RIGHT_X[] = { 21, 121, 221 };
int FRAMES_PLAYER_ATTACK_RIGHT_XC[] = { 43, 53, 79 };
int FRAMES_PLAYER_ATTACK_RIGHT_Y[] = { 448, 423, 461 };
int FRAMES_PLAYER_ATTACK_RIGHT_YC[] = { 83, 109, 82 };
int FRAMES_PLAYER_ATTACK_LEFT_X[] = { 736, 626, 500 }; // 
int FRAMES_PLAYER_ATTACK_LEFT_XC[] = { 43, 53, 79 };
int FRAMES_PLAYER_ATTACK_LEFT_Y[] = { 448, 423, 461 };
int FRAMES_PLAYER_ATTACK_LEFT_YC[] = { 83, 109, 82 };
int FRAMES_PLAYER_ATTACK_Y_CORRECT[] = { -22, -43, 0};

int FRAMES_FX1[] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7 };
int FRAMES_FX1_COUNT = 24;
int FRAMES_FX1_X[] = { 0,188,376,564,752,940,1128,1316 };
int FRAMES_FX1_XC[] = { 188, 188, 188, 188, 188, 188, 188, 188 };
int FRAMES_FX1_Y[] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int FRAMES_FX1_YC[] = { 50, 50, 50, 50, 50, 50, 50, 50 };
int FX1_HEIGHT = 20;

int FRAMES_BEE_FLY[] = { 0,0,1,1 };
int FRAMES_BEE_FLY_COUNT = 4;
int FRAMES_BEE_FLY_LOWER_RIGHT_X[] = { 28, 107 };
int FRAMES_BEE_FLY_LOWER_RIGHT_XC[] = { 36, 36 };
int FRAMES_BEE_FLY_LOWER_RIGHT_Y[] = { 2, 6 };
int FRAMES_BEE_FLY_LOWER_RIGHT_YC[] = { 31, 31 };
int FRAMES_BEE_FLY_LOWER_LEFT_X[] = { 338, 418 };
int FRAMES_BEE_FLY_LOWER_LEFT_XC[] = { 35, 34 };
int FRAMES_BEE_FLY_LOWER_LEFT_Y[] = { 6, 0 };
int FRAMES_BEE_FLY_LOWER_LEFT_YC[] = { 27, 33 };
int FRAMES_BEE_FLY_UPPER_LEFT_X[] = { 91, 187 };
int FRAMES_BEE_FLY_UPPER_LEFT_XC[] = { 39, 36 };
int FRAMES_BEE_FLY_UPPER_LEFT_Y[] = { 309, 326 };
int FRAMES_BEE_FLY_UPPER_LEFT_YC[] = { 41, 38 };
int FRAMES_BEE_FLY_UPPER_RIGHT_X[] = { 604, 510};
int FRAMES_BEE_FLY_UPPER_RIGHT_XC[] = { 36, 39 };
int FRAMES_BEE_FLY_UPPER_RIGHT_Y[] = { 298, 309};
int FRAMES_BEE_FLY_UPPER_RIGHT_YC[] = { 41, 41 };

int FRAMES_BOSS[] = { 0 };
int FRAMES_BOSS_COUNT = 1;
int FRAMES_BOSS_X[] = { 0 };
int FRAMES_BOSS_XC[] = { 305};
int FRAMES_BOSS_Y[] = { 0 };
int FRAMES_BOSS_YC[] = { 371 };


//地图信息
//todo: MAP_SIZE_CX[]
//TODO: MAP_SIZE_CY[]


// TODO: 在此添加其它全局变量

bool showHelp = false;
bool mission_failed = false;
bool mission_success = false;

//UI
UI HpBar;
UI HP;
UI HPBG;
UI MpBar;
UI MP;
UI MPBG;

//物理量
double Default_Gravity = 1.0; //默认重力加速度




double const PI = acos(double(-1));


#pragma endregion


#pragma region Win32程序框架



// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_CONTRAGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CONTRAGAME));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CONTRAGAME);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindow(szWindowClass, szTitle,
		WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // 设置窗口样式，不可改变大小，不可最大化,
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		// 初始化游戏窗体
		InitGame(hWnd, wParam, lParam);
		break;
	case WM_KEYDOWN:
		// 键盘按下事件
		KeyDown(hWnd, wParam, lParam);
		break;
	case WM_KEYUP:
		// 键盘松开事件
		KeyUp(hWnd, wParam, lParam);
		break;
	case WM_MOUSEMOVE:
		// 鼠标移动事件
		MouseMove(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONDOWN:
		// 鼠标左键按下事件
		LButtonDown(hWnd, wParam, lParam);
		break;
	case WM_LBUTTONUP:
		// 鼠标左键松开事件
		LButtonUp(hWnd, wParam, lParam);
		break;
	case WM_TIMER:
		// 定时器事件
		if (currentStage != NULL && currentStage->timerOn) TimerUpdate(hWnd, wParam, lParam);
		break;
	case WM_PAINT:
		// 绘图
		Paint(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


#pragma endregion


#pragma region 事件处理函数

// 初始化游戏窗体函数
void InitGame(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));

	//加载图像资源
	bmp_Grass = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_GRASS));
	bmp_StartMenu = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BG_STARTMENU));
	bmp_City = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CITY));
	bmp_Pause = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PAUSE));
	bmp_Castle = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_CASTLE));
	bmp_Tutorial = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_TUTORIAL));
	bmp_Help0 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP0));
	bmp_Success = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SUCCESS));

	bmp_block1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLOCK1));
	bmp_block2_0 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLOCK2_0));
	bmp_block2_1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLOCK2_1));
	bmp_spike = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_SPIKE));
	bmp_gate = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_GATE));

	bmp_StartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_START));
	bmp_QuitButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_QUIT));
	bmp_ResumeButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESUME));
	bmp_MainMenuButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MAIN_MENU));
	bmp_HelpButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HELP));
	bmp_RestartButton = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RESTART));

	bmp_bullet = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BULLET));

	bmp_UI_HpBar = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HPBAR));
	bmp_UI_HP = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_HP));
	bmp_UI_MP = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MP));
	bmp_UI_GREY = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_GREY));


	bmp_Unit_Red = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_RED));
	bmp_Unit_Blue = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BLUE));
	bmp_Unit_Marine = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_MARINE));
	bmp_Unit_Player = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_PLAYER));
	bmp_Unit_Bee = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BEE));
	bmp_Unit_Boss = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_BOSS));

	bmp_FX1 = LoadBitmap(((LPCREATESTRUCT)lParam)->hInstance, MAKEINTRESOURCE(IDB_BITMAP_FX1));

	//添加按钮

	Button* startButton = CreateButton(BUTTON_STARTGAME, bmp_StartButton,
		(WINDOW_WIDTH - BUTTON_DEFAULT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2);
	buttons.push_back(startButton);

	Button* quitButton = CreateButton(BUTTON_QUITGAME, bmp_QuitButton,
		(WINDOW_WIDTH + BUTTON_DEFAULT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2 + 100);
	buttons.push_back(quitButton);

	Button* resumeButton = CreateButton(BUTTON_RESUMEGAME, bmp_ResumeButton,
		(WINDOW_WIDTH - BUTTON_DEFAULT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2 - 100, true);
	buttons.push_back(resumeButton);

	Button* helpButton = CreateButton(BUTTON_HELP, bmp_HelpButton,
		(WINDOW_WIDTH + BUTTON_DEFAULT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2 + 200);
	buttons.push_back(helpButton);
	
	Button* mainmenuButton = CreateButton(BUTTON_MAINMENU, bmp_MainMenuButton,
		(WINDOW_WIDTH - BUTTON_DEFAULT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2 + 100, true);
	buttons.push_back(mainmenuButton);

	Button* restartButton = CreateButton(BUTTON_RESTART, bmp_RestartButton,
		(WINDOW_WIDTH - BUTTON_DEFAULT_WIDTH) / 2, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2, true);
	buttons.push_back(restartButton);

	Button* helpbackButton = CreateButton(BUTTON_HELPBACK, bmp_MainMenuButton,
		(WINDOW_WIDTH + BUTTON_DEFAULT_WIDTH) / 2 - 100, (WINDOW_WIDTH - BUTTON_DEFAULT_HEIGHT) / 2 + 100);
	buttons.push_back(helpbackButton);

	//初始化UI
	InitUI();


	//初始化开始场景
	InitStage(hWnd, STAGE_STARTMENU);

	//初始化主计时器
	SetTimer(hWnd, TIMER_GAMETIMER, TIMER_GAMETIMER_ELAPSE, NULL);
}
void InitUI()
{
	/*
	UI HpBar;
	UI HP;
	UI HPBG
	UI MPBar;
	UI MP;
	UI MPBG;
	*/
	HPBG.img = bmp_UI_GREY;
	MPBG.img = bmp_UI_GREY;
	HpBar.img = bmp_UI_HpBar;
	MpBar.img = bmp_UI_HpBar;
	HP.img = bmp_UI_HP;
	MP.img = bmp_UI_MP;

	HpBar.x = 0;
	HpBar.y = 0;
	HpBar.cx = UI_HP_WIDTH;
	HpBar.cy = UI_HP_HEIGHT;
	HpBar.type = 0;

	HP.x = UI_HP_X;
	HP.y = 0;
	HP.cx = UI_HP_CX;
	HP.cy = UI_HP_HEIGHT;
	HP.type = UI_HP;

	HPBG.x = 0;
	HPBG.y = 0;
	HPBG.cx = UI_HP_WIDTH;
	HPBG.cy = UI_HP_HEIGHT;
	HPBG.type = 0;

	MpBar.x = 0;
	MpBar.y = UI_HP_HEIGHT;
	MpBar.cx = UI_HP_WIDTH;
	MpBar.cy = UI_HP_HEIGHT;
	MpBar.type = 0;

	MP.x = UI_HP_X;
	MP.y = UI_HP_HEIGHT;
	MP.cx = UI_HP_CX;
	MP.cy = UI_HP_HEIGHT;
	MP.type = UI_MP;

	MPBG.x = 0;
	MPBG.y = UI_HP_HEIGHT;
	MPBG.cx = UI_HP_WIDTH;
	MPBG.cy = UI_HP_HEIGHT;
	MPBG.type = 0;

	UIs.push_back(&HPBG);
	UIs.push_back(&HP);
	UIs.push_back(&HpBar);
	
	UIs.push_back(&MPBG);
	UIs.push_back(&MP);
	UIs.push_back(&MpBar);
}

// 键盘按下事件处理函数
void KeyDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = true;
		break;
	case VK_DOWN:
		keyDownDown = true;
		break;
	case VK_LEFT:
		keyLeftDown = true;
		break;
	case VK_RIGHT:
		keyRightDown = true;
		break;
	case VK_SPACE:
		keySpaceDown = true;
		break;
	case VK_SHIFT:
		keyShiftDown = true;
		break;
	case VK_TAB:
		keyTabDown = true;
		break;
	case VK_ESCAPE:
		MyPause(hWnd);
		break;
	case 'A':
		keyADown = true;
		break;
	case 'D':
		keyDDown = true;
		break;
	case 'S':
		keySDown = true;
		break;
	case 'W':
		keyWDown = true;
		break;
	case 'J':
		keyJDown = true;
		break;
	case 'K':
		attack = true;
		break;
	case 'F':
		keyFDown = true;
		break;
	case 'H':
		keyHDown = true;
		showHelp ^= 1;
		break;
	default:
		break;
	}
}

// 键盘松开事件处理函数
void KeyUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	// TODO
	switch (wParam)
	{
	case VK_UP:
		keyUpDown = false;
		break;
	case VK_DOWN:
		keyDownDown = false;
		break;
	case VK_LEFT:
		keyLeftDown = false;
		break;
	case VK_RIGHT:
		keyRightDown = false;
		break;
	case VK_SPACE:
		keySpaceDown = false;
		keySpaceHasUp = true;
		break;
	case VK_SHIFT:
		keyShiftDown = false;
		break;
	case VK_TAB:
		keyTabDown = false;
		break;
	case 'A':
		keyADown = false;
		break;
	case 'D':
		keyDDown = false;
		break;
	case 'S':
		keySDown = false;
		break;
	case 'W':
		keyWDown = false;
		break;
	case 'J':
		keyJDown = false;
		keySpaceHasUp = true;
		break;
	case 'F':
		keyFDown = false;
		break;
	case 'H':
		keyHDown = false;
		break;
	default:
		break;
	}
}

// 鼠标移动事件处理函数
void MouseMove(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
}

// 鼠标左键按下事件处理函数
void LButtonDown(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = true;

	//attack
	if (currentStage->stageID != STAGE_STARTMENU)
		attack = true;

	//buttons
	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (((currentStage->timerOn || currentStage->stageID==STAGE_STARTMENU || currentStage->stageID == STAGE_HELP) && button->visible) || (!currentStage->timerOn && button->pause))
		{
			if (button->x <= mouseX
				&& button->x + button->width >= mouseX
				&& button->y <= mouseY
				&& button->y + button->height >= mouseY)
			{
				switch (button->buttonID) {
				case BUTTON_STARTGAME:
					//TODO：判断进入哪个关卡
					InitStage(hWnd, STAGE_1);
					break;
				case BUTTON_QUITGAME:
					PostQuitMessage(0);
					break;
				case BUTTON_MAINMENU:
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				case BUTTON_RESTART:
					InitStage(hWnd, currentStage->stageID);
					break;
				case BUTTON_RESUMEGAME:
					MyPause(hWnd);
					break;
				case BUTTON_HELP:
					InitStage(hWnd, STAGE_HELP);
					break;
				case BUTTON_HELPBACK:
					InitStage(hWnd, STAGE_STARTMENU);
					break;
				}
			}
		}
	}
}	


// 鼠标左键松开事件处理函数
void LButtonUp(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	mouseX = LOWORD(lParam);
	mouseY = HIWORD(lParam);
	mouseDown = false;
}

// 定时器事件处理函数
void TimerUpdate(HWND hWnd, WPARAM wParam, LPARAM lParam)
{	
	currentStage->time++;

	UpdateTerrains(hWnd);
	UpdateUnits(hWnd);
	UpdateBullets(hWnd);

	if (mission_failed)
	{
		mission_failed = false;
		//InitStage(hWnd, STAGE_FAIL);
		InitStage(hWnd, currentStage->stageID);
	}
	else if (mission_success)
	{
		mission_success = false;
		switch (currentStage->stageID)
		{
		case STAGE_1:
			InitStage(hWnd, STAGE_2);
			break;
		case STAGE_2:
			InitStage(hWnd, STAGE_SUCCESS);
			break;

		}
	}

	cam->move();

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}

void MyPause(HWND hWnd)
{
	if(currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_CNT)
		currentStage->timerOn = !currentStage->timerOn;
	InvalidateRect(hWnd, NULL, FALSE);
	return;
}


#pragma endregion


#pragma region 其它游戏状态处理函数



//TODO: 添加游戏需要的更多函数

// 添加按钮函数
Button* CreateButton(int buttonID, HBITMAP img, int x, int y, bool is_pause, int width, int height)
{
	Button* button = new Button();
	button->buttonID = buttonID;
	button->img = img;
	button->width = width;
	button->height = height;
	button->x = x;
	button->y = y;

	button->visible = false;
	button->pause = is_pause;
	return button;
}

// 添加主角函数
Unit* CreateUnit(int side, int type, int x, int y, int health, double gravity = Default_Gravity, int cx = UNIT_SIZE_X, int cy = UNIT_SIZE_Y, int mana = 100)
{
	Unit* unit = new Unit();
	unit->side = side;
	unit->time = 0;
	unit->visible = true;
	unit->death_cnt = -1;
	unit->del = false;

	if (side == UNIT_SIDE_RED) {
		unit->img = bmp_Unit_Red;
		unit->direction = UNIT_DIRECT_LEFT;
	}
	else if (side == UNIT_SIDE_BLUE) {
		unit->img = bmp_Unit_Blue;
		//unit->img = bmp_Unit_Marine;
		unit->direction = UNIT_DIRECT_RIGHT;
	}

	switch (type)
	{
	case UNIT_TYPE_PLAYER:
		unit->img = bmp_Unit_Player;

		unit->type = type;
		unit->state = UNIT_STATE_HOLD;


		unit->frame_row = type;
		unit->frame_column = UNIT_LAST_FRAME * unit->direction;

		unit->frame_sequence = FRAMES_PLAYER_HOLD;
		unit->frame_count = FRAMES_PLAYER_HOLD_COUNT;
		unit->frame_id = 0;

		unit->frame_x = FRAMES_PLAYER_WALK_RIGHT_X;
		unit->frame_xc = FRAMES_PLAYER_WALK_RIGHT_XC;
		unit->frame_y = FRAMES_PLAYER_WALK_RIGHT_Y;
		unit->frame_yc = FRAMES_PLAYER_WALK_RIGHT_YC;

		unit->g = gravity;

		unit->x = x;
		unit->y = y;
		unit->cx = cx;
		unit->cy = cy;
		unit->vx = 0;
		unit->vy = 0;
		unit->vx_limit = 20.0;
		unit->vy_limit = 20.0;
		unit->ax = 0;
		unit->ay = 0;

		unit->hover = true;
		unit->JumpStage = 2;
		unit->JumpCount = 1;

		unit->health = PLAYER_HP_MAX;
		unit->mana = PLAYER_MANA_MAX;
		unit->maxHealth = PLAYER_HP_MAX;
		unit->maxMana = PLAYER_MANA_MAX;

		unit->FX1 = false;

		unit->attack_damage = AT_DAMEGE_UNIT;
		unit->attack_range = AT_RANGE_UNIT;

		return unit;

		break;

	case UNIT_TYPE_BEE:
		unit->img = bmp_Unit_Bee;

		unit->type = type;
		unit->state = UNIT_STATE_HOLD;


		unit->frame_row = type;
		unit->frame_column = UNIT_LAST_FRAME * unit->direction;

		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_id = 0;

		unit->frame_x = FRAMES_BEE_FLY_LOWER_RIGHT_X;
		unit->frame_xc = FRAMES_BEE_FLY_LOWER_RIGHT_XC;
		unit->frame_y = FRAMES_BEE_FLY_LOWER_RIGHT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_LOWER_RIGHT_YC;

		unit->g = 0;

		unit->x = x;
		unit->y = y;
		unit->cx = cx;
		unit->cy = cy;
		unit->vx = 0;
		unit->vy = 0;
		unit->vx_limit = 20.0;
		unit->vy_limit = 20.0;
		unit->ax = 0;
		unit->ay = 0;

		unit->hover = true;
		unit->JumpStage = 2;
		unit->JumpCount = 1;

		unit->health = BEE_HP_MAX;
		unit->mana = mana;
		unit->maxHealth = health;
		unit->maxMana = mana;

		unit->FX1 = false;

		unit->attack_range = AT_RANGE_BEE;
		unit->attack_damage = AT_DMG_BEE;
		unit->attack = false;
		unit->attack_cd = 0;

		return unit;

		break;
	case UNIT_TYPE_BEE2:
		unit->img = bmp_Unit_Bee;

		unit->type = type;
		unit->state = UNIT_STATE_HOLD;


		unit->frame_row = type;
		unit->frame_column = UNIT_LAST_FRAME * unit->direction;

		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_id = 0;

		unit->frame_x = FRAMES_BEE_FLY_LOWER_RIGHT_X;
		unit->frame_xc = FRAMES_BEE_FLY_LOWER_RIGHT_XC;
		unit->frame_y = FRAMES_BEE_FLY_LOWER_RIGHT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_LOWER_RIGHT_YC;

		unit->g = 0;

		unit->x = x;
		unit->y = y;
		unit->cx = cx;
		unit->cy = cy;
		unit->vx = 0;
		unit->vy = 0;
		unit->vx_limit = 20.0;
		unit->vy_limit = 20.0;
		unit->ax = 0;
		unit->ay = 0;

		unit->hover = true;
		unit->JumpStage = 2;
		unit->JumpCount = 1;

		unit->health = BEE2_HP_MAX;
		unit->mana = mana;
		unit->maxHealth = health;
		unit->maxMana = mana;

		unit->FX1 = false;

		unit->attack_range = AT_RANGE_BEE;
		unit->attack_damage = AT_DMG_BEE;
		unit->attack = false;
		unit->attack_cd = 0;

		return unit;
		break;
	case UNIT_TYPE_BOSS:
		unit->img = bmp_Unit_Boss;

		unit->type = type;
		unit->state = UNIT_STATE_HOLD;


		unit->frame_row = type;
		unit->frame_column = UNIT_LAST_FRAME * unit->direction;

		unit->frame_sequence = FRAMES_BOSS;
		unit->frame_count = FRAMES_BOSS_COUNT;
		unit->frame_id = 0;

		unit->frame_x = FRAMES_BOSS_X;
		unit->frame_xc = FRAMES_BOSS_XC;
		unit->frame_y = FRAMES_BOSS_Y;
		unit->frame_yc = FRAMES_BOSS_YC;

		unit->g = 0;

		unit->x = x;
		unit->y = y;
		unit->cx = cx;
		unit->cy = cy;
		unit->vx = 0;
		unit->vy = 0;
		unit->vx_limit = 20.0;
		unit->vy_limit = 20.0;
		unit->ax = 0;
		unit->ay = 0;

		unit->hover = true;
		unit->JumpStage = 2;
		unit->JumpCount = 1;

		unit->health = BOSS_HP_MAX;
		unit->mana = mana;
		unit->maxHealth = health;
		unit->maxMana = mana;

		unit->FX1 = false;

		unit->attack_range = AT_RANGE_BEE;
		unit->attack_damage = AT_DMG_BEE;
		unit->attack = false;
		unit->attack_cd = 0;

		return unit;

		break;
	default:
		break;
	}

	unit->type = type;
	unit->state = UNIT_STATE_HOLD;


	unit->frame_row = type;
	unit->frame_column = UNIT_LAST_FRAME * unit->direction;

	unit->frame_sequence = FRAMES_HOLD;
	unit->frame_count = FRAMES_HOLD_COUNT;
	unit->frame_id = 0;

	unit->g = gravity;

	unit->x = x;
	unit->y = y;
	unit->cx = cx;
	unit->cy = cy;
	unit->vx = 0;
	unit->vy = 0;
	unit->vx_limit = 20.0;
	unit->vy_limit = 20.0;
	unit->ax = 0;
	unit->ay = 0;
	unit->health = health;


	unit->hover = true;
	return unit;
}
Terrain* CreateTerrain(int id, int type, int x, int y, int cx, int cy, bool vis = true, HBITMAP bitmap = bmp_block1, int bmp_cx = TR_BLOCK1_WIDTH, int bmp_cy = TR_BLOCK1_HEIGHT, Terrain *pre = NULL)
{
	Terrain* terrain = new Terrain();
	terrain->img = bitmap;
	terrain->visible = vis;
	terrain->id = id;
	terrain->type = type;
	terrain->x = x;
	terrain->y = y;
	terrain->cx = cx;
	terrain->cy = cy;
	terrain->img_width = bmp_cx;
	terrain->img_height = bmp_cy;

	terrain->timestamp = 0;
	terrain->vx = 1;
	terrain->vy = 1;
	terrain->dx = 0;
	terrain->dy = 0;

	terrain->pre = pre;
	
	switch (terrain->id)
	{
	case 6:
		terrain->vx = 2.0;
		terrain->vy = 0;
		break;
	case 13:
		terrain->vx = 2.0;
		terrain->vy = 0;
		break;
	}

	return terrain;
}
void DeleteTerrain(Terrain *terrain)
{
	if (terrain == NULL)
		return;
	delete terrain;
}
//单位和地形的碰撞检测（AABB包围盒）
bool point_inside_rect(int x0, int y0, int x, int cx, int y, int cy)
{
	return ((x <= x0) && (x0 <= x + cx) && (y <= y0) && (y0 <= y + cy));
}

Bullet* CreateBullet(int x, int y, int tarx, int tary, double v, int damage = 10)
{
	Bullet* bullet = new Bullet();
	bullet->x = x;
	bullet->y = y;
	bullet->tarx = tarx;
	bullet->tary = tary;
	double vx, vy, dist;
	dist = Dist(x, y, tarx, tary);
	vx = v * (tarx - x) / dist;
	vy = v * (tary - y) / dist;
	bullet->vx = vx;
	bullet->vy = vy;
	bullet->del = false;
	bullet->damage = damage;
	return bullet;
}

int CollisionDetectionForRectAndRect(Unit* unit, vector<Terrain*> &Terrains, int start_id = 0)
{
	if (&Terrains == NULL)
		return -1;
	int size = Terrains.size();
	for (int i = start_id; i < size; i++)
	{
		RectCollider* terrain = Terrains[i];
		if ((abs(unit->x + double(unit->cx) / 2 - terrain->x - double(terrain->cx) / 2) <= double(unit->cx + terrain->cx) / 2) &&
			(abs(unit->y + double(unit->cy) / 2 - terrain->y - double(terrain->cy) / 2) <= double(unit->cy + terrain->cy) / 2))
			return i;
	}
	return -1;
}
int CollisionDetectionForRectAndRect(Bullet* unit, std::vector<Terrain*>& Terrains, int start_id = 0)
{
	if (&Terrains == NULL)
		return -1;
	int size = Terrains.size();
	for (int i = start_id; i < size; i++)
	{
		RectCollider* terrain = Terrains[i];
		if ((abs(unit->x + double(unit->cx) / 2 - terrain->x - double(terrain->cx) / 2) <= double(unit->cx + terrain->cx) / 2) &&
			(abs(unit->y + double(unit->cy) / 2 - terrain->y - double(terrain->cy) / 2) <= double(unit->cy + terrain->cy) / 2))
			return i;
	}
	return -1;
}

int CollisionDetectionForRectAndRect(Unit* unit, vector<Bullet*>& Terrains, int start_id = 0)
{
	if (&Terrains == NULL)
		return -1;
	int size = Terrains.size();
	for (int i = start_id; i < size; i++)
	{
		RectCollider* terrain = Terrains[i];
		if ((abs(unit->x + double(unit->cx) / 2 - terrain->x - double(terrain->cx) / 2) <= double(unit->cx + terrain->cx) / 2) &&
			(abs(unit->y + double(unit->cy) / 2 - terrain->y - double(terrain->cy) / 2) <= double(unit->cy + terrain->cy) / 2))
			return i;
	}
	return -1;
}

int CollisionDetectionForRectAndRect(Unit* unit, Unit* x)
{
	if ((abs(unit->x + double(unit->cx) / 2 - x->x - double(x->cx) / 2) <= double(unit->cx + x->cx) / 2) &&
		(abs(unit->y + double(unit->cy) / 2 - x->y - double(x->cy) / 2) <= double(unit->cy + x->cy) / 2))
		return 0;
	return -1;
}

void Camera::move()
{
	if (follow_id < 0 || follow_id >= units.size())
		return;
	Unit* unit = units[follow_id];
	int screen_x = unit->x - x; //实际打印在屏幕上的位置x
	int screen_y = unit->y - y;	//实际打印在屏幕上的位置y
	int stat = 0;				//这个位置和镜头允许的limit（中央区域）的关系
	/*
	1|2|3
	-----
	4|5|6          区域5表示limit允许的区域
	-----
	7|8|9
	*/
	if (screen_x < limit_x)
	{
		stat = 1;
		x = unit->x - limit_x;
	}
	else if (screen_x >= limit_x + limit_cx)
	{
		stat = 3;
		x = unit->x - (limit_x + limit_cx - 1);
	}
	else
		stat = 2;
	if (screen_y < limit_y)
	{
		stat += 0;
		y = unit->y - limit_y;
	}
	else if (screen_y >= limit_y + limit_cy)
	{
		stat += 6;
		y = unit->y - (limit_y + limit_cy - 1);
	}
	else
		stat += 3;

	if (x < 0)		
		x = 0;
	if (y < 0)
		y = 0;
	// if x >= MAP_SIZE_CX[??]
	// x = MAP_SIZE_CX[??]-1;
	// if y >= .. 


}


// 初始化游戏场景函数
void InitStage(HWND hWnd, int stageID)
{
	// 初始化场景实例

	//delete stage
	if (currentStage != NULL) delete currentStage;

	//clear units
	for (int i = 0, len = units.size(); i < len; i++)
		delete units[i];
	units.clear();

	//clear terrains
	for (int i = 0, len = terrains.size(); i < len; i++)
		delete terrains[i];
	terrains.clear();

	//clear bullets
	for (int i = 0, len = bullets.size(); i < len; i++)
		delete bullets[i];
	bullets.clear();

	currentStage = new Stage();
	currentStage->stageID = stageID;


	if (stageID == STAGE_STARTMENU) {
		currentStage->bg = bmp_Background;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		//显示开始界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_STARTGAME || button->buttonID == BUTTON_QUITGAME || button->buttonID == BUTTON_HELP)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}


	}
	else if (stageID == STAGE_HELP) {
		currentStage->bg = bmp_Help0;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_HELPBACK)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID == STAGE_SUCCESS) {
		currentStage->bg = bmp_Success;
		currentStage->timeCountDown = 0;
		currentStage->timerOn = false;

		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->buttonID == BUTTON_MAINMENU)
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}
	}
	else if (stageID >= STAGE_1 && stageID <= STAGE_CNT) //TODO：添加多个游戏场景
	{
		switch (stageID) {
		case STAGE_1:
			currentStage->bg = bmp_Tutorial;
			break;
		case STAGE_2:
			//bmp_Background = InitBackGround(hWnd, bmp_City);
			currentStage->bg = bmp_Castle;
			break;
		default:
			break;
		}

		currentStage->timeCountDown = 10000;
		currentStage->timerOn = true;

		//显示游戏界面的按钮
		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (false) //TODO：加载游戏界面需要的按钮
			{
				button->visible = true;
			}
			else
			{
				button->visible = false;
			}
		}


		// 按场景初始化单位，镜头，地形
		int units_size = units.size();
		for (int i = 0; i < units_size; i++)
			if(units[i] != NULL)
				delete units[i];
		units.clear();
		switch (stageID) {
		case STAGE_1:
			//showHelp = true;

			//player
			units.push_back(CreateUnit(UNIT_SIDE_ALLY, UNIT_TYPE_PLAYER, 300, 200, 100));

			if (cam != NULL) delete cam;
			cam = new Camera(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH / 3, 0, WINDOW_WIDTH / 3, WINDOW_HEIGHT);
			cam->follow_id = 0;

			//terrains
			Terrain* pre;

			terrains.push_back(CreateTerrain(1, TR_GROUND, 0, 478, 15000, 100, false)); // 改数据！
			terrains.push_back(CreateTerrain(2, 0, 0, 0, 45, WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT + 500, false));
			terrains.push_back(CreateTerrain(2, 0, 5500, 0, 45, WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT + 500, false));

			terrains.push_back(CreateTerrain(3, TR_SPIKE | TR_NO_COLLISION, 1000, 465, 100, 50, true, bmp_spike, TR_SPIKE_WIDTH, TR_SPIKE_HEIGHT));
			
			terrains.push_back(CreateTerrain(4, TR_SPIKE | TR_NO_COLLISION, 1500, 465, 500, 50, true, bmp_spike, TR_SPIKE_WIDTH, TR_SPIKE_HEIGHT));
			terrains.push_back(CreateTerrain(5, TR_BLOCK_2 | TR_GROUND, 1500, 350, 500, 50, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT));

			terrains.push_back(CreateTerrain(6, TR_SPIKE | TR_NO_COLLISION | TR_MOVING, 2500, 470, 200, 50, true, bmp_spike, TR_SPIKE_WIDTH, TR_SPIKE_HEIGHT));
			
			terrains.push_back(CreateTerrain(7, TR_SPIKE | TR_NO_COLLISION, 3000, 465, 700, 50, true, bmp_spike, TR_SPIKE_WIDTH, TR_SPIKE_HEIGHT));
			terrains.push_back(CreateTerrain(8, TR_BLOCK_2 | TR_GROUND, 3000, 350, 300, 40, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT));
			terrains.push_back(CreateTerrain(9, TR_BLOCK_2 | TR_NO_COLLISION, 3300, 350, 200, 40, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT));
			terrains.push_back(CreateTerrain(10, TR_BLOCK_2 | TR_GROUND, 3200, 235, 200, 40, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT));

			terrains.push_back(CreateTerrain(11, TR_SPIKE | TR_NO_COLLISION, 4000, 465, 500, 50, true, bmp_spike, TR_SPIKE_WIDTH, TR_SPIKE_HEIGHT));
			terrains.push_back(pre = CreateTerrain(12, TR_BLOCK_2 | TR_NO_COLLISION, 4000, 350, 300, 40, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT));
			terrains.push_back(CreateTerrain(13, TR_BLOCK_2 | TR_GROUND | TR_MOVING, 4300, 350, 200, 40, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT, pre));
			terrains.push_back(CreateTerrain(14, TR_BLOCK_2 | TR_GROUND, 4200, 235, 200, 40, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT));

			terrains.push_back(CreateTerrain(0, TR_GATE, 5000, 480-TR_GATE_HEIGHT, 84, 180, true, bmp_gate, TR_GATE_WIDTH, TR_GATE_HEIGHT));
			break;
		case STAGE_2:

			units.push_back(CreateUnit(UNIT_SIDE_ALLY, UNIT_TYPE_PLAYER, 300, 200, PLAYER_HP_MAX));

			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE, 500, 200, BEE_HP_MAX));

			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE, 1500, 200, BEE_HP_MAX));

			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE, 2500, 200, BEE_HP_MAX));
			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE, 2520, 300, BEE_HP_MAX));

			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE2, 3520, 300, BEE_HP_MAX));

			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE2, 4500, 300, BEE_HP_MAX));
			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE, 4200, 300, BEE_HP_MAX));
			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE2, 3520, 300, BEE_HP_MAX));

			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BOSS, 5000, 200, BOSS_HP_MAX, 0, BOSS_WIDTH / 3.5, BOSS_HEIGHT / 3.5));
			


			if (cam != NULL) delete cam;
			cam = new Camera(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3, WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3); // 
			cam->follow_id = 0;

			//terrains
			terrains.push_back(CreateTerrain(-1, TR_GROUND | TR_BLOCK_2, 0, 490, 15000, 100, true, bmp_block2_0, TR_BLOCK2_0_WIDTH, TR_BLOCK2_0_HEIGHT)); // 改数据！
			terrains.push_back(CreateTerrain(-2, 0, 0, 0, 45, WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT + 500, false));
			terrains.push_back(CreateTerrain(-3, 0, 6500, 0, 45, WINDOW_HEIGHT + WINDOW_TITLEBARHEIGHT + 500, false));

		default:
			break;
		}


	}

	//刷新显示
	InvalidateRect(hWnd, NULL, FALSE);
}


// 刷新单位状态函数
void UpdateUnits(HWND hWnd)
{
	for (int i = 0, len = units.size(); i < len; i++) {
		Unit* unit = units[i];
		unit->time++;

		//根据单位类型选择行为函数
		switch (unit->type) {
		case UNIT_TYPE_CASTER:
			UnitBehaviour_1(unit);
			break;
		case UNIT_TYPE_REAPER:
		case UNIT_TYPE_SABER:
		case UNIT_TYPE_SHIELDER:
		case UNIT_TYPE_HOPLITE:
			MyUnitBehaviour_2(unit);

			break;
		case UNIT_TYPE_MARINE:
			UnitBehaviour_marine(unit);
			break;
		case UNIT_TYPE_PLAYER:
			UnitBehaviour_Player(unit);
			break;
		case UNIT_TYPE_BEE:
			UnitBehaviour_Bee(unit);
			break;
		case UNIT_TYPE_BEE2:
			UnitBehaviour_Bee2(unit);
			break;
		case UNIT_TYPE_BOSS:
			UnitBehaviour_Boss(unit);
		}

	}
	for (int len = units.size(), i = len-1; i >= 0; i--) {
		Unit* unit = units[i];
		if (unit->del)
		{
			delete unit;
			units.erase(units.begin() + i, units.begin() + i + 1);
			//AllocConsole();
			//_cprintf("%d\n",units.size());
		}
	}

}
void UpdateTerrains(HWND hWnd)
{
	for (int len = terrains.size(), i = 0; i < len; i++)
	{
		switch (terrains[i]->id)
		{
		case 6:
			terrains[i]->x += terrains[i]->vx;
			terrains[i]->dx += terrains[i]->vx;
			terrains[i]->y += terrains[i]->vy;
			terrains[i]->dy += terrains[i]->vy;

			if (abs(terrains[i]->dx) > 100)
				terrains[i]->vx *= -1;
			if (abs(terrains[i]->dy) > 100)
				terrains[i]->vy *= -1;
			break;
		case 13:
			if (terrains[i]->pre != NULL && !terrains[i]->pre->visible)
			{
				terrains[i]->x += terrains[i]->vx;
				terrains[i]->dx += terrains[i]->vx;
				terrains[i]->y += terrains[i]->vy;
				terrains[i]->dy += terrains[i]->vy;

				if (terrains[i]->dx > 0 || terrains[i]->dx < -320)
					terrains[i]->vx *= -1;
				if (abs(terrains[i]->dy) > 100)
					terrains[i]->vy *= -1;
			}
			break;
		}
	}
}

void UpdateBullets(HWND hWnd)
{
	int collision_id;
	//move
	for (int i = 0, len = bullets.size(); i < len; i++)
	{
		Bullet* bullet = bullets[i];
		bullet->x += bullet->vx;
		bullet->y += bullet->vy;
		collision_id = CollisionDetectionForRectAndRect(bullet, terrains);
		while (collision_id >= 0)
		{
			bullet->del = true;
			collision_id = CollisionDetectionForRectAndRect(bullet, terrains, collision_id+1);
		}
	}

	
	
	
	//delete
	for (int len = bullets.size(), i = len-1; i >=0; i--)
	{
		Bullet* bullet = bullets[i];
		if (bullet->del)
		{
			delete bullet;
			bullets.erase(bullets.begin()+i, bullets.begin()+i+1);
		}
	}
}

//单位行为函数
void UnitBehaviour_Player(Unit* unit) {

	if (unit->health <= 0 || unit->y > 2048)
	{
		Death(unit);
		unit->vx = 0;
		unit->vy = 0;
		return;
	}

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;

	if ((unit->frame_sequence == FRAMES_PLAYER_ATTACK) && (unit->frame_id < FRAMES_PLAYER_ATTACK_COUNT - 1))
	{
		attack = true;
		
	}
	//if ((unit->frame_sequence == FRAMES_PLAYER_ATTACK) && (unit->frame_id == FRAMES_PLAYER_ATTACK_COUNT - 1))
		
	//move : A,D,Lshift,Space
	bool keyspacedown = keySpaceDown;
	keySpaceDown = keySpaceDown | keyJDown;
	if (!keyADown && !keyDDown && !keySpaceDown)
	{
		if (attack)
		{
			Attack(unit);
		}
		else if (!unit->hover || (unit->frame_sequence == FRAMES_PLAYER_ATTACK))
		{
			unit->frame_sequence = FRAMES_PLAYER_HOLD;
			unit->frame_count = FRAMES_PLAYER_HOLD_COUNT;
			if (unit->direction == UNIT_DIRECT_LEFT)
			{
				unit->frame_x = FRAMES_PLAYER_HOLD_LEFT_X;
				unit->frame_xc = FRAMES_PLAYER_HOLD_LEFT_XC;
				unit->frame_y = FRAMES_PLAYER_HOLD_LEFT_Y;
				unit->frame_yc = FRAMES_PLAYER_HOLD_LEFT_YC;
			}
			else
			{
				unit->frame_x = FRAMES_PLAYER_HOLD_RIGHT_X;
				unit->frame_xc = FRAMES_PLAYER_HOLD_RIGHT_XC;
				unit->frame_y = FRAMES_PLAYER_HOLD_RIGHT_Y;
				unit->frame_yc = FRAMES_PLAYER_HOLD_RIGHT_YC;
			}
			//unit->vx = 0;
			//unit->vy = 0;
		}
	}
	else if (keyADown && !keyDDown && !keyShiftDown && !keySpaceDown) // A
	{
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -SPEED_PLAYER_WALK;
		if (attack)
			Attack(unit);
		else
		{
			unit->frame_sequence = FRAMES_PLAYER_WALK;
			unit->frame_count = FRAMES_PLAYER_WALK_COUNT;
			unit->frame_x = FRAMES_PLAYER_WALK_LEFT_X;
			unit->frame_xc = FRAMES_PLAYER_WALK_LEFT_XC;
			unit->frame_y = FRAMES_PLAYER_WALK_LEFT_Y;
			unit->frame_yc = FRAMES_PLAYER_WALK_LEFT_YC;
		}

	}
	else if (!keyADown && keyDDown && !keyShiftDown && !keySpaceDown) // D
	{
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = SPEED_PLAYER_WALK;
		if (attack)
			Attack(unit);
		else
		{
			unit->frame_sequence = FRAMES_PLAYER_WALK;
			unit->frame_count = FRAMES_PLAYER_WALK_COUNT;

			unit->frame_x = FRAMES_PLAYER_WALK_RIGHT_X;
			unit->frame_xc = FRAMES_PLAYER_WALK_RIGHT_XC;
			unit->frame_y = FRAMES_PLAYER_WALK_RIGHT_Y;
			unit->frame_yc = FRAMES_PLAYER_WALK_RIGHT_YC;
		}
	}
	else if (keyADown && !keyDDown && keyShiftDown && !keySpaceDown) // A+Lshift
	{
		unit->direction = UNIT_DIRECT_LEFT;
		if (attack)
		{
			Attack(unit);
			if(!unit->hover)
				unit->vx = -SPEED_PLAYER_RUN;
		}
		else
		{
			if (!unit->hover)
			{
				unit->frame_sequence = FRAMES_PLAYER_RUN;
				unit->frame_count = FRAMES_PLAYER_RUN_COUNT;

				unit->frame_x = FRAMES_PLAYER_WALK_LEFT_X;
				unit->frame_xc = FRAMES_PLAYER_WALK_LEFT_XC;
				unit->frame_y = FRAMES_PLAYER_WALK_LEFT_Y;
				unit->frame_yc = FRAMES_PLAYER_WALK_LEFT_YC;
				unit->vx = -SPEED_PLAYER_RUN;
			}
		}
	}
	else if (!keyADown && keyDDown && keyShiftDown && !keySpaceDown) // D+Lshift
	{
		unit->direction = UNIT_DIRECT_RIGHT;
		if (attack)
		{
			Attack(unit);
			if (!unit->hover)
				unit->vx = SPEED_PLAYER_RUN;
		}
		else
		{
			if (!unit->hover)
			{
				unit->frame_sequence = FRAMES_PLAYER_RUN;
				unit->frame_count = FRAMES_PLAYER_RUN_COUNT;
				unit->frame_x = FRAMES_PLAYER_WALK_RIGHT_X;
				unit->frame_xc = FRAMES_PLAYER_WALK_RIGHT_XC;
				unit->frame_y = FRAMES_PLAYER_WALK_RIGHT_Y;
				unit->frame_yc = FRAMES_PLAYER_WALK_RIGHT_YC;
				unit->vx = SPEED_PLAYER_RUN;
			}
		}
	}
	else if (!keyADown && !keyDDown && !keyShiftDown && keySpaceDown) // Space
	{
		if (attack)
			Attack(unit);
		if (unit->JumpCount < unit->JumpStage && (!unit->JumpCount || keySpaceHasUp))
		{
			unit->JumpCount++;
			keySpaceHasUp = false;
			unit->hover = true;
			unit->vy = -SPEED_PLAYER_JUMP;
			//unit->ay = unit->g;
		}
	}
	else if (keyADown && !keyDDown && !keyShiftDown && keySpaceDown) // A+Space
	{
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -SPEED_PLAYER_WALK;
		if (attack)
			Attack(unit);
		else
		{
			unit->frame_sequence = FRAMES_PLAYER_WALK;
			unit->frame_count = FRAMES_PLAYER_WALK_COUNT;

			unit->frame_x = FRAMES_PLAYER_WALK_LEFT_X;
			unit->frame_xc = FRAMES_PLAYER_WALK_LEFT_XC;
			unit->frame_y = FRAMES_PLAYER_WALK_LEFT_Y;
			unit->frame_yc = FRAMES_PLAYER_WALK_LEFT_YC;
		}
		
		if (unit->JumpCount < unit->JumpStage && (!unit->JumpCount || keySpaceHasUp))
		{
			unit->JumpCount++;
			keySpaceHasUp = false;
			unit->hover = true;
			unit->vy = -SPEED_PLAYER_JUMP;
			//unit->ay = unit->g;
		}
	}
	else if (!keyADown && keyDDown && !keyShiftDown && keySpaceDown) // D+Space
	{
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = SPEED_PLAYER_WALK;
		if (attack)
		{
			Attack(unit);
		}
		else
		{
			unit->frame_sequence = FRAMES_PLAYER_WALK;
			unit->frame_count = FRAMES_PLAYER_WALK_COUNT;

			unit->frame_x = FRAMES_PLAYER_WALK_RIGHT_X;
			unit->frame_xc = FRAMES_PLAYER_WALK_RIGHT_XC;
			unit->frame_y = FRAMES_PLAYER_WALK_RIGHT_Y;
			unit->frame_yc = FRAMES_PLAYER_WALK_RIGHT_YC;
		}
		if (unit->JumpCount < unit->JumpStage && (!unit->JumpCount || keySpaceHasUp))
		{
			unit->JumpCount++;
			keySpaceHasUp = false;
			unit->hover = true;
			unit->vy = -SPEED_PLAYER_JUMP;
			//unit->ay = unit->g;
		}
		
		
	}
	else if (keyADown && !keyDDown && keyShiftDown && keySpaceDown) // A+Lshift+Space
	{
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -SPEED_PLAYER_RUN;

		if (attack)
			Attack(unit);
		else
		{
			unit->frame_sequence = FRAMES_PLAYER_RUN;
			unit->frame_count = FRAMES_PLAYER_RUN_COUNT;
			unit->frame_x = FRAMES_PLAYER_WALK_LEFT_X;
			unit->frame_xc = FRAMES_PLAYER_WALK_LEFT_XC;
			unit->frame_y = FRAMES_PLAYER_WALK_LEFT_Y;
			unit->frame_yc = FRAMES_PLAYER_WALK_LEFT_YC;
		}
		
		if (unit->JumpCount < unit->JumpStage && (!unit->JumpCount || keySpaceHasUp)) //多段跳计数器
		{
			unit->JumpCount++;
			keySpaceHasUp = false;
			unit->hover = true;
			unit->vy = -SPEED_PLAYER_JUMP;
			//unit->ay = unit->g;
		}
	}
	else if (!keyADown && keyDDown && keyShiftDown && keySpaceDown) // D+Lshift+Space
	{
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = SPEED_PLAYER_RUN;

		if (attack)
			Attack(unit);
		else
		{
			unit->frame_sequence = FRAMES_PLAYER_RUN;
			unit->frame_count = FRAMES_PLAYER_RUN_COUNT;
			unit->frame_x = FRAMES_PLAYER_WALK_RIGHT_X;
			unit->frame_xc = FRAMES_PLAYER_WALK_RIGHT_XC;
			unit->frame_y = FRAMES_PLAYER_WALK_RIGHT_Y;
			unit->frame_yc = FRAMES_PLAYER_WALK_RIGHT_YC;
		}
		if (unit->JumpCount < unit->JumpStage && (!unit->JumpCount || keySpaceHasUp))		//多段跳计数器
		{
			unit->JumpCount++;
			keySpaceHasUp = false;
			unit->hover = true;
			unit->vy = -SPEED_PLAYER_JUMP;
			//unit->ay = unit->g;
		}
	
	}

	int original_x = unit->x;
	int original_y = unit->y;
	//动画运行到下一帧
	//if (unit->hover)

	//技能
	unit->FX1 = false;
	if (keyWDown && unit->hover && unit->mana)	//F:浮空
	{
		unit->FX1 = true;

		unit->ax = 0;

		unit->vx = 0;
		unit->vy = 0.25*sin(unit->time/15.0);

		//AllocConsole();
		//_cprintf("i=%lf\n", unit->vy);

		unit->y += unit->vy;

		//unit->JumpCount = 0;

		unit->mana--;
		unit->mana_recover_time = PLAYER_MANA_RECOVER_TIME;
	}
	else										//常规
	{
		unit->ay = unit->g;
		unit->vx += unit->ax;
		unit->vy += unit->ay;
		unit->x += unit->vx;
		unit->y += unit->vy;

	}

	//AllocConsole();
	//_cprintf("%lf\n", unit->vy);

	bool collision_with_ground = false;
	int collision_id = CollisionDetectionForRectAndRect(unit, terrains);
	while (collision_id >= 0)
	{
		if (terrains[collision_id]->type & TR_GATE)
		{
			mission_success = true;
			break;
		}
		if (!(terrains[collision_id]->type & TR_NO_COLLISION))
		{
			//replace
			unit->x = original_x;
			unit->y = original_y;
			unit->hover = false;

			//physical collision event
			if (terrains[collision_id]->type & TR_GROUND)	
			{
				if (unit->y + unit->cy <= terrains[collision_id]->y) //collision with ground
				{
					collision_with_ground = true;
					unit->hover = false;	//不再悬空
					unit->JumpCount = 0;
					unit->ax = 0;
					unit->ay = 0;
					unit->y = terrains[collision_id]->y - unit->cy - 1;
					unit->x += unit->vx;
					unit->vx = 0;
					unit->vy = 0;
				}
				else if (terrains[collision_id]->type & TR_MOVING)
				{
					unit->x += terrains[collision_id]->vx;
					unit->y += terrains[collision_id]->vy;
					unit->vx = terrains[collision_id]->vx;
					unit->vy = terrains[collision_id]->vy;
				}
				else
				{
					unit->vx = 0;
					unit->vy = 0;
				}
			}
			else
			{
				unit->ax = 0;
				unit->ay = 0;
				unit->vx = 0;
				unit->vy = 0;
			}
		}
		if (!collision_with_ground)
			unit->hover = true;

		if (terrains[collision_id]->type & TR_SPIKE)
		{
			if (abs(currentStage->time - terrains[collision_id]->timestamp) >= TR_SPIKE_CD) {
				unit->health -= TR_SPIKE_DAMAGE;
				terrains[collision_id]->timestamp = currentStage->time;
			}
			
		}
		if (terrains[collision_id]->id == 9 || terrains[collision_id]->id == 12)
		{
			terrains[collision_id]->visible = false;
		}

		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}

	collision_id = CollisionDetectionForRectAndRect(unit, bullets);
	while (collision_id >= 0)
	{
		unit->health -= bullets[collision_id]->damage;
		bullets[collision_id]->del = true;
		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}


	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	attack = false;

	keySpaceDown = keyspacedown;

	if (unit->mana_recover_time)
		--unit->mana_recover_time;
	else if(unit->mana < PLAYER_MANA_MAX)
		unit->mana++;
	
}

void UnitBehaviour_Bee(Unit* unit)
{
	if (unit->health <= 0)
	{
		Death(unit);
		return;
	}

	Unit* player = units[cam->follow_id];

	double dirX = player->x + player->cx / 2 - unit->x - unit->cx / 2;
	double dirY = player->y + player->cy / 2 - unit->y - unit->cy / 2;
	double dist = sqrt(dirX*dirX + dirY*dirY);

	unit->direction = 0;
	if (dirX > 1)
	{
		if (dirY > 1)
			unit->direction = UNIT_DIRECT_LOWER_RIGHT;
		else
			unit->direction = UNIT_DIRECT_UPPER_RIGHT;
	}
	else
	{
		if (dirY > 1)
			unit->direction = UNIT_DIRECT_LOWER_LEFT;
		else
			unit->direction = UNIT_DIRECT_UPPER_LEFT;
	}
	
	switch (unit->direction) {
	case UNIT_DIRECT_LOWER_LEFT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_LOWER_LEFT_X;
		unit->frame_xc = FRAMES_BEE_FLY_LOWER_LEFT_XC;
		unit->frame_y = FRAMES_BEE_FLY_LOWER_LEFT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_LOWER_LEFT_YC;
		break;
	case UNIT_DIRECT_LOWER_RIGHT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_LOWER_RIGHT_X;
		unit->frame_xc = FRAMES_BEE_FLY_LOWER_RIGHT_XC;
		unit->frame_y = FRAMES_BEE_FLY_LOWER_RIGHT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_LOWER_RIGHT_YC;
		break;
	case UNIT_DIRECT_UPPER_LEFT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_UPPER_LEFT_X;
		unit->frame_xc = FRAMES_BEE_FLY_UPPER_LEFT_XC;
		unit->frame_y = FRAMES_BEE_FLY_UPPER_LEFT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_UPPER_LEFT_YC;
		break;
	case UNIT_DIRECT_UPPER_RIGHT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_UPPER_RIGHT_X;
		unit->frame_xc = FRAMES_BEE_FLY_UPPER_RIGHT_XC;
		unit->frame_y = FRAMES_BEE_FLY_UPPER_RIGHT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_UPPER_RIGHT_YC;
		break;
	}

	//是否开始攻击追击
	if (!unit->attack && dist < unit->attack_range && !unit->attack_cd)
	{

		unit->attack_cd  = AT_CD_BEE;
		unit->attack = 1;

		unit->vx = 0;
		unit->vy = 0;
		unit->vx_limit = abs(AT_SPEED_BEE * dirX / dist);
		unit->vy_limit = abs(AT_SPEED_BEE * dirY / dist);
		//unit->ax = min(AT_ACC_BEE * dirX / dist, unit->vx_limit - unit->vx);
		//unit->ay = min(AT_ACC_BEE * dirY / dist, unit->vy_limit - unit->vy);
		unit->ax = AT_ACC_BEE * dirX / dist;
		unit->ay = AT_ACC_BEE * dirY / dist;
		unit->attack_x = player->x + player->cx / 2;
		unit->attack_y = player->y + player->cy / 2;
	}

	//是否停止攻击追击并结算伤害
	if (unit->attack)
	{
		if (sqrt(((unit->x + unit->cx / 2) - unit->attack_x) * ((unit->x + unit->cx / 2) - unit->attack_x)
			+ ((unit->y + unit->cy / 2) - unit->attack_y) * ((unit->y + unit->cy / 2) - unit->attack_y)) <= 2* AT_SPEED_BEE)
		{
			if (dist <= 20)
				player->health -= AT_DMG_BEE;

			unit->attack = 0;
		}
		
	}

	if(unit->attack)
	{
		unit->vx += unit->ax;
		unit->vy += unit->ay;
		
		if ((abs(unit->vx) > unit->vx_limit) || (abs(unit->vy) > unit->vy_limit))
		{
			unit->vx -= unit->ax;
			unit->vy -= unit->ay;
		}
	}
	else if(dist < AT_EYESIGHT_BEE)
	{
		unit->vx = SPEED_BEE * dirX / dist;
		unit->vy = SPEED_BEE * dirY / dist;
	}
	//AX, AY
	unit->x += unit->vx;
	unit->y += unit->vy;
	
	
	int collision_id = CollisionDetectionForRectAndRect(unit, terrains);
	while (collision_id >= 0)
	{
		//physical collision event

		unit->x -= unit->vx;
		unit->y -= unit->vy;
		unit->ax = 0;
		unit->ay = 0;
		unit->vx = 0;
		unit->vy = 0;

		unit->attack = 0;

		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	if (unit->attack_cd)
		unit->attack_cd--;

}

void UnitBehaviour_Bee2(Unit* unit)
{
	if (unit->health <= 0)
	{
		Death(unit);
		return;
	}

	Unit* player = units[cam->follow_id];

	double dirX = player->x + player->cx / 2 - unit->x - unit->cx / 2;
	double dirY = player->y + player->cy / 2 - unit->y - unit->cy / 2;
	double dist = sqrt(dirX * dirX + dirY * dirY);

	unit->direction = 0;
	if (dirX > 1)
	{
		if (dirY > 1)
			unit->direction = UNIT_DIRECT_LOWER_RIGHT;
		else
			unit->direction = UNIT_DIRECT_UPPER_RIGHT;
	}
	else
	{
		if (dirY > 1)
			unit->direction = UNIT_DIRECT_LOWER_LEFT;
		else
			unit->direction = UNIT_DIRECT_UPPER_LEFT;
	}

	switch (unit->direction) {
	case UNIT_DIRECT_LOWER_LEFT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_LOWER_LEFT_X;
		unit->frame_xc = FRAMES_BEE_FLY_LOWER_LEFT_XC;
		unit->frame_y = FRAMES_BEE_FLY_LOWER_LEFT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_LOWER_LEFT_YC;
		break;
	case UNIT_DIRECT_LOWER_RIGHT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_LOWER_RIGHT_X;
		unit->frame_xc = FRAMES_BEE_FLY_LOWER_RIGHT_XC;
		unit->frame_y = FRAMES_BEE_FLY_LOWER_RIGHT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_LOWER_RIGHT_YC;
		break;
	case UNIT_DIRECT_UPPER_LEFT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_UPPER_LEFT_X;
		unit->frame_xc = FRAMES_BEE_FLY_UPPER_LEFT_XC;
		unit->frame_y = FRAMES_BEE_FLY_UPPER_LEFT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_UPPER_LEFT_YC;
		break;
	case UNIT_DIRECT_UPPER_RIGHT:
		unit->frame_sequence = FRAMES_BEE_FLY;
		unit->frame_count = FRAMES_BEE_FLY_COUNT;
		unit->frame_x = FRAMES_BEE_FLY_UPPER_RIGHT_X;
		unit->frame_xc = FRAMES_BEE_FLY_UPPER_RIGHT_XC;
		unit->frame_y = FRAMES_BEE_FLY_UPPER_RIGHT_Y;
		unit->frame_yc = FRAMES_BEE_FLY_UPPER_RIGHT_YC;
		break;
	}

	if (dist < AT_ESCAPE_BEE2)
	{
		unit->vx = -SPEED_BEE2 * dirX / dist;
		if (unit->y > terrains[0]->y - 100)
			unit->vy = -SPEED_BEE2;
		else
			unit->vy = 0;
	}
	else if (dist < AT_RANGE_BEE2)
	{
		if (dist > AT_APPROACH_BEE2)
		{
			unit->vx = SPEED_BEE2 * dirX / dist;
			unit->vy = SPEED_BEE2 * dirY / dist;
		}
		else
		{
			unit->vx = 0;
			unit->vy = 0;
			if (!unit->attack_cd)
			{
				bullets.push_back(CreateBullet(unit->x + unit->cx / 2, unit->y + unit->cy / 2, player->x + player->cx / 2, player->y + player->cy / 2, BULLET_SPEED));
				unit->attack_cd = AT_CD_BEE2;
			}
		}
	}
	else if (dist < AT_EYESIGHT_BEE2)
	{
		unit->vx = SPEED_BEE2 * dirX / dist;
		unit->vy = SPEED_BEE2 * dirY / dist;
	}
	else
	{
		unit->vx = 0;
		unit->vy = 0;
	}

	//AX, AY
	unit->x += unit->vx;
	unit->y += unit->vy;


	int collision_id = CollisionDetectionForRectAndRect(unit, terrains);
	while (collision_id >= 0)
	{
		//physical collision event

		unit->x -= unit->vx;
		unit->y -= unit->vy;
		unit->ax = 0;
		unit->ay = 0;
		unit->vx = 0;
		unit->vy = 0;

		unit->attack = 0;

		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	if (unit->attack_cd)
		unit->attack_cd--;
}
void UnitBehaviour_Boss(Unit* unit)
{
	if (unit->health <= 0)
	{
		Death(unit);
		return;
	}
	
	Unit* player = units[cam->follow_id];
	double dirX = player->x + player->cx / 2 - unit->x - unit->cx / 2;
	double dirY = player->y + player->cy / 2 - unit->y - unit->cy / 2;
	double dist = sqrt(dirX * dirX + dirY * dirY);

	unit->vy = sin(unit->time / 15);
	if (unit->time % BOSS_MOVE_CD == 7)
	{
		unit->vx = ((rand() % 3) - 1);
	}

	unit->x += unit->vx;
	unit->y += unit->vy;

	if(dist < BOSS_EYESIGHT && unit->time % BOSS_SUMMON_CD == 0)
	{
		for (int i = 0; i < (rand() % 3); i++)
		{
			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE2, unit->x, unit->y, BEE2_HP_MAX));
		}
		for (int i = 0; i < (rand() % 3); i++)
		{
			units.push_back(CreateUnit(UNIT_SIDE_ENEMY, UNIT_TYPE_BEE, unit->x, unit->y, BEE_HP_MAX));
		}
	}

	int collision_id = CollisionDetectionForRectAndRect(unit, terrains);
	while (collision_id >= 0)
	{
		//physical collision event

		unit->x -= unit->vx;
		unit->y -= unit->vy;
		unit->ax = 0;
		unit->ay = 0;
		unit->vx = 0;
		unit->vy = 0;

		unit->attack = 0;

		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}
}

void Attack(Unit* unit)
{
	if (unit->frame_sequence == FRAMES_PLAYER_ATTACK) // 当前正在攻击
	{
		if ((unit->frame_id == FRAMES_PLAYER_ATTACK_COUNT - 1) && attack)
			unit->frame_id = -1;
		return;
	}
	unit->frame_sequence = FRAMES_PLAYER_ATTACK;
	unit->frame_count = FRAMES_PLAYER_ATTACK_COUNT;
	unit->frame_id = -1;				//重要，因为frame_id其实就是攻击动作的计时器
	if (unit->direction == UNIT_DIRECT_RIGHT) {
		unit->frame_x = FRAMES_PLAYER_ATTACK_RIGHT_X;
		unit->frame_xc = FRAMES_PLAYER_ATTACK_RIGHT_XC;
		unit->frame_y = FRAMES_PLAYER_ATTACK_RIGHT_Y;
		unit->frame_yc = FRAMES_PLAYER_ATTACK_RIGHT_YC;
	}
	else
	{
		unit->frame_x = FRAMES_PLAYER_ATTACK_LEFT_X;
		unit->frame_xc = FRAMES_PLAYER_ATTACK_LEFT_XC;
		unit->frame_y = FRAMES_PLAYER_ATTACK_LEFT_Y;
		unit->frame_yc = FRAMES_PLAYER_ATTACK_LEFT_YC;
	}

	//伤害
	for (int len = units.size(), i = 0; i < len; i++)
	{
		if (!units[i]->visible)
			continue;
		double dist = Dist(units[i]->x, units[i]->y,unit->x,unit->y);
		
		if (units[i]->side == UNIT_SIDE_ENEMY && dist <= unit->attack_range)
		{
			units[i]->health -= unit->attack_damage;
		}
	}
	return;
}

void Death(Unit *unit)
{
	if (unit->death_cnt == -1)
	{
		unit->death_cnt = 5;
		if (unit->type != UNIT_TYPE_PLAYER)
		{
			units[0]->health += rand() % 10;
			units[0]->health = min(units[0]->health, PLAYER_HP_MAX);
		}
		unit->time = 0;
	}
	else if (unit->death_cnt > 0)
	{
		if (unit->time % 6 == 0)
		{
			unit->death_cnt--;
			unit->visible ^= 1;
		}
	}
	else
	{
		unit->del = true;
		if (unit->type == UNIT_TYPE_BOSS)
			mission_success = true;
		if (unit->type == UNIT_TYPE_PLAYER)
			mission_failed = true;
	}
}
double Dist(double x1, double y1, double x2, double y2)
{
	double ans = 0;
	ans = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
	return ans;
}

void UnitBehaviour_1(Unit* unit) {

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;


	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		if (dirLen < 400) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	case UNIT_STATE_WALK:
		if (dirLen >= 400) {
			next_state = UNIT_STATE_HOLD;
		}
		else if (dirLen < 200) {
			next_state = UNIT_STATE_ATTACK;
		}
		else {
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (dirLen >= 200) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		};
	}

	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}
void MyUnitBehaviour_2(Unit* unit)
{
	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y; 

	//move : A,D,Lshift,Space
	if (!keyADown && !keyDDown && !keySpaceDown)
	{
		if (!unit->hover)
		{
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
		}
	}
	else if (keyADown && !keyDDown && !keyShiftDown && !keySpaceDown) // A
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -4.0;

	}
	else if (!keyADown && keyDDown && !keyShiftDown && !keySpaceDown) // D
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = 4.0;
	}
	else if (keyADown && !keyDDown && keyShiftDown && !keySpaceDown) // A+Lshift
	{
		if (!unit->hover)
		{
			unit->frame_sequence = FRAMES_RUN;
			unit->frame_count = FRAMES_RUN_COUNT;
			unit->direction = UNIT_DIRECT_LEFT;
			unit->vx = -7.0;
		}
	}
	else if (!keyADown && keyDDown && keyShiftDown && !keySpaceDown) // D+Lshift
	{
		if (!unit->hover)
		{
			unit->frame_sequence = FRAMES_RUN;
			unit->frame_count = FRAMES_RUN_COUNT;
			unit->direction = UNIT_DIRECT_RIGHT;
			unit->vx = 7.0;
		}
	}
	else if (!keyADown && !keyDDown && !keyShiftDown && keySpaceDown) // Space
	{
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
	}
	else if (keyADown && !keyDDown && !keyShiftDown && keySpaceDown) // A+Space
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -4.0;
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
	}
	else if (!keyADown && keyDDown && !keyShiftDown && keySpaceDown) // D+Space
	{
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = 4.0;
	}
	else if (keyADown && !keyDDown && keyShiftDown && keySpaceDown) // A+Lshift+Space
	{
		unit->frame_sequence = FRAMES_RUN;
		unit->frame_count = FRAMES_RUN_COUNT;
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -7.0;
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
	}
	else if (!keyADown && keyDDown && keyShiftDown && keySpaceDown) // D+Lshift+Space
	{
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
		unit->frame_sequence = FRAMES_RUN;
		unit->frame_count = FRAMES_RUN_COUNT;
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = 7.0;
	}

	int original_x = unit->x;
	int original_y = unit->y;
	//动画运行到下一帧
	//if (unit->hover)
		unit->ay = unit->g;
	unit->vx += unit->ax;
	unit->vy += unit->ay;
	unit->x += unit->vx;
	unit->y += unit->vy;

	

	int collision_id = CollisionDetectionForRectAndRect(unit, terrains);
	while(collision_id >= 0)
	{
		//replace
		unit->x = original_x;
		unit->y = original_y;

		//physical collision event
		if ((terrains[collision_id]->type & TR_GROUND) && (unit->y + unit->cy <= terrains[collision_id]->y))	//collision with ground
		{
			unit->hover = false;	//不再悬空
			unit->ax = 0;
			unit->ay = 0;
			unit->y = terrains[collision_id]->y - unit->cy - 1;
			unit->x += unit->vx;
			unit->vx = 0;
			unit->vy = 0;
		}
		else
		{
			unit->ax = 0;
			unit->ay = 0;
			unit->vx = 0;
			unit->vy = 0;
		}
		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);
}
void UnitBehaviour_2(Unit* unit) {

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;
	double dirLen = sqrt(dirX * dirX + dirY * dirY) + 0.0001;


	if (dirX > 0) {
		unit->direction = UNIT_DIRECT_RIGHT;
	}
	else {
		unit->direction = UNIT_DIRECT_LEFT;
	}


	//判断当前状态, 以及判断是否需要状态变化
	int next_state = unit->state;
	switch (unit->state) {
	case UNIT_STATE_HOLD:
		next_state = UNIT_STATE_WALK;
		break;
	case UNIT_STATE_WALK:
		if (dirLen < 32) {
			next_state = UNIT_STATE_ATTACK;
		}
		else {
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
		}
		break;
	case UNIT_STATE_ATTACK:
		if (dirLen >= 32) {
			next_state = UNIT_STATE_WALK;
		}
		break;
	};

	if (next_state != unit->state) {
		//状态变化
		unit->state = next_state;
		unit->frame_id = -1;

		switch (unit->state) {
		case UNIT_STATE_HOLD:
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		case UNIT_STATE_WALK:
			unit->frame_sequence = FRAMES_WALK;
			unit->frame_count = FRAMES_WALK_COUNT;
			unit->vx = dirX / dirLen * UNIT_SPEED;
			unit->vy = dirY / dirLen * UNIT_SPEED;
			break;
		case UNIT_STATE_ATTACK:
			unit->frame_sequence = FRAMES_ATTACK;
			unit->frame_count = FRAMES_ATTACK_COUNT;
			unit->vx = 0;
			unit->vy = 0;
			break;
		};
	}

	//动画运行到下一帧
	unit->x += unit->vx;
	unit->y += unit->vy;

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;

	int column = unit->frame_sequence[unit->frame_id];
	unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);


}

void UnitBehaviour_marine(Unit* unit) 
{

	double dirX = mouseX - unit->x;
	double dirY = mouseY - unit->y;

	//move : A,D,Lshift,Space
	
	if (!keyADown && !keyDDown && !keyShiftDown && !keySpaceDown)
	{
		if (!unit->hover)
		{
			unit->frame_sequence = FRAMES_HOLD;
			unit->frame_count = FRAMES_HOLD_COUNT;
			unit->vx = 0;
			unit->vy = 0;
		}
	}
	
	if (keyADown && !keyDDown && !keyShiftDown && !keySpaceDown) // A
	{
		/*
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -4.0;
		*/
		unit->frame_sequence = FRAMES_MARINE_WALK;
		unit->frame_x = FRAMES_MARINE_WALK_X;
		unit->frame_xb = FRAMES_MARINE_WALK_XB;
		unit->frame_y = FRAMES_MARINE_WALK_Y;
		unit->frame_yb = FRAMES_MARINE_WALK_YB;
		unit->frame_count = FRAMES_MARINE_WALK_COUNT;
		unit->direction = UNIT_DIRECT_LEFT;

		unit->vx = -4.0;

	}
	/*
	else if (!keyADown && keyDDown && !keyShiftDown && !keySpaceDown) // D
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = 4.0;
	}
	else if (keyADown && !keyDDown && keyShiftDown && !keySpaceDown) // A+Lshift
	{
		if (!unit->hover)
		{
			unit->frame_sequence = FRAMES_RUN;
			unit->frame_count = FRAMES_RUN_COUNT;
			unit->direction = UNIT_DIRECT_LEFT;
			unit->vx = -7.0;
		}
	}
	else if (!keyADown && keyDDown && keyShiftDown && !keySpaceDown) // D+Lshift
	{
		if (!unit->hover)
		{
			unit->frame_sequence = FRAMES_RUN;
			unit->frame_count = FRAMES_RUN_COUNT;
			unit->direction = UNIT_DIRECT_RIGHT;
			unit->vx = 7.0;
		}
	}
	else if (!keyADown && !keyDDown && !keyShiftDown && keySpaceDown) // Space
	{
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
	}
	else if (keyADown && !keyDDown && !keyShiftDown && keySpaceDown) // A+Space
	{
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_LEFT;
		unit->vx = -4.0;
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
	}
	else if (!keyADown && keyDDown && !keyShiftDown && keySpaceDown) // D+Space
	{
		if (!unit->hover)
		{
			unit->hover = true;
			unit->vy = -10.0;
			//unit->ay = unit->g;
		}
		unit->frame_sequence = FRAMES_WALK;
		unit->frame_count = FRAMES_WALK_COUNT;
		unit->direction = UNIT_DIRECT_RIGHT;
		unit->vx = 4.0;
	}
	else if (keyADown && !keyDDown && keyShiftDown && keySpaceDown) // A+Lshift+Space
	{
		clock();
	}
	else if (!keyADown && keyDDown && keyShiftDown && keySpaceDown) // D+Lshift+Space
	{
	}
	*/

	int original_x = unit->x;
	int original_y = unit->y;
	//动画运行到下一帧
	//if (unit->hover)
	unit->ay = unit->g;
	unit->vx += unit->ax;
	unit->vy += unit->ay;
	unit->x += unit->vx;
	unit->y += unit->vy;



	int collision_id = CollisionDetectionForRectAndRect(unit, terrains);
	while (collision_id >= 0)
	{
		//replace
		unit->x = original_x;
		unit->y = original_y;

		//physical collision event
		if ((terrains[collision_id]->type & TR_GROUND) && (unit->y + unit->cy <= terrains[collision_id]->y))	//collision with ground
		{
			unit->hover = false;	//不再悬空
			unit->ax = 0;
			unit->ay = 0;
			unit->y = terrains[collision_id]->y - unit->cy - 1;
			unit->x += unit->vx;
			unit->vx = 0;
			unit->vy = 0;
		}
		else
		{
			unit->ax = 0;
			unit->ay = 0;
			unit->vx = 0;
			unit->vy = 0;
		}
		collision_id = CollisionDetectionForRectAndRect(unit, terrains, collision_id + 1);
	}

	unit->frame_id++;
	unit->frame_id = unit->frame_id % unit->frame_count;
	//int column = unit->frame_sequence[unit->frame_id];
	//unit->frame_column = column + unit->direction * (UNIT_LAST_FRAME - 2 * column);

}



#pragma endregion


#pragma region 绘图函数
// 绘图函数
void Paint(HWND hWnd)
{

	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);
	HDC hdc_text = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	blankBmp = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, blankBmp);

	// all sorts of calculation that translate map_x_y to camera_x_y then paint！！

	//暂停界面
	if(currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_CNT && currentStage->timerOn == false)
	{
		SelectObject(hdc_loadBmp, bmp_Pause);
		TransparentBlt(
			hdc_memBuffer, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0,
			BG_PAUSE_WIDTH, BG_PAUSE_HEIGHT,
			RGB(255, 255, 255));

		for (int i = 0; i < buttons.size(); i++)
		{
			Button* button = buttons[i];
			if (button->pause)
			{
				SelectObject(hdc_loadBmp, button->img);
				TransparentBlt(
					hdc_memBuffer, button->x, button->y,
					BUTTON_DEFAULT_WIDTH, BUTTON_DEFAULT_HEIGHT,
					hdc_loadBmp, 0, 0, button->width, button->height,
					RGB(255, 255, 255)
				);
			}
		}


		// 最后将所有的信息绘制到屏幕上
		BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

		// 回收资源所占的内存（非常重要）
		DeleteObject(blankBmp);
		DeleteDC(hdc_memBuffer);
		DeleteDC(hdc_loadBmp);

		// 结束绘制
		EndPaint(hWnd, &ps);
		return;
	}

	// 绘制背景到缓存
	//SelectObject(hdc_loadBmp, currentStage->bg);
	//SelectObject(hdc_loadBmp, bmp_Background);
	//BitBlt(hdc_memBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_loadBmp, 0, 0, SRCCOPY);
	//GetBackGround(hWnd, currentStage->bg);

	int cam_x = 0;
	int x_src;
	int xc_src;
	int y_src;
	int yc_src;
	switch (currentStage->stageID) {
	case STAGE_STARTMENU:
		SelectObject(hdc_loadBmp, bmp_StartMenu);
		TransparentBlt(
			hdc_memBuffer, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0,
			BG_STARTMENU_WIDTH, BG_STARTMENU_HEIGHT,
			RGB(255, 255, 255));
		break;
	case STAGE_1:
		SelectObject(hdc_loadBmp, bmp_Tutorial);
		if (cam == NULL)
			cam_x = 0;
		else
			cam_x = cam->x;

		x_src = cam_x % BG_TUTORIAL_SINGLE_WIDTH;
		y_src = 0;
		xc_src = WINDOW_WIDTH;//* BG_TUTORIAL_HEIGHT / WINDOW_HEIGHT;
		yc_src = BG_TUTORIAL_HEIGHT;

		TransparentBlt(
			hdc_memBuffer, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, x_src, y_src,
			xc_src, yc_src,
			RGB(255, 255, 255));
		break;
	case STAGE_2:
		SelectObject(hdc_loadBmp, bmp_Castle);
		if (cam == NULL)
			cam_x = 0;
		else
			cam_x = cam->x;

		x_src = cam_x % BG_CASTLE_SINGLE_WIDTH;
		y_src = 0;
		xc_src = WINDOW_WIDTH * BG_CASTLE_HEIGHT / WINDOW_HEIGHT;
		yc_src = BG_CASTLE_HEIGHT;

		TransparentBlt(
			hdc_memBuffer, 0, 0,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, x_src, y_src,
			xc_src, yc_src,
			RGB(255, 255, 255));
		break;

	case STAGE_HELP:
		SelectObject(hdc_loadBmp, bmp_Help0);
		TransparentBlt(
			hdc_memBuffer, -10, -10,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			RGB(0, 255, 0)
		);
		break;
	case STAGE_SUCCESS:
		SelectObject(hdc_loadBmp, bmp_Success);
		TransparentBlt(
			hdc_memBuffer, -10, -10,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			RGB(0, 255, 0)
		);
		break;
	default:
		break;
	}

	//绘制地形到缓存
	for (int len = terrains.size(), i = 0; i < len; i++)
	{
		Terrain* terrain = terrains[i];
		if (terrain->visible)
		{
			if(terrain->type & TR_BLOCK_2)
			{
				SelectObject(hdc_loadBmp, terrain->img);
				for (int i = 0; i < terrain->cx; i += terrain->img_width) // j = 0 : line 1
				{
					int cx = min(terrain->img_width, terrain->cx - i);
					int cy = min(terrain->img_height, terrain->cy);
					TransparentBlt(
						hdc_memBuffer, terrain->x + i - cam->x, terrain->y - cam->y,
						cx, cy,
						hdc_loadBmp, 0, 0, cx, cy,
						RGB(255, 255, 255));
				}
				SelectObject(hdc_loadBmp, bmp_block2_1);
				for (int i = 0; i < terrain->cx; i += TR_BLOCK2_1_WIDTH)
					for (int j = TR_BLOCK2_1_HEIGHT; j < terrain->cy; j += TR_BLOCK2_1_HEIGHT)
					{
						int cx = min(TR_BLOCK2_1_WIDTH, terrain->cx - i);
						int cy = min(TR_BLOCK2_1_HEIGHT, terrain->cy - j);
						TransparentBlt(
							hdc_memBuffer, terrain->x + i - cam->x, terrain->y + j - cam->y,
							cx, cy,
							hdc_loadBmp, 0, 0, cx, cy,
							RGB(255, 255, 255));
					}
			}
			else if (terrain->type & TR_SPIKE){
				SelectObject(hdc_loadBmp, terrain->img);
				for (int i = 0; i < terrain->cx; i += terrain->img_width) // j = 0 : line 1
				{
					int cx = min(terrain->img_width, terrain->cx - i);
					int cy = min(terrain->img_height, terrain->cy);
					TransparentBlt(
						hdc_memBuffer, terrain->x + i - cam->x, terrain->y - cam->y,
						cx, cy,
						hdc_loadBmp, 0, 0, cx, cy,
						RGB(0, 255, 0));
				}
			}
			else
			{
				SelectObject(hdc_loadBmp, terrain->img);
				for (int i = 0; i < terrain->cx; i += terrain->img_width)
					for (int j = 0; j < terrain->cy; j += terrain->img_height)
					{
						int cx = min(terrain->img_width, terrain->cx - i);
						int cy = min(terrain->img_height, terrain->cy - j);
						TransparentBlt(
							hdc_memBuffer, terrain->x + i - cam->x, terrain->y + j - cam->y,
							cx, cy,
							hdc_loadBmp, 0, 0, cx, cy,
							RGB(255, 255, 255));
					}
			}
		}
	}

#ifndef frameID
#define frameID unit->frame_sequence[unit->frame_id]
#endif 

	int x_in_camera = 0;
	int y_in_camera = 0;
	// 按场景分类绘制内容到缓存
	if (currentStage->stageID == STAGE_STARTMENU) {

	}
	else if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_CNT) //TODO：添加多个游戏场景
	{
		// 绘制单位到缓存
		for (int i = 0; i < units.size(); i++) {
			Unit* unit = units[i];

			if (!unit->visible)
				continue;

			SelectObject(hdc_loadBmp, unit->img);
			switch (unit->type)
			{
			case UNIT_TYPE_MARINE:
				
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * unit->cx, unit->y - 0.5 * unit->cy,
					unit->cx, unit->cy,
					hdc_loadBmp, unit->frame_x[frameID], unit->frame_y[frameID], unit->frame_xb[frameID] - unit->frame_x[frameID], unit->frame_yb[frameID] - unit->frame_y[frameID],
					RGB(0,0,0)
				);
				break;
			case UNIT_TYPE_PLAYER:
					
				x_in_camera = unit->x - cam->x;
				y_in_camera = unit->y -cam->y;
				
				if (unit->frame_sequence == FRAMES_PLAYER_ATTACK)
				{
					TransparentBlt(
						hdc_memBuffer, x_in_camera, y_in_camera + FRAMES_PLAYER_ATTACK_Y_CORRECT[frameID],
						unit->cx * unit->frame_xc[frameID] / FRAMES_PLAYER_WALK_RIGHT_XC[frameID], unit->cy * unit->frame_yc[frameID] / FRAMES_PLAYER_WALK_RIGHT_YC[frameID],
						hdc_loadBmp, unit->frame_x[frameID], unit->frame_y[frameID], unit->frame_xc[frameID], unit->frame_yc[frameID],
						RGB(0, 255, 0));
				}
				else
				{
					TransparentBlt(
						hdc_memBuffer, x_in_camera + (unit->direction == UNIT_DIRECT_LEFT ? -10 : 10), y_in_camera,
						unit->cx, unit->cy,
						hdc_loadBmp, unit->frame_x[frameID], unit->frame_y[frameID], unit->frame_xc[frameID], unit->frame_yc[frameID],
						RGB(0, 255, 0));
				}


				
				//fx
				if (unit->FX1)
				{
					SelectObject(hdc_loadBmp, bmp_FX1);
					TransparentBlt(
						hdc_memBuffer, x_in_camera, y_in_camera + unit->cy,
						unit->cx, FX1_HEIGHT,
						hdc_loadBmp, FRAMES_FX1_X[FRAMES_FX1[unit->time % FRAMES_FX1_COUNT]], FRAMES_FX1_Y[FRAMES_FX1[unit->time % FRAMES_FX1_COUNT]], FRAMES_FX1_XC[FRAMES_FX1[unit->time % FRAMES_FX1_COUNT]], FRAMES_FX1_YC[FRAMES_FX1[unit->time % FRAMES_FX1_COUNT]],
						RGB(0, 0, 0));
				
				}
				break;
			case UNIT_TYPE_BEE:
				x_in_camera = unit->x - cam->x;
				y_in_camera = unit->y - cam->y;
				TransparentBlt(
					hdc_memBuffer, x_in_camera + (unit->direction == UNIT_DIRECT_LEFT ? -10 : 10), y_in_camera,
					unit->cx, unit->cy,
					hdc_loadBmp, unit->frame_x[frameID], unit->frame_y[frameID], unit->frame_xc[frameID], unit->frame_yc[frameID],
					RGB(0, 255, 0));
				break;

			case UNIT_TYPE_BEE2:
				x_in_camera = unit->x - cam->x;
				y_in_camera = unit->y - cam->y;
				TransparentBlt(
					hdc_memBuffer, x_in_camera + (unit->direction == UNIT_DIRECT_LEFT ? -10 : 10), y_in_camera,
					unit->cx, unit->cy,
					hdc_loadBmp, unit->frame_x[frameID], unit->frame_y[frameID], unit->frame_xc[frameID], unit->frame_yc[frameID],
					RGB(0, 255, 0));

				break;
			case UNIT_TYPE_BOSS:
				x_in_camera = unit->x - cam->x;
				y_in_camera = unit->y - cam->y;
				TransparentBlt(
					hdc_memBuffer, x_in_camera + (unit->direction == UNIT_DIRECT_LEFT ? -10 : 10), y_in_camera,
					unit->cx, unit->cy,
					hdc_loadBmp, unit->frame_x[frameID], unit->frame_y[frameID], unit->frame_xc[frameID], unit->frame_yc[frameID],
					RGB(255, 255, 255));

				break;
			default:
				TransparentBlt(
					hdc_memBuffer, unit->x - 0.5 * unit->cx, unit->y - 0.5 * unit->cy,
					unit->cx, unit->cy,
					hdc_loadBmp, unit->cx * unit->frame_column, unit->cy * unit->frame_row, unit->cx, unit->cy,
					RGB(255, 255, 255)
				);
			}
		}

		//子弹绘制
		SelectObject(hdc_loadBmp, bmp_bullet);
		for (int i = 0, len = bullets.size(); i < len; i++)
		{
			Bullet* bullet = bullets[i];
			TransparentBlt(
				hdc_memBuffer, bullet->x - cam->x, bullet->y - cam->y,
				BULLET_WIDTH/1.2, BULLET_HEIGHT/1.2,
				hdc_loadBmp, 0, 0, BULLET_WIDTH, BULLET_HEIGHT,
				RGB(255, 255,255));
		}

		//UI绘制
		for (int i = 0, len = UIs.size(); i < len; i++)
		{
			UI* ui = UIs[i];
			SelectObject(hdc_loadBmp, ui->img);
			switch (ui->type)
			{
			case UI_HP:
				TransparentBlt(
					hdc_memBuffer, ui->x, ui->y,
					ui->cx * units[cam->follow_id]->health / PLAYER_HP_MAX, ui->cy,
					hdc_loadBmp, UI_HP_X, UI_HP_Y, UI_HP_CX, UI_HP_CY,
					RGB(0, 255, 0));
				break;
			case UI_MP:
				TransparentBlt(
					hdc_memBuffer, ui->x, ui->y,
					ui->cx* units[cam->follow_id]->mana / PLAYER_MANA_MAX, ui->cy,
					hdc_loadBmp, UI_HP_X, UI_HP_Y, UI_HP_CX, UI_HP_CY,
					RGB(0, 255, 0));
				break;
			default:
				TransparentBlt(
					hdc_memBuffer, ui->x, ui->y,
					ui->cx, ui->cy,
					hdc_loadBmp, 0, 0, UI_HP_WIDTH , UI_HP_HEIGHT,
					RGB(0, 255, 0));
				break;
			}
		}

	}


	// 绘制按钮到缓存

	for (int i = 0; i < buttons.size(); i++)
	{
		Button* button = buttons[i];
		if (button->visible)
		{
			SelectObject(hdc_loadBmp, button->img);
			TransparentBlt(
				hdc_memBuffer, button->x, button->y,
				BUTTON_DEFAULT_WIDTH, BUTTON_DEFAULT_HEIGHT,
				hdc_loadBmp, 0, 0, button->width, button->height,
				RGB(255, 255, 255)
			);
		}
	}

	//绘制游戏中的帮助界面
	if (currentStage->stageID >= STAGE_1 && currentStage->stageID <= STAGE_CNT && showHelp)
	{
		SelectObject(hdc_loadBmp, bmp_Help0);
		TransparentBlt(
			hdc_memBuffer, -10, -10,
			WINDOW_WIDTH, WINDOW_HEIGHT,
			hdc_loadBmp, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
			RGB(0, 255, 0)
		);
	}


	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteObject(blankBmp);
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);
	DeleteDC(hdc_text);


	// 结束绘制
	EndPaint(hWnd, &ps);
}

// 初始化背景函数
HBITMAP InitBackGround(HWND hWnd, HBITMAP bmp_src) {

	srand(time(NULL));
	PAINTSTRUCT ps;
	HDC hdc_window = BeginPaint(hWnd, &ps);

	HDC hdc_memBuffer = CreateCompatibleDC(hdc_window);
	HDC hdc_loadBmp = CreateCompatibleDC(hdc_window);

	//初始化缓存
	HBITMAP	bmp_output = CreateCompatibleBitmap(hdc_window, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(hdc_memBuffer, bmp_output);

	//加载资源
	SelectObject(hdc_loadBmp, bmp_src);


	for (int i = 0; i < BG_ROWS; i++) {

		int src_row = 1;
		if (i >= BG_ROWS_SKY)
			src_row = 0;

		for (int j = 0; j < BG_COLUMNS; j++) {
			int src_column = rand() % BG_SRC_COUNT;

			TransparentBlt(
				hdc_memBuffer, j*BG_CELL_WIDTH, i*BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				hdc_loadBmp, src_column * BG_CELL_WIDTH, src_row * BG_CELL_HEIGHT,
				BG_CELL_WIDTH, BG_CELL_HEIGHT,
				RGB(255, 255, 255)
			);

		}
	}

	// 最后将所有的信息绘制到屏幕上
	BitBlt(hdc_window, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdc_memBuffer, 0, 0, SRCCOPY);

	// 回收资源所占的内存（非常重要）
	DeleteDC(hdc_memBuffer);
	DeleteDC(hdc_loadBmp);

	// 结束绘制
	EndPaint(hWnd, &ps);

	return bmp_output;
}

#pragma endregion