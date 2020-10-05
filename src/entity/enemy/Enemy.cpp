#include "Enemy.hpp"
#include "../Bullet/Bullet_Manager.hpp"
#include <iostream>

Enemy::Enemy(Bullet_Manager* bullet_manager)
	: m_bullet_manager(bullet_manager)
{
}

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

std::vector<Spawn_Data> Enemy::get_babies()
{
	return std::vector<Spawn_Data>();
}

bool Enemy::is_alive()
{
	return m_stats.health_>0;
}

void Enemy::take_damage(float damage)
{
	//std::cout<<"take damage ="<<m_stats.health_<<std::endl;
	m_stats.health_ -= damage;
}

float Enemy::get_health()
{
	return m_stats.health_;
}

EnemyStats Enemy::get_stats()
{
	return m_stats;
}
