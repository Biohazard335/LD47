#ifndef CIRCLE_PLAYER_HPP
#define CIRCLE_PLAYER_HPP

#include "Circular_Entity.hpp"
#include "../input/Mousey.hpp"
#include "../input/Keyblade.hpp"
#include "../input/Gamepad.hpp"

class Circle_Player: public Circular_Entity{

private:
	double speed=3;
public:
	Circle_Player(){
		animations.push_back(Animation("green_circle"));
		animations.push_back(Animation("red_circle"));
	}

	void update(Circle_Player other_p, Keyblade& keyboard, Gamepad& gamepad){
		Point dir= Point(0,0);

		if(keyboard.get_key('a').is_pressed() || gamepad.get_left_stick_x()<0 ){
			dir=Cardinal::West;
			movement=movement+(dir*speed);
		}
		if(keyboard.get_key('d').is_pressed() || gamepad.get_left_stick_x()>0 ){
			dir=Cardinal::East;
			movement=movement+(dir*speed);
		}
		if(keyboard.get_key('w').is_pressed() || gamepad.get_left_stick_y()<0 ){
			dir=Cardinal::North;
			movement=movement+(dir*speed);
		}
		if(keyboard.get_key('s').is_pressed() || gamepad.get_left_stick_y()>0 ){
			dir=Cardinal::South;
			movement=movement+(dir*speed);
		}

		if(is_colliding(other_p)){
			current_animation_int=1;
		}else{
			current_animation_int=0;
		}
		move();
		movement=Point(0,0);
	}

};

#endif