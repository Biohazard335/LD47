#ifndef BULLET_BLUEPRINT_HPP
#define BULLET_BLUEPRINT_HPP

#include "../enemy/Enemy.hpp"

enum BULLET_TYPES{
	LINEAR=0,
	SINE=1,
	HOMING=2
};

class Bullet_Blueprint{
public:
	Bullet_Blueprint(BULLET_TYPES t_p,int d_p, Point dir_p,Point c_p, float s_p, Enemy* sender){
		type=t_p;
		direction=dir_p;
		damage=d_p;
		center=c_p;
		speed=s_p;
		sender_ = sender;
	}

	BULLET_TYPES type;
	int damage;
	Point direction;
	Point center;
	float speed;
	Enemy* sender_;
};


#endif