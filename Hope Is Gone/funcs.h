void GameTimer()  //Игровой таймер, держит фпс в границах 100
{
	time2=curTm;

	while(time2-10<time1)
	{
		Sleep(1);
		time2=timeGetTime();
	}

}

int GetTime()
{
	curTm=timeGetTime();
	return curTm;
}

int RandInt(int min,int max)
{
	return ((rand()%(max-min))+min);
}


int CurrentType() //возвращает идентификатор нажатой клавиши
{
	if(KeyCheck(DIK_1)&&!KeyCheck(DIK_LSHIFT))
	{
		return 1;
	}
	if(KeyCheck(DIK_2)&&!KeyCheck(DIK_LSHIFT))
	{
		return 2;
	}
	if(KeyCheck(DIK_3)&&!KeyCheck(DIK_LSHIFT))
	{
		return 3;
	}
	if(KeyCheck(DIK_4)&&!KeyCheck(DIK_LSHIFT))
	{
		return 4;
	}
	if(KeyCheck(DIK_5)&&!KeyCheck(DIK_LSHIFT))
	{
		return 5;
	}
	if(KeyCheck(DIK_6)&&!KeyCheck(DIK_LSHIFT))
	{
		return 6;
	}
	if(KeyCheck(DIK_7)&&!KeyCheck(DIK_LSHIFT))
	{
		return 7;
	}
	if(KeyCheck(DIK_8)&&!KeyCheck(DIK_LSHIFT))
	{
		return 8;
	}
	if(KeyCheck(DIK_9)&&!KeyCheck(DIK_LSHIFT))
	{
		return 9;
	}
	if(KeyCheck(DIK_0)&&!KeyCheck(DIK_LSHIFT))
	{
		return 10;
	}
	if(KeyCheck(DIK_1)&&KeyCheck(DIK_LSHIFT))
	{
		return 11;
	}
	if(KeyCheck(DIK_2)&&KeyCheck(DIK_LSHIFT))
	{
		return 12;
	}
	if(KeyCheck(DIK_3)&&KeyCheck(DIK_LSHIFT))
	{
		return 13;
	}
	if(KeyCheck(DIK_4)&&KeyCheck(DIK_LSHIFT))
	{
		return 14;
	}
	if(KeyCheck(DIK_5)&&KeyCheck(DIK_LSHIFT))
	{
		return 15;
	}
	if(KeyCheck(DIK_6)&&KeyCheck(DIK_LSHIFT))
	{
		return 16;
	}
	if(KeyCheck(DIK_8)&&KeyCheck(DIK_LSHIFT))
	{
		return 18;
	}

	
} 


void MapGenerator()  //генератор мира
{
	for(int i=0;i<winW;i++)
	{
		for(int j=25;j<50;j++)
		{
			if(j==32&&(i==5||i==6||i==7))
				world->Add(i*50,j*50,3);
			else
				world->Add(i*50,j*50,1);
		}
	}
}

