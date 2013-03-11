
int heroAnimDesk[15]={0,7,16,9,16,16,8,8,0,17,17,0,18,26,10};
int theroAnimDesk[6]={0,0,0,1,1,0};

_hero::_hero()
{
	// power, force, agility, intellect, stamina;
	power = 2;
	force = 1;
	agility = 1;
	intellect = 3;
	stamina = 1;

	x=4000;
	y=1053;
	hand_x=0;
	hand_y=0;
	ht=48;
	wt=26;
	tp=1;
	keyp=false;
	jumpTime=0;
	speed=4;
	maxspeed=4;
	SetHP(100);
	SetEnergy(50);
	SetHpRes(0);
	SetEnRes(0.03);
	steps=0;
	onFire=false;
	dieng=false;
	expiriense=0;
	money=0;
	onPlatform=false;
	tih=true;
	level=0;
	dir=true;
	h_angle=0;
	changeScene(0);
	anim=CreateAnimationEx(spr,heroAnimDesk,5,0,9,30,50);
	animF=CreateAnimation(L"docOnFireLoop.png",5,10,5,60,50);
	t_anim=CreateAnimationEx(L"docTAnim.png",theroAnimDesk,2,0,1,30,50);
	t_curAnim=1;
	curAnim=1;
	jAngle=0;
	jPower=0;
	curWpn=L"wpn_greenGun.png";
	curBlt=1;
	ganim=CreateAnimation(L"Alien.png",40,10,10,150,190);

	untouchable=false;
	untouchTime=0;
	allowDraw=true;
	allowMove=true;

	quaked=false;
	quakedTime=40;

	maxRockets=3;
	rockets=0;

	score=0;

	onStare=false;

	keySize=1;

	jump=false;
	jumpTime=0;

	curLvlIndex=1;
}

void _hero::Respawn()
{
	x=100;
	y=100;
	ht=48;
	wt=26;
	keyp=false;
	jumpTime=0;
	speed=0;
	hp=100;
	steps=0;
	onFire=false;
	dieng=false;
	maxspeed=4;
	allowDraw=true;
	untouchable=false;

	anim=CreateAnimationEx(spr,heroAnimDesk,5,0,9,30,50);
	curAnim=1;
	animF=CreateAnimation(L"docOnFireLoop.png",5,10,5,60,50);
}

void _hero::death()
{
	if(!gameover)
	{
		Live();
		if(!DrawSpriteA(anim,x,y))
	    {
		    gameover=true;
			objects->Add(4,x,y);
	    }
	}
	else
	{
		GameOver();
		Live();
		if(onFire)
		{
			if(!DrawSpriteA(animF,x,y))
			{
				ResetAnimation(animF);
			}
			

		    if(!GetSoundState(burn))
			    burn=SoundPlayEx(L"bodyfire.wav",0.1);
		}
	}
}

void _hero::Jump()
{
	a=-6;
	SoundPlayEx(L"jumpUp.wav",0.1);
}

bool _hero::Visible(int _x, int _y)
{
	if(!cross(x-1000,y-500,1100,2000,_x,_y,100,100))
	{
		return false;
	}
	else
		return true;
}


void _hero::changeScene(int i)
{
	if(i==1)
	{
		spr=andyAnim;
	}
	if(i==0)
	{
		spr=scntAnim;
	}
}

void _hero::Life()
{
	/*
	wchar_t name[]=L"àíòîí âàñÿ êîëÿ";
	const wchar_t *seps=L" ";
	token=wcstok(name,seps);
	int ij=0;
	while(token!=NULL)
	{
		Print(token,x-100,y-200+ij*30,0.5,3);
		DrawSprite(L"platform.png",x-80,y-200+ij*30,2);
		token=wcstok(NULL,seps);
		ij++;
	}*/

	if(!dieng)
	{
		Draw();
		//PrintDigit(x,0,x,y-100,1,1);
		//PrintDigit(timeD,5,x,y-50,1,1);
	}
	else
	{
		death();
	}
}

