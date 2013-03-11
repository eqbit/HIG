_effect::_effect()
{
	type=1;
	sprite=L"";
	x=0;
	y=0;
	dtm=0;
	maxdtm=100;
	animated=false;
	number=false;
	anim=0;
	finished=false;
	size=1;
	num=0;
	showtm=50;
	red=green=blue=0;
	transparency=255;
	centrCoef=0;
	angle=0;
	a=0;
	speed=0;
	maxspeed=0.5;
}

void _effect::Add(int _type, int _x, int _y)
{
	x=_x;
	y=_y;
	type=_type;

	switch(_type)
	{
	case 1:
		animated=true;
		sprite=L"bulletExplodeLite.png";
		anim=CreateAnimation(sprite,8,RandInt(15,40),8,50,50);
		ResetAnimation(anim);/*
		if(hero->CrossZone(x,y,400))
		{
			int mid_x=hero->x+13, mid_y=hero->y;
			int length=sqrt((x-mid_x)*(x-mid_x)+(y-mid_y)*(y-mid_y));
			//h_angle=atan2(mouseY-h_y,mouseX-h_x)*180/3.14;
			int angle=atan2(y-mid_y,x-mid_x)*180/3.14;
			hero->MakeRJ(angle, length);
			len=length;
		}*/
		break;
	case 2:
		animated=true;
		sprite=L"jumpEffect.png";
		anim=CreateAnimation(sprite,8,RandInt(5,20),8,100);
		ResetAnimation(anim);
		size=0.6;
		break;
	case 3:
		animated=true;
		sprite=L"jumpCEffect.png";
		anim=CreateAnimation(sprite,4,RandInt(5,20),4,100);
		ResetAnimation(anim);
		break;
	case 4:
		animated=true;
		sprite=L"jumpCEffect.png";
		anim=CreateAnimation(sprite,4,RandInt(5,20),4,100);
		ResetAnimation(anim);
		size=RandInt(0,5)*0.1;
		centrCoef=100*size/2;
		break;
	case 5:
		{
		animated=true;
		sprite=L"rocketEffect.png";
		anim=CreateAnimation(sprite,5,RandInt(3,19),5,40);
		ResetAnimation;
		float sizeT=RandInt(5,13);
		size=sizeT/10;
		centrCoef=size*5;
		break;
		}
	case 6:
		{
		animated=true;
		sprite=L"plazma_explode.png";
		anim=CreateAnimation(sprite,25,RandInt(16,35),5,64,64,2);
		ResetAnimation(anim);
		angle=RandInt(0,360);
		float sizeT=RandInt(7,15);
		size=sizeT/10;
		centrCoef=32;
		break;
		}
	case 7:
		{
			animated=true;
			sprite=L"stuffBlockCrack.png";
			anim=CreateAnimation(sprite,10,25,10,150);
			ResetAnimation(anim);

			a=-3;

			break;
		}

	case 8:
		{
			animated=true;
			sprite=L"borderBlockCrack.png";
			anim=CreateAnimation(sprite,8,25,10,150);
			ResetAnimation(anim);

			a=-3;

			break;
		}
	}
}

void _effect::AddNum(int _num, int _x, int _y)
{
	num=_num;
	x=_x;
	y=_y;
	number=true;
	showtm=45;
	red=RandInt(150,255);
	green=RandInt(0,40);
	transparency=255;
	size=0.2;
}

void _effect::Draw()
{
	if(!finished)
	{
	    if(animated)
	    {
			if(camera->Vis(x,y))
			{
				if(!DrawSpriteA(anim,x-centrCoef,y-centrCoef,1,angle,size))
			    {
		    	    finished=true;
				    DeleteAnimation(anim);
				    anim=0;
			    }
			}
			else
			{
				finished=true;
				DeleteAnimation(anim);
				anim=0;
			}

	    }
		if(number)
		{
			PrintDigit(num,0,x,y,size,1,COLOR(transparency,red,green,0));

			if(showtm>30)
			{
			    y-=4*RandInt(0,2);
			    size+=0.04;
			}
			else
			{
				if(showtm<15)
				    transparency-=17;
			}

			showtm--;

			if(showtm<0)
				finished=true;
		}

		if(type==7||type==8)
		{
			if(a<0)
				a++;
			else
				a+=0.2;

			if(speed<maxspeed)
				speed+=a;

			y+=speed;
		}
	}
}

bool _effect::Finish()
{
	if(finished)
		return true;
	else
		return false;
}

effects::effects()
{
	count =0;
}

effects::~effects()
{
	eft.clear();
}

void effects::Add(int type, int x, int y)
{
	eft.push_back(_effect());
	eft.at(count).Add(type,x,y);
	count++;
}

void effects::AddNum(int num, int x, int y)
{
	eft.push_back(_effect());
	eft.at(count).AddNum(num,x,y);
	count++;
}

void effects::Clear()
{
	count = 0;
	eft.clear();
}

void effects::Destroy(int i)
{
	if(i<count)
		eft[i]=eft.back();

	eft.pop_back();
	count--;
}

void effects::Draw()
{
	for(int i=0;i<count;i++)
	{
		eft.at(i).Draw();

		if(eft.at(i).Finish())
			Destroy(i);
	}
}

