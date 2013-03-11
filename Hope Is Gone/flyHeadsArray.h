flyHeads::flyHeads()
{
	count = 0;
}

flyHeads::~flyHeads()
{
	heads.clear();
}

void flyHeads::Add(int x, int y)
{
	heads.push_back(_flyHead(x,y));
	count++;
}

void flyHeads::Draw()
{
	for(int i=0;i<count;i++)
		heads[i].Draw();
}

void flyHeads::Save(ofstream &par)
{
	for(int i=0;i<count;i++)
	{
		int x=heads.at(i).getStartX();
		int y=heads.at(i).getStartY();
		par<<6<<" "<<x<<" "<<y<<" ";
	}
}

void flyHeads::Clear()
{
	heads.clear();
	count=0;
}