void _hero::Save(int mapIndex)
{
	ofstream out("saves/hero.sav");

	out<<mapIndex<<" "<<rockets<<" "<<score;

	out.close();
}

void _hero::Load()
{
	ifstream in("saves/hero.sav");
	int mapIndex;
	in>>mapIndex>>rockets>>score;
	hp=maxHP;
	energy=maxenergy;
	
	keyp=false;
	jumpTime=0;
	speed=0;
	steps=0;
	onFire=false;
	dieng=false;
	placed=false;
	SoundsStop();

	anim=CreateAnimationEx(spr,heroAnimDesk,5,0,9,30,50);
	animF=CreateAnimation(L"docOnFireLoop.png",5,10,5,60,50);
	curAnim=1;


	in.close();
}

void _hero::Draw()
{
	SetSoundListener(x,y);
	Interface();
	//InterfaceDigits(x,y);

	
	int _x=(x+wt/2),_y=(y+ht-15);


	if(placed||onStare)
	{
		jump=false;
		jumpTime=50;
	}

	if((KeyCheck(DIK_A)||KeyCheck(DIK_LEFTARROW)))
	{
		if(speed>0)
			speed=0;

		if(speed>(-maxspeed)&&!onStare)
		{
		    if(jumpTime>0)
			    speed-=0.4;
			else
				speed-=0.2;
		}

		curAnim=2;
	}

	if((KeyCheck(DIK_D)||KeyCheck(DIK_RIGHTARROW)))
	{
		if(speed<0)
			speed=0;

		if(speed<maxspeed&&!onStare)
		{
			if(jumpTime>0)
				speed+=0.4;
			else
				speed+=0.2;
		}

		curAnim=1;
	}
	
	if((KeyCheck(DIK_SPACE)||KeyCheck(DIK_UPARROW))&&!keyp&&placed&&!onStare)
	{
		Jump();
		jump=true;
		keyp=true;
	}

	if(onStare)
	{

		int riseSpeed=1;

		if(KeyCheck(DIK_W)&&world->CheckType(_x,_y-1)==16)
			y-=riseSpeed;

		if(KeyCheck(DIK_S)&&world->CheckType(_x,_y+1)==16)
			y+=riseSpeed;

		if(KeyCheck(DIK_SPACE))
		{
			onStare=false;
			a=-8.1;
		    SoundPlayEx(L"jumpUp.wav",0.1);
		    keyp=true;
		}

		if(KeyCheck(DIK_A)||KeyCheck(DIK_D))
			onStare=false;
	}

	Move(speed*timeD/10);

	if(quaked)
	{
		quakedTime--;

		if(quakedTime==0)
		{
			quakedTime=40;
			quaked=false;
		}
	}



	if(!placed&&!onStare)
	{
		switch(curAnim)
		{
		case 1: curAnim=3; break;
		case 2: curAnim=4; break;
		default:curAnim=3; break;
		}

		if(speed>maxspeed+1||speed<-maxspeed-1||(a<-8.2))
			objects->AddEffect(3,x-28+RandInt(-8,8),y-30+RandInt(-8,8));

		if(jumpTime>0)
			jumpTime--;
		else
		{
			if(speed>0)
			{
				speed-=0.09;

				if(speed<0.1)
					speed=0;
			}

			if(speed<0)
			{
				speed+=0.09;

				if(speed>-0.1)
					speed=0;
			}
		}
	}
	if(placed&&curAnim!=1&&curAnim!=2&&!onStare)
	{
		switch(curAnim)
		{
		case 3: curAnim=1;break;
		case 4: curAnim=2;break;
		default: curAnim=1;break;
		}
	}

	
	if(!onPlatform&&!onStare)
	    Live();
	else
		timer();

	if(world->CheckType(_x,_y)==8)
	{
		Hit(50);
		onFire=true;
		if(!GetSoundState(burn))
			burn=SoundPlayEx(L"bodyfire.wav",0.1);
	}
	else
	{
		if(onFire)
	    {
		    onFire=false;
		    if(GetSoundState(burn))
			        SoundStop(burn);
	    }
	}
	/*
	if(world->CheckType(_x,_y)==16)
	{
		Stare(_x-15);
	}
	else
	{
		onStare=false;
	}*/

	

	if(hp>0&&hp<maxHP&&!onFire)
		hp+=hpRes;

	EnergyStatus();
	
	/////ÍÅÓßÇÂÈÌÎÑÒÜ///////
	if(untouchable)
	{
		untouchTime--;
		if(untouchTime%2==0)
			allowDraw=!allowDraw;

		if(untouchTime<=0)
		{
			untouchable=false;
			allowDraw=true;
		}
	}
	

	/////////ÎÒÐÈÑÎÂÊÀ///////////

	SetAnimation(anim,curAnim);
	if(allowDraw)
	{
	    if(!DrawSpriteA(anim,x,y,2))
	    {
		    ResetAnimation(anim);
	    }
		if(!onStare)
			DrawSpriteA(t_anim,x,y+2,2);
	
	    
	   /* if(!DrawSpriteA(ganim,x+100,y+100,1,0,0.5))
		    ResetAnimation(ganim);*/

	    DrawSprite(L"bulletLight.png",-100,-100,1);

		if(!onStare)
			HandDraw();

	}
	if(!btncheck&&!btnchk)
		Create();


	if((!KeyCheck(DIK_A)&&!KeyCheck(DIK_D)&&!KeyCheck(DIK_LEFTARROW)&&!KeyCheck(DIK_RIGHTARROW)&&!KeyCheck(DIK_W)&&!KeyCheck(DIK_S)))
	{
		ResetAnimation(anim);
		SetAnimationSpeed(anim,0);
		if(speed!=0)
		{
			if(placed)
			{

			    if(speed<0)
			    {
				    if(speed<1)
					    speed+=0.4;
				    else
					    speed=0;
			    }
			    else
			    {
				    if(speed>1)
				    	speed-=0.4;
				    else
					    speed=0;
			    }
			}
			else
			{
				if(speed<0)
			    {
				    if(speed<0.5)
					    speed+=0.1;
				    else
					    speed=0;
			    }
			    else
			    {
				    if(speed>0.5)
				    	speed-=0.1;
				    else
					    speed=0;
			    }
			}
		}
	}

	

	if(hp<=0)
	{
		if(onFire)
		{
			anim=CreateAnimation(L"docOnFire.png",10,10,5,60,50);
			x-=15;
		}
		else
		{
			anim=CreateAnimation(L"docBleeding.png",10,15,5,100);
			SoundPlayEx(L"rustle.wav",0.3);
			x-=28;
		}
		dieng=true;
	    ResetAnimation(anim);
	}
	

	if(!KeyCheck(DIK_SPACE))
	{
		keyp=false;
	}
}

