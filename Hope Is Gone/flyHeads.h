
_flyHead::_flyHead()
{
	SetData(0,0,0,30,30,120,40,0,150,0.5);
}

int headAnimDesk[]={0,6,10,10,16,10};

_flyHead::_flyHead(int _x, int _y)
{
	SetData(_x,_y,0,30,30,120,40,0,150,0.5);

	speedIncrement=0.03;//прирост скорости


	const int radius=220;//радиус определяющий зону патруля при появлении

	leftTarget=getX()-radius;
	rightTarget=getX()+getWidth()+radius;


	direction=false;//направление движения. true означает вправо, false влево


	int animationCount=2;
	int animationSpeed=8;
	int frameWidthCount=10;
	int frameWidth=65;
	int frameHeight=70;
	int layer=1;

	allowDraw=true;

	curAnim=1;

	anim=CreateAnimationEx(L"flyHeadAnim.png",headAnimDesk,animationCount,animationSpeed,frameWidthCount,frameWidth,frameHeight,layer);
	SetAnimation(anim,1);
}

void _flyHead::Patrol()
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
			curAnim=1;
			SetAnimation(anim,curAnim);
			direction=true;
		}
	}
	Move();
}

void _flyHead::Draw()
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
				allowDraw=false;
		}

	}
}

/*
bool _flyHead::HeroTrigger(int startX, int endX)
{
	if(hero->CrossObj(startX,getY()-20,endX-startX,getHeight()+20))
		return true;
	else
		return false;
}
*/

void _flyHead::Act()
{
	Patrol();

	if(!DrawSpriteA(anim,getX(),getY()))
		   ResetAnimation(anim);

	Update();
}

void _flyHead::Kill()
{
	makeDead();
	SetAnimation(anim,2);
	ResetAnimation(anim);
	SoundPlay(L"golemDeath.wav",1,getX(),getY(),0,1500);
}


#include "flyHeadsArray.h"


