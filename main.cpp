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

public:
    GameEngine() {
        score = 0;
        
        grid = std::vector<std::vector<int>>(rows, std::vector<int>(columns, 0));
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

    
    int getScore() const { return score; }
    std::vector<std::vector<int>> getGrid() const { return grid; }

    void SpawnNextBlock(){
        
        int randomBlock = rand() % 7;
        int startX = 3;
        int startY = 2;

        switch (randomBlock) {
        case 0: activeBlock = new TBlock(startX, startY); break;
        case 1: activeBlock = new OBlock(startX, startY); break;
        case 2: activeBlock = new IBlock(startX, startY); break;
        case 3: activeBlock = new LBlock(startX, startY); break;
        case 4: activeBlock = new JBlock(startX, startY); break;
        case 5: activeBlock = new ZBlock(startX, startY); break;
        case 6: activeBlock = new SBlock(startX, startY); break;
        }
    }
};

int main() {
    srand(time(0));

    GameEngine engine;

    int e = rand() % 100;
    std::cout << e;

    std::cout << "Engine initialized. Current Score: " << engine.getScore() << std::endl;

    return 0;
}