void _hero::Up(int up)
{
	a=up;
}

void _hero::ChExp(int ex)
{
	expiriense+=ex;
}

bool _hero::CrossObj(int _x, int _y, int _wt, int _ht)
{
	if(cross(x,y,ht,wt,_x,_y,_ht,_wt)&&Alive())
		return true;
	else
		return false;
}


bool _hero::Alive()
{
		if(hp>0)
		return true;
		else
			return false;
}

void _hero::OnPlat(bool on)
{
	onPlatform=on;
}

void _hero::Interface()
{
	int hpt=hp/dhp;
	int egt=energy/deg;

	for(int i=0;i<16;i++)
	{
		DrawSprite(L"eghpback_interface.png",125+i*8,30,0);
		DrawSprite(L"eghpback_interface.png",125+i*8,58,0);
	}

	for(int i=0;i<hpt;i++)
	{
		DrawSprite(L"hp_interface.png",125+i*8,30,0);
	}

	

	for(int i=0;i<egt;i++)
	{
		DrawSprite(L"eg_interface.png",125+i*8,58,0);
	}


	PrintDigit(score,0,320,67,0.5,0,COLOR(255,255,189,59));

	PrintDigit(rockets,0,342,20,1,0,COLOR(255,0,240,0));

	if(!gotKey)
		DrawSprite(L"havntKey.png",384,27,0);
	else
		DrawSprite(L"haveKey.png",384,27,0,0,keySize);

	if(keySize>1)
		keySize--;

	/*
	PrintDigit(hp,0,283,30,0.4,0,COLOR(255,10,10,10));
	PrintDigit(energy,0,283,60,0.4,0,COLOR(255,10,10,10));
	
	PrintDigit(money,0,403,30,0.4,0,COLOR(255,10,10,10));
	PrintDigit(expiriense,0,403,60,0.4,0,COLOR(255,10,10,10));
	*/
	if(DrawButton(winW-100,100,40,40,L"changeMode.png",L"changeMode.png",0))
	{
		if(creative)
		{
			creative=false;
			fight=true;
		}
		else
		{
		    if(fight)
		    {
			    fight=false;
			    obj_creative=true;
		    }
			else
			{
		        if(obj_creative)
		        {
			        obj_creative=false;
			        creative=true;
		        }
			}
		}
	}

	if(DrawButton(winW-100,150,40,40,L"musicOnOff.png",L"musicOnOff.png",0))
	{
		if(GetSoundState(GameTheme))
			SoundStop(GameTheme);
		else
			GameTheme=SoundPlayEx(L"mine_theme.wav",0.2,0,0,0,0,true,1000,10);
	}

	if(DrawButton(winW-100,200,40,40,L"fpsOnOff.png",L"fpsOnOff.png",0))
	{
		devHelp=!devHelp;
	}

	if(DrawButton(winW-100,200,40,40,L"fpsOnOff.png",L"fpsOnOff.png",0))
	{
		devHelp=!devHelp;
	}


	if(creative)
	{
		Print(L"CREATIVE",30,260,0.5);
	}

	if(fight)
	{
		Print(L"FIGHT",30,260,0.5);
	}

	if(obj_creative)
	{
		Print(L"MOB CREATE",30,260,0.5);

		if(DrawButton(100,150,30,30,L"turbtn.png",L"turbtn.png",0))
			tp=2;
		if(DrawButton(140,150,30,30,L"ballbtn.png",L"ballbtn.png",0))
			tp=1;
		if(DrawButton(180,150,30,30,L"h_gstbtn.png",L"h_gstbtn.png",0))
			tp=3;
		if(DrawButton(220,150,30,30,L"plt.png",L"plt.png",0))
			tp=4;
		if(DrawButton(260,150,30,30,L"golemBtn.png",L"golemBtn.png",0))
			tp=5;
		if(DrawButton(300,150,30,30,L"flyHeadBtn.png",L"flyHeadBtn.png",0))
			tp=6;
	}
}

