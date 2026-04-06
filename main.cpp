#include <iostream>
#include <vector>
#include "blocks.h"
#include <cstdlib>
#include <ctime>

class GameEngine {
private:
    Block* activeBlock;
    int score;
    const int rows = 20;
    const int columns = 10;

    std::vector<std::vector<int>> grid;

    int dropIntervalMs = 1000;
    int dropAccumulatorMs = 0;
    bool gameOver = false;

public:
    GameEngine() {
        score = 0;
        activeBlock = nullptr;
        grid = std::vector<std::vector<int>>(rows, std::vector<int>(columns, 0));
    }

    ~GameEngine() {
        if (activeBlock) {
            delete activeBlock;
            activeBlock = nullptr;
        }
    }

    bool canPlace(Block* b, int x, int y, bool rotated = false) {
        if (!b) return false;

        std::vector<std::pair<int, int>> cells;
        if (rotated) {
            cells = b->getRotatedCells();
        }
        else {
            cells = b->getCells();
        }

        for (auto& c : cells) {
            int worldX = x + c.first;
            int worldY = y + c.second;

            if (worldX < 0 || worldX >= columns || worldY < 0 || worldY >= rows) {
                return false;
            }

            if (grid[worldY][worldX] != 0) {
                return false;
            }
        }

        return true;
    }

    void checkLines() {
        for (int i = rows - 1; i >= 0; i--) {
            bool fullRow = true;

            for (int j = 0; j < columns; j++) {
                if (grid[i][j] == 0) {
                    fullRow = false;
                    break;
                }
            }

            if (fullRow) {
                score += 100;
                grid.erase(grid.begin() + i);
                grid.insert(grid.begin(), std::vector<int>(columns, 0));
                i++;
            }
        }
    }

    int getScore() const {
        return score;
    }

    std::vector<std::vector<int>> getGrid() const {
        return grid;
    }

    bool isGameOver() const {
        return gameOver;
    }

    void SpawnNextBlock() {
        if (activeBlock) {
            delete activeBlock;
            activeBlock = nullptr;
        }

        int randomBlock = rand() % 7;
        int startX = 3;
        int startY = 0;

        switch (randomBlock) {
        case 0: activeBlock = new TBlock(startX, startY); break;
        case 1: activeBlock = new OBlock(startX, startY); break;
        case 2: activeBlock = new IBlock(startX, startY); break;
        case 3: activeBlock = new LBlock(startX, startY); break;
        case 4: activeBlock = new JBlock(startX, startY); break;
        case 5: activeBlock = new ZBlock(startX, startY); break;
        case 6: activeBlock = new SBlock(startX, startY); break;
        }

        if (!canPlace(activeBlock, activeBlock->getX(), activeBlock->getY())) {
            gameOver = true;
        }
    }

    void lockActiveBlock() {
        if (!activeBlock) return;

        for (auto& c : activeBlock->getCells()) {
            int worldX = activeBlock->getX() + c.first;
            int worldY = activeBlock->getY() + c.second;

            if (worldY >= 0 && worldY < rows && worldX >= 0 && worldX < columns) {
                grid[worldY][worldX] = 1;
            }
        }

        delete activeBlock;
        activeBlock = nullptr;

        checkLines();
    }

    void update(int deltaMs) {
        if (gameOver) return;

        dropAccumulatorMs += deltaMs;

        if (!activeBlock) {
            SpawnNextBlock();
        }

        while (dropAccumulatorMs >= dropIntervalMs && !gameOver) {
            dropAccumulatorMs -= dropIntervalMs;

            int nx = activeBlock->getX();
            int ny = activeBlock->getY() + 1;

            if (canPlace(activeBlock, nx, ny)) {
                activeBlock->move(0, 1);
            }
            else {
                lockActiveBlock();
                SpawnNextBlock();
            }
        }
    }

    void moveLeft() {
        if (activeBlock && canPlace(activeBlock, activeBlock->getX() - 1, activeBlock->getY())) {
            activeBlock->move(-1, 0);
        }
    }

    void moveRight() {
        if (activeBlock && canPlace(activeBlock, activeBlock->getX() + 1, activeBlock->getY())) {
            activeBlock->move(1, 0);
        }
    }

    void moveDown() {
        if (!activeBlock) return;

        if (canPlace(activeBlock, activeBlock->getX(), activeBlock->getY() + 1)) {
            activeBlock->move(0, 1);
        }
        else {
            lockActiveBlock();
            SpawnNextBlock();
        }
    }

    void rotateActiveBlock() {
        if (activeBlock && canPlace(activeBlock, activeBlock->getX(), activeBlock->getY(), true)) {
            activeBlock->rotate();
        }
    }

    void PrintGrid() {
        std::vector<std::vector<int>> display = grid;

        if (activeBlock) {
            for (auto& c : activeBlock->getCells()) {
                int worldX = activeBlock->getX() + c.first;
                int worldY = activeBlock->getY() + c.second;

                if (worldY >= 0 && worldY < rows && worldX >= 0 && worldX < columns) {
                    display[worldY][worldX] = 2;
                }
            }
        }

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (display[i][j] == 0) {
                    std::cout << "0";
                }
                else if (display[i][j] == 1) {
                    std::cout << "1";
                }
                else {
                    std::cout << "2";
                }
            }
            std::cout << "\n";
        }

        std::cout << "Score: " << score << "\n";
        if (gameOver) {
            std::cout << "GAME OVER\n";
        }
        std::cout << std::endl;
    }

};

int main() {
    srand(static_cast<unsigned>(time(0)));

    GameEngine engine;

    std::cout << "Engine initialized. Current Score: " << engine.getScore() << std::endl;

    engine.SpawnNextBlock();
    engine.PrintGrid();

    for (int i = 0; i < 10 && !engine.isGameOver(); i++) {
        engine.update(1000);
        engine.PrintGrid();
    }

    return 0;
}