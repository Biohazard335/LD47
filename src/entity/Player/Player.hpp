#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../Entity.hpp"

class Player : public Entity
{
    private:
        int i_PlayerSpd;

        std::vector<Point> v_Line;
        float f_LineLimit;
    public:
        Player() {};
        int get_PlayerSpd() { return i_PlayerSpd; };
        void set_PlayerSpd(int i) { i_PlayerSpd = i; };
        float get_LineLimit() { return f_LineLimit; };
        void set_LineLimit(float f) { f_LineLimit = f; };
};

#endif