
_money::_money()
{
	x=y=0;
	count=0;
	deleted=false;
	lifetm=0;
	speed=0;
	a=0;
	fall_a=0;
	dir=true;
	up=true;
}


void _money::Add(int _x, int _y, int _count)
{
	SoundPlayEx(L"drop_coins.wav",1,_x,_y,0,1000);
	x=_x;
	y=_y;
	count=1;
	lifetm=0;
	deleted=false;
	if(rNum>50)
	{
		dir=true;
		speed=RandInt(0,4);
	}
	else
	{
		dir=false;
		speed=-RandInt(0,4);
	}
	up=true;
	fall_a=-RandInt(2,5);
	anim=CreateAnimation(L"coin.png",6,RandInt(10,15),6,20);
	
}

void _money::Draw()
{
	if(!deleted)
	{
		Throw();

		if(hero->CrossObj(x+5,y+5,10,10))
		{
			GiveMoney();
		}

		if(!DrawSpriteA(anim,x,y))
			ResetAnimation(anim);
	
		if(lifetm<3000)
			lifetm++;
	    else
		    Destroy();
	}
}

void _money::Throw()
{
	int lx=(x+4)/50,rx=(x+26)/50,mx=(x+25)/50,my=(y+25)/50,ty=(y+4)/50;

	if(!dir)
	{
		if(exist(lx,my))
		{
			speed=-speed;
			dir=!dir;
		}
	}
	else
	{
		if(exist(rx,my))
		{
			speed=-speed;
			dir=!dir;
		}
	}

	if(up)
	{
		if(fall_a>0)
			up=false;

		if(exist(mx,ty))
		{
			up=false;
			fall_a=0;
		}
	}
	else
	{
		if(!exist(mx,my))
		{
			fall_a+=0.1;
		}
		else
		{
			fall_a=0;
			speed=0;
		}
	}

	y+=fall_a;
	x+=speed;

	if(speed>0)
	{
		if(speed>0.1)
			speed-=0.005;
		else
			speed=0;
	}

	if(speed<0)
	{
		if(speed<-0.1)
			speed+=0.005;
		else
			speed=0;
	}

	fall_a+=0.1;	
}

void _money::GiveMoney()
{
	hero->AddMoney(count);
	SoundPlayEx(L"GotCoin.wav");
	Destroy();
}

void _money::Destroy()
{
	deleted=true;
	DeleteAnimation(anim);
	anim=0;
}

bool _money::Destroyed()
{
	if(deleted)
		return true;
	else
		return false;
}

void moneys::Add(int x, int y, int _count)
{
	mn.push_back(_money());
	mn.at(count).Add(x,y,_count);
	count++;
}



void moneys::Draw()
{
	for(int i=0;i<count;i++)
	{
		mn.at(i).Draw();

		if(mn.at(i).Destroyed())
		{
			if(i<count)
			{
				mn[i]=mn.back();
			}
			mn.pop_back();
			count --;
		}
	}
}

moneys::moneys()
{
	count = 0;
}

moneys::~moneys()
{
	mn.clear();
}

void moneys::Clear()
{
	count=0;
	mn.clear();
}