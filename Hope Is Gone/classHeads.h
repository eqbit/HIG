class block
{
public:
	float x,y;
	float yCoef,yCoefFactor;
	int angle,angleCoef;
	wchar_t *w_type; int type;
	int hp, start_hp;
	int anim, curAnim;
	bool animated, back,changed, turning;
	bool quake;
	bool touched;
	int touchTime;
	int quakeTime, halfQuakeTime;
	int coefFactor;
	int transparency;
	

	block();
	int ReturnType();
	void Draw();
	void Add(int _x, int _y, int _type);
	void ChangeType(int _type);
	void Del();
	bool is();
	bool is2();
	bool othEx();
	void Change(){changed=true;};
	void Quake();
	bool Quaked(){return quake;};
	void Hit(int damage);
};

class _world
{
	char* currentMap;
	int currentMapIndex;
	bool loading;
public:
	int width, height;
	block **map;
	_world();
	~_world();
	void Draw(int x, int y);
	void Add(int x, int y, int _type);
	void Del(int x, int y);
	void Save();
	void Load();
	void Change(int _x, int _y);
	void ChangeMap(char *mapName, int mapIndex);
	void Hit(int x, int y, int damage);
	int MapIndex(){return currentMapIndex;}
	int CheckType(int x, int y)
	{
		x=x/50;
		y=y/50;
		if(OthExist(x,y))
			return map[x][y].type;
		else
			return 0;
	}
};

_world* world;

class _cloud
{
	float x, y,startx, starty;
	wchar_t* sprite;
	float speed;
public:
	_cloud();
	void Add();
	void Del();
	void Draw();
};

class clouds
{
	int count;
	vector<_cloud> cld;
public:
	void Draw();
	clouds();
	~clouds();
	void Load();
};

class thing
{
	double x,y;
	wchar_t *sprite;
	int layer;
public:
	void Draw();
	thing();
	thing(int _x, int _y, wchar_t *_sprite, int _layer);
	void Set(int _x, int _y, wchar_t *_sprite, int _layer);
};

class things
{
	vector <thing> tArr;
public:
	void Add(int x, int y, wchar_t* sprite, int layer){tArr.push_back(thing(x,y,sprite,layer));}
	things(){}
	~things(){tArr.clear();}
	int Count(){return tArr.size();}
	void Draw();
};

class dinamicThing : public thing
{
	double fallSpeed;
	int width, height;
public:
	void Draw();
	dinamicThing();
	dinamicThing(int _x, int _y, int _width, int _height, wchar_t *_sprite, int _layer);
};

class dinamicThings
{
	vector <dinamicThing> dtArr;
public:
	void Add(int x, int y, int width, int height, wchar_t *sprite, int layer){dtArr.push_back(dinamicThing(x,y,width,height,sprite,layer));}
	dinamicThings(){}
	~dinamicThings(){dtArr.clear();}
	int Count(){return dtArr.size();}
	void Draw();
};

class _camera
{
	int grassY;
public:
	float x,y;
	float h_x, h_y;
	float g_x,g_y;
	float g_x2,g_y2;
	int lenght;
	bool scrpt;
	_camera();
	void Draw();
	void Scene();
	bool Vis(int _x, int _y);
	bool GVis(int _x, int _y);
	void Background();
	void SetGrass(int _y);
	void SetLenght(int _lenght);
};

_camera *camera;


class _character
{
public:
	int vr;//зона видимости
	float x,y,a,speed,strtx,strty;
	float jumpTime;
	int wt,ht,mass,armor,jmpower,gwx,gwy,deathtm,deathlength,maxHP;
	int timeD,stTime,endTime;
	float hp, dhp,maxspeed;
	int exp;
	int tx,ty,hx,hy;
	bool jmp,placed,move;
	bool menuWindow,crossCursor;
	bool deleted,tih,crh,tang,allowMenu;
	bool hitting;
	wchar_t *hit_sound;
	void Move(float distance);
	void Live();
	void SetHP(int _hp);
	void Place();
	_character();
	void ShowHp();
	void CheckSite();
	void Hit(int _hp);
	void Hit(int _hp, int _speed);
	bool CrossHero();
	void CheckDamageBlock();
	void Res();
	bool Visible();
	bool Col(int _x, int _y, int w, int h);
	void TangLive();
	void GhostLive();
	void Push(float dist);
	void CheckBullet();
	bool CheckHeroZone();
	void timer();
	int Mid(){return x+wt/2;}
};

