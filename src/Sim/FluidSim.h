#ifndef FLUIDSIM_H
#define FLUIDSIM_H

#include "Particle.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

class FluidSim {
  public:
    FluidSim();
    ~FluidSim();

    void initialize(sf::RenderWindow* game_window);

    void update(float dt);

    void draw(sf::RenderWindow& window);

    static float smoothingKernel(float radius, float dst);
    float calculateDensity(Particle sample_point);

    float getMagnitude(sf::Vector2f vector);



private:
    sf::RenderWindow* window = nullptr;
    sf::Vector2f window_size;

    const float GRAVITY = 0.f; //500.f;
    const float COLLISION_DAMPING = 0.7f;

    const float SMOOTHING_RADIUS = .5f;



    const sf::Vector2f START_POS = {100, 50};
    static constexpr int PARTICLE_AMOUNT_X = 20;
    static constexpr int PARTICLE_AMOUNT_Y = 10;
    static constexpr int PARTICLE_RADIUS = 10;
    static constexpr int SPACING = PARTICLE_RADIUS * 3.f;
    std::vector<Particle> particles;


};



#endif //FLUIDSIM_H
