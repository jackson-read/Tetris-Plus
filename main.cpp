#include <iostream>
#include <vector>


void Grid() {
	int score = 0;
	bool fullRow = true;
	int rows = 20;
	int columns = 10;
	std::vector<std::vector<bool>> grid(rows, std::vector<bool>(columns, 0)); // Array grid 

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (grid[i][j] != 0) {
				// add code with Blocks class to not move them after check
			}
		}
	}

	for (auto& row : grid) {
		for (bool cell : row) {
			if (cell == 0) {
				fullRow = false;
				break;
			}
		}
		if (fullRow) {
			score++;
		}
	}
}

int main() {

}