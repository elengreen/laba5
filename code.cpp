#include "pch.h" 
#include <locale.h> 
#include <malloc.h> 
#include <limits.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>

void cleaning(int ** seats, int rows);
int InputRow(int rowcount);
int InputSeat(int seatcount);
int** memalloc(int ** seats, int rowcount, int seatcount);
void ArrayFilling(int **seats, int rowcount, int seatcount);
void ArrayRand(int **seats, int rowcount, int seatcount);
void ArrayPrint(int **seats, int rowcount, int seatcount);
int SoldTickets(int** seats, int *rowcount, int *seatcount);
int RowInput(int rowcount);
int RemainTickets(int** seats, int row, int seatcount);
void ArrayFree(int** seats, int rowcount);

int main()
{
	setlocale(LC_ALL, "Russian");

	srand((unsigned)time(NULL)); // инициализация генератора случайных чисел 
	int rowcount = 0;
	int seatcount = 0;
	int** seats = NULL; // указатель на указатель на строку элементов 
	int menu = 0;
	char c = '\0';
	int chosen_row = 0;
	int check = 0;

	do
	{
		do
		{
			printf(" _______________________МЕНЮ_________________________\n");
			printf("|                                                    |\n");
			printf("| Введите цифру от 1 до 6.                           |\n");
			printf("| 1 - Ввод данных.                                   |\n");
			printf("| 2 - Заполнение случайными числами.                 |\n");
			printf("| 3 - Вывод схемы зала на экран.                     |\n");
			printf("| 4 - Вывод количества билетов, проданных на сеанс.  |\n");
			printf("| 5 - Вывод оставшихся билетов на заданном ряду.     |\n");
			printf("| 6 - Выход.                                         |\n");
			printf("|____________________________________________________|\n");
			while ((scanf_s("%d%c", &menu, &c, 1) != 2 || c != '\n')) // проверка ввода пунктов меню 
			{
				while (getchar() != '\n');
			}
		} while ((menu <= 0) || (menu > 6));
		switch (menu)
		{

		case 1:
			cleaning(seats, rowcount);
			rowcount = InputRow(rowcount);
			seatcount = InputSeat(seatcount);
			seats = memalloc(seats, rowcount, seatcount);
			ArrayFilling(seats, rowcount, seatcount);
			check = 1;
			break;

		case 2:

			cleaning(seats, rowcount);
			rowcount = InputRow(rowcount);
			seatcount = InputSeat(seatcount);
			seats = memalloc(seats, rowcount, seatcount);
			ArrayRand(seats, rowcount, seatcount);
			check = 1;
			break;

		case 3:
			if (check == 0)
			{
				printf("Неверный пункт меню.\n");
			}
			else
				ArrayPrint(seats, rowcount, seatcount);
				break;
		case 4:
			if (check == 0)
			{
				printf("Неверный пункт меню.\n");
			}
			else
				printf("На сеанс продано %d билетов.\n", SoldTickets(seats, &rowcount, &seatcount));
				break;

		case 5:
			if (check == 0)
			{
				printf("Неверный пункт меню.\n");
			}
			else
				chosen_row = RowInput(rowcount);
				printf("На этом ряду осталось %d билетов.\n", RemainTickets(seats, chosen_row, seatcount));
				break;
		case 6:
			break;

		}
	} while (menu != 6);
	void ArrayFree(int** seats, int rowcount);
	getchar();
	return 0;
}
void cleaning(int** seats, int rowcount)
{
		for (int i = 0; i < rowcount; i++) // цикл по строкам 
			free(seats[i]); // освобождение памяти под строку 
		free(seats);
}
int InputRow(int rowcount)
{
	do
	{
		printf("Введите количество рядов: ");
		char c = '\0';
		while ((scanf_s("%d%c", &rowcount, &c, 1) != 2 || c != '\n'))
		{
			while (getchar() != '\n');
		}
	} while (rowcount <= 0);
	return rowcount;
}
int InputSeat(int seatcount)
{
	do
	{
		char c = '\0';
		printf("Введите количество мест в ряду: ");
		while ((scanf_s("%d%c", &seatcount, &c, 1) != 2 || c != '\n'))
		{
			while (getchar() != '\n');
		}
	} while (seatcount <= 0);
	return seatcount;
}
int** memalloc(int** seats, int rowcount, int seatcount)
{
	seats = (int**)malloc(rowcount * sizeof(int*)); //выделение памяти 
	for (int i = 0; i < rowcount; i++) // цикл по строкам 
	{
		seats[i] = (int*)malloc(seatcount * sizeof(int)); // Выделение памяти под хранение строк 
	}
	return seats;
}
void ArrayFilling(int** seats, int rowcount, int seatcount)
{
	for (int i = 0; i < rowcount; i++)
	{
		printf("\n");
		for (int j = 0; j < seatcount; j++)
		{
			do
			{
				printf("\n");
				printf("Место [%d][%d] занято?\n", i + 1, j + 1);
				printf("1 - да 0 - нет \n\t");
				char c = '\0';
				while ((scanf_s("%d%c", &seats[i][j], &c, 1) != 2 || c != '\n'))
				{
					while (getchar() != '\n');
				}
			} while ((seats[i][j] < 0) || (seats[i][j] > 1));
		}
	}
}


void ArrayRand(int** seats, int rowcount, int seatcount)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < rowcount; i++)
	{
		for (int j = 0; j < seatcount; j++)
		{
			seats[i][j] = rand() % 2 - 0;
		}
	}
	printf("Массив заполнен случайными числами.\n");
}
void ArrayPrint(int **seats, int rowcount, int seatcount)
{
	for (int i = 0; i < rowcount; i++) // цикл по строкам 
	{
		for (int j = 0; j < seatcount; j++) // цикл по столбцам 
		{
			printf("%5d", seats[i][j]); // 5 знакомест под элемент массива 
		}
		printf("\n");
	}
}
int SoldTickets(int** seats, int *rowcount, int *seatcount)
{
	int tickets = 0;
	for (int i = 0; i < *rowcount; i++)
	{
		for (int j = 0; j < *seatcount; j++)
		{
			if (seats[i][j] == 1)
			{
				tickets += 1;
			}
		}
	}
	return tickets;
}
int RowInput(int rowcount)
{
	char c = '\0';
	int row = 0;
	do
	{
		printf("Введите номер ряда.\n");
		while ((scanf_s("%d%c", &row, &c, 1) != 2 || c != '\n'))
		{
			while (getchar() != '\n');
		}
	} while ((row > rowcount) || (row <= 0));
	return row;
}
int RemainTickets(int** seats, int row, int seatcount)
{
	int remain = 0;
	int i = row - 1;
	for (int j = 0; j < seatcount; j++)
	{
		if (seats[i][j] == 0)
		{
			remain += 1;
		}
	}
	return remain;
}
void ArrayFree(int** seats, int rowcount)
{
	for (int i = 0; i < rowcount; i++) // цикл по строкам 
	{
		free(seats[i]);
	}
	free(seats);
system("cls");
}
