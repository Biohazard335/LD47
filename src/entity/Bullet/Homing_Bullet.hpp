#ifndef HOMING_BULLET_HPP
#define HOMING_BULLET_HPP

#include "Bullet.hpp" 
#include "Bullet_Blueprint.hpp" 

class Homing_Bullet: public Bullet{
private:
public:
	Homing_Bullet();

	void update()override;
	void create(Point center_p, int radius_p, Point direction_p)override;
	Homing_Bullet create_copy(Point center_p, int radius_p, Point direction_p);
	Homing_Bullet create_copy(Bullet_Blueprint);

};

#endif