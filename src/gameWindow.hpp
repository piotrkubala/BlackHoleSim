#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <SFML/Graphics.hpp>

#include "observer.hpp"

class GameWindow
{
    sf::RenderWindow window;
    sf::RectangleShape displayShaderRectangle;
    sf::Texture backgroundTexture;
    sf::Shader mainBlackHoleFragmentShader;

    Observer mainObserver;

    sf::Clock timeSinceOpen;
    sf::Clock timeSinceLastFrame;

    void rescale();
    void events();

    void initialize();

    void observerMovement();

public:
    GameWindow(int x = 100, int y = 100, bool fullScreen = false);
    virtual ~GameWindow();

    void loop();
};

#endif