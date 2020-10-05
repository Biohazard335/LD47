#include "Wave_Manager.hpp"
#include "../communal/Communal.hpp"


Wave_Manager::Wave_Manager(Bullet_Manager* bullet_manager, Player* player, World_Data* world_data, UIHandler* ui_handler)
	: bullet_manager(bullet_manager), player(player), world_data(world_data), ui_handler(ui_handler)
{
	enemy_straight = Enemy_Straight(bullet_manager, player);
	enemy_burst = Enemy_Burst(bullet_manager);
	enemy_sine = Enemy_Sine(bullet_manager, player);
	enemy_v = Enemy_V(bullet_manager);
	enemy_boss = Enemy_Boss(bullet_manager, player, world_data);
	enemies= std::vector<Enemy*>();
	load_templates();

}

Wave_Manager::Wave_Manager()
{	
}


void Wave_Manager::create(){
	initial_wave_time=3000;
	next_wave=Tick_Timer(initial_wave_time);
	generate_waves();
	desired_difficulty=10;
	//enemies.push_back(new Enemy_V(enemy_v.create_copy(Spawn_Data(0,false,Point(400,30),0))));
	//enemies.at(0)->doSpawn();

}

void Wave_Manager::load_animations(Imagehandler & imagehandler)
{
	enemy_straight.load_animations(imagehandler);
	enemy_burst.load_animations(imagehandler);
	enemy_sine.load_animations(imagehandler);
	enemy_v.load_animations(imagehandler);
	enemy_boss.load_animations(imagehandler);
	enemy_straight.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	enemy_burst.scale_animations(Point(48.0f / 360.0f, 48.0f / 360.0f));
	enemy_sine.scale_animations(Point(32.0f / 360.0f, 32.0f / 360.0f));
	enemy_v.scale_animations(Point(32.0f / 343.0f, 32.0f / 323.0f));
	enemy_boss.scale_animations(Point(64.0f / 306.0f, 64.0f / 306.0f));
}

void Wave_Manager::load_templates(){
	std::vector<Wave> tier;

	Enemy_Type_Pool type_pool={{kEnemyStraight,kEnemyBurst,kEnemySine,kEnemyV}};

	std::vector<Spawn_Data> spawn_data={
		Spawn_Data(0,false,false,Point(0.25f,0.3f),0),
		Spawn_Data(0,false,false,Point(0.5f,0.3f),0),
		Spawn_Data(0,false,false,Point(0.75f,0.3f),0)
	};
	int wave_difficulty=10;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));



	type_pool={{kEnemyV},{kEnemyStraight}};
	spawn_data={
		Spawn_Data(1,false,false,Point(0.2f,0.2f),0),
		Spawn_Data(1,false,false,Point(0.8f,0.2f),0),
		Spawn_Data(0,false,false,Point(0.5f,0.2f),0),

	};
	wave_difficulty=10;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyBurst}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.5f,0.2f),0),
		Spawn_Data(0,false,false,Point(0.5f,0.4f),0),
		Spawn_Data(0,false,false,Point(0.5f,0.6f),0),

	};
	wave_difficulty=10;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));

	wave_templates.push_back(tier);
	tier.clear();
/////////
	type_pool={{kEnemySine},{kEnemyV}};
	spawn_data={
		Spawn_Data(0,false,true,Point(0.2f,0.3f),0),
		Spawn_Data(0,false,true,Point(0.5f,0.2f),0),
		Spawn_Data(0,false,false,Point(0.8f,0.3f),0),
		Spawn_Data(1,false,false,Point(0.2f,0.2f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.3f),0),
		Spawn_Data(1,false,false,Point(0.8f,0.2f),0),

	};
	wave_difficulty=20;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyBurst},{kEnemyStraight}};
	spawn_data={
		Spawn_Data(0,false,true,Point(0.5f,0.3f),0),
		Spawn_Data(0,false,true,Point(0.5f,0.6f),0),
		Spawn_Data(1,false,false,Point(0.2f,0.1f),0),
		Spawn_Data(1,false,false,Point(0.8f,0.1f),0),
		Spawn_Data(1,false,false,Point(0.2f,0.9f),0),
		Spawn_Data(1,false,false,Point(0.8f,0.9f),0),

	};
	wave_difficulty=30;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));



	type_pool={{kEnemyV},{kEnemyStraight},{kEnemyStraight,kEnemySine}};
	spawn_data={
		Spawn_Data(0,false,true,Point(0.1f,0.3f),0),
		Spawn_Data(0,false,true,Point(0.5f,0.3f),0),
		Spawn_Data(1,false,false,Point(0.9f,0.3f),0),
		Spawn_Data(1,false,false,Point(0.3f,0.15f),0),
		Spawn_Data(1,false,false,Point(0.7f,0.15f),0),
		Spawn_Data(2,false,false,Point(0.4f,0.15f),0),
		Spawn_Data(2,false,false,Point(0.6f,0.15f),0),

	};
	wave_difficulty=40;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));

	wave_templates.push_back(tier);
	tier.clear();
