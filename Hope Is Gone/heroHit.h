heroHit::heroHit()
{
	x=0;
	y=0;
	speed=0;
	damage=0;
	maxSpeed=0;
	nextBulletTime=0;
}

void heroHit::Move()
{
	x+=speed;
}
