#include "System.h"
// Milo's destruction bomb project

void BitBomb(System& system) {
    // Clear the screen and set up the initial wall of particles
    const auto [ROWS, COLS] = get_terminal_size();
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            Particle wallParticle(x, y, 0, 0, INT_MAX, 255, 255, 255, Particle::STREAMER);
            system.addParticle(wallParticle);
        }
    }

    // Placeholder for the art made out of particles behind the wall
    vector<Particle> catArtParticles;
    // Generate art particles for cat head
    for (int y = ROWS / 2 - 5; y < ROWS / 2 + 5; y++) {
        for (int x = COLS / 2 - 5; x < COLS / 2 + 5; x++) {
            Particle artParticle(x, y, 0, 0, INT_MAX, 255, 165, 0, Particle::BALLISTIC);
            catArtParticles.push_back(artParticle);
        }
    }

    // Event loop for handling user input
    while (true) {
        // Check for user input (click)
        int clickX, clickY;
        if (get_mouse_click(clickX, clickY)) {
            // Create a distinct particle that will explode after a set time
            Particle explosiveParticle(clickX, clickY, 0, 0, 100, 255, 0, 0, Particle::FIREWORK);
            system.addParticle(explosiveParticle);
        }

        // Update system and check for explosions
        system.sysUpdate();

        // Check for particle explosions and destroy wall particles in vicinity
        for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->get_next()) {
            if (curr->getParticle().get_type() == Particle::FIREWORK && curr->getParticle().get_lifetime() == 0) {
                double exX = curr->getParticle().get_x();
                double exY = curr->getParticle().get_y();
                for (Cell* wallCurr = system.get_head(); wallCurr != nullptr; wallCurr = wallCurr->get_next()) {
                    double wx = wallCurr->getParticle().get_x();
                    double wy = wallCurr->getParticle().get_y();
                    if (sqrt(pow(wx - exX, 2) + pow(wy - exY, 2)) < 10.0) { // Radius of effect
                        wallCurr->getParticle().set_lifetime(0); // Destroy wall particle
                    }
                }
            }
        }

        // Check if a set amount of the wall has been destroyed
        int destroyedCount = 0;
        for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->get_next()) {
            if (curr->getParticle().get_lifetime() == 0 && curr->getParticle().get_type() == Particle::STREAMER) {
                destroyedCount++;
            }
        }

        // If enough wall particles are destroyed, trigger final explosion
        if (destroyedCount > (ROWS * COLS / 2)) {
            for (Particle& artParticle : catArtParticles) {
                system.addParticle(artParticle);
            }
            for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->get_next()) {
                if (curr->getParticle().get_type() == Particle::STREAMER) {
                    curr->getParticle().set_lifetime(0); // Destroy all wall particles
                }
            }
            // Trigger final firework explosion
            for (int i = 0; i < 50; i++) {
                double angle = (rand() % 360) * (numbers::pi / 180.0);
                double speed = 2.0;
                double new_dx = speed * cos(angle);
                double new_dy = speed * sin(angle);
                Particle finalExplosionParticle(COLS / 2, ROWS / 2, new_dx, new_dy, INT_MAX, rand() % 256, rand() % 256, rand() % 256, Particle::FIREWORK);
                system.addParticle(finalExplosionParticle);
            }
            break; // Exit the loop after the final explosion
        }
    }
}
