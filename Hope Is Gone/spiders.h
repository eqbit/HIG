spider::spider()
{
}

spider::spider(int _x, int _y)
{
	SetData(_x,_y,4,400,400,70,80,0,500,4);

	int animationCount=8;
	int animationSpeed=8;
	int frameWidthCount=10;
	int frameWidth=75;
	int frameHeight=100;
	int layer=1;

	curAnim=1;

	anim=CreateAnimationEx(L"spiderAnim.png",golemAnimDesk,animationCount,animationSpeed,frameWidthCount,frameWidth,frameHeight,layer);
	SetAnimation(anim,1);
}

void spider::Draw()
{

}