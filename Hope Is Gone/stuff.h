_stuff::_stuff()
{
	x=0;
	y=0;
	ht=30;
	wt=30;
	sprite=L"";
	a=0;
	lifetime=1500;
	max_a=6;
	blink=false;
	deleted=false;
	fly=0;
}

void _stuff::Add(int _type, int _x, int _y)
{
	x=_x;
	y=_y;
	type=_type;

	switch(_type)
	{
	case 1:
		sprite=L"energyDrink.png";
		sound=L"GotEnergy.wav";
		break;
	case 2:
		sprite=L"hpDrink.png";
		sound=L"GotHP.wav";
		break;
	case 3:
		sprite=L"rocketDrink.png";
		sound=L"GotEnergy.wav";
		break;

	case 4:
		sprite=L"key.png";
		sound=L"getKey.wav";
		break;
	}
}

void _stuff::Fall()
{
	int _x=(x+wt/2)/50, _y=(y+ht+1)/50;
	
	if(!exist(_x,_y))
	{
		if(a<max_a)
		    a+=0.1;
	}
	else
		a=0;

	y+=a;

	if(cross(x,y,ht,wt,_x*50,_y*50,50,50))
		y-=0.1;
}

void _stuff::Draw()
{
	if(!deleted)
	{
	    Fall();

		if(type!=4)
			lifetime--;

		if(lifetime<400)
		{
			if(lifetime>100)
			{
				if(lifetime%20==0)
				    blink=!blink;
			}
			else
				if(lifetime%5==0)
				    blink=!blink;

			if(lifetime<=0)
				deleted=true;
		}

		fly+=0.05;
	    if(!blink)
			DrawSprite(sprite,x,y+cos(fly)*3,2);

	    if(hero->CrossObj(x,y,wt,ht))
	    {
		    switch(type)
		    {
		    case 1:
			    hero->AddEnergy(RandInt(20,100));
			    break;
			case 2:
				hero->AddHP(RandInt(30,50));
				break;
			case 3:
				hero->AddRockets(RandInt(1,9));
				break;
			case 4:
				objects->OpenTP();
				hero->Key();
				break;
		    }

			SoundPlay(sound);
		
	        deleted=true;
	    }
	}

}

bool _stuff::Destroyed()
{
	if(deleted)
		return true;
	else
		return false;
}

stuffDesk::stuffDesk()
{
	count = 0;
}

stuffDesk::~stuffDesk()
{
	stf.clear();
}

void stuffDesk::Add(int type, int x, int y)
{
	stf.push_back(_stuff());
	stf.at(count).Add(type,x,y);
	count++;
}

void stuffDesk::Clear()
{
	stf.clear();
	count=0;
}

void stuffDesk::Destroy(int i)
{
	if(i<count)
		stf[i]=stf.back();

	stf.pop_back();
	count--;
}

void stuffDesk::Draw()
{
	for(int i=0;i<count;i++)
	{
		stf[i].Draw();
		if(stf[i].Destroyed())
			Destroy(i);
	}
}





