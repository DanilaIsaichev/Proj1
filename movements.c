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
	else
	{
		*health = *health - 10;
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
	else
	{
		*health = *health - 10;
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
	else
	{
		*health = *health - 10;
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
	else
	{
		*health = *health - 10;
	}
}
