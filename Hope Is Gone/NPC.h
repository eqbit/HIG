_quester::_quester()
{
	x=10035.88;
	y=12500.4;
	ht=46;
	wt=30;
	talking=false;
}

void _quester::Draw()
{
	Live();
	DrawSprite(L"quester.png",x,y);

	if(crossCursor)
	{
		creative = false;
		if(MouseLBPress()&&!mscheck)
		{
			menuWindow=true;
			mscheck=true;
		}
	}

	if(menuWindow)
	{
		if(DrawButton(x,y-20,50,50,L"",L"",1))
			menuWindow=false;
	}
}