#include <stdio.h>

void moveUp(int* x, int* y, int* health, int* score, char** map, char icon)
{
	if (map[*y - 1][*x] != '\xCD' && map[*y - 1][*x] != '#')
	{
		if (map[*y - 1][*x] == '$')
		{
			*score = *score + 20;
		}
		map[*y][*x] = ' ';
		*y = *y - 1;
		map[*y][*x] = icon;
	}
}

void moveDown(int* x, int* y, int* health, int* score, char** map, char icon)
{
	if (map[*y + 1][*x] != '\xCD' && map[*y + 1][*x] != '#')
	{
		if (map[*y + 1][*x] == '$')
		{
			*score = *score + 20;
		}
		map[*y][*x] = ' ';
		*y += 1;
		map[*y][*x] = icon;
	}
}

void moveRight(int* x, int* y, int* health, int* score, char** map, char icon)
{
	if (map[*y][*x + 1] != '\xBA' && map[*y][*x + 1] != '#')
	{
		if (map[*y][*x + 1] == '$')
		{
			*score = *score + 20;
		}
		map[*y][*x] = ' ';
		*x = *x + 1;
		map[*y][*x] = icon;
	}
}

void moveLeft(int* x, int* y, int* health, int* score, char** map, char icon)
{
	if (map[*y][*x - 1] != '\xBA' && map[*y][*x - 1] != '#')
	{
		if (map[*y][*x - 1] == '$')
		{
			*score = *score + 20;
		}
		map[*y][*x] = ' ';
		*x = *x - 1;
		map[*y][*x] = icon;
	}
}

void doNothing(void) {};

void defaultSword(int* x, int* y, int* health, int* score, char** map)
{
	for (int i = *y - 1; i <= *y + 1; i++)
	{
		for (int j = *x - 1; j <= *x + 1; j++)
		{
			if (map[i][j] == '#')
			{
				map[i][j] = ' ';
				*score += 20;
			}
		}
	}
}
