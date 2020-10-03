#ifndef CIRCULAR_ENTITY_HPP
#define CIRCULAR_ENTITY_HPP

#include "Circular_Hitbox.hpp"
#include "Point.hpp"
#include "../image/Animation.hpp"
#include "SFML/Graphics.hpp"
#include <vector>

class Imagehandler;

/*
	Entity holds collision and image data. add_animation shoudl be called in the constructor of your entity derived class. the string passed into add_animation needs to
	EXACTLY equal the name of some animation that has already been loaded by the Imagehandler, otherwise you'll just see a rotating error symbol 
	in the constructor of your state class you should call load_animations AFTER all desired animations have been added. animations added after load_animations will have no texture
	applied to them, and will simply be blank.

	By default the create() method will generate a hitbox the same size as the first animation added, to specify hitbox size use create_hitbox() AFTER create()
	(the bug that caused the program to crash if there was no first animation has been resolved, but you should still specify adding animations before creating an instance)

	Inhereits sf::Drawable, to render call window.draw(this) in your gamestate's render function. you must explicitly call animate() somewhere each tick or the frames wont update
*/


class Circular_Entity:public sf::Drawable{

protected:
	Circular_Hitbox hitbox;
	std::vector<Animation> animations;
	int current_animation_int=0;// window.draw(this) will draw the current frame of the animation at this index in the animations vector

	Point center=Point(0,0);//top left
	double radius;

	Point movement=Point(0,0);//change in position to be applied when you call move()

	Circular_Hitbox projected_hitbox;//used internally to check for collisions

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Circular_Entity(){};

	virtual void create(Point center_p, double radius_p);//point in world space
	virtual void create_hitbox(Point center_p, double radius_p);

	Animation& ref_animation(int i_p){return animations.at(i_p);}//editing animations directly is HIGHLY discouraged!
	void set_current_animation(int i_p){current_animation_int=i_p;}//use this to switch which animation will be displayed when you cann window.draw(this)
	virtual void animate();//needs to be called every tick to advance the animation to the next frame when appropriate 

	void add_animation(std::string name_p){animations.push_back(Animation(name_p));}//DO THIS IN THE CONSTRUCTOR

	Circular_Hitbox get_hitbox(){return hitbox;}
	Circular_Hitbox& ref_hitbox(){return hitbox;}

	Point get_movement(){return movement;}
	Point& ref_movement(){return movement;}
	void set_movement(Point p_p){movement=p_p;}

	void set_center(Point p_p);
	Point get_center(){return center;}

	bool is_colliding(Circular_Entity other_p){return hitbox.is_colliding(other_p.get_hitbox());}


	virtual void move();//Doesn't check for collisions unless you tell it to!
	virtual void load_animations(Imagehandler&);
	virtual void rotate_animations(int);
	virtual void scale_animations(Point);

};


#endif