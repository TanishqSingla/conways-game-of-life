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

public:
	Universe() {
		row = 32;
		col = 32;

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
				int count = 0;
				count += cells[i-1][j-1];
				count += cells[i][j-1];
				count += cells[i+1][j-1];
				count += cells[i-1][j];
				count += cells[i+1][j];
				count += cells[i-1][j+1];
				count += cells[i][j+1];
				count += cells[i+1][j+1];

				if( (count < 0 || count > 8))
					count = 0;
				
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