void _hero::Key()
{
	gotKey=true;
	keySize=10;
}

void _hero::LevelUp(int type, float count)
{
}

void _hero::Create()
{
		if(creative)
	    {
		
		    if(MouseLBPress()&&!mscheck)
	        {
			    int _x=GetWorldX(),_y=GetWorldY();
		        world->Add(_x,_y,curType);
			    mscheck=true;
	        }

	         if(MouseRBPress()&&!mscheck)
	        {
		        world->Del(GetWorldX(),GetWorldY());
				mscheck=true;
	        }

	        if(KeyCheck(DIK_1)||KeyCheck(DIK_2)||KeyCheck(DIK_3)||KeyCheck(DIK_4)||KeyCheck(DIK_5)||KeyCheck(DIK_6)||KeyCheck(DIK_7)||KeyCheck(DIK_8)||KeyCheck(DIK_9)||KeyCheck(DIK_0))
	        {
		        curType=CurrentType();
	        }
	    }
		if(fight)
		{
			
			if(MouseLBPress()&&!mscheck&&energy>6.9&&!onStare)
			{
			    int _x=GetWorldX(),_y=GetWorldY();
				mscheck=true;

				for(int i=0;i<rgParts;i++)
					objects->Add(1,hand_x,hand_y,hand_x+20*cos(h_angle/180*3.14+i/10),hand_y+20*sin(h_angle/180*3.14+i/10));

				energy-=rgRate;
			}

			if(MouseRBPress()&&!mscheck&&!onStare)
			{
				if(rockets>0)
				{
				    int _x=GetWorldX(),_y=GetWorldY();
				    objects->Add(2,hand_x+10,hand_y,_x,_y);
				    mscheck=true;
					rockets--;
				}
				else
				{
					SoundPlay(L"outOfRockets.wav",1);
				    mscheck=true;
				}
			}
		}
		if(obj_creative)
		{
			if(MouseLBPress()&&!mscheck)
			{
				int _x=GetWorldX(),_y=GetWorldY();
				objects->Add(tp,_x,_y);
				mscheck=true;
			}
		}
}

