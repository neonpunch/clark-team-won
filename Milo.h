#pragma once
#include "System.h"
#include "/public/read.h"
#include "/public/colors.h"
#include <csignal>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>

using namespace std;
using namespace chrono;

double delta_t = 0.01;
bool half_destroyed = false;

// Cleanup function
void bailout() {
    set_mouse_mode(false);
    set_raw_mode(false);
    show_cursor(true);
    clearscreen();
    setbgcolor(0, 0, 0);
    setcolor(255, 255, 255);
    int booya = system("clear");
}

// Create the artwork of the cat's head
vector<Particle> create_cat_art(int rows, int cols) {
    vector<Particle> catArtParticles;
    for (int y = rows / 2 - 5; y < rows / 2 + 5; y++) {
        for (int x = cols / 2 - 5; x < cols / 2 + 5; x++) {
            Particle artParticle(x, y, 0, 0, INT_MAX, 255, 165, 0, Particle::BALLISTIC);
            catArtParticles.push_back(artParticle);
        }
    }
    return catArtParticles;
}

void BitBomb(System& system) {
    atexit(bailout);
    show_cursor(false);
    set_raw_mode(true);
    set_mouse_mode(true);
    setbgcolor(100, 100, 100);
    clearscreen();

    const auto [ROWS, COLS] = get_terminal_size();
<<<<<<< HEAD
    
	auto last_time = high_resolution_clock::now();
=======
    cout << "Terminal size: " << ROWS << " rows, " << COLS << " columns" << endl;

    // Create wall of particles
    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            Particle wallParticle(x, y, 0, 0, INT_MAX, 100, 100, 100, Particle::STREAMER);
            system.addParticle(wallParticle);
            system.draw_particle(wallParticle);
        }
    }

    // Create cat artwork behind the wall
    vector<Particle> catArtParticles = create_cat_art(ROWS, COLS);

    auto last_time = high_resolution_clock::now();
    int destroyedCount = 0;
    int totalParticles = ROWS * COLS;
    int halfParticles = totalParticles / 2;
>>>>>>> refs/remotes/origin/main

    while (true) {
        auto cur_time = high_resolution_clock::now();
        duration<double> diff = cur_time - last_time;
        delta_t = diff.count();
        movecursor(ROWS, 0);
     //   setbgcolor(0, 0, 0);
//        cout << "FPS: " << 1/delta_t << "                  " << endl;
        cout << "Q to quit" << endl;
        last_time = cur_time;

        int ch = quick_read();
        if (ch == ERR) {
            // Do nothing
        } else if (ch == 'q') {
            break;
        }

        if (half_destroyed && destroyedCount > halfParticles) {
            // Final big explosion
            for (int i = 0; i < 50; i++) {
                double angle = (rand() % 360) * (numbers::pi / 180.0);
                double speed = 2.0;
                double new_dx = speed * cos(angle);
                double new_dy = speed * sin(angle);
                Particle finalExplosionParticle(COLS / 2, ROWS / 2, new_dx, new_dy, INT_MAX, rand() % 256, rand() % 256, rand() % 256, Particle::FIREWORK);
                system.addParticle(finalExplosionParticle);
                system.draw_particle(finalExplosionParticle);
            }
            for (Particle& artParticle : catArtParticles) {
                system.draw_particle(artParticle);
            }
            break;
        }

        // Random fireworks
        if (rand() % 100 < 5) { // 5% chance every frame
            int firework_x = rand() % COLS;
            int firework_y = ROWS - 1; // Start from the bottom of the screen
            Particle explosiveParticle(firework_x, firework_y, 0, -1, 100, 255, 0, 0, Particle::FIREWORK); // Move upwards
            system.addParticle(explosiveParticle);
            system.draw_particle(explosiveParticle);

            // Move the firework up and then explode
            while (explosiveParticle.get_y() > 0) {
                explosiveParticle.set_y(explosiveParticle.get_y() - 1);
                system.draw_particle(explosiveParticle);
                usleep(50000); // Sleep for 50 milliseconds
            }

            // Destroy part of the wall
            for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->getNext()) {
                Particle tempParticle = curr->getParticle();
                if (tempParticle.get_type() == Particle::STREAMER && sqrt(pow(tempParticle.get_x() - firework_x, 2) + pow(tempParticle.get_y() - explosiveParticle.get_y(), 2)) < 10.0) {
                    tempParticle.set_lifetime(0);
                    system.draw_particle(tempParticle);
                    destroyedCount++;
                }
            }
        }

        if (destroyedCount > halfParticles) {
            half_destroyed = true;
        }

        system.sysUpdate();
        usleep(100000); // Sleep for 100 milliseconds
    }
}
