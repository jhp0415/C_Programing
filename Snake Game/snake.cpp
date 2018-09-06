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
void screen();                   // 게임 전 스크린 출력
void draw_map();                 // 맵 그리기
void feed();                     // 먹이 랜덤으로 위치시키기
void snake_length();             // 뱀 길이 늘리기
int move();                      // 뱀 자동으로 움직이게 하기 + 키보드 입력 받기
void update_head();              // 머리위치
void game_over_message();        // 게임 종료 메시지 출력


int map[23][35];                 // 맵
int snake_x = 2;                 // 뱀 처음 x좌표
int snake_y = 3;                 // 뱀 처음 y좌표
int current_x = snake_x;         // 뱀 나중 x좌표
int current_y = snake_y;         // 뱀 나중 y좌표
int x[10000] = { snake_x, 0, };  // 뱀의 이전 위치들 저장
int y[10000] = { snake_y, 0, };  // 뱀의 이전 위치들 저장
int length = 1;                  // 뱀 길이
int food_x;                      // 먹이 x좌표
int food_y;                      // 먹이 y좌표
int score = 0;                   // 점수

input_result result;

void screen()
{
	draw_map();

	gotoxy(8, 7);
	printf("┌─────────────────┐");
	gotoxy(8, 8);
	printf("│    S     N     A     K     E     │");
	gotoxy(8, 9);
	printf("└─────────────────┘");

	gotoxy(11, 11);
	printf("< PRESS ANY KEY TO START >");
	gotoxy(13, 13);
	printf("←,→,↑,↓ : MOVE");
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

// 맵 그리기
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
				printf("■");
			else printf("  ");
		}
		printf("\n");
	}
}

void snake_length()
{
	// 뱀 머리 좌표와 먹이의 좌표가 같으면 길이++
	if (current_x == food_x && current_y == food_y)
	{
		length++;
		score += 100;
		feed();
	//	x[length - 1] = x[length - 2];
	//	y[length - 1] = y[length - 2];
	}

	// 먹이를 먹으면 길이가 늘어나는지 확인하기 위해 길이 출력
	gotoxy(0, 23);
	printf("length : %d    score : %d", length, score);
}

// 먹이 랜덤으로 위치시키기
void feed()
{
	// 먹이 위치 랜덤으로 생성
	int crash;  // 먹이좌표와 몸통좌표가 겹쳤는지 검사하기위해 사용
	int i;

	while (true)
	{
		crash = 0;
		srand((unsigned)time(NULL));
		food_x = (rand() % 33) + 1;
		food_y = (rand() % 21) + 1;

		// 먹이좌표가 몸통좌표와 겹칠 경우 다시 먹이좌표 생성
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
		printf("♣");
		break;
	}

}

// 뱀 자동으로 움직이기 + 키보드 입력 받기
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
				// 머리가 벽에 닿으면 게임 종료
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_y++;
					return 0;
				}
				update_head();
				Sleep(100);      // 이동속도 조절
				// 머리가 몸통에 닿으면 게임 종료
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
				// 머리가 벽에 닿으면 게임 종료
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_y--;
					return 0;
				}
				update_head();
				Sleep(100);      // 이동속도 조절
				// 머리가 몸통에 닿으면 게임 종료
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
				// 머리가 벽에 닿으면 게임 종료
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_x++;
					return 0;
				}
				update_head();
				Sleep(100);      // 이동속도 조절
				// 머리가 몸통에 닿으면 게임 종료
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
				// 머리가 벽에 닿으면 게임 종료
				if (map[current_y][current_x] == 1)
				{
					game_over_message();
					current_x--;
					return 0;
				}
				update_head();
				Sleep(100);      // 이동속도 조절
				// 머리가 몸통에 닿으면 게임 종료
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
	gotoxy(snake_x, snake_y);  // 이전위치로 돌아가 공백출력
	printf("  ");

	gotoxy(current_x, current_y);  // 현재위치에 플레이어 표시
	printf("◎"); // 머리

	snake_length();

	x[0] = snake_x;  // 이전좌표를 배열에 저장
	y[0] = snake_y;

	snake_x = current_x;  // 이전좌표를 현재위치로 설정
	snake_y = current_y;

	if (length > 1)
	{
		// 길이가 늘어나면 이전좌표에 몸통을 출력
		gotoxy(x[0], y[0]);
		printf("○");

		// 머리와 몸통을 제외한 지나온 자리는 공백 출력
		gotoxy(x[length - 1], y[length - 1]);
		printf("  ");
		for (int i = length - 1; i > 0; i--)
		{
			// 몸통좌표를 한 칸씩 옮김
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