void _hero::SetEnergy(int eg)
{
	energy=eg;
	maxenergy=eg;
	deg=eg/16;
}

void _hero::SetCurrentEnergy()
{
	deg=energy/16;
}

void _hero::Upgrade(int weaponIndex, int branch, int index)
{
	switch(weaponIndex)
	{
	case 1:
		{
			switch(branch)
			{
			case 1:
				{
					if(index==1)
					{
						rgDamage=22;
					}

					if(index==2)
					{
						rgDamage=35;
					}
				}
				break;

			case 2:
				{
					if(index==1)
					{
						rgRate=10;
					}

					if(index==2)
					{
						rgRate=8;
					}

					if(index==3)
					{
						rgRate=6;
					}
				}
				break;

			case 3:
				{
					if(index==1)
					{
						rgParts=2;
					}

					if(index==2)
					{
						rgParts=3;
					}
				}
				break;
			}
		}break;

    case 2:
		{
			switch(branch)
			{
			case 1:
				{
					if(index==1)
					{
						maxRockets=5;
					}

					if(index==2)
					{
						maxRockets=9;
					}
				}break;

			case 2:
				{
					if(index==1)
					{
						rtDamage=250;
					}

					if(index==2)
					{
						rtDamage=400;
					}
				}break;

			case 3:
				{
					if(index==1)
					{

					}

					if(index==2)
					{

					}
				}break;
			}

		}break;


	}

	Save(world->MapIndex());
}

void _hero::SetEnRes(float res)
{
	enRes=res;
}

void _hero::SetHpRes(float res)
{
	hpRes=res;
}

void _hero::AddMoney(int count)
{
	money+=count;
	AddScore(count);
	Save(world->MapIndex());
}

void _hero::AddScore(int scores)
{
	score+=scores;
}

int _hero::getScore()
{
	return score;
}


void _hero::TakeScore(int scores)
{
	score-=scores;
}
void _hero::HandDraw()
{
	
	float h_x=x+5, h_y=y+22;
	int cx=x+15;
	h_angle=atan2(mouseY-h_y,mouseX-h_x)*180/3.14;

	if(dir)
	{
		handLay=1;
		if(mouseX<cx)
		{
		    t_curAnim=2;
		    SetAnimation(t_anim,t_curAnim);
		    dir=false;
		}
	}

	if(!dir)
	{
		handLay=3;
		if(mouseX>cx)
		{
		    t_curAnim=1;
		    SetAnimation(t_anim,t_curAnim);
		    dir=true;
		}
	}

	
	hand_x=h_x+20*cos(h_angle/180*3.14);
	hand_y=h_y+20*sin(h_angle/180*3.14);

	DrawSprite(curWpn,x-26,h_y-10,handLay,h_angle);
}

