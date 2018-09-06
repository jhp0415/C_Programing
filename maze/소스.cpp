#include <stdio.h>
#include <conio.h>
#include <Windows.h> // Console을 제어하기 위해 Windows API 사용
#include<time.h>
#define MAP_HEIGHT 11 // 맵의 세로 크기
#define MAP_WIDTH 15 // 맵의 가로 크기
#define START_X 1 // 플레이어 시작 X 좌표
#define START_Y 1 // 플레이어 시작 Y 좌표
#define EXIT_X 9 // 탈출 지점 X 좌표
#define EXIT_Y 9 // 탈출 지점 Y 좌표
#define OFFSET_X 0 // 맵과 플레이어의 X 오프셋 (무시)
#define OFFSET_Y 0 // 맵과 플레이어의 Y 오프셋 (무시)
#define UP 100 // 방향키 위쪽의 아스키 코드
#define DOWN 101 // 방향키 아래쪽의 아스키 코드
#define LEFT 102 // 방향키 왼쪽의 아스키 코드
#define RIGHT 103 // 방향키 오른쪽의 아스키 코드
#define TRUE 1 // 참
#define FALSE 0 // 거짓
typedef unsigned char byte;
typedef unsigned int uint;
// 전역변수, 미로 맵을 나타내는 2차원 배열
int g_map[MAP_HEIGHT][MAP_WIDTH] =
{
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1 },
    { 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1 },
    { 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1 },
    { 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};
// 전역변수, 플레이어의 좌표를 저장한다
uint g_player_x = START_X;
uint g_player_y = START_Y;
int ob_x1, ob_y1;
int ob_x2, ob_y2;
int ob_x3, ob_y3;
int old_ob_x1, old_ob_y1;
int old_ob_x2, old_ob_y2;// 함수 원형
void gotoxy(uint x, uint y); // Console에서 좌표를 이동시키는 함수
void show_console_cursor(uint flag); // Console에서 깜빡이는커서를 보이게 하거나 보이지 않게하는 함수(문제풀이와 무관)
void print_map(); // 맵을 출력하는 함수
void update_player(); // 플레이어 위치를 업데이트하는 함수,전역변수 g_player_x와 g_player_y에 플레이어(클로버 문양)를표시한다.화면에서 플레이어의 좌표를 옮기고 싶다면 좌표 변수를조작하고 이 함수를 호출하라
uint get_input(); // 키보드 입력을 받는 함수, TOP, DOWN, LEFT,RIGHT 중 하나를 리턴할 것이다
void obstacle();
void auto_obstacle();
int main()
{
    show_console_cursor(FALSE); // 콘솔에서 깜빡이는 커서를안보이게 해준다. (문제 풀이와 무관)
    //****** 이 공간에 업그레이드 박스 게임을 구현하라 ******
    print_map();
    update_player();
    uint result;
    uint old_x, old_y;
    uint count = 0;
    while (1)
    {
        auto_obstacle();
        old_x = g_player_x;
        old_y = g_player_y;
        result = get_input();
        switch (result)
        {
        case UP:
            g_player_y--;
            break;
        case DOWN:
            g_player_y++;
            break;
        case RIGHT:
            g_player_x++;
            break;
        case LEFT:
            g_player_x--;
            break;
        }
        if (g_map[g_player_y][g_player_x] == 1)
        {
            g_player_x = old_x;
            g_player_y = old_y;
            count--;
        }
        if (g_map[g_player_y][g_player_x] == 2)
        {
            g_player_x = START_X;
            g_player_y = START_Y;
        }
        update_player();
        count++;
        if (g_player_x == EXIT_X&&g_player_y == EXIT_Y)
        {
            printf("탈출성공\n\n");
            gotoxy(15, 15);
            if (count == 26)
            {
                printf("점수: 100점\n");
            }
            else if (100 - (count - 26) >= 0)
            {
                printf("점수: %d점\n", 100 - (count - 26));
            }
            else
                printf("점수: 0점\n");
            break;
        }
        
    }

    return 0;
}
// Console에서 좌표를 이동시키는 함수
void gotoxy(uint x, uint y) // Console에서 좌표를 이동시키는 함수
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             coord);
}
// Console에서 깜빡이는 커서를 보이게 하거나 보이지 않게하는 함수(문제풀이와 무관)
void show_console_cursor(uint flag) // Console에서 커서 상태를변경하는 함수
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
// 맵을 출력하는 함수
void print_map()
{
    //obstacle();
    gotoxy(OFFSET_X, OFFSET_Y);
    for (int i = 0; i < MAP_HEIGHT; ++i)
    {
        gotoxy(OFFSET_X, OFFSET_Y + i);
        for (int j = 0; j < MAP_WIDTH; ++j)
        {
            if (g_map[i][j] == 1)
                printf("■");
            //else if (g_map[i][j] == 2)
               // printf("※");
            else printf("  ");
        }
        printf("\n");
    }
    gotoxy(EXIT_X * 2 + OFFSET_X, EXIT_Y + OFFSET_Y);
    printf("◎");
}
// 플레이어 위치를 업데이트하는 함수, 전역변수 g_player_x와g_player_y에 플레이어(클로버 문양)를 표시한다.화면에서 플레이어의좌표를 옮기고 싶다면 좌표 변수를 조작하고 이 함수를 호출하라
void update_player()
{
    static uint old_x = START_X;
    static uint old_y = START_Y;
    gotoxy(old_x * 2 + OFFSET_X, old_y + OFFSET_Y);
    printf("  ");
    gotoxy(g_player_x * 2 + OFFSET_X, g_player_y + OFFSET_Y);
    printf("♧");
    old_x = g_player_x;
    old_y = g_player_y;
}
// 키보드 입력을 받는 함수, TOP, DOWN, LEFT, RIGHT 중 하나를 리턴할
//것이다
uint get_input()
{
    while (TRUE)
    {
        uint c = getch();
        if (c == 224)
        {
            c = getch();
            switch (c)
            {
            case 75:
                return LEFT;
            case 77:
                return RIGHT;
            case 72:
                return UP;
            case 80:
                return DOWN;
            default:
                break;
            }
        }
    }
}

