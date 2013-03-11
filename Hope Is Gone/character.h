_character::_character()
{
	tang=true;
	x=y=ht=wt=0;
	a=0;
	mass=jmpower=hp=armor=0;
	gwx=gwy=0;
	jmp=false;
	menuWindow=false;
	crossCursor=false;
	placed=false;
	move=false;
	speed=0;
	maxHP=0;
	deleted=false;
	tih=crh=false;
	exp=0;
	hit_sound=L"e_rb_hit.wav";
	maxspeed=4;
	deathtm=0;
	deathlength=12000;
	allowMenu=false;
	vr=5;
	timeD=0;
	stTime=curTm;
	hitting=false;
	
}

void _character::Place()
{
	placed=true;
	a=0;
}

void _character::Res()
{
	x=strtx;
	y=strty;
	hp=maxHP;
	deathtm=0;
	a=0;
	speed=0;
}

bool _character::Visible()
{
	if(camera->Vis(x,y))
		return true;
	else
		return false;
}

bool _character::Col(int _x, int _y, int w, int h)
{
	if(cross(_x,_y,h,w,x,y,ht,wt))
		return true;
	else
		return false;
}

bool _character::CrossHero()
{
	if(cross(x,y,ht,wt,hero->x,hero->y,hero->ht,hero->wt))
		return true;
	else
		return false;
}

void _character::ShowHp()
{
	if((hp<maxHP||crossCursor)&&hp>0)
	{
		int ahp=hp/dhp;

		DrawSprite(spr_rhp,x+(wt/2-25),y-15);
		for(int i=0;i<ahp;i+=1)
		{
			DrawSprite(spr_hp,x+(wt/2-25)+i*3,y-15);
		}
	}
}

void _character::CheckSite()
{
	
	if(x<100)
		x=1100;
	if(x>world->width*50-300)
		x=world->width*50-100;

	if(y<100)
		y=100;
	if(y>world->height*50-550)
		y=world->height*50-550;
}


void _character::SetHP(int _hp)
{
	hp=maxHP=_hp;
	dhp=_hp/16;
}

void _character::Hit(int _hp)
{
	hp-=_hp;
	SoundPlayEx(hit_sound,1,x,y,0,500);
	a-=1;
	objects->AddNum(_hp,x+RandInt(-10,ht+10),y+RandInt(-15,5));
	hitting=true;
}
	

void _character::Live()
{
	CheckSite();
	timer();

	gwx=GetWorldX(),gwy=GetWorldY();

	if(cross(x,y,ht,wt,gwx,gwy,1,1))
	{
		crossCursor=true;
	}
	else
		crossCursor=false;

	if(!tih)
	    ShowHp();
	

	if(!tih)
	{
		crh=CrossHero();
	}

	



	
	if(tang)
	{
		TangLive();
	    CheckDamageBlock(); // проверка на наносящие урон блоки
	}
	else
	{
		GhostLive();
	}

	if(!tih)
		CheckBullet();
	/*
	int ax=(x+ht/2)/50,ay=(y+ht/2)/50;
	if(exist(ax,ay)&&cross(x,y,ht,wt,ax*50+20,ay*50+20,10,10))
		y-=30;*/

	if(speed>maxspeed)
		speed-=0.2;
	if(speed<-maxspeed)
		speed+=0.2;

}


void _character::CheckDamageBlock()
{
	int _x=(x+wt/2),_y=(y+ht-15);
	if(world->CheckType(_x,_y)==9&&hp>0)
	{
		Hit(hp+1);
	}
}

void _character::Move(float distance)
{
	float a=distance;

	if(a!=0)
	{

		if(a<0)
		{
			int lx=(x+a-1)/50,ty=y/50;
			int  i,hcnt;
			bool ok=true;
			for(i=0,hcnt=0;hcnt<ht;hcnt+=50, i++)
			{
				if(exist(lx,ty+i))
					ok=false;
			}
			if(exist(lx,(y+ht-1)/50))
				ok=false;

			if(ok)
				x+=a;

		}

		if(a>0)
		{
			int rx=(x+wt+a+1)/50,ty=y/50;
			int  i,hcnt;
			bool ok=true;
			for(i=0,hcnt=0;hcnt<ht;hcnt+=50, i++)
			{
				if(exist(rx,ty+i))
					ok=false;
			}
			if(exist(rx,(y+ht-1)/50))
				ok=false;

			if(ok)
				x+=a;

		}
				
			
	}
}


void _character::TangLive()
{
		y+=a;
	if(a<6)
		a+=0.2;
	placed=false;

	int wcnt=wt/50, hcnt=ht/50;
	int lx=(x-1)/50,rx=(x+wt+1)/50,ty=(y-1)/50,by=(y+ht+1)/50;

	if(exist(lx,by))
	{
		while(cross(x,y+ht-3,3,wt,lx*50+2,by*50,6,46))
			y--;
		placed=true;
		keyp=false;
	}
	if(exist(rx,by))
	{
		while(cross(x,y+ht-3,3,wt,rx*50+2,by*50,6,46))
			y--;
		placed=true;
		keyp=false;
	}

	if(exist(lx,ty))
	{
		y++;
		a=0;
	}
	if(exist(rx,ty))
	{
		y++;
		a=0;
	}
}

void _character::GhostLive()
{
	int wcnt=wt/50, hcnt=ht/50;
	int lx=(x-1)/50,rx=(x+wt+1)/50,ty=(y-1)/50,by=(y+ht+1)/50;

	y+=a;
	if(a<1)
		a+=0.1;
	placed=false;

	if(exist(lx,by))
	{
		while(cross(x,y+ht-3,3,wt,lx*50+2,by*50,6,46))
			y--;
		placed=true;
		keyp=false;
	}
	if(exist(rx,by))
	{
		while(cross(x,y+ht-3,3,wt,rx*50+2,by*50,6,46))
			y--;
		placed=true;
		keyp=false;
	}

	if(exist(lx,ty))
	{
		y++;
		a=0;
	}
	if(exist(rx,ty))
	{
		y++;
		a=0;
	}
}


void _character::Push(float dist)
{
	if(speed>-10&&speed<10)
	    speed+=dist;
}

void _character::CheckBullet()
{
	objects->CheckBullets(*this);
}

void _character::Hit(int _hp, int _speed)
{
	hp-=_hp;
	Push(_speed);
	objects->AddNum(_hp,x+RandInt(-10,ht+10),y+RandInt(-15,5));
	hitting=true;
}

bool _character::CheckHeroZone()
{
	if(cross(x-vr,y-vr,y+ht+vr,x+wt+vr,hero->x,hero->y,40,30)&&!gameover)
		return true;
	else
		return false;
}

void _character::timer()
{
	timeD=curTm-stTime;
	if(timeD>100)
		timeD=100;
	stTime=curTm;
}
