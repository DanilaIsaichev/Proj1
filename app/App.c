#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "movements.h"
#include "enemy.h"

void paint(int, int, int, int, char**, char[]);
void swordAnimation(int, int, int, int, int, int*, char**, char[]);
int fInput(int);

struct stats
{
	char name[12];
	char icon;
	int health, score, x, y;
	int *pHealth, *pScore, *pX, *pY;
} player;

int main()
{
	unsigned int menu;
	do
	{
		system("cls");
		printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA ");
		setlocale(LC_ALL, "Ru");
		printf("Выберите:                ");
		setlocale(LC_ALL, "C");
		printf("\xBA\n\xBA ");
		setlocale(LC_ALL, "Ru");
		printf("1. Начать                ");
		setlocale(LC_ALL, "C");
		printf("\xBA\n\xBA ");
		setlocale(LC_ALL, "Ru");
		printf("0. Выйти                 ");
		setlocale(LC_ALL, "C");
		printf("\xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
		menu = _getch();
		if (menu == 49)
		{
			const int n = 100, m = n / 4;
			const int zk = 3;
			int input, i, j, ik, jk, t, c, k;
			struct stats player = 
			{
				.name = {'p', 'l', 'a', 'y', 'e', 'r'},
				.icon = '@',
				.health = 100,
				.score = 0,
				.x = 1,
				.y = 1,
				.pHealth = &player.health,
				.pScore = &player.score,
				.pX = &player.x,
				.pY = &player.y
			};
			//Ввод имени пользователя
			do {
				system("cls");
				printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA ");
				setlocale(LC_ALL, "Ru");
				printf("Введите имя  пользователя ");
				setlocale(LC_ALL, "C");
				printf("\xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
				fgets(player.name, 6, stdin);
				for (i = 0; i <= 5; i++)
				{
					if (player.name[i] == '\n')
					{
						player.name[i] = ' ';
					}
				}
			} while (player.name[0] == ' ');
			//Генерация уровня
			system("cls");
			char** map = NULL;
			map = (char**)malloc(m * sizeof(char*));
			if (map == NULL)
			{
				return 1;
			}
			for (i = 0; i <= m - 1; i++)
			{
				t = rand() % 100 + 1;
				c = rand() % 100 + 1;
				map[i] = (char*)malloc(n * sizeof(char));
				for (j = 0; j <= n - 1; j++)
				{
					if (i == 0 || i == (m - 1))
					{
						map[i][j] = '\xCD';
					}
					else
					{
						if (j == 0 || j == (n - 1))
						{
							map[i][j] = '\xBA';
						}
						else
						{
							if (j == t)
							{
								map[i][j] = ' ';// '#';
							}
							else
							{
								if (j == c)
								{
									map[i][j] = '$';
								}
								else
								{
									map[i][j] = ' ';
								}
							}
						}
					}
				}
			}
			map[0][0] = '\xC9';
			map[0][n - 1] = '\xBB';
			map[m - 1][0] = '\xC8';
			map[m - 1][n - 1] = '\xBC';
			map[player.y][player.x] = player.icon;
			struct stats* zombies;
			zombies = (struct stats*)malloc(zk * sizeof(struct stats));
			if (zombies == NULL)
			{
				return 1;
			}
			for (int i = 0; i < zk; i++)
			{
				struct stats zombie =
				{
					.name = {' '},
					.icon = ' ',
					.health = 0,
					.score = 0,
					.x = 0,
					.y = 0,
					.pHealth = NULL,
					.pScore = NULL,
					.pX = NULL,
					.pY = NULL
				};
				sprintf(zombies[i].name, "zombie%d", i);
				zombies[i].icon = '#';
				zombies[i].health = 10;
				zombies[i].score = 0;
				zombies[i].x = rand() % 100 + 1;
				zombies[i].y = rand() % 23 + 1,
				zombies[i].pHealth = &zombies[i].health;
				zombies[i].pScore = &zombies[i].score;
				zombies[i].pX = &zombies[i].x;
				zombies[i].pY = &zombies[i].y;
				map[zombies[i].y][zombies[i].x] = zombies[i].icon;
			}
			paint(n, m, player.health, player.score, map, player.name);
			//Игра
			do {
				do {
					input = _getch();
					input = fInput(input);
					Sleep(120);//Задержка перед вводом
				} while (input != 83 && input != 65 && input != 87 && input != 68 && input != 27 && input != 32 && input != 82);
				system("cls");
				switch (input)
				{
				case 83: moveDown(player.pX, player.pY, player.pHealth, player.pScore, map, player.icon);
					break;
				case 65: moveLeft(player.pX, player.pY, player.pHealth, player.pScore, map, player.icon);
					break;
				case 87: moveUp(player.pX, player.pY, player.pHealth, player.pScore, map, player.icon);
					break;
				case 68: moveRight(player.pX, player.pY, player.pHealth, player.pScore, map, player.icon);
					break;
				case 82: doNothing();
					break;
				case 32: swordAnimation(n, m, player.x, player.y, player.health, player.pScore, map, player.name);
					break;
				}
				//Проверка условия выигрыша
				k = 0;
				for (ik = 1; ik <= m-2; ik++)
				{
					for (jk = 1; jk <= n - 2; jk++)
					{
						if (map[ik][jk] == '$')
						{
							k = 5;
							break;
						}
						jk++;
					}
					if (map[ik][jk] == '$')
					{
						k = 5;
						break;
					}
				}
				for (i = 0; i < zk; i++)//ход проивников
				{
					if (map[zombies[i].y][zombies[i].x] == zombies[i].icon)
					{
						zombieMovements(player.x, player.y, player.pHealth, zombies[i].pX, zombies[i].pY, map);
					}
					else
					{
						zombies[i].health = 0;
					}
				}
				paint(n, m, player.health, player.score, map, player.name);
			} while (input != 27 && player.health != 0 && k == 5);
			//Освобождение памяти
			for (i = 0; i <= m - 1; i++)
			{
				free(map[i]);
			}
			free(map);
			free(zombies);
			//Проверка условия проигрыша
			if (player.health == 0)
			{
				system("cls");
				printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA ");
				setlocale(LC_ALL, "Ru");
				printf("Вы проиграли               ");
				setlocale(LC_ALL, "C");
				printf("\xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
				Sleep(120);//Задержка перед вводом
				_getch();
				continue;
			}
			//Проверка условия проигрыша
			if (k != 5)
			{
				system("cls");
				printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA ");
				setlocale(LC_ALL, "Ru");
				printf("Вы выиграли               ");
				setlocale(LC_ALL, "C");
				printf("\xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
				Sleep(120);//Задержка перед вводом
				_getch();
				continue;
			}
			//Проверка нажатия клавишы Esc
			if (input == 27)
			{
				continue;
			}
			break;
		}
	} while (menu != 48);
	system("cls");
	printf("\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA ");
	setlocale(LC_ALL, "Ru");
	printf("Работа программы завершена ");
	setlocale(LC_ALL, "C");
	printf("\xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
	return 0;
}

void paint(int n, int m, int health, int score,  char** map, char name[])
{
	int i, j;
	for (i = 0; i <= m - 1; i++)
	{
		printf("\n");
		for (j = 0; j <= n - 1; j++)
		{
			if (map[i][j] == '$')
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
				printf("%c", map[i][j]);
				SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			}
			else
			{
				if (map[i][j] == '#')
				{
					HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
					printf("%c", map[i][j]);
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				}
				else
				{
					printf("%c", map[i][j]);
				}
			}
		}
	}
	printf("\n\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n\xBA ");
	printf("\t%s\t%d\t%d\t\t W \x1E\t\t SPACE - SWORD\t", name, health, score);
	printf("\xBA\n\xBA\tESC - EXIT\t\t <- A\t S \x1F\tD ->\tR - DO NOTHING\t");
	printf("\xBA\n\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC");
}

int fInput(int input)
{
	if (input == 155 || input == 148 || input == 130 || input == 150 || input == 138)
	{
		switch (input) {
		case 155: input = 83; /* \/ */
			break;
		case 148: input = 65; /* <- */
			break;
		case 130: input = 68; /* -> */
			break;
		case 150: input = 87; /* /\ */
			break;
		case 138: input = 82;
			break;
		}
	}
	else
	{
		if (input == 235 || input == 228 || input == 162 || input == 230 || input == 170)
		{
			switch (input) {
			case 235: input = 83; /* \/ */
				break;
			case 228: input = 65; /* <- */
				break;
			case 162: input = 68; /* -> */
				break;
			case 230: input = 87;/* /\ */
				break;
			case 170: input = 82;
				break;
			}
		}
		else
		{
			if (input == 115 || input == 97 || input == 100 || input == 119 || input == 114)
			{
				switch (input) {
				case 115: input = 83;/* \/ */
					break;
				case 97: input = 65; /* <- */
					break;
				case 100: input = 68; /* -> */
					break;
				case 119: input = 87; /* /\ */
					break;
				case 114: input = 82;
					break;
				}
			}
		}
	}
	return input;
}

void swordAnimation(int n, int m, int x, int y, int health, int *score, char** map, char name[])
{
	for (int i = y - 1; i <= y + 1; i++)
	{
		for (int j = x - 1; j <= x + 1; j++)
		{
			if (map[i][j] == '#')
			{
				*score += 20;
			}
		}
	}
	if (x == 1 || x == n - 2)
	{
		if (x == 1)
		{
			if (y == 1 || y == m - 2)
			{
				if (y == 1) //Левый верхний угол
				{
					map[y][x + 1] = '-';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y][x + 1] = ' ';
					map[y + 1][x + 1] = '\\';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y + 1][x + 1] = ' ';
					map[y + 1][x] = '|';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y + 1][x] = ' ';
				}
				else //Левый нижний угол
				{
					map[y - 1][x] = '|';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y - 1][x] = ' ';
					map[y - 1][x + 1] = '/';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y - 1][x + 1] = ' ';
					map[y][x + 1] = '-';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y][x + 1] = ' ';
				}
			}
			else//Слева
			{
				map[y - 1][x] = '|';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x] = ' ';
				map[y - 1][x + 1] = '/';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x + 1] = ' ';
				map[y][x + 1] = '-';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y][x + 1] = ' ';
				map[y + 1][x + 1] = '\\';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x + 1] = ' ';
				map[y + 1][x] = '|';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x] = ' ';
			}
		}
		else
		{
			if (y == 1 || y == m - 2)
			{
				if (y == 1) //Правый верхний угол
				{
					map[y][x - 1] = '-';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y][x - 1] = ' ';
					map[y + 1][x - 1] = '/';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y + 1][x - 1] = ' ';
					map[y + 1][x] = '|';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y + 1][x] = ' ';
				}
				else //Правый нижний угол
				{
					map[y - 1][x] = '|';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y - 1][x] = ' ';
					map[y - 1][x - 1] = '\\';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y - 1][x - 1] = ' ';
					map[y][x - 1] = '-';
					paint(n, m, health, *score, map, name);
					system("cls");
					map[y][x - 1] = ' ';
				}
			}
			else//Справа
			{
				map[y - 1][x] = '|';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x] = ' ';
				map[y - 1][x - 1] = '\\';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x - 1] = ' ';
				map[y][x - 1] = '-';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y][x - 1] = ' ';
				map[y + 1][x - 1] = '/';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x - 1] = ' ';
				map[y + 1][x] = '|';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x] = ' ';
			}
		}
	}
	else
	{
		if (y == 1 || y == m - 2)
		{
			if (y == 1)//Сверху
			{
				map[y][x + 1] = '-';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y][x + 1] = ' ';
				map[y + 1][x + 1] = '\\';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x + 1] = ' ';
				map[y + 1][x] = '|';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x] = ' ';
				map[y + 1][x - 1] = '/';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y + 1][x - 1] = ' ';
				map[y][x - 1] = '-';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y][x - 1] = ' ';
			}
			else//Снизу
			{
				map[y][x - 1] = '-';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y][x - 1] = ' ';
				map[y - 1][x - 1] = '\\';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x - 1] = ' ';
				map[y - 1][x] = '|';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x] = ' ';
				map[y - 1][x + 1] = '/';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y - 1][x + 1] = ' ';
				map[y][x + 1] = '-';
				paint(n, m, health, *score, map, name);
				system("cls");
				map[y][x + 1] = ' ';
			}
		}
		else//В центре
		{
			map[y - 1][x - 1] = '\\';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y - 1][x - 1] = ' ';
			map[y - 1][x] = '|';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y - 1][x] = ' ';
			map[y - 1][x + 1] = '/';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y - 1][x + 1] = ' ';
			map[y][x + 1] = '-';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y][x + 1] = ' ';
			map[y + 1][x + 1] = '\\';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y + 1][x + 1] = ' ';
			map[y + 1][x] = '|';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y + 1][x] = ' ';
			map[y + 1][x - 1] = '/';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y + 1][x - 1] = ' ';
			map[y][x - 1] = '-';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y][x - 1] = ' ';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y - 1][x - 1] = '\\';
			paint(n, m, health, *score, map, name);
			system("cls");
			map[y - 1][x - 1] = ' ';
		}
	}
}
