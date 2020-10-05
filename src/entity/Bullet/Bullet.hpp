#ifndef BULLET_HPP
#define BULLET_HPP

#include "../Circular_Entity.hpp"
#include "../enemy/Enemy.hpp"
#include <vector>
#include <memory>


class Bullet:public Circular_Entity{
protected:
	float speed=0;
	Point direction=Point(0,0);
	int damage=0;
	bool exploding=false;
	bool removing=false;
    bool returning = false;
	Enemy* sender;

public:
	Bullet(){}
	virtual void update()=0;
	virtual void create(Point center_p, int radius_p, Point direction_p)=0;

	void set_exploding(bool b_p){exploding=b_p;}
	void set_removing(bool b_p){removing=b_p;}
    void set_returning(bool b_p) { returning = b_p; }

	bool is_exploding(){return exploding;}
	bool is_removing(){return removing;}
    bool is_returning() { return returning; }

	int get_damage(){return damage;}

};

typedef std::vector<std::shared_ptr<Bullet>> Bullet_Vector;

#endif