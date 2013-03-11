laboratory::laboratory()
{
	drawing=false;
	researchIndex=1;
    weaponIndex=1;
    rg_extradamage1=0;
	rg_extradamage2=0;
	rg_ballshooter=0;
	rg_saving15=0;
	rg_saving2=0;
	rg_saving4=0;
	rg_speed1=0;
	rg_speed2=0;
	rg_parts2=0;
	rg_parts3=0;
}

void laboratory::Draw()
{
	for(int i=0;i<7;i++)
		for(int j=0; j<4;j++)
			DrawSprite(L"lab_back.png",i*400,j*400,0);

	if(Button(100,200,L"lab_rgdamage1.png",3, rg_extradamage1)&&!rg_extradamage1)
	{
			hero->Upgrade(1,1,1);
			rg_extradamage1=true;
	}

	if(rg_extradamage1)
	{
	    if(Button(100,300,L"lab_rgdamage2.png",100, rg_extradamage2)&&!rg_extradamage2)
	    {
			    hero->Upgrade(1,1,2);
			    rg_extradamage2=true;
	    }
	}

	if(Button(200,200,L"lab_rgrate1.png",100, rg_saving15)&&!rg_saving15)
	{
			hero->Upgrade(1,2,1);
			rg_saving15=true;
	}

	if(rg_saving15)
	{
	    if(Button(200,300,L"lab_rgrate2.png",200, rg_saving2)&&!rg_saving2)
	    {
			    hero->Upgrade(1,2,2);
			    rg_saving2=true;
	    }
	}

	if(rg_saving15&&rg_saving2)
	{
	    if(Button(200,400,L"lab_rgrate3.png",500, rg_saving4)&&!rg_saving4)
	    {
			    hero->Upgrade(1,2,3);
			    rg_saving4=true;
	    }
	}

	if(Button(300,200,L"lab_rgparts2.png",250, rg_parts2)&&!rg_parts2)
	{
			hero->Upgrade(1,3,1);
			rg_parts2=true;
	}

	if(rg_parts2)
	{
		if(Button(300,300,L"lab_rgparts3.png",500, rg_parts3)&&!rg_parts3)
	    {
			hero->Upgrade(1,3,2);
			rg_parts3=true;
	    }
	}


}

bool laboratory::Button(int x, int y, wchar_t *pic, int sum, bool ifo)
{
	if(ifo)
	{
		DrawSprite(L"lab_border.png",x,y,0);
		DrawSprite(pic,x,y,0);
	}
	else
	{
	    if(sum<=hero->getScore())
		    DrawSprite(pic,x,y,0);
	    else
	    {
			
		    DrawSprite(pic,x,y,0);
			DrawSprite(L"lab_overlay.png",x,y,0);

			if(cross(x,y,50,50,mouseMX,mouseMY,1,1))
			{
				for(int i=0;i<exponent(sum)+1;i++)
				    DrawSprite(L"lab_priceBack.png",mouseMX+13+i*8,mouseMY-38,0);

			    PrintDigit(sum,0,mouseMX+16,mouseMY-35,0.4,0,COLOR(200,255,255,255));

			}

		    return false;
	    }
	}

	if(cross(x,y,50,50,mouseMX,mouseMY,1,1))
	{
		if(!ifo)
		{
			DrawSprite(L"lab_dragBorder.png",x-10,y-10,0);

			for(int i=0;i<exponent(sum)+1;i++)
				DrawSprite(L"lab_priceBack.png",mouseMX+13+i*8,mouseMY-38,0);

			PrintDigit(sum,0,mouseMX+16,mouseMY-35,0.4,0,COLOR(200,255,255,255));
		}

		if(MouseLBPress()&&!mscheck&&sum<=hero->getScore()&&!ifo)
	    {
		    SoundPlay(L"buttonClick.wav");
		    mscheck=true;
		    hero->TakeScore(sum);
		    return true;
	    }
	    else
		    return false;
	}
	else
		return false;
}

bool laboratory::Update()
{
	if(drawing)
		Draw();

	if(KeyCheck(DIK_L)&&!checkKeys)
	{
		drawing=!drawing;
		checkKeys=!checkKeys;
	}

	if(drawing)
		return true;
	else
		return false;
}

void laboratory::Save()
{
	ofstream out("saves/abilities.sav");

	out<<rg_extradamage1<<" "<<rg_extradamage2<<" "<<rg_ballshooter<<" "<<rg_saving15<<" "<<rg_saving2<<" "<<rg_saving4<<" "<<rg_speed1<<" "<<rg_speed2<<" "<<rg_parts2<<" "<<rg_parts3<<" ";

	out.close();
}