class _enemy
{
private:
	int x,y;//координаты
	int health;
	float speed, maxspeed;
public:
	void Move();
	void Hit(int damage);
	void CheckBullet();
	void CheckHeroZone();
	void CheckVis();
	void Live();
	_enemy();
	~_enemy();
};

class enemy
{
private:
	float x,y;
	int startX, startY;
	float speed;
	float maxSpeed;
	float startHealth, health;
	int height, width;
	int viewRadius;
	float fallSpeed, fallA, fallMaxSpeed;
	bool alive;
public:
	void Move(float distance);
	void Move();
	void SetSpeed(float increment);
	void Stop(){speed=0;};
	bool Hit(int force);
	void Push(int xForce,int yForce);
	int getX(){return x;};
	int getY(){return y;};
	int getStartX(){return startX;};
	int getStartY(){return startY;};
	int getWidth(){return width;};
	int getHeight(){return height;};
	int getRadius(){return viewRadius;};
	bool CheckFloor();//проверка коллизий
	bool CheckCeiling();
	bool CheckLeftCol();
	bool CheckRightCol();
	bool HeroTrigger();//проверка нахождения игрока в зоне видимости
	void Update();
	virtual void Kill();
	void makeDead(){alive=false;};
	bool Alive(){return alive;};
	enemy();
	enemy(int _x, int _y, float _speed, int _startHealth, int _health, int _height, int _width, float fallSpeed, int _viewRadius);
	void SetData(int _x, int _y, float _speed, int _startHealth, int _health, int _height, int _width, float fallSpeed, int _viewRadius, float _maxSpeed);
};



class _hero : public _character
{
	float power, force, agility, intellect, stamina,energy,maxenergy,deg;
	int rockets,maxRockets, rocketDamage;
	float hpRes, enRes;
	int level, t_anim,t_curAnim, h_anim, h_curAnim;
	float hand_x, hand_y,h_angle,head_angle;
	bool dir;
	int handLay;
	wchar_t* curWpn;

	int curLvlIndex;

	int curBlt;

	float jPower, jAngle;

	bool allowMove;
	bool allowDraw;

	bool untouchable;
	int untouchTime;

	bool quaked;
	int quakedTime;

	int score;

	bool onStare;

	int keySize;

	int jumpTime;
	bool jump;


	

public:
	bool onFire,dieng,onPlatform;
	unsigned long steps,burn,jumpUp;
	int anim,animF,curAnim,tp,expiriense,money,ganim;
	wchar_t *spr;
	float getSpeed(){return speed;};
	_hero();
	void Respawn();
	void changeScene(int i);
	void Draw();
	void death();
	void Life();
	void Load();
	void Save(int mapIndex);
	bool Visible(int _x, int _y);
	void Up(int up);
	void ChExp(int ex);
	bool CrossObj(int _x, int _y, int _wt, int _ht);
	bool CrossZone(int _x, int _y, int rad);
	bool Alive();
	void OnPlat(bool on);
	void Interface();
	void LevelUp(int type, float count);
	void Create();
	void SetEnergy(int eg);
	void SetEnRes(float res);
	void SetHpRes(float res);
	void AddMoney(int count);
	void HandDraw();
	void EnergyStatus();
	void AddEnergy(int _count);
	void SetCurrentEnergy();
	void AddHP(int count);
	void AddRockets(int count);
	void MakeRJ(int angle, int dist);
	void RocketJump();
	void ChangeWeapon(int weaponType);
	void SetCurWpn(wchar_t* wpnName);
	void Quake(int damage);
	void Hit(int force);
	void Hit(int force, float _speed);
	void Stare(int _x);
	void SetCoordinats(int _x, int _y);
	void Reset();
	void Key();
	void AddScore(int scores);
	void TakeScore(int scores);
	int getScore();
	void Jump();

