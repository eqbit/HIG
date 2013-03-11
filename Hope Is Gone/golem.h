_golem::_golem()
{
	SetData(10,10,0,1,1,80,75,0,250,3);
}

int golemAnimDesk[]={0,8,10,10,18,10,20,24,10,25,29,10,30,40,10,50,60,10,80,99,16,100,119,16};

_golem::_golem(int _x, int _y)
{
	SetData(_x, _y, 0.5, 150,150, 85, 75, 0,500,1);

	speedIncrement=0.03;//прирост скорости


	const int radius=320;//радиус определяющий зону патруля при появлении

	leftTarget=getX()-radius;
	rightTarget=getX()+getWidth()+radius;


	direction=chance(50);//направление движения. true означает вправо, false влево

	attack=false;
	attackCicle=50;
	startAttackCicle=50;

	int animationCount=8;
	int animationSpeed=8;
	int frameWidthCount=10;
	int frameWidth=75;
	int frameHeight=100;
	int layer=1;

	allowDraw=true;

	curAnim=1;

	anim=CreateAnimationEx(L"golemAnim.png",golemAnimDesk,animationCount,animationSpeed,frameWidthCount,frameWidth,frameHeight,layer);
	SetAnimation(anim,1);
}

void _golem::Patrol()
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

bool _golem::HeroTrigger()
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

bool _golem::HeroTrigger(int startX, int endX)
{
	if(hero->CrossObj(startX,getY()-20,endX-startX,getHeight()+20))
		return true;
	else
		return false;
}

void _golem::Act()
{

	if(!HeroTrigger())
	{
		Patrol();
		attackCicle=startAttackCicle;

		//ОТРИСОВКА//
	    if(!DrawSpriteA(anim,getX(),getY()))
		    ResetAnimation(anim);
	}
	else
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
					Stamp();
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
					Stamp();
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
	}

	Update();//гравитация

	
}

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
}

void _golem::Draw()
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

void _golem::Kill()
{
	makeDead();
	if(direction)
	{
		curAnim=8;
	}
	else
	{
		curAnim=7;
	}
	SetAnimation(anim,curAnim);
	ResetAnimation(anim);
	SoundPlay(L"golemDeath.wav",1,getX(),getY(),0,1500);
}


#include "golems.h"

