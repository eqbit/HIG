#include "blocks.h"

 

_world::_world()
{
	width=200;
	height=50;

	map = new block*[width];

	currentMap="levels/start.map";
	currentMapIndex=1;

	for(int i=0;i<width;i++)
	{
		map[i] = new block[height];
	}
}

_world::~_world()
{
	for(int i=0;i<width;i++)
	{
		delete[] map[i];
	}
	delete[] map;
}

void _world::Draw(int x,int y)
{
	if(OthExist(x,y))
		map[x][y].Draw();
}

void _world::Change(int _x, int _y)
{
	if(_x>3&&_y>3&&_x<width-3&&_y<height-3)
	{
		map[_x-1][_y].Change();
		map[_x-1][_y-1].Change();
		map[_x][_y].Change();
		map[_x+1][_y].Change();
		map[_x+1][_y-1].Change();
		map[_x][_y-1].Change();
		map[_x][_y+1].Change();
		map[_x-1][_y+1].Change();
		map[_x+1][_y+1].Change();
	}
}

void _world::Add(int x, int y, int _type)
{


	x=x/50;
	y=y/50;

	
	if(Possible(x*50,y*50)&&!OthExist(x,y))
	{
	    if(!map[x][y].is())
	        map[x][y].Add(x*50,y*50,_type);
		Change(x,y);
	}

}

void _world::Del(int x, int y)
{
	x=x/50;
	y=y/50;

	

	if(Possible(x*50,y*50))
	{
	    if(map[x][y].othEx())
	        map[x][y].Del();

		Change(x,y);
	}

}

void _world::Save()
{
	hero->Save(currentMapIndex);

	/*
	ofstream out("levels/default.map");
	
	out<<width<<" "<<height<<" ";

	for(int i=0;i<width;i++)
	{
		for(int j =0;j<height;j++)
		{
			out<<map[i][j].type<<" ";
		}
	}*/
	//objects->Save();
	//out.close();
}

void _world::ChangeMap(char* mapName, int mapIndex)
{
	currentMap=mapName;
	currentMapIndex=mapIndex;
	if(!loading)
		Load();
}

void _world::Load()
{
	loading = true;

	keyBoxNum=0;
	gotKey=false;

	ifstream hIn("saves/hero.sav");

	hIn>>currentMapIndex;

	ChangeLvl(currentMapIndex);

	hIn.close();

	ifstream in(currentMap);

	for(int i=0;i<width;i++)
		delete[] map[i];
	delete [] map;


	in>>width;
	in>>height;

	camera->SetLenght(width);

	map = new block*[width];

	for(int i=0;i<width;i++)
	{
		map[i] = new block[height];
	}

	
	int type;

	for(int i=0;i<width;i++)
	{
		for(int j=0;j<height;j++)
		{
			in>>type;
			Add(i*50,j*50,type);
			if(type==17)
				keyBoxNum++;
		}
	}
	objects->Clear();

	int enemyCount=0;
	in>>enemyCount;

	double x,y;

	for(int i=0;i<enemyCount;i++)
	{
		in>>x;
		in>>y;
		in>>type;
		objects->Add(type,x,y);
	}

	int objCount;
	in>>objCount;

	for(int i=0;i<objCount;i++)
	{
		
		in>>type;
		in>>x;
		in>>y;

		if(type==1)
		{
			hero->SetCoordinats(x,y);
		}
		else
		{

		}
	}

	int finishNum=0, index=1;
	in>>finishNum;

	for(int i=0;i<finishNum;i++)
	{
		in>>x;
		in>>y;
		int _x,_y;
		_x=x;
		_y=y;
		_x=_x-_x%50;
		_y=_y-_y%50;

		in>>index;
		objects->AddFinish(_x,_y,index);
	}


	in.close();

	hero->Load();
	
	loading = false;

	SoundsStop();
	GameTheme=SoundPlayEx(L"Menu.wav",0.2,0,0,0,0,true,1000,10);
}

void _world::Hit(int x, int y, int damage)
{
	map[x][y].Hit(damage);
}