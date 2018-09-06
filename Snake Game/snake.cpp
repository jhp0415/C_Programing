#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>

void gotoxy(int x, int y)
{
	COORD pos = { 2*x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

enum input_result
{
	top = 0,
	down,
	left,
	right,
};

input_result get_input()
{
	while (true)
	{
		int input = getch();
		if (input == 224)
		{
			input = getch();
			if (input == 72)
				return top;
			else if (input == 80)
				return down;
			else if (input == 75)
				return left;
			else if (input == 77)
				return right;
		}
	}
}
void screen();                   // ���� �� ��ũ�� ���
void draw_map();                 // �� �׸���
void feed();                     // ���� �������� ��ġ��Ű��
void snake_length();             // �� ���� �ø���
int move();                      // �� �ڵ����� �����̰� �ϱ� + Ű���� �Է� �ޱ�
void update_head();              // �Ӹ���ġ
void game_over_message();        // ���� ���� �޽��� ���


int map[23][35];                 // ��
int snake_x = 2;                 // �� ó�� x��ǥ
int snake_y = 3;                 // �� ó�� y��ǥ
int current_x = snake_x;         // �� ���� x��ǥ
int current_y = snake_y;         // �� ���� y��ǥ
int x[10000] = { snake_x, 0, };  // ���� ���� ��ġ�� ����
int y[10000] = { snake_y, 0, };  // ���� ���� ��ġ�� ����
int length = 1;                  // �� ����
int food_x;                      // ���� x��ǥ
int food_y;                      // ���� y��ǥ
int score = 0;                   // ����

input_result result;

void screen()
{
	draw_map();

	gotoxy(8, 7);
	printf("��������������������������������������");
	gotoxy(8, 8);
	printf("��    S     N     A     K     E     ��");
	gotoxy(8, 9);
	printf("��������������������������������������");

	gotoxy(11, 11);
	printf("< PRESS ANY KEY TO START >");
	gotoxy(13, 13);
	printf("��,��,��,�� : MOVE");
}

void main()
{
	screen();
	system("pause > null");

	system("cls");
	draw_map();

	feed();
	move();

}

// �� �׸���
void draw_map()
{
	int i, j;

	for (i = 0; i < 23; i++){
		for (j = 0; j < 35; j++){
			if (i == 0 || i == 22 || j == 0 || j == 34)
				map[i][j] = 1;
			else map[i][j] = 0;
		}
	}

	for (i = 0; i < 23; i++){
		for (j = 0; j < 35; j++){
			if (map[i][j] == 1)
				printf("��");
			else printf("  ");
		}
		printf("\n");
	}
}

void snake_length()
{
	// �� �Ӹ� ��ǥ�� ������ ��ǥ�� ������ ����++
	if (current_x == food_x && current_y == food_y)
	{
		length++;
		score += 100;
		feed();
	//	x[length - 1] = x[length - 2];
	//	y[length - 1] = y[length - 2];
	}

	// ���̸� ������ ���̰� �þ���� Ȯ���ϱ� ���� ���� ���
	gotoxy(0, 23);
	printf("length : %d    score : %d", length, score);
}

// ���� �������� ��ġ��Ű��
void feed()
{
	// ���� ��ġ �������� ����
	int crash;  // ������ǥ�� ������ǥ�� ���ƴ��� �˻��ϱ����� ���
	int i;

	while (true)
	{
		crash = 0;
		srand((unsigned)time(NULL));
		food_x = (rand() % 33) + 1;
		food_y = (rand() % 21) + 1;

		// ������ǥ�� ������ǥ�� ��ĥ ��� �ٽ� ������ǥ ����
		for (i = length; i >= 0; i--)
		{
			if (food_x == x[i] && food_y == y[i])
			{
				crash = 1;
				break;
			}
		}

		if (crash == 1)
			continue;

		gotoxy(food_x, food_y);
		printf("��");
		break;
	}

}

// �� �ڵ����� �����̱� + Ű���� �Է� �ޱ�
int move()
{
	while (true)
	{
		update_head();
		result = get_input();
		switch (result)
		{
		case top:
			while (kbhit() == 0)
			{
				current_y--;
				// �Ӹ��� ���� ������ ���� ����
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_y++;
					return 0;
				}
				update_head();
				Sleep(100);      // �̵��ӵ� ����
				// �Ӹ��� ���뿡 ������ ���� ����
				for (int i = 0; i < length; i++)
				{
					if (current_x == x[i] && current_y == y[i])
					{
						game_over_message();
						return 0;
					}
					else continue;
				}
			}
			break;
		case down:
			while (kbhit() == 0)
			{
				current_y++;
				// �Ӹ��� ���� ������ ���� ����
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_y--;
					return 0;
				}
				update_head();
				Sleep(100);      // �̵��ӵ� ����
				// �Ӹ��� ���뿡 ������ ���� ����
				for (int i = 0; i < length; i++)
				{
					if (current_x == x[i] && current_y == y[i])
					{
						game_over_message();
						return 0;
					}
					else continue;
				}
			}
			break;
		case left:
			while (kbhit() == 0)
			{
				current_x--;
				// �Ӹ��� ���� ������ ���� ����
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_x++;
					return 0;
				}
				update_head();
				Sleep(100);      // �̵��ӵ� ����
				// �Ӹ��� ���뿡 ������ ���� ����
				for (int i = 0; i < length; i++)
				{
					if (current_x == x[i] && current_y == y[i])
					{
						game_over_message();
						return 0;
					}
					else continue;
				}
			}
			break;
		case right:
			while (kbhit() == 0)
			{
				current_x++;
				// �Ӹ��� ���� ������ ���� ����
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_x--;
					return 0;
				}
				update_head();
				Sleep(100);      // �̵��ӵ� ����
				// �Ӹ��� ���뿡 ������ ���� ����
				for (int i = 0; i < length; i++)
				{
					if (current_x == x[i] && current_y == y[i])
					{
						game_over_message();
						return 0;
					}
					else continue;
				}
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

void update_head()
{
	gotoxy(snake_x, snake_y);  // ������ġ�� ���ư� �������
	printf("  ");

	gotoxy(current_x, current_y);  // ������ġ�� �÷��̾� ǥ��
	printf("��"); // �Ӹ�

	snake_length();

	x[0] = snake_x;  // ������ǥ�� �迭�� ����
	y[0] = snake_y;

	snake_x = current_x;  // ������ǥ�� ������ġ�� ����
	snake_y = current_y;

	if (length > 1)
	{
		// ���̰� �þ�� ������ǥ�� ������ ���
		gotoxy(x[0], y[0]);
		printf("��");

		// �Ӹ��� ������ ������ ������ �ڸ��� ���� ���
		gotoxy(x[length - 1], y[length - 1]);
		printf("  ");
		for (int i = length - 1; i > 0; i--)
		{
			// ������ǥ�� �� ĭ�� �ű�
			x[i] = x[i - 1];
			y[i] = y[i - 1];
		}
	}

}

void game_over_message()
{
	gotoxy(13, 9);
	printf("<< GAME  OVER >>");
	gotoxy(13, 11);
	printf("SCORE  %d", score);
	gotoxy(13, 12);
	printf("YOU EAT %d FOODS", length - 1);

	gotoxy(0, 24);
}

