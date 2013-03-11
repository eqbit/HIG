
int teleporterDesk[]={0,0,0,1,5,15};

teleporter::teleporter()
{

}

teleporter::teleporter(int _x, int _y, int _index)
{
	x=_x;
	y=_y;
	index=_index;
	opened=false;
	anim=CreateAnimationEx(L"teleporterAnim.png",teleporterDesk,2,0,6,120,100);
	curAnim=1;
	SetAnimation(anim,curAnim);
	ResetAnimation(anim);
}

void teleporter::Draw()
{
	if(!DrawSpriteA(anim,x,y))
		ResetAnimation(anim);

	if(hero->CrossObj(x,y,100,100)&&opened)
	{
		hero->Save(index);
		ChangeLvl(index);
	}

	//PrintDigit(index,3,10,10);

}

void teleporter::Open()
{
	opened=true;
	curAnim=2;
	SetAnimation(anim,curAnim);
	ResetAnimation(anim);
}

teleporters::~teleporters()
{
	tp.clear();
}

void teleporters::Add(int x, int y, int index)
{
	tp.push_back(teleporter(x,y,index));
}

void teleporters::Draw()
{
	PrintDigit(Num(),0,100,300,1,0);
	for(int i=0;i<Num();i++)
		tp[i].Draw();
}

void teleporters::Open()
{
	for(int i=0;i<Num();i++)
		tp[i].Open();
}