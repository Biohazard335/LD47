#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <vector>

#include "../Circular_Entity.hpp"
#include "../../wave/Wave.hpp"

class Bullet_Manager;
class Bullet;

struct EnemyStats{
	EnemyStats()
		: boss_(false), health_(0), damage_(0), bullet_speed_(0), fire_delay_(0), speed_(0), radius_(0) {}
	EnemyStats(bool boss, float health, float damage, float bullet_speed, float fire_delay, float speed, float radius)
		: boss_(boss), health_(health), damage_(damage), bullet_speed_(bullet_speed), fire_delay_(fire_delay), speed_(speed), radius_(radius) {}
	bool boss_;
	float health_;
	float damage_;
	float bullet_speed_;
	float fire_delay_;
	float speed_;
	float radius_;
	float get_difficulty_score() { return (1 / (bullet_speed_*fire_delay_) * 100 + damage_)*(1 + boss_ * 5); }
};

class Enemy : public Circular_Entity
{

public:
	Enemy(Bullet_Manager* bullet_manager);
	Enemy();
	~Enemy();
	virtual void update() = 0;
	virtual void doSpawn() = 0;
	virtual std::vector<Spawn_Data> get_babies();

	bool is_alive();
	void take_damage(float damage);
	float get_health();
	EnemyStats get_stats();
	virtual EnemyType get_type() = 0;
	void set_moving(bool b_p){moving=b_p;}

	int difficulty=1;


protected:
	int m_fire_timer;
	bool m_spawned;
	bool m_spawning;
	std::vector<Bullet*> m_bullets;
	Bullet_Manager* m_bullet_manager;
	std::vector<Point> m_bullet_spawn_points;
	EnemyStats m_stats;
	Point m_spawn_point;
	bool moving=false;

	virtual void flight_path() = 0;
	virtual void spawn_path() = 0;
	virtual void fire() = 0;

};

#endif //ENEMY_HPP