	void Upgrade(int weaponIndex, int branch, int index);
};

_hero *hero;

class laboratory
{
	bool drawing;
    int researchIndex;
    int weaponIndex;
    bool rg_extradamage1,rg_extradamage2, rg_ballshooter;
	bool rg_saving15, rg_saving2, rg_saving4;
	bool rg_speed1, rg_speed2;
	bool rg_parts2, rg_parts3;
	
	bool rt_extradamage1, rt_extradamage2;
	bool rt_increasedInv1, rt_increasedInv2;

public:
	laboratory();
	void Draw();
	bool Update();
	bool Button(int x, int y, wchar_t *pic, int sum, bool ifo);
	void Save();
} ;

laboratory *lab;

class _turret:public _character
{
public:
	bool right,built,exist,gtar;
	unsigned long shot,move;
	float angle;
	int anim,mob_i;
	_turret();
	void Draw();
	void Be();
	void Add(int _x, int _y);
};

class turrets
{
public:
	void Add(int x, int y);
	turrets();
	~turrets();
	void Draw();
	void Save(ofstream &par);
	void Clear();
private:
	int count;
	vector <_turret> tur;
};

turrets *turret;

class _redball:public _character
{
	float angle,tm;
	int damage;
	int anim;
	int type;
	bool dieng;
	//bool gotTarget;
	bool **crd;
	wchar_t *mainTxr, *shdTxr, *dieTxr;
public:
	_redball();
	void Add(int _x, int _y);
	void Be();
	void Draw();
	bool Alive();
	bool CrossZone();
	void TakeTarget();
	void MakePath();
	void Jump();
};

class redballs
{
	int count;
	vector <_redball> balls;
public:
	void Add(int _x, int _y);
	void Draw();
	void Save(ofstream &par);
	void Clear();
	redballs();
	~redballs();
};

class _lredball:public _character
{
	float angle,tm;
	int damage;
	int anim;
	bool dieng;
	//bool gotTarget;
	bool **crd;
	wchar_t *mainTxr, *shdTxr, *dieTxr;
public:
	_lredball();
	void Add(int _x, int _y);
	void Be();
	void Draw();
	bool Alive();
	bool CrossZone();
	void TakeTarget();
	void MakePath();
	void Jump();
};

class lredballs
{
	int count;
	vector <_lredball> balls;
public:
	void Add(int _x, int _y);
	void Draw();
	void Save(ofstream &par);
	void Clear();
	bool Collision();
	lredballs();
	~lredballs();
};

class _h_ghost:public _character
{
	int anim,curAnim;
	int stoptm,maxstoptm, hittm;
	int mvtm,dir_anim;
	bool dir,alive,dead, allowMove,created;
	bool hits;
	float lev;
	unsigned long breath;
public:
	_h_ghost();
	void Add(int _x, int _y);
	void Draw();
	void Be();
	void Death();
	void Kill();
	void Respawn();
	void Anim();
	void Update();
    void SetAnim(int _curAnim);
	void Moving();
};

class h_ghosts
{
	vector <_h_ghost> gst;
	int count;
public:
	void Add(int x, int y);
	void Draw();
	void Save(ofstream &par);
	void Clear();
	h_ghosts();
	~h_ghosts();
};


class _quest
{
	wchar_t *text, *seps;
	int len;
public:
	_quest();
	~_quest();
	void PrintQ();
	void Pars(char *file);
};
_quest *qtxt;


class _quester:public _character
{
	bool talking,heroZone;
	vector <_quest> quests;

public:
	_quester();
	void Draw();
	void Talk();
};

class _platform
{
	int x,y;
	int ht, wt;
	int speed;
	bool up;
	int stoptm;
	int dist,maxdist;

public:
	int startx,starty;
	void Move();
	void Draw();
	void Add(int _x, int _y);
	_platform();
};

class platforms
{
	int count;
	vector <_platform> plt;
public:
	platforms();
	~platforms();
	void Add(int x, int y);
	void Draw();
	void Save(ofstream &par);
	void Clear();

};