/////////

	type_pool={{kEnemyV},{kEnemyBurst},{kEnemySine}};
	spawn_data={
		Spawn_Data(0,false,true,Point(0.25f,0.35f),0),
		Spawn_Data(0,false,true,Point(0.5f,0.25f),0),
		Spawn_Data(0,false,false,Point(0.75f,0.35f),0),
		Spawn_Data(0,false,false,Point(0.5,0.45f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.35f),0),
		Spawn_Data(2,false,false,Point(0.25f,0.25f),0),
		Spawn_Data(2,false,false,Point(0.75f,0.25f),0),

	};
	wave_difficulty=40;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));

	type_pool = { {kEnemyBoss} };
	spawn_data = {
		Spawn_Data(0,false,true,Point(0.5f,0.1f),0),

	};

	wave_difficulty = 40;

	tier.push_back(Wave(type_pool, false, spawn_data, wave_difficulty));


	type_pool={{kEnemyStraight},{kEnemyBurst},{kEnemySine}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.5f,0.1f),0),
		Spawn_Data(0,false,false,Point(0.2f,0.9f),0),
		Spawn_Data(0,false,false,Point(0.8f,0.9f),0),
		Spawn_Data(0,false,false,Point(0.5f,0.9f),0),
		Spawn_Data(1,false,false,Point(0.35f,0.5f),0),
		Spawn_Data(1,false,false,Point(0.7f,0.5f),0),
		Spawn_Data(2,false,false,Point(0.25f,0.25f),0),
		Spawn_Data(2,false,false,Point(0.75f,0.25f),0),

	};
	wave_difficulty=40;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));
	wave_templates.push_back(tier);
	tier.clear();
////

	type_pool={{kEnemyV},{kEnemyBurst,kEnemyStraight}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.15f,0.15f),0),
		Spawn_Data(0,false,false,Point(0.15f,0.3f),0),
		Spawn_Data(0,false,false,Point(0.15f,0.45f),0),
		Spawn_Data(0,false,false,Point(0.85f,0.15f),0),
		Spawn_Data(0,false,false,Point(0.85f,0.3f),0),
		Spawn_Data(0,false,false,Point(0.85f,0.45f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.2f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.4f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.6f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.8f),0),

	};
	wave_difficulty=40;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	type_pool={{kEnemyV},{kEnemyBurst},{kEnemyStraight},{kEnemySine}};
	spawn_data={
		Spawn_Data(0,false,false,Point(0.35f,0.30f),0),
		Spawn_Data(0,false,false,Point(0.7f,0.30f),0),
		Spawn_Data(1,false,false,Point(0.5f,0.45f),0),
		Spawn_Data(2,false,false,Point(0.1f,0.15f),0),
		Spawn_Data(2,false,false,Point(0.5f,0.15f),0),
		Spawn_Data(2,false,false,Point(0.9f,0.15f),0),
		Spawn_Data(3,false,false,Point(0.35f,0.15f),0),
		Spawn_Data(3,false,false,Point(0.5f,0.30f),0),
		Spawn_Data(3,false,false,Point(0.7f,0.15f),0),

	};
	wave_difficulty=40;

	tier.push_back(Wave(type_pool,false,spawn_data,wave_difficulty));


	wave_templates.push_back(tier);
	tier.clear();
////

	type_pool = { {kEnemyBoss} };
	spawn_data = {
		Spawn_Data(0,false,true,Point(0.5f,0.1f),0),

	};
	wave_difficulty = 45;

	boss=Wave(type_pool, false, spawn_data, wave_difficulty);
}



Wave_Manager::~Wave_Manager()
{
	for (int i = 0; i < enemies.size(); i++) {
		delete enemies.at(i);
	}
}


