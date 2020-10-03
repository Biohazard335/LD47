#ifndef ANIMATION_HPP
#define ANIMATION_HPP


#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../entity/Point.hpp"
#include "Animation_Blueprint.hpp"

class Animation{
private:
	std::string name;

	int frame_width=0;
	int frame_height=0;
	int rect_x=0;
	int rect_y=0;

	int origin_x=0;
	int origin_y=0;
	int rows=0;
	int collumns=0;
	int buffer_x=0;
	int buffer_y=0;

	int rotation=0;
	bool mirrored=false;

	bool loop=true;
	bool finished=false;

	float fps_timer=0;
	float desired_fps=12.0f;
	float recorded_fps=60.0f;

	int current_frame=0;
	std::vector<sf::Sprite> sprites;
	int number_of_frames=1;


public:
	Animation(){;}
	Animation(std::string n_p){name=n_p;}
	void load(sf::Texture&,int, int, int,int);
	void load(sf::Texture& ,Animation_Blueprint);

	void set_position(int,int);
	void set_position(Point p_p){
		set_position(p_p.get_x(),p_p.get_y());
	}
	void move(int,int);

	void move(Point p_p);

	int get_frame_width(){return frame_width;}
	int get_frame_height(){return frame_height;}

	void set_desired_fps(float i_p){desired_fps=i_p;}

	bool is_finished(){return finished;}
	void start(){finished=false;current_frame=0;}

	void set_looping(bool l_p){loop=l_p;}
	bool is_looping(){return loop;}

	void set_rotation(int r_p){
		rotation=r_p;
		for(int i=0;i<number_of_frames;i++){
			sprites[i].setRotation(rotation);
		}
	}

	void scale(Point scale){
		for(int i=0;i<number_of_frames;i++){
			sprites[i].scale(scale.get_x(),scale.get_y());
		}
	}

	void set_h_mirror(bool b_p);

	void animate();
	sf::Sprite get_current_frame()const;

	std::string get_name(){return name;}
};

#endif