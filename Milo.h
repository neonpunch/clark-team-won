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
int click_row = -1, click_col = -1;
bool mouse_down = false;

void bailout() {
    set_mouse_mode(false);
    set_raw_mode(false);
    show_cursor(true);
    clearscreen();
    setbgcolor(0, 0, 0);
    setcolor(255, 255, 255);
    int booya = system("clear");
}

void interrupt_handler(int x) {
    exit(0);
}

void mouse_handler(int row, int col) {
    click_row = row;
    click_col = col;
    mouse_down = true;
    cout << "Mouse down at (" << click_col << ", " << click_row << ")" << endl;
}

void mouse_handler2(int row, int col) {
    click_row = row;
    click_col = col;
    mouse_down = false;
    cout << "Mouse up at (" << click_col << ", " << click_row << ")" << endl;
}

void draw_particle(const Particle& p) {
    movecursor(p.get_y(), p.get_x());
    setbgcolor(p.get_r(), p.get_g(), p.get_b());
    cout << " ";
}

void BitBomb(System& system) {
    atexit(bailout);
    signal(SIGINT, interrupt_handler);
    show_cursor(false);
    set_raw_mode(true);
    set_mouse_mode(true);
    on_mousedown(mouse_handler);
    on_mouseup(mouse_handler2);
    setbgcolor(100, 100, 100);
    clearscreen();

    const auto [ROWS, COLS] = get_terminal_size();
    cout << "Terminal size: " << ROWS << " rows, " << COLS << " columns" << endl;

    for (int y = 0; y < ROWS; y++) {
        for (int x = 0; x < COLS; x++) {
            Particle wallParticle(x, y, 0, 0, INT_MAX, 0, 0, 255, Particle::STREAMER);
            system.addParticle(wallParticle);
            draw_particle(wallParticle);
        }
    }

    vector<Particle> catArtParticles;
    for (int y = ROWS / 2 - 5; y < ROWS / 2 + 5; y++) {
        for (int x = COLS / 2 - 5; x < COLS / 2 + 5; x++) {
            Particle artParticle(x, y, 0, 0, INT_MAX, 255, 165, 0, Particle::BALLISTIC);
            catArtParticles.push_back(artParticle);
        }
    }

    while (true) {
        if (mouse_down) {
            mouse_down = false;
            if (click_row >= ROWS or click_col >= COLS or click_row < 0 or click_col < 0) continue;
            cout << "Mouse click at (" << click_col << ", " << click_row << ")" << endl;
            Particle explosiveParticle(click_col, click_row, 0, 0, 100, 255, 0, 0, Particle::FIREWORK);
            system.addParticle(explosiveParticle);
            draw_particle(explosiveParticle);
        }

        system.sysUpdate();

        for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->getNext()) {
            Particle tempParticle = curr->getParticle();
            if (tempParticle.get_type() == Particle::FIREWORK && tempParticle.get_lifetime() == 0) {
                double exX = tempParticle.get_x();
                double exY = tempParticle.get_y();
                for (Cell* wallCurr = system.get_head(); wallCurr != nullptr; wallCurr = wallCurr->getNext()) {
                    Particle tempWallParticle = wallCurr->getParticle();
                    double wx = tempWallParticle.get_x();
                    double wy = tempWallParticle.get_y();
                    if (sqrt(pow(wx - exX, 2) + pow(wy - exY, 2)) < 10.0) {
                        wallCurr->getParticle().set_lifetime(0);
                        draw_particle(wallCurr->getParticle());
                    }
                }
            }
        }

        int destroyedCount = 0;
        for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->getNext()) {
            Particle tempParticle = curr->getParticle();
            if (tempParticle.get_lifetime() == 0 && tempParticle.get_type() == Particle::STREAMER) {
                destroyedCount++;
            }
        }

        if (destroyedCount > (ROWS * COLS / 2)) {
            for (Particle& artParticle : catArtParticles) {
                system.addParticle(artParticle);
                draw_particle(artParticle);
            }
            for (Cell* curr = system.get_head(); curr != nullptr; curr = curr->getNext()) {
                Particle tempParticle = curr->getParticle();
                if (tempParticle.get_type() == Particle::STREAMER) {
                    curr->getParticle().set_lifetime(0);
                    draw_particle(curr->getParticle());
                }
            }
            for (int i = 0; i < 50; i++) {
                double angle = (rand() % 360) * (numbers::pi / 180.0);
                double speed = 2.0;
                double new_dx = speed * cos(angle);
                double new_dy = speed * sin(angle);
                Particle finalExplosionParticle(COLS / 2, ROWS / 2, new_dx, new_dy, INT_MAX, rand() % 256, rand() % 256, rand() % 256, Particle::FIREWORK);
                system.addParticle(finalExplosionParticle);
                draw_particle(finalExplosionParticle);
            }
            break;
        }
        usleep(100000); // Sleep for 100 milliseconds
    }
}
