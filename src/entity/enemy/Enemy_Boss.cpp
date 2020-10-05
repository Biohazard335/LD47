#include "Enemy_Boss.hpp"
#include "../Bullet/Bullet_Manager.hpp"
#include <iostream>
#include "../../wave/Wave_Manager.hpp"

Enemy_Boss::Enemy_Boss()
{
	animations.push_back(Animation("boss_body"));
	animations.push_back(Animation("boss_west"));
	animations.push_back(Animation("boss_east"));
	m_stats = EnemyStats(true, 1000, 10, 5, 10, 2.0f, 0);
	m_cycle_timer = Tick_Timer(m_baby_spawn_tick_time);
	m_procreate = false;
}

Enemy_Boss::Enemy_Boss(Bullet_Manager * bullet_manager, Player* player, World_Data* world_data)
	: m_player(player), m_world_data(world_data)
{
	animations.push_back(Animation("boss_body"));
	animations.push_back(Animation("boss_west"));
	animations.push_back(Animation("boss_east"));
	m_stats = EnemyStats(true, 1000, 10, 5, 10, 2.0f, 0);
	m_enemy_straight = Enemy_Straight(m_bullet_manager, m_player);

	m_bullet_manager = bullet_manager;

	m_distance_travelled = 0;
	m_dir = 1;

	m_fire_timer = 0;

	m_spawning = false;
	m_spawned = false;

	m_bullet_spawn_points.push_back(Point(306.0f / 2, 463.0f));
	m_bullet_spawn_points.push_back(Point(306.0f / 2, 463.0f));
	m_bullet_spawn_points.push_back(Point(306.0f / 2, 463.0f));

	m_bullet_spawn_points.push_back(Point(306.0f / 2 - 362.0f, 463.0f - 89.0f));
	m_bullet_spawn_points.push_back(Point(306.0f / 2 - 362.0f, 463.0f - 89.0f));
	m_bullet_spawn_points.push_back(Point(306.0f / 2 - 362.0f, 463.0f - 89.0f));

	m_bullet_spawn_points.push_back(Point(306.0f / 2 + 362.0f, 463.0f - 89.0f));
	m_bullet_spawn_points.push_back(Point(306.0f / 2 + 362.0f, 463.0f - 89.0f));
	m_bullet_spawn_points.push_back(Point(306.0f / 2 + 362.0f, 463.0f - 89.0f));

	m_cycle_timer = Tick_Timer(m_baby_spawn_tick_time);
	m_open = true;
	m_procreate = false;
}

Enemy_Boss::~Enemy_Boss()
{
}

void Enemy_Boss::update()
{
	update_arms();
	if (m_spawned) {
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

	if (m_cycle_timer.do_timer_loop())
		m_open = !m_open;
}

void Enemy_Boss::doSpawn()
{
	m_spawning = true;
}

void Enemy_Boss::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < animations.size(); i++)
		target.draw(animations.at(i).get_current_frame(), states);
}

std::vector<Spawn_Data> Enemy_Boss::get_babies()
{
	return m_babies;
}

bool Enemy_Boss::is_procreating()
{
	return m_procreate;
}

bool Enemy_Boss::is_open()
{
	return m_open;
}

void Enemy_Boss::set_procreating(bool procreate)
{
	m_procreate = procreate;
}

void Enemy_Boss::set_origin(Point p_p)
{
	animations.at(0).set_origin(p_p.get_x(), p_p.get_y());
	animations.at(1).set_origin(238-103, -99);
	animations.at(2).set_origin(544 - 494, -99);
	/*animations.at(2).set_origin(159, -264);
	animations.at(4).set_origin(-55, -264);*/

}

Animation Enemy_Boss::getCurrentAnimation()
{
	return animations.at(current_animation_int);
}

EnemyType Enemy_Boss::get_type()
{
	return kEnemyBoss;
}

Enemy_Boss Enemy_Boss::create_copy(Point center, int radius)
{
	m_spawn_point = center;

	update_template(center);

	create(Point(center.get_x(), -2 * radius), radius);

	m_stats.radius_ = radius;
	return *this;
}

Enemy_Boss Enemy_Boss::create_copy(Spawn_Data data)
{
	create_copy(data.pos, data.radius);
	return *this;
}

