#include <cstdio>
#include <iostream>

#define ALIVE 1
#define DEAD 0

// Rule 1: Any live cell with less than 2 live neighbours dies, as of underpopulation
// Rule 2: Any live cell with 2 or 3 live neighbours lives
// Rule 3: Any live cell with more than 3 neighbours dies, as of overpopulation
// Rule 4: Any dead cell with 3 or more live neighbour becomes alive, as of reproduction

class Universe {
private:
	int row;
	int col;
	int cells[32][32];
	bool is_ok(int n) {
		return n % 2 == 0 || n % 7 == 0;
	}

	int neighbour_count(int y, int x) {
		int count = 0;

		int north = y == 0 ? row - 1 : y - 1;
		int south = y == row - 1 ? 0 : y + 1;
		int west = x == 0 ? col - 1 : x - 1;
		int east = x == col - 1 ? 0 : col + 1;

		count += cells[north][west];
		count += cells[north][x];
		count += cells[north][east];
		count += cells[y][west];
		count += cells[y][east];
		count += cells[south][west];
		count += cells[south][x];
		count += cells[south][east];

		return count;
	}

public:
	Universe() {
		row = 16;
		col = 16;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				is_ok(i + j) ?
					cells[i][j] = ALIVE :
					cells[i][j] = DEAD;
			}
		}
	}

	void tick() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				int count = neighbour_count(i, j);
				
				if (cells[i][j] == ALIVE && count < 2)
					cells[i][j] = DEAD;
				else if (cells[i][j] == ALIVE && (count == 2 || count == 3))
					cells[i][j] = ALIVE;
				else if (cells[i][j] == ALIVE && count > 3)
					cells[i][j] = DEAD;
				else if (cells[i][j] == DEAD && count == 3)
					cells[i][j] = ALIVE;
			}
		}
	}

	void render() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				cells[i][j] ? printf("+") : printf("-");
			printf("\n");
		}
	}
};

int main()
{
	Universe universe = Universe();
	
	universe.render();

	char c;

	while (true) {
		universe.tick();
		universe.render();
		system("cls");
	}

	return 0;
}
