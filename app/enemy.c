#include <stdlib.h>
void zombieMovements(int px, int py, int* ph, int* zx, int* zy, char** map)
{
	if (abs(px - *zx) < abs(py - *zy))
	{
		if (*zx < px)
		{
			if (*zx + 1 == px && *zy == py)
			{
				(*ph) -= 10;
			}
			else
			{
				map[*zy][*zx + 1] = '#';
				map[*zy][*zx] = ' ';
				(*zx)++;
			}
		}
		else
		{
			if (*zx > px)
			{
				if (*zx - 1 == px && *zy == py)
				{
					(*ph) -= 10;
				}
				else
				{
					map[*zy][*zx - 1] = '#';
					map[*zy][*zx] = ' ';
					(*zx)--;
				}
			}
			else
			{
				if (*zy < py)
				{
					if (*zy + 1 == py && *zx == px)
					{
						(*ph) -= 10;
					}
					else
					{
						map[*zy + 1][*zx] = '#';
						map[*zy][*zx] = ' ';
						(*zy)++;
					}
				}
				else
				{
					if (*zy - 1 == py && *zx == px)
					{
						(*ph) -= 10;
					}
					else
					{
						map[*zy - 1][*zx] = '#';
						map[*zy][*zx] = ' ';
						(*zy)--;
					}
				}
			}
		}
	}
	else
	{
		if (*zy < py)
		{
			if (*zy + 1 == py && *zx == px)
			{
				(*ph) -= 10;
			}
			else
			{
				map[*zy + 1][*zx] = '#';
				map[*zy][*zx] = ' ';
				(*zy)++;
			}
		}
		else
		{
			if (*zy < py)
			{
				if (*zy - 1 == py && *zx == px)
				{
					(*ph) -= 10;
				}
				else
				{
					map[*zy - 1][*zx] = '#';
					map[*zy][*zx] = ' ';
					(*zy)--;
				}
			}
			else
			{
				if (*zx < px)
				{
					if (*zx + 1 == px && *zy == py)
					{
						(*ph) -= 10;
					}
					else
					{
						map[*zy][*zx + 1] = '#';
						map[*zy][*zx] = ' ';
						(*zx)++;
					}
				}
				else
				{
					if (*zx - 1 == px && *zy == py)
					{

						(*ph) -= 10;
					}
					else
					{
						map[*zy][*zx - 1] = '#';
						map[*zy][*zx] = ' ';
						(*zx)--;
					}
				}
			}
		}
	}
}
