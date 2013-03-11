
_platform::_platform()
{
	x=0;
	y=0;
	wt=150;
	ht=50;
	speed=5;
	stoptm=0;
	dist=0;
	maxdist=900;
	up=true;
}

void _platform::Add(int _x, int _y)
{
	x=_x-_x%50;
	y=_y-_y%50;
	startx=x;
	starty=y;
}

void _platform::Draw()
{
	if(camera->GVis(x,y))
	{
	    DrawSprite(L"platform.png",x,y);
		if(cross(x,y,20,wt,hero->x,hero->y,hero->ht,hero->wt)&&hero->Alive())
	    {
	        while(cross(x,y,ht,wt,hero->x,hero->y,hero->ht,hero->wt)&&hero->Alive())
	        {
	    	    hero->y--;
	        }
	        hero->Place();
	    }
	    if(cross(x,y-1,2,wt,hero->x,hero->y,hero->ht,hero->wt))
		{
	        hero->OnPlat(1);
			hero->Place();
			if(!up)
				hero->y+=speed;
		}
	    else
	    	hero->OnPlat(0);

		if(cross(x,y+ht-20,20,wt,hero->x,hero->y,hero->ht,hero->wt))
		{
	        hero->Hit(hero->hp+1);
		}


	    Move();
    }
}

void _platform::Move()
{
	if(up)
	{
		if(stoptm>100)
		{
			y-=speed;
			dist+=speed;
			if(dist>maxdist)
			{
				stoptm=0;
				dist=0;
				up=false;
			}
		}
		else
			stoptm++;
	}
	else
	{
		if(stoptm>100)
		{
			y+=speed;
			dist+=speed;
			if(dist>maxdist)
			{
				stoptm=0;
				dist=0;
				up=true;
			}
		}
		else
			stoptm++;
	}
}



platforms::platforms()
{
	count =0;
}

platforms::~platforms()
{
	plt.clear();
}

void platforms::Add(int x, int y)
{
	plt.push_back(_platform());
	plt.at(count).Add(x,y);
	count++;
}

void platforms::Draw()
{
	for(int i=0;i<count;i++)
		plt[i].Draw();
}

void platforms::Save(ofstream &par)
{
	for(int i=0;i<count;i++)
	{
		int x=plt.at(i).startx;
		int y=plt.at(i).starty;
		par<<4<<" "<<x<<" "<<y<<" ";
	}
}

void platforms::Clear()
{
	plt.clear();
	count=0;
}


thing::thing()
{
	x=0;
	y=0;
	sprite=L"";
	layer=1;
}

thing::thing(int _x, int _y, wchar_t *_sprite, int _layer)
{
	x=_x;
	y=_y;
	sprite=_sprite;
	layer=_layer;
}

void thing::Draw()
{
	DrawSprite(sprite,x,y,layer);
}

void things::Draw()
{
	for(int i=0;i<Count();i++)
		tArr[i].Draw();
}


dinamicThing::dinamicThing(int _x, int _y, int _width, int _height, wchar_t *_sprite, int _layer)
{
	thing(_x,_y,_sprite,_layer);
	width=_width;
	height=_height;
	fallSpeed=0;
}