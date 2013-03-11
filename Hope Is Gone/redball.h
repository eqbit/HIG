
_redball::_redball()
{
	angle=0;
	tm=15;
	x=4000;
	y=13000;
	ht=43;
	wt=40;
	SetHP(50);
	anim=0;
	dieng=false;
	deathtm=0;
	deathlength=10000;
	exp=5;
	mainTxr=L"e_redball.png";
	shdTxr=L"e_redball_shadow.png";
	dieTxr=L"e_redball_die.png";
	damage=0;
	type=0;
}

void _redball::Add(int _x, int _y)
{
	x=_x;
	y=_y;
	strtx=x;
	strty=y;
	speed=0;
	angle=RandInt(0,360);
	dieng=false;
	mob_arr.push_back(this);
	if(RandInt(0,100)>80)
	{
	    mainTxr=L"e_yellowball.png";
	    shdTxr=L"e_yellowball_shadow.png";
	    dieTxr=L"e_redball_die.png";
	    maxspeed=RandInt(3,5);
		damage=80;
	    SetHP(100);
		type=1;
	}
	else
	{
		mainTxr=L"e_redball.png";
	    shdTxr=L"e_redball_shadow.png";
	    dieTxr=L"e_redball_die.png";
	    maxspeed=RandInt(7,10);
		damage=40;
	    SetHP(50);
		type=0;
	}

}

void _redball::Be()
{
	
	
	int lx=(x-5)/50,rx=(x+wt+5)/50,mx=(x+wt/2)/50,my=(y+ht/2)/50;
	hx=hero->x;
	hy=hero->y;

	if(hx>x+wt)
	{
		if(speed<maxspeed)
			speed+=RandInt(0,5)*0.01;
	}

	if(hx+hero->wt<x)
	{
		if(speed>(-maxspeed))
			speed-=RandInt(0,5)*0.01;
	}

	if(speed<0&&placed)
	{
		if(exist(lx,my)||!exist(lx,my+1))
		{
			if(!exist(lx,my-1)&&!exist(mx,my-1))
			    Jump();
			else
				speed=-speed/2;
		}
		else
		{
			if((exist(lx,my)||!exist(lx,my+1))&&!exist(lx,my-1)&&!exist(mx,my-1))
		    {
			    Jump();
		    }
		}
		
	}
	
	if(speed>0&&placed)
	{
		if((exist(rx,my)||!exist(rx,my+1)))
		{
			if(!exist(rx,my-1)&&!exist(mx,my-1)&&!exist(rx+1,my-1))
				Jump();
			else
				speed=-speed/2;
		}
		else
		{
			if((exist(rx,my)||!exist(rx,my+1))&&!exist(rx,my-1)&&!exist(mx,my-1))
		    {
			    Jump();
		    }
		}
	
	}

		

		

	Move(speed);
	


	
}

void _redball::Draw()
{
	if(camera->Vis(x,y)&&!deleted)
	{
	    
		
	    angle+=speed;
	    if(Alive())
	    {
			Live();

			if(crh&&!gameover)
	        {
		        hero->Hit(damage);
				hero->Push(speed*2);
				hero->Up(-5);
	        }
	        else
		    {
		    	Be();
	            DrawSprite(mainTxr,x,y,1,angle);
		    	DrawSprite(shdTxr,x,y,1);
		    }
	    }
	    else
	    {
		    if(!dieng)
		    {
		    	anim=CreateAnimation(dieTxr,12,RandInt(20,25),12,80,80);
		    	SoundPlay(L"e_rb_break.wav",1);
	            ResetAnimation(anim);
		    	dieng=true;
		    }
		    else
		    {
			    if(!DrawSpriteA(anim,x-20,y-20))
		        {
			        DeleteAnimation(anim);
					dieng=false;
			        anim=0;
			        deleted=true;
					
					if(type==1)
					{
						int j=RandInt(2,5);

						for(int i=0;i<j;i++)
							objects->AddLRedball(x+RandInt(-20,20),y+RandInt(-20,20));
					}
					GiveSome(x+wt/2,y-30,3,5,1,1);

		        }
		    }
	    }
	}

	if(deleted)
	{
		deathtm++;
		if(deathtm>deathlength)
		{
			Res();
			deleted=false;
		}
	}


}

bool _redball::Alive()
{
	if(hp>0)
		return true;
	else
		return false;
}

redballs::redballs()
{
	count=0;
}

redballs::~redballs()
{
	balls.clear();
}

void redballs::Add(int _x, int _y)
{
	balls.push_back(_redball());
	balls.at(count).Add(_x,_y);
	count++;
}

void redballs::Draw()
{
	for(int i=0;i<count;i++)
	{
		balls.at(i).Draw();
	}
}

void redballs::Save(ofstream &par)
{
	for(int i=0;i<count;i++)
	{
		int x=balls.at(i).strtx;
		int y=balls.at(i).strty;
		par<<1<<" "<<x<<" "<<y<<" ";
	}
}

void redballs::Clear()
{
	balls.clear();
	count=0;
}

void _redball::Jump()
{         
	
	 a=-6.3;
	 SoundPlayEx(L"raw.wav",1,x,y,0,1000);
}

bool _redball::CrossZone()
{
	if(cross(hx,hy,50,50,x-200,y-150,450,300))
		return true;
	else
		return false;
}

void _redball::TakeTarget()
{
	hx=hero->x;
	hy=hero->y;
	tx=(hx+20)/50;
	ty=(hy+20)/50;
}

void _redball::MakePath()
{
	bool xdir,ydir;
	int mx=(x+20)/50, my=(y+20)/50;

	if(mx<tx)
		xdir=false;
	else
		xdir=true;

	if(my<ty)
		ydir=true;
	else
		ydir=false;

}

