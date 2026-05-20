#include <stdio.h>
#include "sandpiles.h"

/**
 * print_grid - Print a 3x3 grid
 * @grid: 3x3 grid to print
 */
static void print_grid(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (j)
				printf(" ");
			printf("%d", grid[i][j]);
		}
		printf("\n");
	}
}

/**
 * is_stable - Check if a grid is stable (no cell >= 4)
 * @grid: 3x3 grid to check
 *
 * Return: 1 if stable, 0 otherwise
 */
static int is_stable(int grid[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			if (grid[i][j] >= 4)
				return (0);
	return (1);
}

/**
 * topple - Perform one simultaneous toppling step
 * @grid: 3x3 grid to topple in place
 *
 * Each cell >= 4 loses 4 grains and distributes 1 to each
 * of its (up to 4) direct neighbours. All topplings happen
 * simultaneously via a delta accumulator.
 */
static void topple(int grid[3][3])
{
	int i, j;
	int delta[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] >= 4)
			{
				delta[i][j] -= 4;
				if (i > 0)
					delta[i - 1][j] += 1;
				if (i < 2)
					delta[i + 1][j] += 1;
				if (j > 0)
					delta[i][j - 1] += 1;
				if (j < 2)
					delta[i][j + 1] += 1;
			}
		}
	}

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			grid[i][j] += delta[i][j];
}

/**
 * sandpiles_sum - Compute the sum of two sandpile grids
 * @grid1: First 3x3 grid (modified in place, receives the result)
 * @grid2: Second 3x3 grid (read only)
 *
 * Adds grid2 into grid1, then repeatedly topples until stable.
 * Prints each intermediate unstable state before toppling it.
 */
void sandpiles_sum(int grid1[3][3], int grid2[3][3])
{
	int i, j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			grid1[i][j] += grid2[i][j];

	while (!is_stable(grid1))
	{
		printf("=\n");
		print_grid(grid1);
		topple(grid1);
	}
}
