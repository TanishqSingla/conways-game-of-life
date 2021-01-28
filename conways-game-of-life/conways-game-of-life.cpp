#include <cstdio>

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

public:
	Universe() {
		row = 32;
		col = 32;

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cells[i][j] = ALIVE;
			}
		}
	}

	void render() {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++)
				printf("%d", cells[i][j]);
			printf("\n");
		}
	}
};

int main()
{
	Universe universe = Universe();

	universe.render();
}
