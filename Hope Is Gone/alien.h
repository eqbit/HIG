alien::alien()
{
	SetData(10,10,0,1,1,80,75,0,250,3);
}

int alienAnimDesk[]={0,9,10,10,19,10,25,35,14,45,55,14};

alien::alien(int _x, int _y)
{
	SetData(_x, _y,0.5,180,180,190,150,0,300,1);

	speedIncrement=0.03;//прирост скорости


	const int radius=320;//радиус определяющий зону патруля при появлении

	leftTarget=getX()-radius;
	rightTarget=getX()+getWidth()+radius;


	direction=chance(50);//направление движения. true означает вправо, false влево


	
	attack=false;
	attackCicle=50;
	startAttackCicle=50;

	allowDraw=true;

	int animationCount=4;
	int animationSpeed=8;
	int frameWidthCount=10;
	int frameWidth=150;
	int frameHeight=190;
	int layer=1;

	curAnim=2;

	anim=CreateAnimationEx(L"Alien.png",alienAnimDesk,animationCount,animationSpeed,frameWidthCount,frameWidth,frameHeight,layer);
	SetAnimation(anim,2);
}

void alien::Patrol()
{
	if(direction)
	{
		if(getX()+getWidth()<rightTarget&&!exist50(getX()+getWidth()+50,getY())&&!exist50(getX()+getWidth()+50,getY()+50))
			SetSpeed(speedIncrement);
		else
		{
			Stop();
			curAnim=1;
			SetAnimation(anim,curAnim);
			direction=false;
		}

	}
	else
	{
		if(getX()>leftTarget&&!exist50(getX()-50,getY())&&!exist50(getX()-50,getY()+50))
			SetSpeed(-speedIncrement);
		else
		{
			Stop();
			curAnim=2;
			SetAnimation(anim,curAnim);
			direction=true;
		}
	}
	Move();
}

bool alien::HeroTrigger()
{

	if(direction)
	{
		if(HeroTrigger(getX()+30,getX()+getRadius()))
		{
			return true;
		}
		else
		{
			if(curAnim!=2)
			{
				curAnim=2;
				SetAnimation(anim,curAnim);
				ResetAnimation(anim);
			}

			return false;
		}
	}
	else
	{
		if(HeroTrigger(getX()+getWidth()-getRadius(), getX()))
		{
			return true;
		}
		else
		{
			if(curAnim!=1)
			{
				curAnim=1;
				SetAnimation(anim,curAnim);
				ResetAnimation(anim);
			}

			return false;
		}
	}


}

bool alien::HeroTrigger(int startX, int endX)
{
	if(hero->CrossObj(startX,getY()-20,endX-startX,getHeight()+20))
		return true;
	else
		return false;
}

void alien::Act()
{

	//if(!HeroTrigger())
	//{
		Patrol();
		attackCicle=startAttackCicle;

		//ОТРИСОВКА//
	    if(!DrawSpriteA(anim,getX(),getY()))
		    ResetAnimation(anim);
	//}
	/*else
	{

		if(direction)
		{
			if(curAnim!=4&&curAnim!=6)
			{
				curAnim=6;
				SetAnimation(anim,curAnim);
				ResetAnimation(anim);
				SoundPlay(L"golemStay.wav",1,getX(),getY(),0,1000);
			}

			if(curAnim==4)
			{
				if(!DrawSpriteA(anim,getX(),getY()))
				{
					curAnim=6;
					SetAnimation(anim,curAnim);
					ResetAnimation(anim);
				}
			}

			if(curAnim==6)
			{
				if(!DrawSpriteA(anim,getX(),getY()))
				{
					curAnim=4;
					SetAnimation(anim,curAnim);
					ResetAnimation(anim);
				}
			}
		}
		else
		{
			if(curAnim!=3&&curAnim!=5)
			{
				curAnim=5;
				SetAnimation(anim,curAnim);
				ResetAnimation(anim);
				SoundPlay(L"golemStay.wav",1,getX(),getY(),0,1000);
			}

			if(curAnim==3)
			{
				if(!DrawSpriteA(anim,getX(),getY()))
				{
					curAnim=5;
					SetAnimation(anim,curAnim);
					ResetAnimation(anim);
				}
			}

			if(curAnim==5)
			{
				if(!DrawSpriteA(anim,getX(),getY()))
				{
					curAnim=3;
					SetAnimation(anim,curAnim);
					ResetAnimation(anim);
				}
			}
		}

		if(attack)
		{
			attackCicle--;
			if(attackCicle==0)
				attack=false;
		}
	}*/

	Update();//гравитация

	
}
/*
void _golem::Stamp()
{
	if(!attack)
	{
	    if(direction)
	   {
		   objects->Add(3,getX()+10,getY()+75,getX()+20,getY()+75);
		   //objects->Add(5,getX()+15,getY()+50,getX(),getY());
	   }
	   else
	   {
		   objects->Add(3,getX()-10,getY()+75,getX()-20,getY()+75);
		   //objects->Add(5,getX(),getY()+50,getX(),getY());
	   }
	   attack=true;
	   attackCicle=startAttackCicle;
	}
}*/

void alien::Draw()
{
	if(Alive())
	{
		Act();
	}
	else
	{
		if(allowDraw)
		{
			if(!DrawSpriteA(anim,getX(),getY()))
			{
				allowDraw=false;
				GiveSome(getX()+getWidth()/2,getY()-30,3,5,1,1);
			}
		}

	}
}

void alien::Kill()
{
	makeDead();
	if(direction)
	{
		curAnim=4;
	}
	else
	{
		curAnim=3;
	}
	SetAnimation(anim,curAnim);
	ResetAnimation(anim);
	SoundPlay(L"golemDeath.wav",1,getX(),getY(),0,1500);
}



aliens::aliens()
{
	count=0;
}

aliens::~aliens()
{
	aln.clear();
}

void aliens::Add(int x, int y)
{
	aln.push_back(alien(x,y));
	count++;
}

void aliens::Draw()
{
	for(int i=0;i<count;i++)
	{
		aln[i].Draw();
	}
}

void aliens::Clear()
{
	aln.clear();
	count =0;
}