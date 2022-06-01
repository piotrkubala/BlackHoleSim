#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <SFML/Graphics.hpp>

class Observer
{
    sf::Vector3f position;
    sf::Vector3f rotationX, rotationY, rotationZ;
    float speed;

    float length(const sf::Vector3f &v);
    float dot(const sf::Vector3f &v, const sf::Vector3f &u);
    sf::Vector3f cross(const sf::Vector3f &v, const sf::Vector3f &u);
    sf::Vector3f rotateAroundVector(float angle, sf::Vector3f axis, sf::Vector3f v);

public:
    Observer(const sf::Vector3f &pos_ = sf::Vector3f(0.0, 0.0, 0.0), float speed_ = 1.0);
    virtual ~Observer();

    void rotateAround(const float &angle, const sf::Vector3f &axis);
    void translate(const sf::Vector3f &v);

    void move(const sf::Vector3f &dirs);

    sf::Vector3f getRotationX()const;
    sf::Vector3f getRotationY()const;
    sf::Vector3f getRotationZ()const;

    sf::Vector3f getPosition()const;

    float getSpeed()const;

    void setPosition(const sf::Vector3f &pos_);
    void setSpeed(const float &speed_);
};

#endif