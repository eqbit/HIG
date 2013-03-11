
_camera::_camera()
{
	x=hero->x;
	y=hero->y;
	h_x=15000;
	h_y=7000;
	g_x=0;
	g_y=0;
	g_x2=0;
	g_y2=0;
	scrpt=false;
	grassY=0;
}


void _camera::Scene()
{
	int ax,ay,bx,by;

	ax=x/50-1;

	ay=y/50-1;

	bx=ax+winW/50+4;
	by=ay+winH/50+4;

	for(int i=ax;i<bx;i++)
	{
		for(int j=ay;j<by;j++)
		{
			world->Draw(i,j);
		}
	}
}

void _camera::SetGrass(int _y)
{
	grassY=_y;
}

void _camera::SetLenght(int _lenght)
{
	lenght=(_lenght*50)/1500;
}

void _camera::Draw()
{
	

	float lx=x+(winW/3),rx=x+(winW/3)*2;
	int ty=y+(winH/5)*2,by=y+(winH/5)*3;

	int hx=hero->x,hy=hero->y;

	float _lx=x+(winW/5)*2, _rx=x+(winW/5)*3;
	int _ty=y+(winH/7)*3,_by=y+(winH/7)*4;

	if(hx<_lx)
	{
		x-=2;
		h_x-=1.8;
		g_x-=1.2;
		g_x2-=1.6;
		_lx=x+(winW/5)*2;
	}

	if(hx>_rx)
	{
		x+=2;
		h_x+=1.8;
		g_x+=1.2;
		g_x2+=1.6;
		_rx=x+(winW/5)*3;
	}

	if(hy<_ty)
	{
		y-=2;
		h_y-=0.5;
		_ty=y+(winH/7)*3;
	}

	if(hy>_by)
	{
		y+=2;
		h_y+=0.5;
		_by=y+(winH/7)*4;
	}


	///////////////

	if(hx<lx)
	{
		while(hx<lx)
		{
			x--;
			h_x-=0.9;
			g_x-=0.6;
			g_x2-=0.8;
			lx=x+(winW/3);
		}
	}

	if(hx>rx)
	{
		while(hx>rx)
		{
			x++;
			h_x+=0.9;
			g_x+=0.6;
			g_x2+=0.8;
			rx=x+(winW/3)*2;
		}
	}

	if(hy<ty)
	{
		while(hy<ty)
		{
			y--;
			h_y-=0.25;
			ty=y+(winH/5)*2;
		}
	}

	if(hy>by)
	{
		while(hy>by)
		{
			y++;
			h_y+=0.25;
			by=y+(winH/5)*3;
		}
	}

	int asd=0;
	if(KeyCheck(DIK_G))
	{
		asd=RandInt(-2,2);
	}
	

	if(y>getHeight()*50-winH/2)
		y=getHeight()*50-winH;

	//InterfaceDigits(x,y);
	SetViewport(x+asd, y+asd);


	Scene();

	
}

bool _camera::Vis(int _x, int _y)
{
	if(cross(x-200,y-200,winH+200,winW+200,_x,_y,100,100))
		return true;
	else
		return false;
}

bool _camera::GVis(int _x, int _y)
{
	if(cross(x-1400,y-1400,winH+2800,winW+2800,_x,_y,100,100))
		return true;
	else
		return false;
}

void _camera::Background()
{
	DrawSprite(spr_background,x-500,y-800,7);
	
	/*
	for(int i=-8;i<3;i++)
		for(int j=-17;j<14;j++)
			DrawSprite(L"hback.png",h_x+i*1600,h_y+j*900,6);*/


	//DrawSprite(spr_fbackground,x-500,y-800,5);

	
	for(int i=0;i<lenght;i++)
	{
		DrawSprite(L"woodBack2.png",g_x2+i*1500,grassY-500,4);
		DrawSprite(L"woodBack.png",g_x+i*1500,grassY-500,4);
	}
}


void _cloud::Add()
{
	if(!madeMap)
		x=RandInt(camera->x,camera->x+winW)-800;
	else
		x=camera->x+winW+RandInt(100,1500);

	y=camera->y+RandInt(-200,winH+300);
	startx=x;
	starty=y;
	speed=RandInt(1,100)*0.005;
	int SwSpr=RandInt(0,7);

	switch(SwSpr)
	{
	case 1:
		sprite=L"cloud1.png";
		break;
	case 2:
		sprite=L"cloud2.png";
		break;
	case 3:
		sprite=L"cloud3.png";
		break;
	case 4:
		sprite=L"cloud4.png";
		break;
	case 5:
		sprite=L"cloud5.png";
		break;
	case 6:
		sprite=L"cloud6.png";
		break;
	default:
		sprite=L"cloud1.png";
		break;
	}
}

void _cloud::Del()
{
	Add();
}

void _cloud::Draw()
{
	x-=speed;

	if(!cross(x,y,300,800,camera->x-200,camera->y-200,winH+400,winW+400))
	{
		Del();
	}

	DrawSprite(sprite,x,y,3);
}

_cloud::_cloud()
{
	x=0;
	y=0;
	startx=0;
	starty=0;
	speed=0;
	sprite=L"";
}

clouds::clouds()
{
	count=0;
}

clouds::~clouds()
{
	cld.clear();
}

void clouds::Load()
{
	count=20;
	for(int i=0;i<count;i++)
	{
		cld.push_back(_cloud());
		cld.at(i).Add();
	}
}

void clouds::Draw()
{
	for(int i=0;i<count;i++)
		cld[i].Draw();
}