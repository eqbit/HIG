
objs::objs()
{
	obj_count=0;
	tur = new turrets;
	balls = new redballs;
	lballs= new lredballs;
	h_gst = new h_ghosts;
	plt=new platforms;
	blt =new bullets;
	mn = new moneys;
	inv = new _inventory;
	stf=new stuffDesk;
	eft = new effects;
	golemStruct = new golems;
	flyHead= new flyHeads;
	tps= new teleporters;
	alns = new aliens;
	count=0;
}

objs::~objs()
{
	delete tur;
	delete balls;
	delete lballs;
	delete h_gst;
	delete plt;
	delete blt;
	delete mn;
	delete inv;
	delete stf;
	delete eft;
	delete golemStruct;
	delete flyHead;
	delete tps;
	delete alns;
}

void objs::Draw()
{
	balls->Draw();
	lballs->Draw();
	tur->Draw();
	h_gst->Draw();
	plt->Draw();
	blt->Draw();
	//InterfaceDigits(blt->BulletCount(),0,200);
	mn->Draw();
	camera->Background();
	stf->Draw();
	eft->Draw();
	golemStruct->Draw();
	flyHead->Draw();
	tps->Draw();
	alns->Draw();

	if(invent)
	    inv->Draw();
	//PrintDigit(obj_count,0,100,100);
}


void objs::Clear()
{
	balls->Clear();
	h_gst->Clear();
	mob_arr.clear();
	plt->Clear();
	mn->Clear();
	golemStruct->Clear();
	flyHead->Clear();
	tps->Clear();
	alns->Clear();
}
void objs::Load()
{
	ifstream in("saves/objs.sav");

	Clear();


	int x=0,y=0,type=0,_count=0;
	obj_count=0; count=0;

	in>>_count;

	for(int i=0;i<_count;i++)
	{
		in>>type>>x>>y;
        Add(type,x,y);
	}

	obj_count=_count;

	in.close();
}

void objs::Save()
{
	ofstream of("saves/objs.sav");
	of<<obj_count<<" ";

	balls->Save(of);
	h_gst->Save(of);
	plt->Save(of);
	golemStruct->Save(of);
	flyHead->Save(of);

	of.close();
	
}

void objs::Add(int type, int x, int y)
{
	switch(type)
	{
	case 1:
		balls->Add(x,y);
		obj_count++;
		break;

	case 2:
		flyHead->Add(x,y);
		obj_count++;
		break;
		
	case 3:
		golemStruct->Add(x,y);
		obj_count++;
		break;

	case 4:
		h_gst->Add(x,y);
		obj_count++;
		break;

	case 5:
		alns->Add(x,y);
		obj_count++;
		break;
	case 6:
		plt->Add(x,y);
		obj_count++;
		break;

	}
}

void objs::Add(int type, int x, int y, int tx, int ty)
{
	blt->Add(x,y,tx,ty,type);
	obj_count++;
}

void objs::AddLRedball(int x, int y)
{
	lballs->Add(x,y);
}

void objs::AddMoney(int x, int y,int _count)
{
	mn->Add(x,y,_count);
}

void objs::CheckBullets(_character &mob)
{
	if(blt->There())
	{
		blt->CheckCollision(mob);
	}
}

void objs::CheckBulletCollision(enemy &mob)
{
	if(blt->There())
	{
		blt->CheckEnemyCollision(mob);
	}
}

void objs::AddStuff(int x, int y, int type)
{
	stf->Add(type,x,y);
}



///Ёффекты
//1:эффект взрыва маленькой пули
//2:3:4:эффекты прыжков
//5:дым за ракетой
//6:взрыв плазмы
void objs::AddEffect(int type, int x, int y)
{
	eft->Add(type, x, y);
}

void objs::AddNum(int num, int x, int y)
{
	eft->AddNum(num,x,y);
}

void objs::AddFinish(int x, int y, int index)
{
    tps->Add(x,y,index);
}

void objs::OpenTP()
{
	tps->Open();
}