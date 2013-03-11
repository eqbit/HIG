golems::golems()
{
	count=0;
}

golems::~golems()
{
	golemDesk.clear();
}

void golems::Add(int x, int y)
{
	golemDesk.push_back(_golem(x,y));
	count++;
}

void golems::Draw()
{
	for(int i=0;i<count;i++)
	{
		golemDesk[i].Draw();
	}
}

void golems::Save(ofstream &par)
{
	for(int i=0;i<count;i++)
	{
		int x=golemDesk.at(i).getStartX();
		int y=golemDesk.at(i).getStartY();
		par<<5<<" "<<x<<" "<<y<<" ";
	}
}

void golems::Clear()
{
	golemDesk.clear();
	count =0;
}
