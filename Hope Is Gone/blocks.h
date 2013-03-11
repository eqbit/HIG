
//Базовый класс блоков

int borderAnimDesk[9]={0,0,0,1,1,0,2,2,0};

block::block()
{
	type=0;
	hp=start_hp=100;
	w_type=L"";
	anim=0;
	animated=false;
	fireBurn=SoundPlayEx(L"fire.wav",0.05,x,y,0,700,false);
	back=false;
	changed=true;
	quake=false;
	quakeTime=0;
	halfQuakeTime=0;
	angle=0;
	angleCoef=0;
	yCoef=0;
	yCoefFactor=0;
	coefFactor=0;
	touched=false;
	touchTime=0;
	transparency=255;
}

void block::Draw()
{
	if(type!=0)
	{
		if(!animated&&!turning&&type!=18)
	        DrawSprite(w_type,x,y+yCoef,4,angleCoef,1,COLOR(transparency,255,255,255));
		if(animated)
		{
			
			if(!DrawSpriteA(anim,x,y+yCoef,4,angleCoef))
			{
				ResetAnimation(anim);
			}
		}
		if(turning)
			DrawSprite(w_type,x,y+yCoef,4,angle+angleCoef);


	  if(type==1)
	  {
		if(changed)
		{
			int a=x/50,b=y/50,s=0;
			
			if(exist2(a-1,b)) s++;
			if(exist2(a+1,b)) s++;
			if(exist2(a,b-1)) s++;
			if(exist2(a,b+1)) s++;

			if(s==4)
			{
				int rand=RandInt(0,5);
				switch(rand)
				{
				case 1:
				    w_type=spr_dirt;
					break;
				case 2:
					w_type=spr_dirt_1;
					break;
				case 3:
					w_type=spr_dirt_2;
					break;
				case 4:
					w_type=spr_dirt_3;
					break;
				case 5:
					w_type=spr_dirt_4;
					break;
				default:
					w_type=spr_dirt;
					break;
				}
			}
			else
			{
				if(s==0)
					w_type=spr_dirt_alone;
				else
				{
					if(s==1)
					{
						if(exist2(a-1,b))
							w_type=spr_dirt_top_right_alone;
						if(exist2(a+1,b))
							w_type=spr_dirt_top_left_alone;
						if(exist2(a,b-1))
							w_type=spr_dirt_bottom_alone;
						if(exist2(a,b+1))
							w_type=spr_dirt_alone_top;
					}

					if(s==2)
					{
						if(exist2(a,b-1))
						{
							if(exist2(a-1,b))
								w_type=spr_dirt_bottom_right;
							if(exist2(a+1,b))
								w_type=spr_dirt_bottom_left;
							if(exist2(a,b+1))
								w_type=spr_dirt_middle;
						}
						else
						{
							if(exist2(a,b+1))
							{
								if(exist2(a-1,b))
									w_type=spr_dirt_right;
								else
									w_type=spr_dirt_left;
							}
							else
								w_type=spr_dirt_top_middle;
						}
					}

					if(s==3)
					{
						if(exist2(a,b-1))
						{
							if(exist2(a-1,b)&&exist(a,b+1))
								w_type=spr_dirt_middle_right;
							if(exist2(a+1,b)&&exist(a,b+1))
								w_type=spr_dirt_middle_left;
							if(exist2(a-1,b)&&exist(a+1,b))
							{
								int randomIndex=RandInt(0,4);

								switch(randomIndex)
								{
								case 0:
									w_type=L"bottomDirt_1.png";
									break;

								case 1:
									w_type=L"bottomDirt_2.png";
									break;

								case 2:
									w_type=L"bottomDirt_3.png";
									break;

								case 3:
									w_type=L"bottomDirt_4.png";
									break;

								case 4:
									w_type=L"bottomDirt_5.png";
									break;
								}

							}
						}
						else
						{
							int r=RandInt(0,5);
							switch(r)
							{
							case 1:	w_type=spr_dirt_top; break;
							case 2: w_type=L"grass1.png";break;
							case 3: w_type=L"grass2.png";break;
							case 4: w_type=L"grass3.png";break;
							default: w_type=spr_dirt_top;break;
							}
						}
					}
				}
			}

			
		}


		
	  }

	  if(type==2)
	  {
		if(changed)
		{
			int a=x/50,b=y/50,s=0;
			
			if(exist(a-1,b)) s++;
			if(exist(a+1,b)) s++;
			if(exist(a,b-1)) s++;
			if(exist(a,b+1)) s++;

			if(s==4)
			{
				w_type=L"bricks.png";

				if(!exist(a-1,b-1))
					w_type=L"bricksATLO.png";
				if(!exist(a+1,b-1))
					w_type=L"bricksATRO.png";
				if(!exist(a-1,b+1))
					w_type=L"bricksABLO.png";
				if(!exist(a+1,b+1))
					w_type=L"bricksABRO.png";
			}
			else
			{
				if(s==0)
					w_type=L"bricksAlone.png";
				else
				{
					if(s==1)
					{
						if(exist(a-1,b))
							w_type=L"bricksLC.png";
						if(exist(a+1,b))
							w_type=L"bricksRC.png";
						if(exist(a,b-1))
							w_type=L"bricksTC.png";
						if(exist(a,b+1))
							w_type=L"bricksBC.png";
					}

					if(s==2)
					{
						if(exist(a,b-1))
						{
							if(exist(a-1,b))
								w_type=L"bricksTLC.png";
							if(exist(a+1,b))
								w_type=L"bricksTRC.png";
							if(exist(a,b+1))
								w_type=L"bricksTBC.png";
						}
						else
						{
							if(exist(a,b+1))
							{
								if(exist(a-1,b))
									w_type=L"bricksBLC.png";
								else
									w_type=L"bricksBRC.png";
							}
							else
								w_type=L"bricksRLC.png";
						}
					}

					if(s==3)
					{
						if(exist(a,b-1))
						{
							if(exist(a-1,b)&&exist(a,b+1))
								w_type=L"bricksRO.png";
							if(exist(a+1,b)&&exist(a,b+1))
								w_type=L"bricksLO.png";
							if(exist(a-1,b)&&exist(a+1,b))
								w_type=L"bricksBO.png";
						}
						else
						{
							w_type=L"bricksTO.png";
						}
					}
				}
			}

			
		}


		
	  }

	  if(type==5)
	  {
		  if(curAnim==1)
		  {
			  if(hp<66)
			  {
				  curAnim=2;
				  SetAnimation(anim, curAnim);
			  }
		  }

		  if(curAnim==2)
		  {
			  if(hp<33)
			  {
				  curAnim=3;
				  SetAnimation(anim,curAnim);
			  }
		  }

		  if(curAnim==3)
		  {
			  if(hp<0)
			  {
				  Del();
				  objects->AddEffect(8,x-50,y-50);
				  int _x=x/50,_y=y/50;
			  }
		  }

	  }

		if(type==8)
		{
			if(!GetSoundState(fireBurn)&&hero->Visible(x,y))
			{
				fireBurn=SoundPlayEx(L"fire.wav",0.05,x,y,0,700,false);
			}

			if(!hero->Visible(x,y))
			{
				if(GetSoundState(fireBurn)) SoundStop(fireBurn);
			}
		}

		if(type==11)
		{
			if(hero->CrossObj(x+5,y-7,40,7))
			{
				hero->Up(-18);
				SoundPlay(L"uper.wav",1,x,y,0,700);
				objects->AddEffect(2,x-8,y-30);
			}
		}

		if(type==12)
		{
			if(hero->CrossObj(x+25,y-25,50,50))
			{
				hero->Push(20);
				hero->Up(-13);
				SoundPlay(L"uper.wav",1,x,y,0,700);
				objects->AddEffect(2,x+15,y-25);
			}
		}

		if(type==13)
		{
			if(hero->CrossObj(x-50,y-25,50,50))
			{
				hero->Push(-20);
				hero->Up(-13);
				SoundPlay(L"uper.wav",1,x,y,0,700);
				objects->AddEffect(2,x-25,y-25);
			}
		}

		if(type==14)
		{
			if(hero->CrossObj(x,y-3,50,5)&&!touched)
			{
				w_type=L"marbleActive.png";
			    touched=true;
			}

			if(touched)
			{
				if(touchTime<50)
					touchTime++;
				else
				{
					if(transparency>30)
						transparency-=25;
					else
					{
					    Del();
					    touchTime=0;
					    touched=false;
						transparency=255;
					}
				}
			}
		}

		if(type==16)
		{
			if(hero->CrossObj(x,y,50,50))
			{
				hero->Stare(x+10);
			}
		}

		if(type==17)
		{
			if(hp<0)
			  {
				  Del();
				  objects->AddEffect(7,x-50,y-50);
				  keyBoxNum--;

				  if(chance(5)&&!gotKey)
					  GiveStuff(x,y+25,false,0);
				  else
				  {

				      if(keyBoxNum>1)
				      {
					      GiveStuff(x+25,y+25,true,60);
				      }
				      else
				      {
						  if(!gotKey)
							  GiveStuff(x,y+25,false,0);
						  else
							  GiveStuff(x+25,y+25,true,60);
				      }
				  }

				  int _x=x/50,_y=y/50;
			  }
		}	

		if(type==18)
		{
			DrawSprite(L"dirtBack.png",x,y,5);
		}
	}
	changed=false;

	if(quake)
		Quake();
}

