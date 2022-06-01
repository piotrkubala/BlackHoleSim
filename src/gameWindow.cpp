#include "gameWindow.hpp"

#include <iostream>
#include <cmath>

GameWindow::GameWindow(int x, int y, bool fullScreen): window(sf::VideoMode(x, y), "Schwarzschild Black Hole Simulation", fullScreen ? sf::Style::Fullscreen : sf::Style::Resize | sf::Style::Close)
{
    initialize();
}

GameWindow::~GameWindow()
{
    window.close();
}

void GameWindow::rescale()
{
    sf::Vector2f rozmiary = static_cast <sf::Vector2f> (window.getSize());
    
    displayShaderRectangle.setPosition(sf::Vector2f(0.0f, 0.0f));

    mainBlackHoleFragmentShader.setUniform("u_resolution", rozmiary);
}

void GameWindow::initialize()
{
    if(!backgroundTexture.loadFromFile("./img/milkyWayImage.png"))
        std::cerr << "CERR: nie udalo sie wczytac pliku tekstury ./img/milkyWayImage.png\n";
    
    if(!mainBlackHoleFragmentShader.loadFromFile("./shaders/mainBlackHoleShader.frag", sf::Shader::Fragment))
        std::cerr << "CERR: nie udalo sie wczytac pliku zrodlowego shadera ./shaders/mainBlackHoleShader.frag\n";

    window.setFramerateLimit(60);
    timeSinceOpen.restart();
    displayShaderRectangle.setSize(static_cast <sf::Vector2f> (window.getSize()));
    mainBlackHoleFragmentShader.setUniform("u_background", backgroundTexture);
    mainBlackHoleFragmentShader.setUniform("u_angle", 50.0f);
    mainBlackHoleFragmentShader.setUniform("u_maxDfi", 0.001f);
    rescale();
}

void GameWindow::events()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            window.close();

        if(event.type == sf::Event::Resized)
            rescale();
    }
}

void GameWindow::loop()
{
    while (window.isOpen())
    {
        events();

        mainBlackHoleFragmentShader.setUniform("u_time", static_cast <float> (timeSinceOpen.getElapsedTime().asMilliseconds()) * 0.001f);
        mainBlackHoleFragmentShader.setUniform("u_polozeniePocz", sf::Vector3f(4.0, 0.0, 0.0));
        mainBlackHoleFragmentShader.setUniform("u_alfaParam", 1.0f);

        window.clear(sf::Color(255, 255, 255, 255));
        window.draw(displayShaderRectangle, &mainBlackHoleFragmentShader);
        window.display();
    }
}