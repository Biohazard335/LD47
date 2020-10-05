#ifndef ENEMY_V_HPP
#define ENEMY_V_HPP

#include "Enemy.hpp"
#include "../../wave/Wave.hpp"
#include "../Player/Player.hpp"

class Enemy_V : public Enemy
{
public:
	Enemy_V();
	Enemy_V(Bullet_Manager* bullet_manager);
	~Enemy_V();
	virtual void update();
	virtual void doSpawn();
	Animation getCurrentAnimation();
	virtual EnemyType get_type();

	Enemy_V create_copy(Point center, int radius);
	Enemy_V create_copy(Spawn_Data data);


private:
	int m_length;
	int m_distance_travelled;
	int m_dir;


	virtual void flight_path();
	virtual void spawn_path();
	virtual void fire();
};

#endif