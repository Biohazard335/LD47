#ifndef CIRCULAR_HITBOX
#define CIRCULAR_HITBOX

#include "Point.hpp"

class Circular_Hitbox{
private:
	Point center;
	double radius;

public:
	Circular_Hitbox(){}
	void create(Point center_p, double radius_p){
		center=center_p;
		radius=radius_p;
	}

	Point get_center(){return center;}
	double get_radius(){return radius;}

	void move(Point p_p){
		center+=p_p;
	}

	void set_center(Point p_p){
		center=p_p;
	}

	bool is_colliding(Circular_Hitbox other_p){
		double x_dist=center.get_x()-other_p.get_center().get_x();
		double y_dist=center.get_y()-other_p.get_center().get_y();
		double distance_squared=y_dist*y_dist + x_dist*x_dist;
		double radii_squared=(radius+other_p.get_radius())*(radius+other_p.get_radius());
		if(distance_squared <= radii_squared){
			return true;
		}else{
			return false;
		}
	}
};

#endif