class _bullet
{
	float x,y,speed,angle,size,fall_a;
	int damage,type;
	bool ex, dir,animated,exploded;
	bool nextAdded;
	int anim;
	int transparency;
	int nextBulletTime;
	unsigned long sound;
	int livetm;
	wchar_t* shoot_sound;
public:
	void Move();
	void Explode();
	void Draw();
	void Add(float _x, float _y, float _tx, float _ty ,int _type);
	bool There();
	void CheckCollision(_character &mob);
	void CheckEnemy(enemy &mob);
	_bullet();
};

class bullets
{
	int count;
	vector <_bullet> blt;
public:
	void Add(int x, int y, int tx, int ty, int type);
	void Draw();
	bool There();
	int BulletCount();
	void CheckCollision(_character &mob);
	void CheckEnemyCollision(enemy &mober);
	bullets();
	~bullets();
};

class heroHit
{
	float x,y;
	int damage;
	float speed;
	float maxSpeed;
	int nextBulletTime;

public:
	float getX(){return x;};
	float getY(){return y;};
	float getSpeed(){return speed;};
	void Move();
	void Update();
	heroHit();
	heroHit(int _type, int _x,int _y);
};

class heroHits
{
	int count;
	vector <heroHit> hitDesk;
public:
	void Add(int _type, int _x, int _y, bool _direction);
	void Draw();
	bool There();
	bool HeroCollision();
	heroHits();
	~heroHits();
};

class _money
{
	float x,y,speed,a,fall_a;
	int count,anim;
	int flytm,maxflytm,lifetm;
	bool throwing,dir,up,deleted;
public:
	void Throw();
	void GiveMoney();
	void Add(int _x, int _y, int _count);
	void Draw();
	bool Destroyed();
	void Destroy();
	_money();
};

class moneys
{
	int count;
	vector <_money> mn;
public:
	void Add(int x, int y, int _count);
	void Draw();
	void Clear();
	moneys();
	~moneys();
};

class _stuff
{
	int type;
	float x, y;
	int ht,wt;
	float fly;
	int lifetime;
	bool blink;
	float a,max_a;
	wchar_t *sprite,*sound;
	bool deleted;
public:
	void Add(int _type, int _x, int _y);
	void Draw();
	bool Destroyed();
	void Fall();
	_stuff();
};

class stuffDesk
{
	int count;
	vector <_stuff> stf;
public:
	void Add(int type, int x, int y);
	void Destroy(int i);
	void Draw();
	void Clear();
	stuffDesk();
	~stuffDesk();
};


class inv_object
{
	int x,y;
	int type;
	int count;
	wchar_t *sprite;
	bool deleted;
public:
	void Add(int _type);
	void Draw(int _x, int _y);
	inv_object();
};

class _inventory
{
	int count;
	int x,y;
	vector <inv_object> inv;
public:
	void Draw();
	void Clear();
	void Save();
	void Load();
	_inventory();
   ~_inventory();
};

class _effect
{
	float x,y;
	float centrCoef;
	int dtm, maxdtm,num,showtm;
	int transparency;
	int red,green, blue;
	bool animated,finished,number;
	int anim;
	wchar_t *sprite;
	int type;
	float size;
	int angle;
	float a,speed,maxspeed;
public:
	_effect();
	void Draw();
	void Add(int _type, int _x, int _y);
	void AddNum(int _num,int _x, int _y);
	bool Finish();
};

class effects
{
	int count;
	vector <_effect> eft;
public:
	effects();
	~effects();
	void Add(int type, int x, int y);
	void AddNum(int num, int x, int y);
	void Draw();
	void Clear();
	void Destroy(int i);
};





class _golem:public enemy
{

private:
	bool direction;
	bool attack;
	int attackCicle, startAttackCicle;//время до следующей атаки
	int anim, curAnim;
	int leftTarget,rightTarget;
	float speedIncrement;
	bool allowDraw;

public:
	void Stamp();//Удар ногой по земле
	void Draw();
	void Act();
	void Patrol();//Патрулирование территории, возвращает true при HeroTrigger
	bool HeroTrigger();
	bool HeroTrigger(int startX, int endX);
	void Kill();
	_golem();
	_golem(int _x, int _y); 
};

