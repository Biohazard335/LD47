#include "UIHandler.hpp"

void UIHandler::load_animations(Imagehandler& image_handler)
{
    // Load Animations
    // Health Sprite
    a_Health[0] = Animation("Health_UI");
    image_handler.load_animation(a_Health[0]);

    a_Health[0].scale(Point(0.75, 0.75));
    a_Health[0].set_position(Point(world->left + (a_Health[0].get_frame_width() / 2) + 20, world->bottom - (a_Health[0].get_frame_height() / 2) - 5));
    a_Health[0].set_looping(false);

    a_Health[1] = Animation("Health_Bar");
    image_handler.load_animation(a_Health[1]);

    a_Health[1].scale(Point(0.75, 0.75));
    a_Health[1].set_position(a_Health[0].get_position());
    a_Health[1].set_looping(false);

    // Tutorial Panels
    a_TutorialPanel[0] = Animation("panel_idle");
    image_handler.load_animation(a_TutorialPanel[0]);

    a_TutorialPanel[0].scale(Point(0.91f, 0.91f));
    a_TutorialPanel[0].set_position(Point(world->right - (a_TutorialPanel[0].get_frame_width() / 2) - 20, world->active_top + (a_TutorialPanel[0].get_frame_height() / 2)));
    a_TutorialPanel[0].set_looping(false);

    a_TutorialPanel[1] = Animation("panelxbox_idle");
    image_handler.load_animation(a_TutorialPanel[1]);

    a_TutorialPanel[1].scale(Point(0.91f, 0.91f));
    a_TutorialPanel[1].set_position(a_TutorialPanel[0].get_position());
    a_TutorialPanel[1].set_looping(false);

    // Line Bar
    a_LineBar[0] = Animation("Linebar_corner");
    a_LineBar[1] = Animation("Linebar_topbot");
    a_LineBar[2] = Animation("Linebar_corner");
    a_LineBar[3] = Animation("Linebar_side");
    a_LineBar[4] = Animation("Linebar_back");
    a_LineBar[5] = Animation("Linebar_side");
    a_LineBar[6] = Animation("Linebar_corner");
    a_LineBar[7] = Animation("Linebar_topbot");
    a_LineBar[8] = Animation("Linebar_corner");
    a_LineBar[9] = Animation("Linebar_bar");

    for (int i = 0; i < 10; i++)
    {
        image_handler.load_animation(a_LineBar[i]);
        a_LineBar[i].set_looping(false);
        a_LineBar[i].scale(Point(1.f, 1.f));
    }

    a_LineBar[8].set_position(Point(world->active_left - (a_LineBar[8].get_frame_width() / 2) - 15, world->active_bottom - (a_LineBar[8].get_frame_height() / 2)));
    a_LineBar[7].set_position(a_LineBar[8].get_position() - Point(a_LineBar[8].get_frame_width() / 2 + a_LineBar[7].get_frame_width() /2, 0.0f));
    a_LineBar[6].set_position(a_LineBar[7].get_position() - Point(a_LineBar[7].get_frame_width() / 2 + a_LineBar[6].get_frame_width() / 2, 0.0f));
    a_LineBar[8].set_rotation(180);
    a_LineBar[6].set_rotation(-90);

    float f_lineBarScaleY = 0.8f;
    a_LineBar[5].scale(Point(1.0f, f_lineBarScaleY)); // 462 tall
    a_LineBar[4].scale(Point(1.0f, f_lineBarScaleY));
    a_LineBar[3].scale(Point(1.0f, f_lineBarScaleY));
    a_LineBar[5].set_position(a_LineBar[8].get_position() - Point(0.0f, a_LineBar[8].get_frame_height() / 2 + a_LineBar[5].get_frame_height() / 2));
    a_LineBar[4].set_position(a_LineBar[5].get_position() - Point(a_LineBar[5].get_frame_width() / 2 + a_LineBar[4].get_frame_width() / 2, 0.0f));
    a_LineBar[3].set_position(a_LineBar[4].get_position() - Point(a_LineBar[4].get_frame_width() / 2 + a_LineBar[3].get_frame_width() / 2, 0.0f));

    a_LineBar[2].set_position(a_LineBar[5].get_position() - Point(0.0f, a_LineBar[5].get_frame_height() / 2 + a_LineBar[2].get_frame_height() / 2));
    a_LineBar[1].set_position(a_LineBar[2].get_position() - Point(a_LineBar[2].get_frame_width() / 2 + a_LineBar[1].get_frame_width() / 2, 0.0f));
    a_LineBar[0].set_position(a_LineBar[1].get_position() - Point(a_LineBar[1].get_frame_width() / 2 + a_LineBar[0].get_frame_width() / 2, 0.0f));
    a_LineBar[2].set_rotation(90);

    a_LineBar[9].scale(Point(1.0f, f_lineBarScaleY));
    a_LineBar[9].set_position(a_LineBar[4].get_position());;

    // Boss Bar
    a_BossBar[0] = Animation("Linebar_corner_enem");
    a_BossBar[1] = Animation("Linebar_topbot_enem");
    a_BossBar[2] = Animation("Linebar_corner_enem");
    a_BossBar[3] = Animation("Linebar_side_enem");
    a_BossBar[4] = Animation("Linebar_back_enem");
    a_BossBar[5] = Animation("Linebar_side_enem");
    a_BossBar[6] = Animation("Linebar_corner_enem");
    a_BossBar[7] = Animation("Linebar_topbot_enem");
    a_BossBar[8] = Animation("Linebar_corner_enem");
    a_BossBar[9] = Animation("Linebar_bar_enem");

    for (int i = 0; i < 10; i++)
    {
        image_handler.load_animation(a_BossBar[i]);
        a_BossBar[i].set_looping(false);
        a_BossBar[i].scale(Point(1.f, 1.f));
    }

    a_BossBar[8].set_position(Point(world->active_right + 15 + (a_BossBar[8].get_frame_width() / 2) + a_BossBar[7].get_frame_width() + a_BossBar[6].get_frame_width(), world->active_bottom - (a_BossBar[8].get_frame_height() / 2)));
    a_BossBar[7].set_position(a_BossBar[8].get_position() - Point(a_BossBar[8].get_frame_width() / 2 + a_BossBar[7].get_frame_width() / 2, 0.0f));
    a_BossBar[6].set_position(a_BossBar[7].get_position() - Point(a_BossBar[7].get_frame_width() / 2 + a_BossBar[6].get_frame_width() / 2, 0.0f));
    a_BossBar[8].set_rotation(180);
    a_BossBar[6].set_rotation(-90);

    float f_barScaleY = 1.6f;
    a_BossBar[5].scale(Point(1.0f, f_barScaleY)); // 462 tall
    a_BossBar[4].scale(Point(1.0f, f_barScaleY));
    a_BossBar[3].scale(Point(1.0f, f_barScaleY));
    a_BossBar[5].set_position(a_BossBar[8].get_position() - Point(0.0f, a_BossBar[8].get_frame_height() / 2 + a_BossBar[5].get_frame_height() / 2));
    a_BossBar[4].set_position(a_BossBar[5].get_position() - Point(a_BossBar[5].get_frame_width() / 2 + a_BossBar[4].get_frame_width() / 2, 0.0f));
    a_BossBar[3].set_position(a_BossBar[4].get_position() - Point(a_BossBar[4].get_frame_width() / 2 + a_BossBar[3].get_frame_width() / 2, 0.0f));

    a_BossBar[2].set_position(a_BossBar[5].get_position() - Point(0.0f, a_BossBar[5].get_frame_height() / 2 + a_BossBar[2].get_frame_height() / 2));
    a_BossBar[1].set_position(a_BossBar[2].get_position() - Point(a_BossBar[2].get_frame_width() / 2 + a_BossBar[1].get_frame_width() / 2, 0.0f));
    a_BossBar[0].set_position(a_BossBar[1].get_position() - Point(a_BossBar[1].get_frame_width() / 2 + a_BossBar[0].get_frame_width() / 2, 0.0f));
    a_BossBar[2].set_rotation(90);

    a_BossBar[9].scale(Point(1.0f, f_barScaleY));
    a_BossBar[9].set_position(a_BossBar[4].get_position());;

    // Left Pane;
    a_LeftPanel[0] = Animation("Linebar_corner");
    a_LeftPanel[1] = Animation("Linebar_topbot");
    a_LeftPanel[2] = Animation("Linebar_corner");
    a_LeftPanel[3] = Animation("Linebar_side");
    a_LeftPanel[4] = Animation("Linebar_back");
    a_LeftPanel[5] = Animation("Linebar_side");
    a_LeftPanel[6] = Animation("Linebar_corner");
    a_LeftPanel[7] = Animation("Linebar_topbot");
    a_LeftPanel[8] = Animation("Linebar_corner");

    for (int i = 0; i < 9; i++)
    {
        image_handler.load_animation(a_LeftPanel[i]);
        a_LeftPanel[i].set_looping(false);
        a_LeftPanel[i].scale(Point(1.f, 1.f));
    }

    Point PanelScale = Point(7.5f, 1.08f);
    a_LeftPanel[7].scale(Point(PanelScale.get_x(), 1.0));
    a_LeftPanel[8].set_position(Point(a_LineBar[0].get_position().get_x() - 15 - (a_LineBar[0].get_frame_width() / 2) - (a_LeftPanel->get_frame_width() / 2), a_Health[0].get_position().get_y() - 15 - (a_Health[0].get_frame_width() / 2)));
    a_LeftPanel[7].set_position(a_LeftPanel[8].get_position() - Point(a_LeftPanel[8].get_frame_width() / 2 + a_LeftPanel[7].get_frame_width() / 2, 0.0f));
    a_LeftPanel[6].set_position(a_LeftPanel[7].get_position() - Point(a_LeftPanel[7].get_frame_width() / 2 + a_LeftPanel[6].get_frame_width() / 2, 0.0f));
    a_LeftPanel[8].set_rotation(180);
    a_LeftPanel[6].set_rotation(-90);

    a_LeftPanel[5].scale(Point(1.0, PanelScale.get_y())); // 462 tall
    a_LeftPanel[4].scale(PanelScale);
    a_LeftPanel[3].scale(Point(1.0, PanelScale.get_y()));
    a_LeftPanel[5].set_position(a_LeftPanel[8].get_position() - Point(0.0f, a_LeftPanel[8].get_frame_height() / 2 + a_LeftPanel[5].get_frame_height() / 2));
    a_LeftPanel[4].set_position(a_LeftPanel[5].get_position() - Point(a_LeftPanel[5].get_frame_width() / 2 + a_LeftPanel[4].get_frame_width() / 2, 0.0f));
    a_LeftPanel[3].set_position(a_LeftPanel[4].get_position() - Point(a_LeftPanel[4].get_frame_width() / 2 + a_LeftPanel[3].get_frame_width() / 2, 0.0f));

    a_LeftPanel[1].scale(Point(PanelScale.get_x(), 1.0));
    a_LeftPanel[2].set_position(a_LeftPanel[5].get_position() - Point(0.0f, a_LeftPanel[5].get_frame_height() / 2 + a_LeftPanel[2].get_frame_height() / 2));
    a_LeftPanel[1].set_position(a_LeftPanel[2].get_position() - Point(a_LeftPanel[2].get_frame_width() / 2 + a_LeftPanel[1].get_frame_width() / 2, 0.0f));
    a_LeftPanel[0].set_position(a_LeftPanel[1].get_position() - Point(a_LeftPanel[1].get_frame_width() / 2 + a_LeftPanel[0].get_frame_width() / 2, 0.0f));
    a_LeftPanel[2].set_rotation(90);

    // Load shaders
    if (sf::Shader::isAvailable)
    {
        // Load from file
        if (!sh_Circular.loadFromFile("../assets/shader/sh_3_4_CircularBar.fsh", sf::Shader::Fragment))
        {// throw a fit
            cout << "Circular shader failed to load." << endl;
        }
        if (!sh_Vertical.loadFromFile("../assets/shader/sh_VerticalBar.fsh", sf::Shader::Fragment))
        {// throw a fit
            cout << "Vertical bar shader failed to load." << endl;
        }
        if (!sh_Alpha.loadFromFile("../assets/shader/sh_Alpha.fsh", sf::Shader::Fragment))
        {// throw a fit
            cout << "Vertical bar shader failed to load." << endl;
        }
    }
    else
    {//you're out of luck as far as shaders go
        cout << "Shaders not supported. Some UI elements may not appear correctly." << endl;
    }


	if (!f_score_font.loadFromFile("../assets/font/System_Breach_wide.ttf"))
	{
		std::cout << "Error Loading Font!";
	}

	t_score_text.setFont(f_score_font);

	t_score_text.setCharacterSize(18);
	t_score_text.setFillColor(sf::Color::White);

	t_score_text.setPosition(a_LeftPanel[0].get_position().get_x() + 10, a_LeftPanel[0].get_position().get_y() + 10);

}