bool Possible(int x, int y) //проверяет возможность существования блока по заданным координатам
{
	x=x/50;
	y=y/50;

	if(x>=0&&y>=0&&x<world->width&&y<world->height)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool cross(int x_hero, int y_hero, int h_hero, int w_hero, int x_obj, int y_obj,  int h_obj, int w_obj)
{
	if(x_hero+w_hero>x_obj && x_hero<x_obj+w_obj && y_hero<y_obj+h_obj && y_hero +h_hero>y_obj)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool exist(int x, int y)
{
	if(x>=0&&x<=world->width&&y>=0&&y<=world->height)
	{
	    if(world->map[x][y].is())
		    return true;
	    else
		    return false;
	}
	else
		return false;
}

bool exist2(int x, int y)
{
	if(x>=0&&x<=world->width&&y>=0&&y<=world->height)
	{
	    if(world->map[x][y].is2())
		    return true;
	    else
		    return false;
	}
	else
		return false;
}

bool exist50(int x, int y)
{
    x=x/50;
	y=y/50;
	if(x>=0&&x<=world->width&&y>=0&&y<=world->height)
	{
	    if(world->map[x][y].is())
		    return true;
	    else
		    return false;
	}
	else
		return false;
}

bool OthExist(int x, int y)
{
	if(x>=0&&x<=world->width&&y>=0&&y<=world->height)
	{
	    if(world->map[x][y].othEx())
		    return true;
	    else
		    return false;
	}
	else
		return false;
}


void btnClck(wchar_t *sound)
{
	if(!GetSoundState(buttonClick))
	{
		buttonClick=SoundPlayEx(sound);
	}
}

bool DrawMenuButton(int _x, int _y, wchar_t *_pic, wchar_t *a_pic)
{
	int x,y;
	x=GetMouseX();
	y=GetMouseY();

	int _ht=50;
	int _wt=150;
	
	if(MouseLBPress()&&cross(_x,_y,_ht,_wt,x,y,1,1)&&!mscheck)
	{
		mscheck=true;
		btnClck(L"buttonClick.wav");
		return true;
	}
	else
	{
		if(!cross(_x,_y,_ht,_wt,x,y,1,1))
			DrawSprite(_pic,_x,_y,0,0,0.5);
		else
		{
			DrawSprite(a_pic,_x,_y,0,0,0.6);
			btncheck=true;
		}
		return false;
	}
}

void Choose()
{
	int _i=winW/800+1, _j=winH/600+1;

	for(int i=0;i<_i;i++)
		for(int j=0;j<_j;j++)
			DrawSprite(L"menuBack.png",i*800,j*600,0);

	
	if(DrawMenuButton(70,winH-400,L"loadGame.png", L"loadGameActive.png"))
	{
		choose=false;
	    SoundsStop();
	    GameTheme=SoundPlayEx(L"mine_theme.wav",0.2,0,0,0,0,true,1000,10);
		gameover=false;
	}

	if(DrawMenuButton(70,winH-350,L"newGame.png", L"newGameActive.png"))
	{
		hero->Reset();
		ChangeLvl(1);
		choose=false;
	    SoundsStop();
	    GameTheme=SoundPlayEx(L"mine_theme.wav",0.2,0,0,0,0,true,1000,10);
		gameover=false;
	}


	if(DrawMenuButton(70,winH-300,L"options.png", L"optionsActive.png"))
	{
	}

	if(DrawMenuButton(70,winH-250,L"developersButton.png", L"developersButtonActive.png"))
	{
		ShellExecute(0, 0, L"http://www.google.com", 0, 0 , SW_SHOW );
	}

	if(DrawMenuButton(70,winH-200,L"exitGame.png", L"exitGameActive.png"))
	{
		PostQuitMessage(1);
	}

	Sleep(3);
}


bool DrawButton(int _x, int _y, int _wt, int _ht, wchar_t *_pic, wchar_t * a_pic,int lay)
{

	int x,y;
	if(lay==0)
	{
		x=GetMouseX();
	    y=GetMouseY();
	}
	else
	{
		x=GetWorldX();
		y=GetWorldY();
	}
	
	if(MouseLBPress()&&cross(_x,_y,_ht,_wt,x,y,1,1)&&!mscheck)
	{
		mscheck=true;
		btnClck(L"buttonClick.wav");
		return true;
	}
	else
	{
		if(!cross(_x,_y,_ht,_wt,x,y,1,1))
			DrawSprite(_pic,_x,_y,lay);
		else
		{
			DrawSprite(a_pic,_x,_y,lay);
			btncheck=true;
		}
		return false;
	}
		
}

void DrawTrt(wchar_t* image, int x, int y, int transparency,int layer)
{
	DrawSprite(image,x,y,layer,0,1,COLOR(transparency,255,255,255));
}

void GameOver()
{
	if(goTime_back<130)
		goTime_back+=1;
	else
	{
		if(goTimeNYA<255)
	    {
		    goTimeNYA+=3;
	    }
	    else
	    {
		    if(goTimeDead<255)
			    goTimeDead+=5;
	    }
	}

	for(int i=0;i<winW/800+1;i++)
	{
		for(int j=0;j<winH/600+1;j++)
			DrawTrt(L"DeadScreen_back.png",i*800,j*600,goTime_back);
	}

	DrawTrt(L"DeadScreen_nowYouAre.png",winW/2-91,250,goTimeNYA);
	DrawTrt(L"DeadScreen_dead.png",winW/2-250,350,goTimeDead);

	if(KeyCheck(DIK_SPACE)||MouseLBPress())
	{
		world->Load();
		mscheck=true;
		btnchk=true;
		goTimeNYA=0;
		goTimeDead=0;
		goTime_back=0;
		choose=true;
	}
}


void Interface()
{
	DrawSprite(L"hud.png",0,0,0);
}

void ExitWindow()
{
	DrawSprite(L"exitback.png",winW/2-100,winH/2-240,0);
	if(DrawButton(winW/2-60,winH/2-100,100,40,L"exitbtn.png",L"exitAbtn.png",0))
		PostQuitMessage(1);
	if(DrawButton(winW/2+60,winH/2-100,100,40,L"cancel_exitbtn.png",L"cancel_exitAbtn.png",0))
		extWin=false;
}

void GiveSome(int x, int y, int money, int exp=0, bool aid=false, bool eg=false)
{
	if(money>0)
	{
	    int times=RandInt(0,money);

	    for(int i=0;i<times;i++)
		    objects->AddMoney(x,y,3);
	}

	if(eg)
		if(rNum>90)
		    objects->AddStuff(x,y-30,1);
	if(aid)
		if(rNum<10)
			objects->AddStuff(x,y-30,2);
	if(rNum>50&&rNum<60)
		objects->AddStuff(x,y,3);
}

void GiveStuff(int x, int y, bool ammunition, int Chance)
{
	if(ammunition)
	{
		if(chance(Chance))
		{
			int i=RandInt(0,100);

			if(i<50)
				objects->AddStuff(x,y,1);
			else
			{
				if(i<90)
					objects->AddStuff(x,y,2);
				else
					objects->AddStuff(x,y,3);
			}

		}
		else
		{
			int j=RandInt(3,10);
			for(int i=0;i<j;i++)
				objects->AddMoney(x,y,1);
		}
	}
	else
		objects->AddStuff(x,y,4);
}

void InterfaceDigits(int first, int second, int coef)
{
	PrintDigit(first,0,100+coef,100,0.5);
	PrintDigit(second,0,100+coef,130,0.5);
}

void DrawRectangle(int x1, int y1, int x2, int y2)
{
	DrawLine(x1,y1,x2,y1,3);
	DrawLine(x1,y1,x1,y2,3);
	DrawLine(x1,y2,x2,y2,3);
	DrawLine(x2,y1,x2,y2,3);
}

bool chance(int percent)
{
	if(RandInt(0,100)>percent)
		return false;
	else
		return true;
}

int getWidth()
{
	return world->width;
}

int getHeight()
{
	return world->height;
}

void ChangeLvl(int index)
{
	switch(index)
		{
		case 1:
			world->ChangeMap("levels/start.map",1);
			break;
		case 2:
			world->ChangeMap("levels/second.map",2);
			break;
		case 3:
			world->ChangeMap("levels/marbleLvl.map",3);
			break;
		case 4:
			world->ChangeMap("levels/durt.map",4);
			break;
		case 5:
			world->ChangeMap("levels/firewalker.map",5);
		}
}

int exponent(double digit)
{
	int i=1;

	while(digit>10)
	{
		digit=digit/10;
		i++;
	}

	return i;
}