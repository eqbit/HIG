
button::button()
{
	x=y=ht=wt=0;
	pressed=false;
}

void button::Life()
{
	DrawSprite(pic,x,y,0);
	if(MouseLBPress()&&cross(x,y,ht,wt,GetMouseX(),GetMouseY(),1,1))
	{
		pressed=true;
	}
	if(pressed)
	{
		MakeThat();
	}
}

void button::Create(int _x, int _y, int _wt, int _ht, wchar_t *_pic, void (*func)(void))
{
	x=_x;
	y=_y;
	wt=_wt;
	ht=_ht;
	pic=_pic;
	MakeThat=func;
}

void buttons::Add(int _x, int _y, int _wt, int _ht, wchar_t *_pic, void (*func)(void))
{
	btns.push_back(button());
	int i=btns.size();
	btns[i-1].Create(_x, _y, _wt, _ht, _pic, func);
}


buttons::~buttons()
{
	btns.clear();
}

void buttons::Draw(int i)
{
	btns.at(i).Life();
}


