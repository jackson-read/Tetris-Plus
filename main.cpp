#include <iostream>
#include <vector>


class GameEngine {
private:
    
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
};

int main() {
    GameEngine engine;

   
    std::cout << "Engine initialized. Current Score: " << engine.getScore() << std::endl;

    return 0;
}