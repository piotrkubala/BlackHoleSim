#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <SFML/Graphics.hpp>

class GameWindow
{
    sf::RenderWindow window;
    sf::RectangleShape displayShaderRectangle;
    sf::Texture backgroundTexture;
    sf::Shader mainBlackHoleFragmentShader;

    sf::Clock timeSinceOpen;

    void rescale();
    void events();

    void initialize();

public:
    GameWindow(int x = 100, int y = 100, bool fullScreen = false);
    virtual ~GameWindow();

    void loop();
};

#endif