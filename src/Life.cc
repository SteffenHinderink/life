#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

const int TIME = 100;
const int HEIGHT = 45;
const int WIDTH = 203;
const char ALIVE = '#';
const char DEAD = ' ';

std::vector<std::vector<bool>> cells;

void draw() {
    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << (cells[i][j] ? ALIVE : DEAD);
        }
        std::cout << std::endl;
    }
}

void loop() {
    std::vector<std::vector<bool>> next(HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        next[i] = std::vector<bool>(WIDTH);
        for (int j = 0; j < WIDTH; j++) {
            int cnt = 0;
            for (int id = -1; id <= 1; id++) {
                for (int jd = -1; jd <= 1; jd++) {
                    if (!(id == 0 && jd == 0)) {
                        if (cells[(i + id + HEIGHT) % HEIGHT][(j + jd + WIDTH) % WIDTH]) {
                            cnt++;
                        }
                    }
                }
            }
            if (cells[i][j] && (cnt == 2 || cnt == 3)) {
                next[i][j] = true;
            } else if (!cells[i][j] && cnt == 3) {
                next[i][j] = true;
            } else {
                next[i][j] = false;
            }
        }
    }
    cells = next;
    draw();
}

void init() {
    cells = std::vector<std::vector<bool>>(HEIGHT);
    for (int i = 0; i < HEIGHT; i++) {
        cells[i] = std::vector<bool>(WIDTH);
        for (int j = 0; j < WIDTH; j++) {
            cells[i][j] = false;
        }
    }
    // Glider
    cells[0][0] = true;
    cells[1][1] = true;
    cells[1][2] = true;
    cells[2][0] = true;
    cells[2][1] = true;
}

int main() {
    init();
    draw();
    std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
    while (true) {
        loop();
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME));
    }
}
