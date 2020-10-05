#ifndef ENEMY_STRAIGHT_HPP
#define ENEMY_STRAIGHT_HPP

#include "Enemy.hpp"
#include "../../wave/Wave.hpp"
#include "../Player/Player.hpp"

class Enemy_Straight : public Enemy
{
public:
	Enemy_Straight();
	Enemy_Straight(Bullet_Manager* bullet_manager, Player* player);
	~Enemy_Straight();
	virtual void update();
	virtual void doSpawn();
	Animation getCurrentAnimation();
	virtual EnemyType get_type();

	Enemy_Straight create_copy(Point center, int radius);
	Enemy_Straight create_copy(Spawn_Data data);


private:
	int m_length;
	int m_distance_travelled;
	int m_dir;
	Player* m_player;

	virtual void flight_path();
	virtual void spawn_path();
	virtual void fire();

};

#endif //ENEMY_STRAIGHT_HPP