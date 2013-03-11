inv_object::inv_object()
{
	x=0;
	y=0;
	type=1;
	sprite=L"";
}

void inv_object::Draw(int _x, int _y)
{
	int mx=GetMouseX(), my=GetMouseY();
	if(cross(_x,_y,100,100,mx,my,1,1))
	{
		DrawSprite(L"inv_box_back.png",_x,_y,0);
		if(MouseLBPress())
		{
			mscheck=true;
		}
	}

	DrawSprite(sprite,_x,_y,0);
	switch(type)
	{

	case 1:
		if(count>0)
		{
			
			PrintDigit(count,0,_x+80,_y+80,0.5,0,COLOR(255,255,255,0));
		    if(cross(_x,_y,100,100,mx,my,1,1)&&MouseRBPress()&&!mscheck)
		    {
			    hero->SetEnergy(50);
			    mscheck=true;
				count--;
		    }
		}

	case 2:
		if(count>0)
		{
			
			PrintDigit(count,0,_x+80,_y+80,0.5,0,COLOR(255,255,255,0));
		    if(cross(_x,_y,100,100,mx,my,1,1)&&MouseRBPress()&&!mscheck)
		    {
				hero->SetHP(100);
			    mscheck=true;
				count--;
		    }
		}


	}
}

void inv_object::Add(int _type)
{
	switch(_type)
	{
	case 1:
		type=1;
		sprite=L"energyBottle.png";
		count=4;
		deleted=false;
		break;

	case 2:
		type=2;
		sprite=L"hpBottle.png";
		count=4;
		deleted=false;
		break;
	}
}

_inventory::_inventory()
{
	count =0;
	x=100;
	y=100;
	inv.push_back(inv_object());
	inv.at(count).Add(1);
	count++;
	inv.push_back(inv_object());
	inv.at(count).Add(2);
	count++;
}

_inventory::~_inventory()
{
	inv.clear();
}

void _inventory::Draw()
{
	DrawSprite(L"inventory_back.png",x,y,0);
	for(int i=0;i<count;i++)
	{
		inv.at(i).Draw(x+i*100,y);
	}
}