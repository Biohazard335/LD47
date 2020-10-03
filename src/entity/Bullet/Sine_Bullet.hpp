#ifndef SINE_BULLET_HPP
#define SINE_BULLET_HPP

#include "Bullet.hpp" 
#include "Bullet_Blueprint.hpp" 

class Sine_Bullet: public Bullet{
private:
public:
	Sine_Bullet();

	void update()override;
	void create(Point center_p, int radius_p, Point direction_p)override;
	Sine_Bullet create_copy(Point center_p, int radius_p, Point direction_p);
	Sine_Bullet create_copy(Bullet_Blueprint);

};

#endif