void _hero::EnergyStatus()
{
	
	if(energy<0)
		energy=0;

	if(energy<maxenergy)
	{
		if(energy>25)
			energy+=enRes*3;
		else
		{
			if(energy>15)
			    energy+=enRes*2;
		    else
			    energy+=enRes;
		}
	}

	if(energy>maxenergy)
	{
		if(energy-maxenergy<1)
			energy=maxenergy;
		else
			energy-=enRes/2;

		SetCurrentEnergy();
	}
}

void _hero::AddEnergy(int _count)
{
	energy+=_count;
	if(energy>maxenergy)
	    SetCurrentEnergy();
}

void _hero::AddHP(int count)
{
	if(hp+count<=maxHP)
		hp+=count;
	else
		hp=maxHP;
}

void _hero::AddRockets(int count)
{
	if(rockets+count<=maxRockets)
	{
		rockets+=count;
		Save(world->MapIndex());
	}
	else
		rockets=maxRockets;
}

bool _hero::CrossZone(int _x, int _y, int rad)
{
	int mid_x=x+wt/2;
	int mid_y=y+ht/2;
	if(((mid_x-_x)*(mid_x-_x+(mid_y-_y)*(mid_y-_y))<rad*rad))
		return true;
	else
		return false;
}

void _hero::MakeRJ(int angle, int dist)
{
	jAngle=angle;

	if(dist!=0)
	    jPower=500/dist;
	else
		jPower=0;

	if(jPower>60)
		jPower=60;
	if(jPower<-60)
		jPower=-60;
}

void _hero::RocketJump()
{
	x+=jPower*cos((jAngle)/180*3.14);
	y+=jPower*sin((jAngle)/180*3.14);
	if(jPower<0)
		jPower+=0.2;
	if(jPower>0)
		jPower-=0.2;
	PrintDigit(jAngle,0,100,130);
	PrintDigit(jPower,5,100,160);
}


void _hero::ChangeWeapon(int weaponType)
{
	switch(weaponType)
	{
	case 0:
		SetCurWpn(L"wpn_pistol.png");
		break;
	case 1:
		SetCurWpn(L"wpn_laserGun.png");
		break;
	case 2:
		SetCurWpn(L"wpn_plazmaGun.png");
		break;
	case 3:
		SetCurWpn(L"wpn_greenGun.png");
		break;
	case 4:
		SetCurWpn(L"wpn_EpicGun.png");
			break;
	}
}

void _hero::SetCurWpn(wchar_t* wpnName)
{
	curWpn=wpnName;
}

void _hero::Quake(int damage)
{
	if(!quaked)
	{
		quaked=true;
		Hit(damage);
		Up(-4);
	}
}


void _hero::Hit(int force)
{
	if(!untouchable)
	{
		hp-=force;
	    SoundPlayEx(hit_sound,1,x,y,0,500);
	    Up(-1);
	    objects->AddNum(force,x+RandInt(-10,ht+10),y+RandInt(-15,5));

		untouchable=true;
		untouchTime=150;
	}

}

void _hero::Hit(int force, float _speed)
{
	if(!untouchable)
	{
		hp-=force;
	    Push(_speed);
	    SoundPlayEx(hit_sound,1,x,y,0,500);
	    Up(-1);
	    objects->AddNum(force,x+RandInt(-10,ht+10),y+RandInt(-15,5));

		untouchable=true;
		untouchTime=150;
	}

}

void _hero::Stare(int _x)
{

	if(KeyCheck(DIK_W)||KeyCheck(DIK_S))
	{
	    if(!onStare)
	    {
		    curAnim=5;
		    SetAnimation(anim,curAnim);
		    ResetAnimation(anim);
			speed=0;
	    }

		onStare=true;
		x=_x;
		placed=false;
	}

}


void _hero::SetCoordinats(int _x, int _y)
{
	x=_x;
	y=_y;
}


void _hero::Reset()
{
	hp=maxHP;
	money=0;
	rockets=maxRockets;
	energy=maxenergy;
	score=0;
	Save(1);

}