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

struct Firework {
    Particle particle;
    int explosion_y; // Explosion point

    Firework(Particle p, int ey) : particle(p), explosion_y(ey) {}
};

void BigBayBoom(System& system) {
    atexit(bailout);
    show_cursor(false);
    set_raw_mode(true);
    set_mouse_mode(true);
    setbgcolor(0, 0, 0);
    clearscreen();

    const auto [ROWS, COLS] = get_terminal_size();
    
    auto last_time = high_resolution_clock::now();

    cout << "'q' to quit" << endl;
    
    vector<Firework> fireworks;
    
    while (true) {
        auto cur_time = high_resolution_clock::now();
        duration<double> diff = cur_time - last_time;
        delta_t = diff.count();
        movecursor(ROWS, 0);
        setbgcolor(0, 0, 0);
        last_time = cur_time;

        int ch = quick_read();
        if (ch == 'q') {
            break;
        }

        // Fireworks at a consistent rate
        if (rand() % 10 == 0) { // Consistent rate
            int firework_x = rand() % COLS;
            int firework_y = ROWS - 1; // Start from the bottom of the screen
            int explosion_y = rand() % (ROWS - 5); // Random explosion point within the screen (ensuring it doesn't hit the top)
            Particle explosiveParticle(firework_x, firework_y, 0, -1, 100, 0, 0, 0, Particle::FIREWORK); // Move upwards
            fireworks.emplace_back(explosiveParticle, explosion_y);
            system.addParticle(explosiveParticle);
        }

        // Update all particles
        vector<Firework> new_fireworks;
        for (auto& firework : fireworks) {
            if (firework.particle.get_y() > firework.explosion_y) {
                firework.particle.set_y(firework.particle.get_y() - 1);
                system.drawParticle(firework.particle);
                new_fireworks.push_back(firework);
            } else {
                // Explosion in rainbow colors
                for (int i = 0; i < 360; i += 30) {
                    double angle = i * (numbers::pi / 180.0);
                    double speed = 2.0;
                    double new_dx = speed * cos(angle);
                    double new_dy = speed * sin(angle);
                    Particle explosionParticle(firework.particle.get_x(), firework.explosion_y, new_dx, new_dy, INT_MAX, rand() % 256, rand() % 256, rand() % 256, Particle::FIREWORK);
                    system.addParticle(explosionParticle);
                    system.drawParticle(explosionParticle);
                }
            }
        }
        fireworks = new_fireworks;

        system.sysUpdate();
        usleep(100000); // Sleep for 100 milliseconds
    }
}