class golems
{
	int count;
	vector <_golem> golemDesk;
public:
	golems();
	~golems();
	void Add(int x, int y);
	void Draw();
	void Clear();
	void Destroy(int i);
	void Save(ofstream &par);
};

class _flyHead:public enemy
{

private:
	bool direction;
	int leftTarget, rightTarget;
	bool allowDraw;
	float speedIncrement;
	int anim, curAnim;

public:

	void Draw();
	void Act();
	void Patrol();
	//bool HeroTrigger(int startX, int endX);
	void Kill();
	void Animate(int animIndex);
	_flyHead();
	_flyHead(int _x, int _y);
};

class flyHeads
{

private:

	int count;
	vector<_flyHead> heads;

public:

	void Add(int x, int y);
	void Draw();
	void Clear();
	void Destroy(int i);
	void Save(ofstream &par);
	flyHeads();
	~flyHeads();
};

class alien : public enemy
{
private:
	bool direction;
	bool attack;
	bool allowDraw;
	int leftTarget, rightTarget;
	int anim, curAnim;
	double speedIncrement;
	int attackCicle, startAttackCicle;

public:
	void Draw();
	void Patrol();
	void Kill();
	bool HeroTrigger();
	bool HeroTrigger(int startX, int endX);
	void Act();
	alien();
	alien(int _x, int _y);
};

class aliens
{
private:
	vector <alien> aln;
	int count;

public:
	void Add(int x, int y);
	void Draw();
	void Clear();
	int Count(){return aln.size();}
	aliens();
	~aliens();
};

class spider:public enemy
{
private:
	bool direction;
	bool attack;
	int leftTarget, rTarget;
	int anim, curAnim;
public:
	void Draw();
	void Patrol();
	//void Kill();
	bool HeroTrigger(int startX, int endX);
	void Act();
	spider();
	spider(int _x, int _y);
};

class spiders
{
private:
	spider *spd;
public:
	void Add(int x, int y);
	void Draw();
	int Count();
	void Clear();
	spiders();
	~spiders();
};

class teleporter
{
	int index;
	int x,y;
	int anim, curAnim;
	bool opened;
public:
	void Draw();
	teleporter();
	teleporter(int _x, int _y, int _index);
	void Open();
};

class teleporters
{
	vector<teleporter> tp;
public:
	void Add(int x, int y, int index);
	void Draw();
	void Clear(){tp.clear();}
	void Open();
	int Num(){return tp.size();}
	~teleporters();
};

class objs
{
	int count;
	
public:
	turrets *tur;
	redballs *balls;
	lredballs *lballs;
	h_ghosts *h_gst;
	platforms *plt;
	bullets *blt;
	moneys* mn;
	_inventory *inv;
	stuffDesk *stf;
	effects *eft;
	golems *golemStruct;
	flyHeads *flyHead;
	aliens *alns;
	teleporters* tps;

	objs();
	~objs();
	void Draw();
	void Load();
	void Save();
	void Add(int type, int x, int y);//мобы
	void AddLRedball(int x, int y);
	void Add(int type, int x, int y, int tx, int ty);//пули
	void AddMoney(int x, int y, int _count);//деньги
	void AddStuff(int x, int y, int type);
	void AddEffect(int type, int x, int y);
	void AddFinish(int x, int y, int index);
	void AddNum(int num, int x, int y);
	void CheckBullets(_character &mob);
	void CheckBulletCollision(enemy &mob);
	void Clear();
	void OpenTP();
};

objs *objects;
vector <_character *> mob_arr;




#include "camera.h"
#include "character.h"
#include "hero.h"
#include "turret.h"
#include "redball.h"
#include "lredball.h"
#include "h_ghost.h"
#include "NPC.h"
#include "things.h"
#include "objects.h"
#include "bullets.h"
#include "heroHit.h"
#include "money.h"
#include "inventory.h"
#include "stuff.h"
#include "effects.h"
#include "quests.h"
#include "enemy.h"
#include "golem.h"
#include "flyHeads.h"
#include "alien.h"
#include "teleporters.h"
#include "lab.h"
#include "spiders.h"