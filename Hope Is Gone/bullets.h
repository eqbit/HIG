_bullet::_bullet()
{
	x=0;
	y=0;
	speed=0;
	angle=0;
	damage=20;
	type=1;
	ex=false;
	dir=false;
	exploded=false;
	size=1;
	livetm=0;
	fall_a=0;
	anim=0;
	animated=false;
	shoot_sound=L"shotLite.wav";
	nextBulletTime=0;
	nextAdded=false;
	transparency=0;
}

void _bullet::Move()
{
	switch(type)
	{
	case 1:
		x+=speed*cos(angle/180*3.14);
		y+=speed*sin(angle/180*3.14);
		break;

	case 2:
		x+=speed*cos(angle/180*3.14);
		y+=speed*sin(angle/180*3.14);
		break;
		
	case 3:
		x+=speed;
		break;

	case 4:
		x+=speed*cos(angle/180*3.14);
		y+=speed*sin(angle/180*3.14);
		break;

	}
}

void _bullet::Add(float _x, float _y, float _tx, float _ty ,int _type)
{
	float sizeT=RandInt(7,15);
	type=_type;
	ex=true;
	
	int particleNum=RandInt(5,15);

	switch(_type)
	{
	case 1:
	    x=_x;
	    y=_y;
	    angle=atan2(_ty-_y,_tx-_x)*180/3.14;
		speed=5;
		size=sizeT/10;
		damage=RandInt(rgDamage, rgDamage+8);
	    shoot_sound=L"shotLite.wav";
		if(_tx>_x)
			dir=true;
		else
			dir=false;
		break;

	case 2:
		x=_x;
	    y=_y;
	    angle=atan2(_ty-_y,_tx-_x)*180/3.14;
		speed=6;
		size=1;
		damage=RandInt(rtDamage,rtDamage+50);
		shoot_sound=L"rocketLauncher.wav";
		if(_tx>_x)
			dir=true;
		else
			dir=false;
		animated=true;
		anim=CreateAnimation(L"rocketAnim.png",12,12,12,15,40,1);
		break;

	case 3:
		x=_x;
		y=_y;
		if(_tx>_x)
			speed=8;
		else
			speed=-8;
		damage=RandInt(15,40);
		//animated=true;
		//anim=CreateAnimation(L"stampHit.png",8,10,8,20,20);
		shoot_sound=L"rumble.wav";
		//ResetAnimation(anim);
		break;

	case 4:
		x=_x;
		y=_y;
	    angle=atan2(_ty-_y,_tx-_x)*180/3.14;
		speed=RandInt(1,4);
		shoot_sound=L"shotLite.wav";
		transparency=255;
		size=RandInt(1,2);
		break;

	case 5:

		for(int i=0;i<particleNum;i++)
			objects->Add(4,_x,_y,_x+RandInt(-20,20),_y+RandInt(-20,20));


		ex=false;

	}
	SoundPlayEx(shoot_sound,1,x,y,0,1500);
}

void _bullet::Explode()
{
	

	switch(type)
	{
	case 1:
	    ex=false;
		SoundPlayEx(L"explodeLite.wav",0.5,x,y,0,1500);
	    objects->AddEffect(1,x-20,y-20);
		break;

	case 2:
		exploded=true;
		SoundPlay(L"rocketExplode.wav",0.7,x,y,0,1500);


		break;

	case 3:
		ex=false;
		break;
	}
}

