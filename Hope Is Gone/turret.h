
_turret::_turret()
{
	x=4000;
	y=13000;
	ht=50;
	wt=50;
	angle=0;
	hp=maxHP=250;
	built=false;
	dhp=hp/15;
	right=true;
	anim=0;
	gtar=false;
	mob_i=1;
}

void _turret::Add(int _x, int _y)
{
	x=_x-25;
	y=_y-25;
	deleted=false;

	built=false;
	anim=CreateAnimation(L"turretAnim.png",10,8,10,50);
	ResetAnimation(anim);

	SoundPlayEx(L"turAddBuild.wav",1,x,y,0,1000);
	SoundPlayEx(L"turBuild.wav",1,x,y,0,1000);
}


void _turret::Draw()
{
	Live();

	if(crossCursor&&MouseLBPress()&&!mscheck&&built)
	{
		mscheck=true;
		right=!right;
		angle=0;
	}

	if(!built)
	{
		if(!DrawSpriteA(anim,x,y))
		{
			built=true;
		}
	}
	else
	{
		if(right)
		{
			
			
			if(!gtar)
			{
				for(int i=0;i<mob_arr.size();i++)
			    {
				    _character &mob=*mob_arr.at(i);
				    if(mob.Visible())
				    {
						if(mob.Col(x+50,y-300,500,600)&&!mob.deleted)
						{
							gtar=true;
							mob_i=i;
						}
					}
				}
			}

			if(gtar)
			{
				_character &mob=*mob_arr.at(mob_i);

				int tangle=atan2(mob.y-(y+25),mob.x-(x+25))*180/3.14;

				
			    if(tangle>angle&&angle<30)
				{
				    angle+=0.5;
					if(!GetSoundState(move))
						move=SoundPlayEx(L"turMove.wav",0.4,x,y,0,600,false);
				}
			    if(tangle<angle&&angle>-30)
				{
				    angle-=0.5;
					if(!GetSoundState(move))
						move=SoundPlayEx(L"turMove.wav",0.4,x,y,0,600,false);
				}

	            if(angle>30)
		            angle=30;
	            if(angle<-30)
		            angle=-30;

				

				if(rNum>80&&(angle>tangle-2&&angle<tangle+2))
				{
					
					int cx,cy;
					cx=25*cos(angle)/180*3.14;
					cy=25*sin(angle)/180*3.14;
					DrawLine(x+25+cx,y+25+cy,mob.x+25,mob.y+25,1,2,COLOR(255,0,255,228));mob.Hit(2);
				    if(!GetSoundState(shot))
				    {
					    shot=SoundPlayEx(L"tur_shot.wav",1,x,y,0,1000);
				    }
					mob.Hit(15);
				}

				if(!mob.Col(x+50,y-300,600,600)||mob.deleted||mob.hp<0)
				{
					gtar=false;
					mob_i=0;
				}
				

			}

			DrawSprite(L"turretRightBottom.png",x,y);
			DrawSprite(L"turretRightTop.png",x-3,y+12,1,angle);
		}
		else
		{

			if(!gtar)
			{
				for(int i=0;i<mob_arr.size();i++)
			    {
				    _character &mob=*mob_arr.at(i);
				    if(mob.Visible())
				    {
						if(mob.Col(x-500,y-300,500,600)&&!mob.deleted)
						{
							gtar=true;
							mob_i=i;
						}
					}
				}
			}

			if(gtar)
			{
				_character &mob=*mob_arr.at(mob_i);

				int tangle=atan2((y+25)-mob.y,(x+25)-mob.x)*180/3.14;

				
				
			     if(tangle>angle&&angle<30)
				{
				    angle+=0.5;
					if(!GetSoundState(move))
						move=SoundPlayEx(L"turMove.wav",0.4,x,y,0,600,false);
				}
			    if(tangle<angle&&angle>-30)
				{
				    angle-=0.5;
					if(!GetSoundState(move))
						move=SoundPlayEx(L"turMove.wav",0.4,x,y,0,600,false);
				}

	            if(angle>30)
		            angle=30;
	            if(angle<-30)
		            angle=-30;

				
				if(rNum>80&&(angle>tangle-2&&angle<tangle+2))
				{
					
					int cx,cy;
					cx=25*cos(angle)/180*3.14;
					cy=25*sin(angle)/180*3.14;
					if(!GetSoundState(shot))
				    {
					    DrawLine(x+cx+25,y+cy+25,mob.x+30,mob.y+25,1,2,COLOR(255,0,255,228));
					    shot=SoundPlayEx(L"tur_shot.wav",1,x,y,0,1000);
				    }
					mob.Hit(15);
				}

				if(!mob.Col(x+50,y-300,600,600)||mob.deleted||mob.hp<0)
				{
					gtar=false;
					mob_i=0;
				}
				

			}

			DrawSprite(L"turretLeftBottom.png",x,y);
			DrawSprite(L"turretLeftTop.png",x+2,y+12,1,angle);
		}
	}
	if(deleted)
		exist=false;
}

void _turret::Be()
{
	if(exist)
		Draw();
}


turrets::turrets()
{
	count=0;
}

turrets::~turrets()
{
	tur.clear();
}

void turrets::Add(int x, int y)
{
	tur.push_back(_turret());
	tur.at(count).Add(x,y);
	count++;
}

void turrets::Draw()
{
	for(int i=0;i<count;i++)
	{
		tur.at(i).Be();
		if(tur.at(i).deleted)
		{
			if(count>i)
			{
				tur[i]=tur.back();
			}
			tur.pop_back();
			count--;
			obj_count--;
		}
	}


}
