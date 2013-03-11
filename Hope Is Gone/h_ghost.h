int h_ghostDesk[27]={0,9,10,10,14,10,15,19,10,20,29,10,30,34,10,35,39,10,40,50,15,55,66,15,70,79,10};

_h_ghost::_h_ghost()
{
	SetHP(40);
	x=0;
	y=0;
	ht=48;
	wt=40;
	exp=4;
	mvtm=0;
	anim=0;
	curAnim=1;
	dir=false;
	dir_anim=1;
	lev=0;
	tang=false;
	alive=false;
	maxspeed=0.5;
	breath=0;
	dead=false;
	deathlength=1000;
	allowMove=false;
	vr=400;
	hits=false;
	hittm=0;
}

void _h_ghost::Draw()
{
	if(alive)
	{
		if(!dead)
		{
		    Live();
			Update();
		    Anim();
		}
		else
		{
			if(!DrawSpriteA(anim,x,y))
			{
				alive=false;
			}
		}

	
	}
	else
	{
		if(!created)
		{
			if(!DrawSpriteA(anim,x,y))
			{
				created=true;
				alive=true;
				anim=CreateAnimationEx(L"ghostAnim.png",h_ghostDesk,9,0,10,40,50,2);
				SetAnim(4);
			}
		}
		else
			Death();

	}
	
}

void _h_ghost::Update()
{
	
	if(hitting)
	{
		hitting=false;

		if(dir)
		{
			SetAnim(3);
		}
		else
		{
			SetAnim(6);
		}
	}

	if(hp<=0&&!dead)
		Kill();


	if(CheckHeroZone())
	{
		//PrintDigit(hittm,0,x-100,y-200,0.5,1);
		if(CrossHero())
		{
			if(!hits)
			{
			    hits=true;
				if(hero->Mid()>Mid())
					SetAnim(7);
				else
					SetAnim(8);
				hittm=0;
			}
			else
			{
				if(hittm>380)
				{
					hero->Hit(50,10);
					hittm=0;
				}
				hittm+=timeD;
				
			}

		}
		else
		{
			Moving();
			if(hits)
			{
				if(!DrawSpriteA(anim,x,y))
				{
					hits=false;
					hittm=0;
					if(dir)
						SetAnim(1);
					else
						SetAnim(4);
				}
			}
		}
	}

	if(!hero->Alive())
	{
		SetAnim(1);
	}
}

void _h_ghost::Anim()
{
	if(!DrawSpriteA(anim,x,y))
	{
		if(curAnim==3)
		{
			SetAnimation(anim,1);
		    curAnim=1;
		}

		if(curAnim==6)
		{
			SetAnimation(anim,4);
		    curAnim=4;
		}

		ResetAnimation(anim);
	}
}

void _h_ghost::Be()
{
	if(camera->Vis(x,y))
		Draw();
}

void _h_ghost::Kill()
{
	curAnim=9;
	SetAnimation(anim,curAnim);
	ResetAnimation(anim);
	SoundPlay(L"ghost_death.wav",1,x,y,0,1000);

	GiveSome(x+wt/2,y-30,2,3,1,1);
	dead=true;
}

void _h_ghost::Death()
{
	timer();
	deathtm+=timeD;
	if(deathtm>deathlength)
		Respawn();
}

void _h_ghost::Respawn()
{
	x=strtx;
	y=strty;
	anim=CreateAnimation(L"e_h_ghost_rise.png",10,15,10,40,50);
	ResetAnimation(anim);
	alive=false;
	created=false;
	speed=0;
	dead=false;
	SetHP(maxHP);
	deathtm=0;
}


void _h_ghost::Add(int _x, int _y)
{
	x=_x;
	y=_y;
	strtx=_x;
	strty=_y;
	stoptm=0;
	maxstoptm=RandInt(100,500);
	anim=CreateAnimation(L"e_h_ghost_rise.png",10,15,10,40,50);
	
	ResetAnimation(anim);
	alive=false;
	created=false;
}

void _h_ghost::SetAnim(int _curAnim)
{
	SetAnimation(anim,_curAnim);
	curAnim=_curAnim;
	ResetAnimation(anim);
}

h_ghosts::h_ghosts()
{
	count=0;
}

h_ghosts::~h_ghosts()
{
	gst.clear();
}

void h_ghosts::Add(int x, int y)
{
	gst.push_back(_h_ghost());
	gst.at(count).Add(x,y);
	count++;
}

void h_ghosts::Draw()
{
	for(int i=0;i<count;i++)
		gst[i].Be();
}



void h_ghosts::Save(ofstream &par)
{
	for(int i=0;i<count;i++)
	{
		int x=gst.at(i).strtx;
		int y=gst.at(i).strty;
		par<<3<<" "<<x<<" "<<y<<" ";
	}
}

void h_ghosts::Clear()
{
	gst.clear();
	count=0;
}


void _h_ghost::Moving()
{
	if(dir)
	{
		if(speed<maxspeed)
			speed+=timeD/100;
		if(dir_anim!=1)
		{
			SetAnim(1);
			dir_anim=1;
		}
	}
	else
	{
		if(speed>-maxspeed)
			speed-=timeD/100;
		if(dir_anim!=2)
		{
			SetAnim(4);
			dir_anim=2;
		}
	}

	Move(speed);
	mvtm+=timeD;
	if(mvtm>10000)
	{
		mvtm=0;
		dir=!dir;
	}
}

