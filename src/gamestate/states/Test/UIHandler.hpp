#ifndef UIHANDLER_HPP
#define UIHANDLER_HPP

#include "../../../image/Imagehandler.hpp"
#include "../../../communal/LDUtil.hpp"

//sf::Shader sh_VerticalBar;

class UIHandler
{
    private:
        World_Data* world;

        Animation a_Health[2];
        Animation a_LineBar[10];
        Animation a_BossBar[10];
        Animation a_LeftPanel[9];
        Animation a_TutorialPanel[2];
        Animation a_PowerUpShelf;
        std::vector<Animation> v_Powerups;

        int i_score = 0;

        bool b_gamepadControlActive = false;
        bool b_isBossActive = false;

        float f_Health_Ratio = 1.0f;
        float f_Line_Ratio = 1.0f;
        float f_Boss_Ratio = 1.0f;

		sf::Font f_score_font;
		sf::Text t_score_text;

        sf::Shader sh_Circular;
        sf::Shader sh_Vertical;
        sf::Shader sh_Alpha;

    public:
        UIHandler() {};
        UIHandler(const UIHandler& original);
        UIHandler(World_Data& world_pointer) { world = &world_pointer; };

        int get_score() { return i_score; };
        void set_score(int i) { i_score = i; };
        void add_score(int i) { i_score += i; };

        bool get_is_gamepad_active() { return b_gamepadControlActive; };
        void set_is_gamepad_active(bool b) { b_gamepadControlActive = b; };
        void toggle_control_scheme() { b_gamepadControlActive = !b_gamepadControlActive; };

        void load_animations(Imagehandler& image_handler);
        void update(float health_ratio, float line_ratio, float boss_ratio = -1.f);
        void draw(sf::RenderWindow& window);
};

#endif // !UIHANDLER_HPP