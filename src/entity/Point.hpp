#ifndef POINT_HPP
#define POINT_HPP
#include <math.h>

class Point{
private:
	float x;
	float y;
public:
	Point(){};
	Point(float x_p, float y_p):x(x_p),y(y_p){}

	Point operator +(Point p_p){return Point(x+p_p.get_x(),y+p_p.get_y());}
	Point operator -(Point p_p){return Point(x-p_p.get_x(),y-p_p.get_y());}
	Point operator *(float i_p){return Point(x*i_p,y*i_p);}
	Point operator /(float i_p){return Point(x/i_p,y/i_p);}
	Point operator *=(float d_p) { return Point(x *= d_p, y *= d_p); }
	Point operator +=(Point p_p) { return Point(x += p_p.get_x(), y += p_p.get_y()); }
	Point operator =(Point p_p) { return Point(x = p_p.get_x(), y = p_p.get_y()); }

	Point operator -(){return Point(-x,-y);}
	bool operator ==(Point p_p){
		if(p_p.get_x()==x && p_p.get_y()==y)return true;
		else return false;
	}
	bool operator !=(Point p_p){
		if(p_p.get_x()!=x || p_p.get_y()!=y)return true;
		else return false;
	}

	void normalize(){
		float length=sqrt(x*x+y*y);
		x=x/length;
		y=y/length;
	}

	float get_x(){return x;}
	float get_y(){return y;}
	void set_x(float x_p){x=x_p;}
	void set_y(float y_p){y=y_p;}
	void set_point(float x_p, float y_p){set_x(x_p);set_y(y_p);}
	void set_point(Point new_p){set_x(new_p.get_x());set_y(new_p.get_y());}

	void move(float x_p, float y_p){x+=x_p;y+=y_p;}
	void move(Point p_p){x+=p_p.get_x();y+=p_p.get_y();}
};

namespace Cardinal{
	const Point North=Point(0,-1);
	const Point South=Point(0,1);
	const Point East=Point(1,0);
	const Point West=Point(-1,0);
	const Point none=Point(0,0);

	static int to_degrees(Point p_p){
		if(p_p==North)return 270;
		else if(p_p==West)return 180;
		else if(p_p==South)return 90;
		else return 0;
	}
	static Point orthogonal(Point p_p){
		if(p_p.get_x()==0){
			return Point(1,0);
		}else{
			return Point(0,1);
		}
	}
}
#endif