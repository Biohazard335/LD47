#ifndef WAVE_HPP
#define WAVE_HPP

#include <vector>

#include "../communal/Tick_Timer.hpp"
#include "../entity/Point.hpp"



enum EnemyType {
	kEnemyStraight,
	kEnemyBurst,
	kEnemySine,
	kEnemyV,
	kEnemyHoming,
	kEnemyBoss
};
struct Spawn_Data {

	Spawn_Data(int enemy_type, bool elite, bool moving, Point pos, float spawn_delay_p)
		: enemy_type(enemy_type),elite(elite), pos(pos), spawn_delay(spawn_delay_p){}

	int enemy_type;
	Point pos;
	bool elite;
	bool moving=false;
	Tick_Timer spawn_delay;
	float radius=5;
};

typedef std::vector<std::vector<EnemyType>> Enemy_Type_Pool;
typedef std::initializer_list<std::vector<EnemyType>> ETP_Initializer;

struct Wave {

	Wave(Enemy_Type_Pool enemy_type_pool, bool boss, std::vector<Spawn_Data> spawn_data, int difficulty)
		: enemy_type_pool(enemy_type_pool), boss(boss), spawn_data(spawn_data),difficulty(difficulty)
	{
	}
	Wave() {};
	void update();
	bool is_spawning_enemy(){return spawning_enemy;}
	std::vector<Spawn_Data> get_enemies_to_spawn(){return enemies_to_spawn;}

	std::vector<Spawn_Data> enemies_to_spawn;
	Enemy_Type_Pool enemy_type_pool;
	bool boss;
	bool spawning_enemy=false;
	std::vector<Spawn_Data> spawn_data;
	int difficulty;

	int time_used=-8000;

};



#endif //WAVE_HPP