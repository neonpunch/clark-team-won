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

void BitBomb(System& system) {
    atexit(bailout);
    show_cursor(false);
    set_raw_mode(true);
    set_mouse_mode(true);
    setbgcolor(0, 0, 0);
    clearscreen();

    const auto [ROWS, COLS] = get_terminal_size();
    
    auto last_time = high_resolution_clock::now();

    while (true) {
        auto cur_time = high_resolution_clock::now();
        duration<double> diff = cur_time - last_time;
        delta_t = diff.count();
        movecursor(ROWS, 0);
        setbgcolor(0, 0, 0);
        cout << "FPS: " << 1/delta_t << "                  " << endl;
        cout << "Q to quit" << endl;
        last_time = cur_time;

        int ch = quick_read();
        if (ch == ERR) {
            // Do nothing
        } else if (ch == 'q') {
            break;
        }

        // Fireworks at a consistent rate
        if (rand() % 10 == 0) { // Consistent rate
            int firework_x = rand() % COLS;
            int firework_y = ROWS - 1; // Start from the bottom of the screen
            int explosion_y = rand() % (ROWS / 2); // Random explosion point within the screen
            Particle explosiveParticle(firework_x, firework_y, 0, -1, 100, 255, 0, 0, Particle::FIREWORK); // Move upwards
            system.addParticle(explosiveParticle);

            // Move the firework up and then explode at the random explosion point
            while (explosiveParticle.get_y() > explosion_y) {
                explosiveParticle.set_y(explosiveParticle.get_y() - 1);
                system.drawParticle(explosiveParticle);
                usleep(50000); // Sleep for 50 milliseconds
            }

            // Explosion in rainbow colors
            for (int i = 0; i < 360; i += 30) {
                double angle = i * (numbers::pi / 180.0);
                double speed = 2.0;
                double new_dx = speed * cos(angle);
                double new_dy = speed * sin(angle);
                Particle explosionParticle(explosiveParticle.get_x(), explosion_y, new_dx, new_dy, INT_MAX, rand() % 256, rand() % 256, rand() % 256, Particle::FIREWORK);
                system.addParticle(explosionParticle);
                system.drawParticle(explosionParticle);
            }
        }

        system.sysUpdate();
        usleep(100000); // Sleep for 100 milliseconds
    }
}
