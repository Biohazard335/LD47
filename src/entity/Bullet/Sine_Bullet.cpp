#include "Sine_Bullet.hpp"
#include "../../communal/Communal.hpp"
#include <math.h>
#include <iostream>

Sine_Bullet::Sine_Bullet(){
	animations.push_back(Animation("bullet_flying2"));
	animations.push_back(Animation("bullet_burst2"));
	animations.at(1).set_looping(false);
	damage=5;
	speed=5;
	radius=5;
	mod_speed=6;
	mod_amount=0.5f;
}

void Sine_Bullet::update(){
	if(degrees>359){
		degrees=0;
	}else{
		degrees+=mod_speed;
	}
	Point mod=Point(sin_degrees(degrees),sin_degrees(degrees+90));
	movement=direction+mod*mod_amount;
	movement.normalize();
	movement*=speed;
	Bullet::update();
}

void Sine_Bullet::create(Point center_p, int radius_p, Point direction_p){
	int degrees=90;
	set_center(center_p);
	hitbox.create(center_p,radius_p);

	direction=direction_p;
	direction.normalize();
	degrees=atan2_degrees(direction.get_y(),(direction.get_x()))+180;
	movement=direction*speed;
	rotate_animations(degrees);
}



Sine_Bullet Sine_Bullet::create_copy(Point center_p, int radius_p, Point direction_p, Enemy* sender){
	create(center_p,radius_p,direction_p);
	this->sender = sender;
	return *this;
}

Sine_Bullet Sine_Bullet::create_copy(Bullet_Blueprint b_p){
	create(b_p.center,radius,b_p.direction);
	this->sender = b_p.sender_;
	return *this;
}