#include "observer.hpp"

#include <cmath>

Observer::Observer(const sf::Vector3f &pos_, float speed_): position(pos_), rotationX(1.0f, 0.0f, 0.0f), rotationY(0.0f, 1.0f, 0.0f), rotationZ(0.0f, 0.0f, 1.0f), speed(speed_)
{

}

Observer::~Observer()
{

}

float Observer::length(const sf::Vector3f &v)
{
    return sqrt(dot(v, v));
}

float Observer::dot(const sf::Vector3f &v, const sf::Vector3f &u)
{
    return v.x * u.x + v.y * u.y + v.z * u.z;
}

sf::Vector3f Observer::cross(const sf::Vector3f &v, const sf::Vector3f &u)
{
    return sf::Vector3f(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x);
}

sf::Vector3f Observer::rotateAroundVector(float angle, sf::Vector3f axis, sf::Vector3f v)
{
    axis /= length(axis);

    sf::Vector3f rownolegly = dot(axis, v) * axis;
    sf::Vector3f prost1 = v - rownolegly;

    float dlugoscProst = length(prost1);

    if(dlugoscProst == 0.0)
        return v;

    prost1 /= dlugoscProst;
    sf::Vector3f prost2 = cross(axis, prost1);

    return rownolegly + (prost1 * cosf(angle) + prost2 * sinf(angle)) * dlugoscProst;
}

void Observer::rotateAround(const float &angle, const sf::Vector3f &axis)
{
    rotationX = rotateAroundVector(angle, axis, rotationX);
    rotationY = rotateAroundVector(angle, axis, rotationY);
    rotationZ = rotateAroundVector(angle, axis, rotationZ);
}

void Observer::translate(const sf::Vector3f &v)
{
    position += v;
}

sf::Vector3f Observer::getRotationX()const
{
    return rotationX;
}

sf::Vector3f Observer::getRotationY()const
{
    return rotationY;
}

sf::Vector3f Observer::getRotationZ()const
{
    return rotationZ;
}

sf::Vector3f Observer::getPosition()const
{
    return position;
}

void Observer::setPosition(const sf::Vector3f &pos_)
{
    position = pos_;
}