void Wave_Manager::add_enemy(Spawn_Data spawn_data){

	switch(static_cast<EnemyType>(spawn_data.enemy_type)){
		case kEnemyStraight:enemies.push_back(new Enemy_Straight(enemy_straight.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemyBurst:enemies.push_back(new Enemy_Burst(enemy_burst.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemySine:enemies.push_back(new Enemy_Sine(enemy_sine.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemyV:enemies.push_back(new Enemy_V(enemy_v.create_copy(spawn_data)));enemies.back()->doSpawn();break;
		case kEnemyBoss:enemies.push_back(new Enemy_Boss(enemy_boss.create_copy(spawn_data))); enemies.back()->doSpawn(); break;
		default:break;
	}
}

void Wave_Manager::update()
{game_tick++;

	//determine current desired difficulty level based on time spent in game/number of waves defeated

	desired_difficulty=(game_tick/200)+waves_defeated*2;
	//determine current actual difficulty level	based on current spawning waves and persistent enemies


	if(waves_defeated>0 && waves_defeated%10==0){
		add_enemy(Spawn_Data(kEnemyBoss,false,true,Point(0.5f,0.1f),0));
		next_wave.restart();
	}

	// if neccessary push back new wave based on difference between desired and actual using templates

	// for current waves spawn enemies if neccessary

	for(int i=0;i<(int)current_waves.size();i++){
		current_waves.at(i).update();
		for(int j=0;j<(int)current_waves.at(i).enemies_to_spawn.size();j++){
			add_enemy(current_waves.at(i).enemies_to_spawn.at(j));
		}
		current_waves.at(i).enemies_to_spawn.clear();
		if(current_waves.at(i).spawn_data.size()==0){
			current_waves.erase(current_waves.begin()+i);
		}
	}

	// for current enemies update
	current_difficulty=0;
	for(int i=0;i<(int)enemies.size();i++){
		if(enemies.at(i)->is_alive()){
			if (enemies.at(i)->get_type() == kEnemyBoss) {
				if (((Enemy_Boss*)enemies.at(i))->is_procreating() && !((Enemy_Boss*)enemies.at(i))->is_open()) {
					std::vector<Spawn_Data> babies = enemies.at(i)->get_babies();
					for (int j = 0; j < babies.size(); j++) {
						add_enemy(babies.at(j));
					}
					((Enemy_Boss*)enemies.at(i))->set_procreating(false);
				}
			}
			enemies.at(i)->update();
			current_difficulty+=enemies.at(i)->difficulty;
		}else{
			enemies.erase(enemies.begin()+i);
			i--;
			ui_handler->set_score(ui_handler->get_score() + 1);
		}
	}

	if(enemies.size()==0){
		generate_waves();
		next_wave.restart();
	}
	if(next_wave.do_timer_loop()){
		generate_waves();
	}
	//std::cout<<desired_difficulty<<std::endl;

}

void Wave_Manager::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < enemies.size(); i++) {
		target.draw(*enemies.at(i));
	}
}

void Wave_Manager::generate_waves()
{	//std::cout<<"generate_waves"<<std::endl;
	if(current_waves.size()==0){while(current_difficulty<desired_difficulty){

	Point center = Point(world_data->width / 2, world_data->height / 2);
	Point opos;


	//AI LOGIC
	int tier=-1;
	int desired_tier=(int)((desired_difficulty-current_difficulty)/10);
	std::vector<int> possibles=std::vector<int>();
	do{
		if(desired_tier<0){
			tier=0;
		}else if(desired_tier>wave_templates.size()-1){
			desired_tier--;
		}else{
			for(int i=0;i<(int)wave_templates.at(desired_tier).size();i++){
				std::cout<<wave_templates.at(desired_tier).at(i).time_used<<std::endl;
				if(wave_templates.at(desired_tier).at(i).time_used<7000){
					possibles.push_back(i);
					if(tier==-1){
						current_difficulty+=wave_templates.at(desired_tier).at(i).difficulty;
						tier=desired_tier;
					}
				}
			}
			if(possibles.size()==0){
				desired_tier--;
			}
		}
		std::cout<<"desired="<<desired_difficulty<<" c="<<current_difficulty<<" d_tier="<<desired_tier<<" possibles="<<possibles.size()<<std::endl;
		//std::cout<<"desired="<<desired_difficulty<<"c="<<current_difficulty<<"d_tier="<<desired_tier<<"possibles="<<possibles.size();
	}while(tier==-1);

	std::cout<<std::endl<<std::endl;


	if(tier!=-1){


		int r=random(0,possibles.size()-1);
		r=possibles.at(r);

		if(testing_wave_x!=-1){
			tier=testing_wave_x;
			r=testing_wave_y;
		}

	//std::cout<<r<<std::endl;

		Wave blueprint= wave_templates.at(tier).at(r);

		wave_templates.at(tier).at(r).time_used=game_tick;

		current_difficulty+=blueprint.difficulty;

		Enemy_Type_Pool wave_pool={};
		std::vector<Spawn_Data> spawn_data=blueprint.spawn_data;
		bool boss=blueprint.boss;
		int difficulty=0;

		std::vector<EnemyType> types_chosen={};
		for(int i=0;i<(int)blueprint.enemy_type_pool.size();i++){
			int pool_size=blueprint.enemy_type_pool.at(i).size()-1;

			//AI LOGIC
			r= random(0,pool_size);

			types_chosen.push_back(blueprint.enemy_type_pool.at(i).at(r));
		}

		for(int i=0;i<(int)spawn_data.size();i++){
			spawn_data.at(i).enemy_type=(int)types_chosen.at(spawn_data.at(i).enemy_type);
			opos=spawn_data.at(i).pos;
			spawn_data.at(i).pos=Point(opos.get_x()*world_data->active_width+world_data->active_left,opos.get_y()*world_data->active_height+world_data->active_top)
				/*+Point(random(-50,50),random(-50,50))*/;
		}

		current_waves.push_back(Wave(wave_pool,boss,spawn_data,difficulty));

		next_wave.set_max(initial_wave_time+waves_defeated*20);

	}
		
}}}

