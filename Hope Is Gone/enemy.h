enemy::enemy()
{
	x=10;
	y=10;
	startX=0;
	startY=0;
	speed=0;
	maxSpeed=3;
	startHealth=20;
	health=20;
	height=50;
	width=30;
	fallSpeed=0;
	fallA=0.08;
	fallMaxSpeed=3;
}

enemy::enemy(int _x, int _y, float _speed, int _startHealth, int _health, int _height, int _width, float fallSpeed, int _viewRadius)
{
	x=_x;
	y=_y;
	startX=x;
	startY=y;
	speed=_speed;
	startHealth=_startHealth;
	health=_health;
	height=_height;
	width=_width;
	fallSpeed=0;
	viewRadius=_viewRadius;
}

void enemy::SetData(int _x, int _y, float _speed, int _startHealth, int _health, int _height, int _width, float fallSpeed, int _viewRadius, float _maxSpeed)
{
	x=_x;
	y=_y;
	startX=x;
	startY=y;
	speed=_speed;
	startHealth=_startHealth;
	health=_health;
	height=_height;
	width=_width;
	fallSpeed=0;
	viewRadius=_viewRadius;
	maxSpeed=_maxSpeed;
}

void enemy::Move(float distance)
{
	x+=distance;
	if(CheckRightCol()||CheckLeftCol())
		x-=distance;
}

void enemy::Move()
{
	x+=speed;
	if(CheckRightCol()||CheckLeftCol())
		x-=speed;
}

void enemy::SetSpeed(float increment)
{
	if(speed>-maxSpeed&&speed<maxSpeed)
	    speed+=increment;
}

bool enemy::Hit(int force)
{
	health-=force;
	objects->AddNum(force,x+RandInt(-10,height+10),y+RandInt(-15,5));

	if(health<0)
		return true;
	else
		return false;

}


void enemy::Push(int xForce, int yForce)
{
	fallSpeed+=yForce;
	speed+=xForce;
}

bool enemy::CheckCeiling()
{
	if(exist50(x,y-1)||exist50(x+width,y-1)||exist50(x+width/2,y-1))
		return true;
	else
		return false;
}

bool enemy::CheckFloor()
{
	if(exist50(x,y+height)||exist50(x+width/2,y+height)||exist50(x+width,y+height))
		return true;
	else
		return false;
}

bool enemy::CheckLeftCol()
{
	if(exist50(x-1,y)||exist50(x-1,y+height/2)||exist50(x-1,y+height))
		return true;
	else
		return false;
}

bool enemy::CheckRightCol()
{
	if (exist50(x+width+1,y)||exist50(x+width+1,y+height/2)||exist50(x+width+1,y+height))
		return true;
	else
		return false;
}

bool enemy::HeroTrigger()
{
	if(hero->CrossZone((x+width/2),(y+height/2), viewRadius))
		return true;
	else
		return false;
}

void enemy::Update()
{
	if(!CheckFloor())
	{
		if(fallSpeed<fallMaxSpeed)
			fallSpeed+=fallA;
	}
	else
		fallSpeed=0;

	y+=fallSpeed;

	while(CheckFloor())
		y-=fallA;

	objects->CheckBulletCollision(*this);

	if(hero->CrossObj(x,y,width/2,height))
	{
		hero->Move(-1*((hero->x+hero->wt)-x));
		hero->Hit(10,-8);
	}

	if(hero->CrossObj(x+width/2,y,width/2,height))
	{
		hero->Move((x+width)-hero->x);
		hero->Hit(10,8);
	}

	if(health<=0)
		Kill();
}

void enemy::Kill()
{
	alive=false;
}