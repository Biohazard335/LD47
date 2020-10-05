#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Circular_Entity.hpp"
#include "../../communal/LDUtil.hpp"
#include "../Bullet/Bullet_Manager.hpp"
#include "../../image/Imagehandler.hpp"

#include <iostream>

class Player : public Circular_Entity
{
    private:
        Bullet_Manager* p_BulletMan;
        Animation a_Ring;
        Animation a_Core;
        Animation a_HappyCore;
        Animation a_DeadCore;
        Animation a_DeadRing;

        float f_HealthLimit = 100.f;
        float f_HealthLeft = f_HealthLimit;
        float f_PlayerSpd = 7.f;
        bool b_isDead = false;
        bool b_isDeadOver = false;

        std::vector<Point> v_Line;
        float f_LineLimit = 2.5f;
        float f_LineLeft = f_LineLimit;
        bool b_isLooping = false;
        bool b_isHoldingLoop = false;
        bool b_isSnappingLoop = false;

    public:
        Player() {};
        Player(Bullet_Manager* b_man) { p_BulletMan = b_man; };

        float get_HealthLimit() { return f_HealthLimit; };
        void set_HealthLimit(float f) { f_HealthLimit = f; };
        float get_HealthLeft() { return f_HealthLeft; };
        void set_HealthLeft(float f) { f_HealthLeft = f; };
        bool get_isDead() { return b_isDead; };
        void set_isDead(bool b) { b_isDead = b; };
        bool get_isDeadOver() { return b_isDeadOver; };
        void set_isDeadOver(bool b) { b_isDeadOver = b; };

        float get_PlayerSpd() { return f_PlayerSpd; };
        void set_PlayerSpd(int i) { f_PlayerSpd = i; };

        std::vector<Point> get_Line() { return v_Line; };
        float get_LineLimit() { return f_LineLimit; };
        void set_LineLimit(float f) { f_LineLimit = f; };
        float get_LineLeft() { return f_LineLeft; };
        void set_LineLeft(float f) { f_LineLeft = f; };

        bool get_isLooping() { return b_isLooping; };
        void set_isLooping(bool b) { b_isLooping = b; };
        bool get_isHoldingLoop() { return b_isHoldingLoop; };
        void set_isHoldingLoop(bool b) { b_isHoldingLoop = b; };

        float get_HealthRatio() { return f_HealthLeft / f_HealthLimit; };
        float get_LineRatio() { return f_LineLeft / f_LineLimit; };

        void update(World_Data world, Point move, bool shifted);
        void draw(World_Data world, sf::RenderWindow& window);

        void load_ring(Imagehandler& image_handler);
        void take_damage(float damage);
        void start_loop();
        void validate_loop();
};

#endif