void block::Quake()
{
	if(!quake)
	{
		quake=true;
		quakeTime=RandInt(15,30);
		halfQuakeTime=quakeTime/2;
		float abs=RandInt(3,10);
		yCoefFactor=abs/halfQuakeTime;
		yCoef=0;
		coefFactor=RandInt(1,5);
		SoundPlayEx(L"explodeLite.wav",0.5,x,y,0,1500);
	}

	if(quakeTime>halfQuakeTime)
		yCoef-=yCoefFactor;
	else
		yCoef+=yCoefFactor;

	angleCoef=RandInt(-coefFactor,coefFactor);

	quakeTime--;

	if(quakeTime==0)
	{
		quake=false;
		yCoef=0;
		angleCoef=0;
	}
}

void block::Add(int _x, int _y, int _type)
{
	turning=false;
	x=_x;
	y=_y;
	type=_type;
	animated=false;
	back=false;
	quake=false;
	switch(_type)
	{
	case 1: w_type=spr_dirt; break;
	case 2: w_type=spr_bricks; break;
	case 3: w_type=spr_stone; break;
	case 4: w_type=spr_wood; break;

	case 5: 
		animated=true;
		anim=CreateAnimationEx(L"borderBlockAnim.png",borderAnimDesk,3,0,3,50);
		curAnim=1;
		hp=start_hp;
		break;

	case 6: w_type=spr_blueback; back=true; break;
	case 7: w_type=spr_greyback; back=true; break;
	case 8:
		animated=true;
		anim=CreateAnimation(L"fire.png",10,RandInt(12,16),10,50);
		break;
	case 9: w_type=spr_spikes; break;
	case 10: w_type=spr_essence; break;
	case 11:
		animated=true;
		anim=CreateAnimation(L"uperAnim.png",20,13,20,50);
		break;
	case 12:
		w_type=L"pusher.png";
		angle=90;
		turning=true;
		break;
	case 13:
		w_type=L"pusher.png";
		angle=0;
		turning=true;
		break;

	case 14: w_type=spr_marble; break;
	case 15: w_type=spr_sand; break;
	case 16: w_type=L"stare.png"; back=true; break;
	case 17: w_type=L"stuffblock.png"; 
		     hp=10; 
			 break;
	case 18: w_type=L"grassLevel.png";
		     camera->SetGrass(_y);
		     break;

	}
}

