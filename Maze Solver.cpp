#include<stdio.h>
#include<stdlib.h>
typedef struct
{
	unsigned int n : 1;
	unsigned int s : 1;
	unsigned int e : 1;
	unsigned int w : 1;
	unsigned int visit : 1;
} tile;
int movex[4] = { 0, 1, 0, -1};
int movey[4] = { -1, 0, 1, 0};
int row, column;
void printboard(int a, int b, tile* board)
{
	getchar();
	for (int i = 0; i < column; i++)
	{
		printf("+-");
	}
	printf("+\n");
	for (int i = 0; i < row; i++)
	{
		printf("|");
		for (int j = 0; j < column; j++)
		{
			if (i == a && j == b)
			{
				printf("x");
			}
			else if (board[i * column + j].visit == 0)
			{
				printf(".");
			}
			else
			{
				printf(" ");
			}
			if (board[i * column + j].e == 0)
			{
				printf(" ");
			}
			else
			{
				printf("|");
			}
		}
		printf("\n");
		printf("+");
		for (int j = 0; j < column; j++)
		{
			if (board[i * column + j].s == 1)
			{
				printf("-");
			}
			else
			{
				printf(" ");
			}
			printf("+");
		}
		printf("\n");
	}
}
void movetile(int a, int b, tile* board)
{
	printboard(a, b, board);
	for (int i = 0; i < 4; i++)
	{
		if (board[(a + movex[i]) * column + b + movey[i]].visit == 0)
		{
			if (i == 1 && board[a * column + b].s == 0)
			{
				board[(a + movex[i]) * column + b + movey[i]].visit = 1;
				movetile(a + movex[i], b + movey[i], board);
				printboard(a, b, board);
			}
			else if (i == 2 && board[a * column + b].e == 0)
			{
				board[(a + movex[i]) * column + b + movey[i]].visit = 1;
				movetile(a + movex[i], b + movey[i], board);
				printboard(a, b, board);
			}
			else if (i == 3 && board[a * column + b].n == 0)
			{
				board[(a + movex[i]) * column + b + movey[i]].visit = 1;
				movetile(a + movex[i], b + movey[i], board);
				printboard(a, b, board);
			}
			else if (i == 0 && board[a * column + b].w == 0)
			{
				board[(a + movex[i]) * column + b + movey[i]].visit = 1;
				movetile(a + movex[i], b + movey[i], board);
				printboard(a, b, board);
			}
		}
	}
}
int main()
{
	FILE* input = fopen("maze.txt", "r");
	fscanf(input, "%d %d\n", &row, &column);
	char waste[256];
	fgets(waste, 256, input);
	tile* board = (tile*)calloc(row * column, sizeof(tile));
	for (int i = 0; i < row; i++)
	{
		char ch;
		fscanf(input, "|");
		for (int j = 0; j < column; j++)
		{
			if (i == 0)
			{
				board[i * column + j].n = 1;
			}
			if (i == row - 1)
			{
				board[i * column + j].s = 1;
			}
			if (j == 0)
			{
				board[i * column + j].w = 1;
			}
			if (j == column - 1)
			{
				board[i * column + j].e = 1;
			}
			fscanf(input, "%c", &ch);
			if (ch == '_')
			{
				board[i * column + j].s = 1;
				if (i != row - 1)
				{
					board[(i + 1) * column + j].n = 1;
				}
			}
			fscanf(input, "%c", &ch);
			if (ch == '|')
			{
				board[i * column + j].e = 1;
				if (j != column - 1)
				{
					board[i * column + j + 1].w = 1;
				}
			}
		}
		fscanf(input, "\n");
	}
	fclose(input);
	board[0].visit = 1;
	printf("Press enter to move forward in the maze:\n");
	movetile(0, 0, board);
}
