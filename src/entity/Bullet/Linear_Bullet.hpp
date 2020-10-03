#ifndef LINEAR_BULLET_HPP
#define LINEAR_BULLET_HPP

#include "Bullet.hpp" 
#include "Bullet_Blueprint.hpp" 

class Linear_Bullet: public Bullet{
private:
public:
	Linear_Bullet();

	void update()override;
	void create(Point center_p, int radius_p, Point direction_p)override;
	Linear_Bullet create_copy(Point center_p, int radius_p, Point direction_p);
	Linear_Bullet create_copy(Bullet_Blueprint);

};

#endif