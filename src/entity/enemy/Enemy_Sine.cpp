#include "Enemy_Sine.hpp"
#include "../../communal/LDUtil.hpp"
#include "../Bullet/Bullet_Manager.hpp"
#include <math.h>

Enemy_Sine::Enemy_Sine()
{
	animations.push_back(Animation("Sine_Idle"));

	animations.push_back(Animation("Sine_Build"));
	animations.at(1).set_looping(false);
	animations.at(1).set_desired_fps(1);
	m_stats = EnemyStats(false, 10, 1, 2, 20, 1, 0);
}

Enemy_Sine::Enemy_Sine(Bullet_Manager * bullet_manager, Player * player)
{
	animations.push_back(Animation("Sine_Idle"));
	animations.push_back(Animation("Sine_Build"));
	animations.at(1).set_looping(false);
	animations.at(1).set_desired_fps(1);
	m_stats = EnemyStats(false, 10, 1, 2, 30, 1, 0);

	m_bullet_manager = bullet_manager;
	m_player = player;

	m_length = 100;
	m_distance_travelled = 0;
	m_dir = 1;

	m_fire_timer = 0;

	m_spawned = false;
	m_spawning = false;

	m_bullet_spawn_points.push_back(Point(16,16));
}

Enemy_Sine::~Enemy_Sine()
{
}

void Enemy_Sine::update()
{
	animate();
	if (m_spawned) {
		set_current_animation(0);
		flight_path();
		if (m_fire_timer >= m_stats.fire_delay_) {
			fire();
			m_fire_timer = 0;
		}

		m_fire_timer++;
	}
	else if (m_spawning) {
		spawn_path();
	}
}

void Enemy_Sine::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	set_movement(Point(m_stats.speed_*m_dir, 0));

	if(moving)
		move();
	sf::Sprite current_animation = animations.at(0).get_current_frame();

	m_distance_travelled++;
}

void Enemy_Sine::spawn_path()
{
	float posy = get_center().get_y();
	float targety = m_spawn_point.get_y();
	rotate_animations(-90);

	if (targety > posy) {
		Point dir(0, targety - posy);
		dir.normalize();

		set_movement(Point(0, m_stats.speed_*dir.get_y()));
		move();

		if (animations.at(current_animation_int).is_finished())
			set_current_animation(0);
	}
	else {
		m_spawning = false;
		m_spawned = true;
	}
}

void Enemy_Sine::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		float rot = getCurrentAnimation().get_current_frame().getRotation();


		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);
		
		Point dir = Point(0, 1);
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::SINE, m_stats.damage_, dir, Point(get_center().get_x(), get_center().get_y()), m_stats.bullet_speed_, this));
	}
	m_bullet_manager->add_bullets(bullets);
}

void Enemy_Sine::doSpawn()
{
	m_spawning = true;
	set_current_animation(1);
}

Animation Enemy_Sine::getCurrentAnimation()
{
	return animations.at(0);
}

EnemyType Enemy_Sine::get_type()
{
	return kEnemySine;
}

Enemy_Sine Enemy_Sine::create_copy(Point center, int radius)
{
	m_spawn_point = center;
	create(Point(center.get_x(), -2 * radius), radius);

	m_stats.radius_ = radius;
	return *this;
}

Enemy_Sine Enemy_Sine::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	moving=data.moving;
	return *this;
}

