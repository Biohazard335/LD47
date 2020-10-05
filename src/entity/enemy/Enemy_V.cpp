#include "Enemy_V.hpp"
#include "../Bullet/Bullet_Manager.hpp"

Enemy_V::Enemy_V()
{
	animations.push_back(Animation("Fish_Idle"));

	animations.push_back(Animation("Fish_Build"));
	animations.at(1).set_looping(false);
	animations.at(1).set_desired_fps(1);
	m_stats = EnemyStats(false, 10, 5, 2, 20, 1, 0);
}

Enemy_V::Enemy_V(Bullet_Manager * bullet_manager)
{
	animations.push_back(Animation("Fish_Idle"));

	animations.push_back(Animation("Fish_Build"));
	animations.at(1).set_looping(false);
	animations.at(1).set_desired_fps(1);
	m_stats = EnemyStats(false, 10, 5, 2, 30, 1, 0);

	m_bullet_manager = bullet_manager;

	m_length = 100;
	m_distance_travelled = 0;
	m_dir = 1;

	m_fire_timer = 0;

	m_spawned = false;
	m_spawning = false;

	m_bullet_spawn_points.push_back(Point(343.0f / 2, 323.0f / 2));
	m_bullet_spawn_points.push_back(Point(343.0f / 2, 323.0f / 2));
}

Enemy_V::~Enemy_V()
{
}

void Enemy_V::update()
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

void Enemy_V::flight_path()
{
	if (m_distance_travelled >= m_length) {
		m_dir = -m_dir;
		m_distance_travelled = 0;
	}

	set_movement(Point(0, m_stats.speed_*m_dir));

	if(moving)
		move();

	m_distance_travelled++;
}

void Enemy_V::spawn_path()
{
	float posy = get_center().get_y();
	float targety = m_spawn_point.get_y();

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

void Enemy_V::fire()
{
	std::vector<Bullet_Blueprint> bullets;
	for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
		float x = m_bullet_spawn_points.at(i).get_x();
		float y = m_bullet_spawn_points.at(i).get_y();

		sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x,y);


		Point dir = Point(cos(60*M_PI/180)*i==0?1:-1, sin(60*M_PI/180));
		dir.normalize();

		bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_stats.damage_, dir, Point(spawn.x, spawn.y), m_stats.bullet_speed_,this));
	}
	m_bullet_manager->add_bullets(bullets);
}

void Enemy_V::doSpawn()
{
	rotate_animations(-90);
	m_spawning = true;
	set_current_animation(1);
}

Animation Enemy_V::getCurrentAnimation()
{
	return animations.at(0);
}

EnemyType Enemy_V::get_type()
{
	return kEnemyV;
}

Enemy_V Enemy_V::create_copy(Point center, int radius)
{
	m_spawn_point = center;
	create(Point(center.get_x(), -2 * radius), radius);

	m_stats.radius_ = radius;

	return *this;
}

Enemy_V Enemy_V::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	moving=data.moving;
	return *this;
}


