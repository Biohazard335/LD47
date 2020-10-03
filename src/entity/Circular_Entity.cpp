#include "Circular_Entity.hpp"
#include "../image/Imagehandler.hpp"
#include <iostream>



void Circular_Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	target.draw(animations.at(current_animation_int).get_current_frame(), states);
}
void Circular_Entity::animate(){
	animations.at(current_animation_int).animate();
}

void Circular_Entity::create(Point center_p, double radius_p){
	hitbox.create(center_p, radius_p);
	set_center(center_p);
}


void Circular_Entity::create_hitbox(Point center_p, double radius_p){
	radius=radius_p;
	hitbox.create(center_p,radius_p);
}


void Circular_Entity::move(){
	center+=movement;
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).move(movement);
	}
	hitbox.move(movement);
}

void Circular_Entity::set_center(Point p_p){
	center=p_p;
	hitbox.set_center(p_p);

	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).set_position(center.get_x(),center.get_y());
	}
}

void Circular_Entity::load_animations(Imagehandler& imagehandler){
	for(int i=0;i<(int)animations.size();i++){
		imagehandler.load_animation(animations.at(i));
	}
}

void Circular_Entity::rotate_animations(int deg_p){
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).set_rotation(deg_p);
	}
}
void Circular_Entity::scale_animations(Point scale_p){
	for(int i=0;i<(int)animations.size();i++){
		animations.at(i).scale(scale_p);
	}
}