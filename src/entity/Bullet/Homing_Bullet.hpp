#ifndef HOMING_BULLET_HPP
#define HOMING_BULLET_HPP

#include "Bullet.hpp" 
#include "Bullet_Blueprint.hpp" 

class Player;

class Homing_Bullet: public Bullet{
private:
	Player* player=nullptr;
public:
	Homing_Bullet();

	void update()override;
	void create(Point center_p, int radius_p, Point direction_p)override;
	Homing_Bullet create_copy(Point center_p, int radius_p, Point direction_p, Enemy* sender,Player* player);
	Homing_Bullet create_copy(Bullet_Blueprint,Player* player);

};

#endif