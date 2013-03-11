#include "windmill.h"
#include <time.h>
#include <MMSystem.h>
#include <vector>
#include <fstream>
using namespace std;
#include <string>
using std::vector;
#include "Resources.h"
#include <math.h>
#include "resource.h"
#pragma comment (lib, "windmill.lib")
#pragma comment (lib,"winmm.lib")
float len=0;
//Глобальные переменные
//параметры инициализации
wchar_t *windowCaption = L"Hope is Gone";
int winW = GetSystemMetrics(0),
	winH = GetSystemMetrics(1),
	windowIcon = IDI_ICON1,
	curType=1;
bool windowResize  = false,
	 windowFScreen = 0;

//Переменные таймера
int time1=0,
    time2=0,
	tD=0;

int curTm=timeGetTime();

//Переменные загрузки

bool loaded=false, choose=true, madeMap=false,
	saving=false,gameover=false;

//Переменные общие

bool keyp=false, mscheck=false,creative=false, fight = true, obj_creative=false, btncheck=false, devHelp=false;
bool checkKeys=false;
bool invent=false,btnchk=false, extWin=false;
unsigned long buttonClick;
unsigned long fireBurn;
unsigned long GameTheme;
int mouseX=GetMouseX(), mouseY=GetMouseY();
int mouseMX,mouseMY;
int obj_count=0;
int rNum=0;
int randtime=0,randNumber=0;
bool allowNextBullet=true;

//ПЕРЕМЕННЫЕ ЛАБОРАТОРИИ
int rgDamage=10;
int rgRate=14;
int rgParts=1;
int rtDamage=100;

//ПЕРЕМЕННЫЕ GAMEOVER
int goTime_back=0, goTimeNYA=0, goTimeDead=0, keyBoxNum=0;
bool gotKey=false;

//Функции
void gameUpdate();//запуск 
void gameRender();//рендер сцены
void GameTimer();//таймер
int RandInt(int min, int max); //возвращает целое в заданном диапазоне
int CurrentType();//возвращает текущий тип блока
void MapGenerator();//генерирует карту
bool Possible(int x, int y);//проверяет возможность создания блока по координатам
bool cross(int x_hero, int y_hero, int h_hero, int w_hero, int x_obj, int y_obj,  int h_obj, int w_obj);//проверяет пересечение
bool exist(int x, int y);//проверяет наличие блока по заданным координатам
bool exist50(int x, int y);//проверка наличия блока по координатам сетки
bool OthExist(int x, int y);
void Choose();//выбор персонажа
bool DrawButton(int _x, int _y, int _wt, int _ht, wchar_t *_pic, wchar_t *a_pic, int lay);//рисует кнопку с указанными параметрами
bool DrawMenuButton(int _x, int _y, wchar_t *_pic, wchar_t *a_pic);
void GameOver();//Ждет нажатия клавиши чтобы продолжить с места последнего сохранения
void Interface();
void ExitWindow();
void GiveSome(int x, int y, int money, int exp, bool aid, bool eg);
int GetTime();
void InterfaceDigits(int first, int second, int coef=0);
void DrawRectangle(int x1, int y1, int x2, int y2);
void DrawTrt(wchar_t* image, int x, int y, int transparency,int layer=0);
bool chance(int percent);
int getWidth();
int getHeight();
void ChangeLvl(int index);
void GiveStuff(int x, int y, bool ammunition, int Chance);
bool exist2(int x, int y);
int exponent(double digit);


//карта

void SaveMap();//функции загрузки
void LoadMap();

char* map_name="saves/start.wld";



#include "classHeads.h"
#include "World.h"





//WinMain
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	//timeStart = time(NULL);

	//Инициализация
	
	WindowIni(windowCaption,winW,winH,windowResize,windowFScreen,windowIcon,L"textures/cursor.cur");
	
	SetWindowLong(GetForegroundWindow(),GWL_STYLE,GetWindowLong(GetForegroundWindow(),GWL_STYLE)^WS_THICKFRAME^WS_MAXIMIZEBOX);
	ResourceIni();
	SceneManagerIni();
	SoundEngineIni(100,true);
	TextGen(L"Tahoma",32);


	world = new _world;
	//turret=new turrets;
	hero = new _hero;
	camera = new _camera;
	objects = new objs;
	lab = new laboratory;
	

	


	RunEngine(gameUpdate);

	delete world;
	delete camera;
	delete hero;
	//delete turret;
	delete objects;
	delete lab;
	//mob_arr.clear();
	return 0;
}

//Update & Render
void gameUpdate()
{

	srand(curTm);

	rNum=RandInt(0,100);

	mouseX=GetWorldX();
	mouseY=GetWorldY();
	mouseMX=GetMouseX();
	mouseMY=GetMouseY();
	btncheck=false;
	if(saving)
	{
		madeMap=false;
		world->Save();
		saving=false;
	}
	//updateFPS(); //Расcчет FPS

	if(KeyCheck(DIK_ESCAPE)&&!btnchk) 
	{
		if(choose&&!gameover)
		    choose=false;
		else
			if(!choose&&!gameover)
			    choose=true;

			btnchk=true;
	}
	if(loaded)
	{
		if(choose)
			Choose();
		else
		{
			gameRender();
		}
	}
	else
	{
		world->Load();
		loaded=true;
	}
	
	if(!MouseLBPress()&&!MouseRBPress())
	{
		mscheck=false;
	}

	if(!KeyCheck(DIK_I)&&!KeyCheck(DIK_ESCAPE))
	{
		btnchk=false;
	}

	if(extWin)
	{
		ExitWindow();
	}
}


void gameRender()
{
	if(!lab->Update())
	{
	    Interface();
	    allowNextBullet=true;
	    //PrintDigit(len,0,100,100);
	    GetTime();
	    time1=curTm;
	    DevelopHelp(devHelp,devHelp);
	    objects->Draw();
	    hero->Life();
	    camera->Draw();
	}
	/*
	PrintDigit(randNumber,0,100,400,0.5);
	randtime++;
	if(randtime==150)
	{
		randtime=0;
		randNumber=RandInt(1,3);
	}
	//PrintDigit(mob_arr.size(),0,100,200);*/
	

	

	if(KeyCheck(DIK_F5))
	{
		Print(L"Сохранение...",winW/2-50,100);
		saving=true;
	}

	if(KeyCheck(DIK_F9))
	{
		Print(L"Загрузка...",winW/2-50,100);
		loaded=false;
	}

	if(!KeysCheck())
		checkKeys=false;

	GameTimer();
	/*
	int mX=GetWorldX(), mY=GetWorldY();
	PrintDigit(world->CheckType(mX,mY),0,100,100,0.5);*/

}



#include "funcs.h"