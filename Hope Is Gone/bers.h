int ber_lightDesk[3]={0,0,0};
_ber_light::_ber_light()
{
	x=0;
	y=0;
	wt=60;
	ht=80;
	anim=0;
	curAnim=1;
	mvtm=0;
	dir=false;
	dead=false;
}

void _ber_light::Add(int _x, int _y)
{
	x=_x;
	y=_y;
	strtx=_x;
	strty=_y;
	speed=0;
	maxspeed=0.5;
	SetHP(100);
	dir=RandInt(0,1);
	anim=CreateAnimationEx(L"e_ber_light.png",ber_lightDesk,1,0,1,60,80);
	ResetAnimation(anim);
}

void _ber_light::Draw()
{
	Live();

	if(mvtm++>1000)
	{
		dir=!dir;
		mvtm=0;
	}

	if(dir)
	{
		if(speed<maxspeed)
			speed+=0.1;
		if(speed>maxspeed)
			speed-=0.1;
	}

	if(!dir)
	{
		if(speed>-maxspeed)
		    speed-=0.1;
		if(speed<-maxspeed)
			speed+=0.1;
	}

	x+=speed;

	if(!DrawSpriteA(anim,x,y))
		ResetAnimation(anim);
}

light_bers::light_bers()
{
	count = 0;
}

light_bers::~light_bers()
{
	ber.clear();
}

void light_bers::Add(int x, int y)
{
	ber.push_back(_ber_light());
	ber[count].Add(x,y);
	count++;
}

void light_bers::Draw()
{
	for(int i=0;i<count;i++)
	{
		ber[i].Draw();
	}
}