void UIHandler::update(float health_ratio, float line_ratio, float boss_ratio)
{
	t_score_text.setString("Score: " + std::to_string(get_score()));

    f_Line_Ratio = line_ratio;
    f_Health_Ratio = health_ratio;

    if (boss_ratio != -1.0f)
    {
        b_isBossActive = true;
        f_Boss_Ratio = boss_ratio;
    }
    else if (b_isBossActive)
        b_isBossActive = false;
}

void UIHandler::draw(sf::RenderWindow& window)
{
    // Draw health
    window.draw(a_Health[0].get_current_frame());
    sh_Circular.setUniform("BaseTexture", sf::Shader::CurrentTexture);
    sh_Circular.setUniform("uv_topLeft", sf::Vector2f(0.0, 0.5));
    sh_Circular.setUniform("uv_botRight", sf::Vector2f(1.0, 1.0));
    sh_Circular.setUniform("percentage", f_Health_Ratio);
    window.draw(a_Health[1].get_current_frame(), &sh_Circular);

    // Draw Line bar
    for (int i = 0; i < 9; i++)
    { window.draw(a_LineBar[i].get_current_frame()); }

    sh_Vertical.setUniform("BaseTexture", sf::Shader::CurrentTexture);
    sh_Vertical.setUniform("v_bounds", sf::Vector2f(0.33, 0.5));
    sh_Vertical.setUniform("percentage", f_Line_Ratio);
    window.draw(a_LineBar[9].get_current_frame(), &sh_Vertical);

    // Draw boss health
    for (int i = 0; i < 9; i++)
    {
        window.draw(a_BossBar[i].get_current_frame());
    }

    if (b_isBossActive)
    {// Use the health shader
        sh_Vertical.setUniform("BaseTexture", sf::Shader::CurrentTexture);
        sh_Vertical.setUniform("v_bounds", sf::Vector2f(0.66, 1.0));
        sh_Vertical.setUniform("percentage", f_Boss_Ratio);
        window.draw(a_BossBar[9].get_current_frame(), &sh_Vertical);
    }
    else
    {// Mute the bar
        sh_Alpha.setUniform("BaseTexture", sf::Shader::CurrentTexture);
        sh_Alpha.setUniform("alpha", 0.0f);
        window.draw(a_BossBar[9].get_current_frame(), &sh_Alpha);
    }

    // Draw left panel
    for (int i = 0; i < 9; i++)
    {
        window.draw(a_LeftPanel[i].get_current_frame());
    }

    // Draw tutorial message
    if (b_gamepadControlActive)
        window.draw(a_TutorialPanel[1].get_current_frame());
    else
        window.draw(a_TutorialPanel[0].get_current_frame());

	window.draw(t_score_text);
}