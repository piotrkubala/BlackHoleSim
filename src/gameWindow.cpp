#include "gameWindow.hpp"

#include <iostream>
#include <cmath>

GameWindow::GameWindow(int x, int y, bool fullScreen): window(sf::VideoMode(x, y), "Black Hole Simulation", fullScreen ? sf::Style::Fullscreen : sf::Style::Resize | sf::Style::Close), mainObserver(sf::Vector3f(10, 0.0, 0.0), 5.0)
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
    mainObserver.rotateAround(-M_PI * 0.5, mainObserver.getRotationY());
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

void GameWindow::observerMovement()
{
    float dt = timeSinceLastFrame.getElapsedTime().asMicroseconds() * 1.0e-6;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        mainObserver.move(sf::Vector3f(1.0f, 0.0f, 0.0f) * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        mainObserver.move(sf::Vector3f(-1.0f, 0.0f, 0.0f) * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        mainObserver.move(sf::Vector3f(0.0f, 0.0f, 1.0f) * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        mainObserver.move(sf::Vector3f(0.0f, 0.0f, -1.0f) * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        mainObserver.move(sf::Vector3f(0.0f, 1.0f, 0.0f) * dt);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    {
        mainObserver.move(sf::Vector3f(0.0f, -1.0f, 0.0f) * dt);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        mainObserver.rotateAround(0.05, mainObserver.getRotationZ());
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        mainObserver.rotateAround(-0.05, mainObserver.getRotationZ());
    }

    mainObserver.rotateAround(-(static_cast <float> (sf::Mouse::getPosition(window).x) / window.getSize().x - 0.5) * 0.5 * dt, mainObserver.getRotationY());
    mainObserver.rotateAround(-(static_cast <float> (sf::Mouse::getPosition(window).y) / window.getSize().y - 0.5) * 0.5 * dt, mainObserver.getRotationX());
}

void GameWindow::loop()
{
    timeSinceLastFrame.restart();
    while (window.isOpen())
    {
        events();

        observerMovement();

        float timeMiliS = timeSinceOpen.getElapsedTime().asMilliseconds() * 0.001f;

        mainBlackHoleFragmentShader.setUniform("u_time", timeMiliS);
        mainBlackHoleFragmentShader.setUniform("u_polozeniePocz", mainObserver.getPosition());
        mainBlackHoleFragmentShader.setUniform("u_alfaParam", 3.5f);

        mainBlackHoleFragmentShader.setUniform("u_baseX", mainObserver.getRotationX());
        mainBlackHoleFragmentShader.setUniform("u_baseY", mainObserver.getRotationY());
        mainBlackHoleFragmentShader.setUniform("u_baseZ", mainObserver.getRotationZ());

        mainBlackHoleFragmentShader.setUniform("u_maxDfi", 0.01f);

        window.clear();
        window.draw(displayShaderRectangle, &mainBlackHoleFragmentShader);
        timeSinceLastFrame.restart();
        window.display();
    }
}