#include <stdio.h>
#include <conio.h>
#include <Windows.h> // Console�� �����ϱ� ���� Windows API ���
#include<time.h>
#define MAP_HEIGHT 11 // ���� ���� ũ��
#define MAP_WIDTH 15 // ���� ���� ũ��
#define START_X 1 // �÷��̾� ���� X ��ǥ
#define START_Y 1 // �÷��̾� ���� Y ��ǥ
#define EXIT_X 9 // Ż�� ���� X ��ǥ
#define EXIT_Y 9 // Ż�� ���� Y ��ǥ
#define OFFSET_X 0 // �ʰ� �÷��̾��� X ������ (����)
#define OFFSET_Y 0 // �ʰ� �÷��̾��� Y ������ (����)
#define UP 100 // ����Ű ������ �ƽ�Ű �ڵ�
#define DOWN 101 // ����Ű �Ʒ����� �ƽ�Ű �ڵ�
#define LEFT 102 // ����Ű ������ �ƽ�Ű �ڵ�
#define RIGHT 103 // ����Ű �������� �ƽ�Ű �ڵ�
#define TRUE 1 // ��
#define FALSE 0 // ����
typedef unsigned char byte;
typedef unsigned int uint;
// ��������, �̷� ���� ��Ÿ���� 2���� �迭
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
// ��������, �÷��̾��� ��ǥ�� �����Ѵ�
uint g_player_x = START_X;
uint g_player_y = START_Y;
int ob_x1, ob_y1;
int ob_x2, ob_y2;
int ob_x3, ob_y3;
int old_ob_x1, old_ob_y1;
int old_ob_x2, old_ob_y2;// �Լ� ����
void gotoxy(uint x, uint y); // Console���� ��ǥ�� �̵���Ű�� �Լ�
void show_console_cursor(uint flag); // Console���� �����̴�Ŀ���� ���̰� �ϰų� ������ �ʰ��ϴ� �Լ�(����Ǯ�̿� ����)
void print_map(); // ���� ����ϴ� �Լ�
void update_player(); // �÷��̾� ��ġ�� ������Ʈ�ϴ� �Լ�,�������� g_player_x�� g_player_y�� �÷��̾�(Ŭ�ι� ����)��ǥ���Ѵ�.ȭ�鿡�� �÷��̾��� ��ǥ�� �ű�� �ʹٸ� ��ǥ �����������ϰ� �� �Լ��� ȣ���϶�
uint get_input(); // Ű���� �Է��� �޴� �Լ�, TOP, DOWN, LEFT,RIGHT �� �ϳ��� ������ ���̴�
void obstacle();
void auto_obstacle();
int main()
{
    show_console_cursor(FALSE); // �ֿܼ��� �����̴� Ŀ�����Ⱥ��̰� ���ش�. (���� Ǯ�̿� ����)
    //****** �� ������ ���׷��̵� �ڽ� ������ �����϶� ******
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
            printf("Ż�⼺��\n\n");
            gotoxy(15, 15);
            if (count == 26)
            {
                printf("����: 100��\n");
            }
            else if (100 - (count - 26) >= 0)
            {
                printf("����: %d��\n", 100 - (count - 26));
            }
            else
                printf("����: 0��\n");
            break;
        }
        
    }

    return 0;
}
// Console���� ��ǥ�� �̵���Ű�� �Լ�
void gotoxy(uint x, uint y) // Console���� ��ǥ�� �̵���Ű�� �Լ�
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
                             coord);
}
// Console���� �����̴� Ŀ���� ���̰� �ϰų� ������ �ʰ��ϴ� �Լ�(����Ǯ�̿� ����)
void show_console_cursor(uint flag) // Console���� Ŀ�� ���¸������ϴ� �Լ�
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = flag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
// ���� ����ϴ� �Լ�
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
                printf("��");
            //else if (g_map[i][j] == 2)
               // printf("��");
            else printf("  ");
        }
        printf("\n");
    }
    gotoxy(EXIT_X * 2 + OFFSET_X, EXIT_Y + OFFSET_Y);
    printf("��");
}
// �÷��̾� ��ġ�� ������Ʈ�ϴ� �Լ�, �������� g_player_x��g_player_y�� �÷��̾�(Ŭ�ι� ����)�� ǥ���Ѵ�.ȭ�鿡�� �÷��̾�����ǥ�� �ű�� �ʹٸ� ��ǥ ������ �����ϰ� �� �Լ��� ȣ���϶�
void update_player()
{
    static uint old_x = START_X;
    static uint old_y = START_Y;
    gotoxy(old_x * 2 + OFFSET_X, old_y + OFFSET_Y);
    printf("  ");
    gotoxy(g_player_x * 2 + OFFSET_X, g_player_y + OFFSET_Y);
    printf("��");
    old_x = g_player_x;
    old_y = g_player_y;
}
// Ű���� �Է��� �޴� �Լ�, TOP, DOWN, LEFT, RIGHT �� �ϳ��� ������
//���̴�
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
    printf("��");
    gotoxy(ob_x2, ob_y2);
    printf("��");

    g_map[old_ob_x1][old_ob_y1] = 0;
    g_map[old_ob_x2][old_ob_y2] = 0;
}