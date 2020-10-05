#ifndef ENEMY_BURST_HPP
#define ENEMY_BURST_HPP

#include "Enemy.hpp"
#include "../../wave/Wave.hpp"
#include "../Player/Player.hpp"

class Enemy_Burst : public Enemy
{
public:
	Enemy_Burst();
	Enemy_Burst(Bullet_Manager* bullet_manager);
	~Enemy_Burst();
	virtual void update();
	virtual void doSpawn();
	
	Animation getCurrentAnimation();
	virtual EnemyType get_type();
	Enemy_Burst create_copy(Point center, int radius);
	Enemy_Burst create_copy(Spawn_Data data);


private:
	int m_length;
	int m_distance_travelled;
	int m_dir;

	virtual void flight_path();
	virtual void spawn_path();
	virtual void fire();
};

#endif //ENEMY_STRAIGHT_HPP