void Enemy_Boss::flight_path()
{
	if (get_center().get_x() + 100 >= m_world_data->active_right && m_dir > 0) {
		m_dir = -m_dir;
	}
	else if (get_center().get_x() - 100 <= m_world_data->active_left && m_dir < 0) {
		m_dir = -m_dir;
	}

	sf::Sprite current_animation = getCurrentAnimation().get_current_frame();

	set_movement(Point(m_stats.speed_*m_dir, 0));
	move();

	m_distance_travelled++;
}

void Enemy_Boss::spawn_path()
{
	float posy = get_center().get_y();
	float targety = m_spawn_point.get_y();

	sf::Sprite body = animations.at(0).get_current_frame();

	set_origin(Point(body.getLocalBounds().width/2, body.getLocalBounds().height/2));

	if (targety > posy) {
		Point dir(0, targety - posy);
		dir.normalize();

		set_movement(Point(0, m_stats.speed_*dir.get_y()));
		move();
	}
	else {
		m_spawning = false;
		m_spawned = true;
	}
}

void Enemy_Boss::fire()
{
	if (m_open) {
		m_procreate = true;
		std::vector<Bullet_Blueprint> bullets;
		for (int i = 0; i < m_bullet_spawn_points.size(); i++) {
			float x = m_bullet_spawn_points.at(i).get_x();
			float y = m_bullet_spawn_points.at(i).get_y();

			float rot = (i % 3 - 1) * 30 - 90;

			sf::Vector2f spawn = getCurrentAnimation().get_current_frame().getTransform().transformPoint(x, y);

			Point dir = Point(-cos(rot*M_PI / 180), -sin(rot*M_PI / 180));
			dir.normalize();

			bullets.push_back(Bullet_Blueprint(BULLET_TYPES::LINEAR, m_stats.damage_, dir, Point(spawn.x, spawn.y), m_stats.bullet_speed_, this));
		}
		m_bullet_manager->add_bullets(bullets);
	}
}

void Enemy_Boss::update_arms()
{
	sf::Vector2f body = animations.at(0).get_current_frame().getPosition();
	//animations.at(1).set_position(body.x - animations.at(0).get_frame_width() / 2 - 10, body.y - animations.at(1).get_frame_height() / 2 + 2);
	//animations.at(3).set_position(body.x + animations.at(0).get_frame_width() / 2 + 10, body.y - animations.at(3).get_frame_height() / 2 + 2);

	Point left = animations.at(1).get_position();
	Point right = animations.at(2).get_position();

	animations.at(1).set_position(body.x - 5, body.y - 45);
	animations.at(2).set_position(body.x, body.y - 45);
	/*
	animations.at(2).set_position(body.x, body.y - 40);
	animations.at(4).set_position(body.x - 7, body.y - 33);
	*/
	//animations.at(2)

	if (m_open) {
		animations.at(1).set_rotation(47);
		animations.at(2).set_rotation(-47);
		/*
		animations.at(2).set_rotation(47);
		animations.at(4).set_rotation(-47);*/
	}
	else{

		animations.at(1).set_rotation(30);
		animations.at(2).set_rotation(-30);

		/*animations.at(2).set_rotation(0);
		animations.at(4).set_rotation(0);*/
	}

}

void Enemy_Boss::update_template(Point center)
{
	m_babies = {
		Spawn_Data(kEnemyStraight,false,false,Point(0.5*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 400),0),
		Spawn_Data(kEnemyStraight,false,false,Point(1.5*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 400),m_baby_spawn_tick_time*1/7),
		Spawn_Data(kEnemyStraight,false,false,Point(2.5*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 400),m_baby_spawn_tick_time*2/7),
		Spawn_Data(kEnemyStraight,false,false,Point(3.5*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 400),m_baby_spawn_tick_time*3/7),

		Spawn_Data(kEnemyStraight,false,false,Point(0.75*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 200),m_baby_spawn_tick_time*4/7),
		Spawn_Data(kEnemyStraight,false,false,Point(1.75*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 200),m_baby_spawn_tick_time*5/7),
		Spawn_Data(kEnemyStraight,false,false,Point(2.75*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 200),m_baby_spawn_tick_time*6/7),
		Spawn_Data(kEnemyStraight,false,false,Point(3.75*m_world_data->active_width / 4 + m_world_data->active_left, get_center().get_y() + 200),m_baby_spawn_tick_time),

	};
}