void obstacle()
{
    srand(time(NULL));
    
    ob_x1 = rand() % 11;
    ob_y1 = rand() % 15;
    ob_x2 = rand() % 11;
    ob_y2 = rand() % 15;
    ob_x3 = rand() % 11;
    ob_y3 = rand() % 15;
    for (int i = 0; i < 11; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (g_map[i][j] != 1)
            {
                g_map[ob_x1][ob_y1] = 2;
                g_map[ob_x2][ob_y2] = 2;
                break;
            }
        }    
    }
}
void auto_obstacle()
{
    
    gotoxy(old_ob_x1, old_ob_y1);
    printf("  ");
    gotoxy(old_ob_x2, old_ob_y2);
    printf("  ");
    gotoxy(g_player_y, g_player_x);

    if ((ob_x1 != g_player_x || ob_y1 != g_player_y)
        && (ob_x1 != START_X || ob_y1 != START_Y) && (ob_x1 != EXIT_X || ob_y1 != EXIT_Y))
    {
        srand(time(NULL));
        ob_x1 = rand() % 11;
        ob_y1 = rand() % 15;
        g_map[ob_x1][ob_y1] = 2;
        old_ob_x1 = ob_x1;
        old_ob_y1 = ob_y1;
    }
    if (ob_x1 != ob_x2 && ob_y1 != ob_y2)
    {
        srand(time(NULL));
        ob_x2 = rand() % 11;
        ob_y2 = rand() % 15;
        g_map[ob_x2][ob_y2] = 2;
        old_ob_x2 = ob_x2;
        old_ob_y2 = ob_y2;
    }

    gotoxy(ob_x1, ob_y1);
    printf("※");
    gotoxy(ob_x2, ob_y2);
    printf("※");

    g_map[old_ob_x1][old_ob_y1] = 0;
    g_map[old_ob_x2][old_ob_y2] = 0;
}