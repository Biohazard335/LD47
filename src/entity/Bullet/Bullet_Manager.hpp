#ifndef BULLET_MANAGER_HPP
#define BULLET_MANAGER_HPP

#include "Bullet.hpp"
#include "Linear_Bullet.hpp"
#include "Sine_Bullet.hpp"
#include "Homing_Bullet.hpp"
#include "Bullet_Blueprint.hpp"
#include "SFML/Graphics.hpp"
#include "../Player/Player.hpp"

class Imagehandler;

class Bullet_Manager:public sf::Drawable{
private:
	Linear_Bullet linear_bullet;
	Homing_Bullet homing_bullet;
	Sine_Bullet sine_bullet;
	Bullet_Vector live_bullets;
	Bullet_Vector captured_bullets;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Bullet_Manager();

	void load_animations(Imagehandler&);

	Bullet_Vector bullets_colliding_with_hitbox(Circular_Hitbox hitbox_p);
	void capture_bullets(std::vector<Point> line_p);
	void add_bullets(std::vector<Bullet_Blueprint>);

	void update_player_position(Point);

	void update();
};


#endif