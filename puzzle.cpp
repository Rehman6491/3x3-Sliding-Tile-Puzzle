//Matthew Joyce

#include<iostream>
#include<cassert>


using namespace std;

enum game_status { uncompleted, completed };

struct spacePosition
{
	int row, col;
};

struct puzzle
{
	game_status status;
	int board[3][3];
	spacePosition position;
	int numberOfMoves;

};

void initializeGoal(puzzle &gam)
{
	gam.position.row = 2;
	gam.position.col = 2;
	int count = 1;
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			gam.board[r][c] = count;
			count++;
		}
	}
	gam.status = completed;
}

void up(puzzle &gam)
{
	int temp[1][1];
	temp[0][0] = gam.board[gam.position.row - 1][gam.position.col];
	gam.board[gam.position.row - 1][gam.position.col] = gam.board[gam.position.row][gam.position.col];
	gam.board[gam.position.row][gam.position.col] = temp[0][0];
	gam.position.row = gam.position.row - 1;
}

void right(puzzle &gam)
{
	int temp[1][1];
	temp[0][0] = gam.board[gam.position.row][gam.position.col + 1];
	gam.board[gam.position.row][gam.position.col + 1] = gam.board[gam.position.row][gam.position.col];
	gam.board[gam.position.row][gam.position.col] = temp[0][0];
	gam.position.col = gam.position.col + 1;
}

void down(puzzle &gam)
{
	int temp[1][1];
	temp[0][0] = gam.board[gam.position.row + 1][gam.position.col];
	gam.board[gam.position.row + 1][gam.position.col] = gam.board[gam.position.row][gam.position.col];
	gam.board[gam.position.row][gam.position.col] = temp[0][0];
	gam.position.row = gam.position.row + 1;
}

void left(puzzle &gam)
{
	int temp[1][1];
	temp[0][0] = gam.board[gam.position.row][gam.position.col - 1];
	gam.board[gam.position.row][gam.position.col - 1] = gam.board[gam.position.row][gam.position.col];
	gam.board[gam.position.row][gam.position.col] = temp[0][0];
	gam.position.col = gam.position.col - 1;
}

puzzle scramblePuzzle(puzzle gam, int shuffle)
{

	gam.status = uncompleted;
	while (shuffle > 0)
	{
		int direction = rand() % 4;

		switch (direction)
		{
			//up
			case 0:
				if (gam.position.row > 0)
				{
					up(gam);
					shuffle = shuffle - 1;
				}
				else
					scramblePuzzle(gam, shuffle);
				break;
				//Right
			case 1:
				if (gam.position.col < 2)
				{
					right(gam);
					shuffle = shuffle - 1;
				}
				else
					scramblePuzzle(gam, shuffle);
				break;
				//Down
			case 2:
				if (gam.position.row < 2)
				{
					down(gam);
					shuffle = shuffle - 1;
				}
				else
					scramblePuzzle(gam, shuffle);
				break;
				//Left
			case 3:
				if (gam.position.col > 0)
				{
					left(gam);
					shuffle = shuffle - 1;
				}
				else
					scramblePuzzle(gam, shuffle);
				break;
		}		
	}

	return gam;
}

void printPuzzle(puzzle gam)
{
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			if (gam.board[r][c] == 9)
				cout << " " << " " << " ";
			else
				cout << " " << gam.board[r][c] << " ";
		}
		cout << endl;
	}
}

int main()
{
	puzzle goalPuzzle;
	puzzle game;
	initializeGoal(goalPuzzle);
	int num = 0;
	cout << "Enter max number of moves needed to solve puzzle optimally: ";
	cin >> num;
	cout << endl;
	game = scramblePuzzle(goalPuzzle, num);
	printPuzzle(game);
	char c;
	while (game.status != completed)
	{
		cout << endl << "Enter:" << endl << "U for Up" << endl << "R for Right"
			<< endl << "D for Down " << endl << "L for Left" << endl << endl;
		cin >> c;



	}

	return 0;
}