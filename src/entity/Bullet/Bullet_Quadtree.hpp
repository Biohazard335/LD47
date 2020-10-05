#ifndef BULLET_QUADTREE_HPP
#define BULLET_QUADTREE_HPP
#include "Bullet.hpp" 
#include <memory>

class Bullet_Quadtree:public sf::Drawable{
private:

	static int instance_cap;

	int max_depth=20;
	int this_depth=0;
	bool children=false;

	Point top_left_bound=Point(0,0);
	Point bottom_right_bound=Point(0,0);
	Point center=Point(0,0);

	Bullet_Vector bullets; 

	std::unique_ptr<Bullet_Quadtree> top_left_child=nullptr;
	std::unique_ptr<Bullet_Quadtree> top_right_child=nullptr;
	std::unique_ptr<Bullet_Quadtree> bottom_left_child=nullptr;
	std::unique_ptr<Bullet_Quadtree> bottom_right_child=nullptr;



	void insert_into_children(std::shared_ptr<Bullet>);
	void split();
	void unsplit();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	//static std::vector<sf::RectangleShape> rectangles;
	sf::RectangleShape rect;
	Bullet_Quadtree(Point tlb_p, Point brb_p,int depth_p);

	bool insert(std::shared_ptr<Bullet>);
	Bullet_Vector get_collidable_bullets(Point p_p);
	Bullet_Vector get_collidable_bullets_bound(Point tl_p,Point br_p);
	bool colliding_with_bound(Point tl_p,Point br_p);
	Bullet_Vector get_all_bullets();
	bool has_children(){return children;}

	void update();
	void clear();
	int get_depth(){return this_depth;}

};

#endif