void _bullet::Draw()
{
	if(x<0||y<0||x>24000||y>14000)
		ex=false;
	if(ex)
	{
		
		switch(type)
		{
		case 1:
			{
			    size*=RandInt(8,10)*0.1;
			    int ccoef=(size*5);
			    DrawSprite(L"bull_light.png",x-ccoef,y-ccoef,2,0,size);
				/*
		        if(camera->Vis(x,y))
			    {
				    int coef=RandInt(-4,4);
		            objects->AddEffect(4,x+coef+ccoef,y+coef+ccoef);
			    }*/

			    size=1;
			    Move();
			}
			break;
		case 2:
			{
				if(!exploded)
				{
					if(!DrawSpriteA(anim,x-15,y-15,2,angle+90,0.8))
					    ResetAnimation(anim);
					if(camera->Vis(x,y))
					{
						objects->AddEffect(5,x-25,y-8);
					}
				    
				    Move();
			        break;
				}
				else
				{
					objects->AddEffect(6,x,y);
					ex=false;
				}
			}
			break;

		case 3:
			{
				//DrawSprite(L"bull_light.png",x,y,2,0,size);
				Move();
				if(!exist50(x,y+30)||!exist50(x+30,y+30)||exist50(x,y)||exist50(x+30,y))
					Explode();

				if(exist50(x+15,y+30))
				{
					int iX=(x+15)/50, iY=(y+30)/50;
					if(!world->map[iX][iY].Quaked())
						world->map[iX][iY].Quake();
				}

				if(hero->CrossObj(x,y,20,10))
				{
					hero->Quake(30);
				}
			}
			break;

		case 4:
			Move();
			DrawSprite(L"particle.png",x,y,1,angle,size,COLOR(transparency,255,255,255));
			transparency-=RandInt(5,15);
			if(transparency<30)
				ex=false;
			break;

		}

		int ax=(x)/50,ay=(y)/50,bx=(x+10)/50,by=(y+10)/50;
		if((exist(ax,ay))&&!exploded&&type!=3)
		{
			Explode();
			world->Hit(ax,ay,damage);
		}
		if((exist(bx,ay))&&!exploded&&type!=3)
		{
			Explode();
			world->Hit(bx,ay,damage);
		}
		if((exist(ax,by))&&!exploded&&type!=3)
		{
			Explode();
			world->Hit(ax,by,damage);
		}
		if((exist(bx,by))&&!exploded&&type!=3)
		{
			Explode();
			world->Hit(bx,by,damage);
		}

	}
}

void  _bullet::CheckCollision(_character &mob)
{
	if(type!=3&&type!=4)
	{
	    if(!exploded)
	    {
	        if(cross(x,y,5,5,mob.x+mob.wt/2-3,mob.y,mob.ht,6))
	        {
		    	if(ex)
				    Explode();

		        if(dir)
		            mob.Hit(damage,speed/2);
		        else
		    	    mob.Hit(damage,-speed/2);
	        }
	    }
	    else
	    {
		    if(cross(x-40,y-40,80,80,mob.x,mob.y,mob.ht,mob.wt))
		    {
			    if(dir)
			    	mob.Hit(damage,speed);
			    else
			    	mob.Hit(damage,-speed);
		    }
	    }
	}

}

void _bullet::CheckEnemy(enemy &mober)
{
	
	if(type!=3&&type!=4)
	{
		if(!exploded)
		{
			if(cross(mober.getX()+mober.getWidth()/2-3,mober.getY(),mober.getHeight(),6,x,y,10,10))
			{
				
				Explode();
				mober.Hit(damage);
			}
		}
	}
}


bool _bullet::There()
{
	if(ex)
		return true;
	else
		return false;
}

bullets::bullets()
{
	count=0;
}

bullets::~bullets()
{
	blt.clear();
}

void bullets::Add(int x, int y, int tx, int ty, int type)
{
	blt.push_back(_bullet());
	blt.back().Add(x,y,tx,ty,type);
}

void bullets::Draw()
{
	for(int i=0;i<BulletCount();i++)
	{
		blt.at(i).Draw();
		if(!blt.at(i).There())
		{
			if(i<BulletCount())
			{
				blt[i]=blt.back();
			}
			blt.pop_back();
		}
	}
}

bool bullets::There()
{
	if(BulletCount()>0)
		return true;
	else
		return false;
}

int bullets::BulletCount()
{
	return blt.size();
}

void bullets::CheckCollision(_character &mob)
{
	for(int i=0;i<BulletCount();i++)
	{
		blt[i].CheckCollision(mob);
	}
}

void bullets::CheckEnemyCollision(enemy &mober)
{
	for(int i=0;i<BulletCount();i++)
	{
		blt[i].CheckEnemy(mober);
	}
}