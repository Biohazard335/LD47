#ifndef ENEMY_SINE_HPP
#define ENEMY_SINE_HPP

#include "Enemy.hpp"
#include "../../wave/Wave.hpp"
#include "../Player/Player.hpp"

class Enemy_Sine : public Enemy
{
public:
	Enemy_Sine();
	Enemy_Sine(Bullet_Manager* bullet_manager, Player* player);
	~Enemy_Sine();
	virtual void update();
	virtual void doSpawn();
	Animation getCurrentAnimation();

	virtual EnemyType get_type();
	Enemy_Sine create_copy(Point center, int radius);
	Enemy_Sine create_copy(Spawn_Data data);


private:
	int m_length;
	int m_distance_travelled;
	int m_dir;
	Player* m_player;

	virtual void flight_path();
	virtual void spawn_path();
	virtual void fire();
};

#endif //ENEMY_SINE_HPP