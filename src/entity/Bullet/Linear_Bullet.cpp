#include "Linear_Bullet.hpp"
#include "../../communal/Communal.hpp"
#include <math.h>
#include <iostream>

Linear_Bullet::Linear_Bullet(){
	animations.push_back(Animation("bullet_flying0"));
	animations.push_back(Animation("bullet_burst0"));
	animations.at(1).set_looping(false);
	damage=5;
	speed=4;
	radius=5;
}

void Linear_Bullet::update(){
	if(exploding){
		current_animation_int=1;
		if(animations.at(1).is_finished()){
			removing=true;
		}
		animate();
	}else{
		move();
	}
}

void Linear_Bullet::create(Point center_p, int radius_p, Point direction_p){
	int degrees=90;
	set_center(center_p);
	hitbox.create(center_p,radius_p);

	direction=direction_p;
	direction.normalize();
	degrees=atan2_degrees(direction.get_y(),(direction.get_x()))+180;
	movement=direction*speed;
	rotate_animations(degrees);
}



Linear_Bullet Linear_Bullet::create_copy(Point center_p, int radius_p, Point direction_p){
	create(center_p,radius_p,direction_p);
	return *this;
}

Linear_Bullet Linear_Bullet::create_copy(Bullet_Blueprint b_p){
	create(b_p.center,radius,b_p.direction);
	return *this;
}