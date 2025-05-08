#include "FluidSim.h"

#include <iostream>
#include <valarray>

FluidSim::FluidSim() {}
FluidSim::~FluidSim() {}

void FluidSim::initialize(sf::RenderWindow* game_window) {
    window = game_window;
    if (window == nullptr) {
        return;
    }

    window_size = static_cast<sf::Vector2f>(window->getSize());
    window_size.y = window_size.y - PARTICLE_RADIUS;


    particles.reserve(PARTICLE_AMOUNT_X * PARTICLE_AMOUNT_X);

    for (int y = 0; y < PARTICLE_AMOUNT_X; y++) {
        for (int x = 0; x < PARTICLE_AMOUNT_X; x++) {
            float px = START_POS.x + x * SPACING;
            float py = START_POS.y + y * SPACING;
            particles.push_back({sf::Vector2f(px, py)});
        }
    }



}

float FluidSim::smoothingKernel(float radius, float dst) {
    float value = std::max(0.0f, ((radius * radius) - (dst * dst)));
    return std::pow(value, 3);
}

float FluidSim::calculateDensity(Particle sample_point) {
    float density = 0.f;
    const float MASS = 1.f;

    //TODO: Look only at particles inside smoothing radius
    for (auto& p : particles) {
        float dst = (getMagnitude((p.position - sample_point.position)));
        float influence = smoothingKernel(SMOOTHING_RADIUS, dst);
        density += MASS + influence;
    }

    return density;
}

float FluidSim::getMagnitude(sf::Vector2f vector) {
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}



void FluidSim::update(float dt) {

    for (auto& p : particles) {
        p.velocity.y += GRAVITY * dt;
        p.position += p.velocity * dt;

        if (p.position.y > window_size.y) {
            p.position.y = window_size.y;
            p.velocity.y *= -COLLISION_DAMPING;
        }

        float d = calculateDensity(p);
        std::cout << "Density: " << d << std::endl;
    }

}


void FluidSim::draw(sf::RenderWindow& window) {

    for (const auto& p : particles) {
        sf::CircleShape circle(PARTICLE_RADIUS);
        circle.setFillColor(sf::Color::Cyan);
        circle.setOrigin(PARTICLE_RADIUS, PARTICLE_RADIUS);
        circle.setPosition(p.position);
        window.draw(circle);
    }

}




