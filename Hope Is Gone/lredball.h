
_lredball::_lredball()
{
	angle=0;
	tm=15;
	x=4000;
	y=13000;
	ht=20;
	wt=20;
	SetHP(3);
	anim=0;
	dieng=false;
	deathtm=0;
	deathlength=10000;
	exp=5;
	mainTxr=L"lball.png";
	shdTxr=L"lball_shadow.png";
	dieTxr=L"lball_die.png";
	damage=0;
}

void _lredball::Add(int _x, int _y)
{
	x=_x;
	y=_y;
	strtx=x;
	strty=y;
	speed=0;
	angle=RandInt(0,360);
	dieng=false;
	mob_arr.push_back(this);
	mainTxr=L"l_ball.png";
	shdTxr=L"lball_shadow.png";
	dieTxr=L"lball_die.png";
	maxspeed=RandInt(6,9);
	damage=10;
	SetHP(10);

}

void _lredball::Be()
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

void _lredball::Draw()
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
				hero->Push(speed);
				hero->Up(-2);
	        }
	        else
		    {
		    	Be();
	            DrawSprite(mainTxr,x,y,1,angle);
		    	//DrawSprite(shdTxr,x,y,1);
		    }
	    }
	    else
	    {
		    if(!dieng)
		    {
		    	anim=CreateAnimation(dieTxr,12,RandInt(20,25),12,20,20);
		    	SoundPlay(L"e_rb_break.wav",1);
	            ResetAnimation(anim);
		    	dieng=true;
		    }
		    else
		    {
			    if(!DrawSpriteA(anim,x,y))
		        {
			        DeleteAnimation(anim);
					dieng=false;
			        anim=0;
			        deleted=true;
					
					GiveSome(x+wt/2,y-30,3,5,1,1);
		        }
		    }
	    }
	}


}

bool _lredball::Alive()
{
	if(hp>0)
		return true;
	else
		return false;
}

lredballs::lredballs()
{
	count=0;
}

lredballs::~lredballs()
{
	balls.clear();
}

void lredballs::Add(int _x, int _y)
{
	balls.push_back(_lredball());
	balls.at(count).Add(_x,_y);
	count++;
}

void lredballs::Draw()
{
	for(int i=0;i<count;i++)
	{
		balls.at(i).Draw();
	}
}

void lredballs::Save(ofstream &par)
{
	for(int i=0;i<count;i++)
	{
		int x=balls.at(i).strtx;
		int y=balls.at(i).strty;
		par<<1<<" "<<x<<" "<<y<<" ";
	}
}

void lredballs::Clear()
{
	balls.clear();
	count=0;
}

void _lredball::Jump()
{         
	
	 a=-6.3;
	 SoundPlayEx(L"l_raw.wav",1,x,y,0,1000);
}

bool _lredball::CrossZone()
{
	if(cross(hx,hy,50,50,x-200,y-150,450,300))
		return true;
	else
		return false;
}

void _lredball::TakeTarget()
{
	hx=hero->x;
	hy=hero->y;
	tx=(hx+20)/50;
	ty=(hy+20)/50;
}

void _lredball::MakePath()
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

