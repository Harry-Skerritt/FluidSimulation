//
// Created by Harry on 08/05/2025.
//

#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML\Graphics.hpp>


struct Particle {
  sf::Vector2f position;
  sf::Vector2f velocity;
  sf::Vector2f force;
  float density = 0.f;
  float pressure = 0.f;

  Particle(sf::Vector2f pos) : position(pos), velocity(0, 0), force(0, 0) {}
};


#endif //PARTICLE_HPP