void block::ChangeType(int _type)
{
	if(animated)
		DeleteAnimation(anim);
	type=_type;
	animated=false;
	back=false;
	if(GetSoundState(fireBurn)) SoundStop(fireBurn);
	switch(_type)
	{
	case 1: w_type=spr_dirt; break;
	case 2: w_type=spr_bricks; break;
	case 3: w_type=spr_stone; break;
	case 4: w_type=spr_wood; break;
	case 5: w_type=spr_border; break;
	case 6: w_type=spr_blueback; back=true; break;
	case 7: w_type=spr_greyback; back=true; break;
	case 8:
		animated=true;
		anim=CreateAnimation(L"fire.png",10,16,10,50);
		break;
	case 9: w_type=spr_spikes;break;
	case 10: w_type=spr_essence; break;
	case 11:
		animated=true;
		anim=CreateAnimation(L"uperAnim.png",20,13,20,50);
		break;
	case 12:
		w_type=L"pusher.png";
		angle=45;
		turning=true;
		break;
	case 13:
		w_type=L"pusher.png";
		angle=315;
		turning=true;
		break;
	}
}

void block::Del()
{
	type=0;
	if(animated)
		DeleteAnimation(anim);
	if(GetSoundState(fireBurn)) SoundStop(fireBurn);
}

int block::ReturnType()
{
	return type;
}

bool block::is()
{
	if(type==0||type==8||type==9||back)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool block::is2()
{
	if(type==0||type==8||type==9||back||type==17)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool block::othEx()
{
	if(type==0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void block::Hit(int damage)
{
	if(type==5||type==17)
		hp-=damage;
}