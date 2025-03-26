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

void interrupt_handler(int x) {
    exit(0);
}

// Mouse down handler
void mouse_handler(int row, int col) {
    click_row = row;
    click_col = col;
    mouse_down = true;
}

// Mouse up handler
void mouse_handler2(int row, int col) {
    click_row = row;
    click_col = col;
    mouse_down = false;
}

// Function to draw particles
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
    
	auto last_time = high_resolution_clock::now();

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

        if (mouse_down) {
            mouse_down = false;
            if (click_row >= ROWS or click_col >= COLS or click_row < 0 or click_col < 0) continue;
            cout << "Mouse click at (" << click_col << ", " << click_row << ")" << endl;
            Particle drawParticle(click_col, click_row, 0, 0, INT_MAX, rand() % 256, rand() % 256, rand() % 256, Particle::BALLISTIC);
            system.addParticle(drawParticle);
            draw_particle(drawParticle);
        }

        system.sysUpdate();

        usleep(100000); // Sleep for 100 milliseconds
    }
}
