#ifndef BULLET_BLUEPRINT_HPP
#define BULLET_BLUEPRINT_HPP

enum BULLET_TYPES{
	LINEAR=0,
	SINE=1,
	HOMING=2
};

class Bullet_Blueprint{
public:
	Bullet_Blueprint(BULLET_TYPES t_p,int d_p, Point dir_p,Point c_p, float s_p){
		type=t_p;
		direction=dir_p;
		damage=d_p;
		center=c_p;
		speed=s_p;
	}

	BULLET_TYPES type;
	int damage;
	Point direction;
	Point center;
	float speed;
};


#endif