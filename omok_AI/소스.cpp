#include<stdio.h>
#include<conio.h>
#include<Windows.h>
enum input_result
{
    top = 0,
    down,
    left,
    right,
    sp,
    enter,
    s,
    l
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
        else if (input == 32)
            return sp;
        else if (input == 13)
            return enter;
        else if (input == 115)
            return s;
        else if (input == 108)
            return l;
    }
}
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                //색변경하기
int xxx, yyy;
int cur_x = 10;          //현재좌표
int cur_y = 10;
char turn = 'B';           //홀수면 흑돌, 짝수면 백돌
int count_hor_B = 0, count_hor_W = 0;
int count_ver_B = 0, count_ver_W = 0;
int count_dia_B_1 = 0, count_dia_B_2 = 0;
int count_dia_W_1 = 0, count_dia_W_2 = 0;
char map[19][19] = {
    { 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8 },
    { 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7 } };
int add_w[19][19] = { 0, };
int add_b[19][19] = { 0, };
int thrstB, thrstW;
int fostB, fostW;
////////////////////////////////////////////////////////////////////////////////////
void gotoxy(int x, int y);
int main_screen();
void cursor();
void make_map();
void move();
void setstone(int _x, int _y);
int check();
int check_horizon_B();
int check_horizon_W();
int check_vertical_B();
int check_vertical_W();
int check_diagnal_B_1();
int check_diagnal_B_2();
int check_diagnal_W_1();
int check_diagnal_W_2();
void save();
void load();
void score_w();
void score_b();
void print_w()
{
    //출력해보기
    gotoxy(0, 20);
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            printf("%d, ", add_w[i][j]);
        }
        printf("\n");
    }
}
void print_b()
{
    gotoxy(0, 20);
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {

            printf("%d, ", add_b[i][j]);
        }
        printf("\n");
    }

}
void threeB_hor();
void threeB_ver();
void threeB_dia1();
void threeB_dia2();
void threestone_B();
void threeW_hor();
void threeW_ver();
void threeW_dia1();
void threeW_dia2();
void threestone_W();
void fourstone();
/////////////////////////////////////main///////////////////////////////////////////
void main()
{
    int start_number, winner;
    start_number = main_screen();
    if (start_number == 2)
        return;
    else if (start_number == 1)     //불러오기
    {
        load();
        do
        {
            move();
            winner = check();
            if (winner == -1)
            {
                gotoxy(23, 5);
                SetConsoleTextAttribute(handle, 15 + 0 * 16);
                printf("***흑승리***");

            }
            else if (winner == 1)
            {
                gotoxy(23, 5);
                SetConsoleTextAttribute(handle, 15 + 0 * 16);
                printf("***백승리***");
            }
        }
        while (winner == 0);
    }

    else if (start_number == 0)     //시작하기
    {
        system("cls");
        SetConsoleTextAttribute(handle, 0 + 14 * 16);
        make_map();
        do
        {
            move();
            
            winner = check();
            if (winner == -1)
            {
                gotoxy(23, 5);
                SetConsoleTextAttribute(handle, 15 + 0 * 16);
                printf("***흑승리***");

            }
            else if (winner == 1)
            {
                gotoxy(23, 5);
                SetConsoleTextAttribute(handle, 15 + 0 * 16);
                printf("***백승리***");
            }
        }
        while (winner == 0);
    }

    ////////////////////////////////////////////////////////////////////////

    

}

////////////////////////////////////필요 함수들//////////////////////////////////////////

void gotoxy(int x, int y)
{
    COORD cursor = { x * 2, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursor);
}
int main_screen()
{
    int arr[19][19] =
    {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };

    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (arr[i][j] == 1)
                printf("■");
            else if (arr[i][j] != 1)
                printf("  ");
        }
        printf("\n");
    }
    gotoxy(7, 13);
    printf("[ START ]");
    gotoxy(7, 14);
    printf("[ LOAD ]");
    gotoxy(7, 15);
    printf("[ EXIT ]");

    cur_y = 13;
    cur_x = 6;

    while (1)
    {
        if (cur_y >= 13 && cur_y <= 15)
        {
            cursor();
            int input = 0;
            gotoxy(cur_x, cur_y);
            input = get_input();
            switch (input)
            {
            case top:
                cur_y--;
                if (cur_y < 13)
                    cur_y = 13;
                break;
            case down:
                cur_y++;
                if (cur_y > 15)
                    cur_y = 15;
                break;
            case enter:
                if (cur_y == 13)
                    return 0;
                else if (cur_y == 14)
                    return 1;
                else if (cur_y == 15)
                    return 2;
            }
        }

    }
}
void cursor()
{
    gotoxy(xxx, yyy);
    printf("  ");
    xxx = cur_x;
    yyy = cur_y;
    gotoxy(cur_x, cur_y);
    printf("☞");
}
void make_map()
{
    SetConsoleTextAttribute(handle, 0 + 14 * 16);
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (map[i][j] == 2)
                printf("┌");
            else if (map[i][j] == 1)
                printf("┬");
            else if (map[i][j] == 4)
                printf("├");
            else if (map[i][j] == 5)
                printf("└");
            else if (map[i][j] == 6)
                printf("┴");
            else if (map[i][j] == 7)
                printf("┘");
            else if (map[i][j] == 8)
                printf("┤");
            else if (map[i][j] == 3)
                printf("┐");
            else if (map[i][j] == 0)
                printf("┼");
            else if (map[i][j] == 9)
                printf("⊙");
            else if (map[i][j] == 'B')
            {
                SetConsoleTextAttribute(handle, 0 + 14 * 16);
                printf("●");
            }

            else if (map[i][j] == 'W')
            {
                SetConsoleTextAttribute(handle, 15 + 14 * 16);
                printf("●");
                SetConsoleTextAttribute(handle, 0 + 14 * 16);
            }


        }
        printf("\n");
    }
}
void move()
{
    int input = 0;
    gotoxy(cur_x, cur_y);
    input = get_input();
    switch (input)
    {
    case top:
        if (cur_y > 0)
        {
            cur_y--;
            if (cur_y < 0)
                cur_y = 0;
        }
        break;
    case down:
        if (cur_y < 18)
        {
            cur_y++;
            if (cur_y > 18)
                cur_y = 18;
        }
        break;
    case left:
        if (cur_x >= 0)
        {
            cur_x--;
            if (cur_x < 0)
                cur_x = 0;
        }
        break;
    case right:
        if (cur_x <= 18)
        {
            cur_x++;
            if (cur_x > 18)
                cur_x = 18;
        }
        break;
    case sp:
        setstone(cur_x, cur_y);
        
        break;
    case s:
        save();
        break;
    case l:
        load();
        break;

    }


}
void setstone(int _x, int _y)
{
    if (map[_y][_x] == 'B' || map[_y][_x] == 'W')
        return;
    gotoxy(_x, _y);
    if (turn == 'B')
    {
        turn = 'W';
        map[cur_y][cur_x] = 'B';
        SetConsoleTextAttribute(handle, 0 + 14 * 16);
        printf("●");
        score_b();
        //print_b();
    }
    else if (turn == 'W')
    {
        turn = 'B';
        map[cur_y][cur_x] = 'W';
        SetConsoleTextAttribute(handle, 15 + 14 * 16);
        printf("●");
        score_w();
        //print_w();
    }
}
int check()
{
    if (int n = check_horizon_B())
        return n;
    if (int n = check_horizon_W())
        return n;
    if (int n = check_vertical_B())
        return n;
    if (int n = check_vertical_W())
        return n;
    if (int n = check_diagnal_B_1())
        return n;
    if (int n = check_diagnal_B_2())
        return n;
    if (int n = check_diagnal_W_1())
        return n;
    if (int n = check_diagnal_W_2())
        return n;

}
int check_horizon_B()
{
    for (int i = 0; i < 19; i++)
    {
        if (map[cur_y][i] == 'B')
        {
            count_hor_B++;
            if (count_hor_B == 5)
            {
                return -1;
            }
        }
        else if (map[cur_y][i] == 'W' || map[cur_y][i] == 0)
        {
            count_hor_B = 0;
        }
    }
    return 0;
}
int check_horizon_W()
{

    for (int i = 0; i < 19; i++)
    {
        if (map[cur_y][i] == 'W')
        {
            count_hor_W++;
            if (count_hor_W == 5)
            {
                return 1;
            }
        }
        else if (map[cur_y][i] == 'B' || map[cur_y][i] == 0)
        {
            count_hor_W = 0;
        }
    }

    return 0;
}
int check_vertical_B()
{
    for (int i = 0; i < 19; i++)
    {
        if (map[i][cur_x] == 'B')
        {
            count_ver_B++;
            if (count_ver_B == 5)
            {
                return -1;
            }
        }
        else if (map[i][cur_x] == 'W' || map[i][cur_x] == 0)
        {
            count_ver_B = 0;
        }
    }
    return 0;
}
int check_vertical_W()
{
    for (int i = 0; i < 19; i++)
    {
        if (map[i][cur_x] == 'W')
        {
            count_ver_W++;
            if (count_ver_W == 5)
            {
                return 1;
            }
        }
        else if (map[i][cur_x] == 'B' || map[i][cur_x] == 0)
        {
            count_ver_W = 0;
        }
    }
    return 0;
}
int check_diagnal_B_1()
{
    count_dia_B_1 = 0;
    if (map[cur_y][cur_x] == 'B')
    {
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y + i][cur_x - i] == 'B')
            {
                count_dia_B_1++;
            }
            else if (map[cur_y + i][cur_x - i] != 'B')
                break;
        }
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y - i][cur_x + i] == 'B')
            {
                count_dia_B_1++;
            }
            else if (map[cur_y - i][cur_x + i] != 'B')
                break;
        }
    }

    if (count_dia_B_1 == 4)
    {
        return -1;
    }
    return 0;
}
int check_diagnal_B_2()
{
    count_dia_B_2 = 0;
    if (map[cur_y][cur_x] == 'B')
    {
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y - i][cur_x - i] == 'B')
            {
                count_dia_B_2++;
            }
            else if (map[cur_y - i][cur_x - i] != 'B')
                break;
        }
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y + i][cur_x + i] == 'B')
            {
                count_dia_B_2++;
            }
            else if (map[cur_y + i][cur_x + i] != 'B')
                break;
        }
    }

    if (count_dia_B_2 == 4)
    {
        return -1;
    }
    return 0;
}
int check_diagnal_W_1()
{
    count_dia_W_1 = 0;
    if (map[cur_y][cur_x] == 'W')
    {
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y - i][cur_x - i] == 'W')
            {
                count_dia_W_1++;
            }
            else if (map[cur_y - i][cur_x - i] != 'W')
                break;
        }
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y + i][cur_x + i] == 'W')
            {
                count_dia_W_1++;
            }
            else if (map[cur_y + i][cur_x + i] != 'W')
                break;
        }
    }

    if (count_dia_W_1 == 4)
    {
        return 1;
    }
    return 0;
}
int check_diagnal_W_2()
{
    count_dia_W_2 = 0;
    if (map[cur_y][cur_x] == 'W')
    {
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y + i][cur_x - i] == 'W')
            {
                count_dia_W_2++;
            }
            else if (map[cur_y + i][cur_x - i] != 'W')
                break;
        }
        for (int i = 1; i < 5; i++)
        {
            if (map[cur_y - i][cur_x + i] == 'W')
            {
                count_dia_W_2++;
            }
            else if (map[cur_y - i][cur_x + i] != 'W')
                break;
        }
    }

    if (count_dia_W_2 == 4)
    {
        return 1;
    }
    return 0;
}
void save()
{
    FILE* fp = fopen("Myfile.txt", "w");
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
            fprintf(fp, "%d ", map[i][j]);
        fprintf(fp, "\n");
    }
    fprintf(fp, "%d", turn);                    //다음턴저장
    fclose(fp);

}
void load()
{
    FILE *fp = fopen("Myfile.txt", "r");
    int buffer[19][19];
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
            fscanf(fp, "%d", &buffer[i][j]);

    }
    fscanf(fp, "%d", &turn);
    fclose(fp);

    SetConsoleTextAttribute(handle, 0);
    system("cls");


    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
            map[i][j] = buffer[i][j];
    }
    make_map();

}
/////////////////////////////////////    AI     /////////////////////////
void score_w()
{
    if (map[cur_y][cur_x] == 'W')
    {
        add_w[cur_y][cur_x] += 10;            //돌
        add_w[cur_y - 1][cur_x]++;            //세로
        if (map[cur_y - 1][cur_x] == 'B')
        {
            add_w[cur_y - 1][cur_x]--;        //다시 원상복귀
            add_w[cur_y - 2][cur_x] --;
            add_w[cur_y - 2][cur_x - 1] --;
            add_w[cur_y - 2][cur_x + 1] --;
        }
        add_w[cur_y + 1][cur_x]++;
        if (map[cur_y + 1][cur_x] == 'B')
        {
            add_w[cur_y + 1][cur_x]--;        //다시 원상복귀
            add_w[cur_y + 2][cur_x] --;
            add_w[cur_y + 2][cur_x - 1] --;
            add_w[cur_y + 2][cur_x + 1] --;
        }

        add_w[cur_y][cur_x - 1]++;            //가로
        if (map[cur_y][cur_x - 1] == 'B')
        {
            add_w[cur_y][cur_x - 1]--;        //다시 원상복귀
            add_w[cur_y][cur_x - 2] --;
            add_w[cur_y - 1][cur_x - 2] --;
            add_w[cur_y + 1][cur_x - 2] --;
        }
        add_w[cur_y][cur_x + 1]++;
        if (map[cur_y][cur_x + 1] == 'B')
        {
            add_w[cur_y][cur_x + 1]--;        //다시 원상복귀
            add_w[cur_y][cur_x + 2] --;
            add_w[cur_y - 1][cur_x + 2] --;
            add_w[cur_y + 1][cur_x + 2] --;
        }

        add_w[cur_y - 1][cur_x - 1]++;        //대각
        if (map[cur_y - 1][cur_x - 1] == 'B')
        {
            add_w[cur_y - 1][cur_x - 1]--;        //다시 원상복귀
            add_w[cur_y - 2][cur_x] --;
            add_w[cur_y - 2][cur_x - 1] --;
            add_w[cur_y - 2][cur_x - 2] --;
            add_w[cur_y - 1][cur_x - 2] --;
            add_w[cur_y][cur_x - 2] --;
        }
        add_w[cur_y + 1][cur_x + 1]++;
        if (map[cur_y + 1][cur_x + 1] == 'B')
        {
            add_w[cur_y + 1][cur_x + 1]--;        //다시 원상복귀
            add_w[cur_y + 2][cur_x] --;
            add_w[cur_y + 2][cur_x + 1] --;
            add_w[cur_y + 2][cur_x + 2] --;
            add_w[cur_y + 1][cur_x + 2] --;
            add_w[cur_y][cur_x + 2] --;
        }

        add_w[cur_y - 1][cur_x + 1]++;        //역대각
        if (map[cur_y - 1][cur_x + 1] == 'B')
        {
            add_w[cur_y - 1][cur_x + 1]--;        //다시 원상복귀
            add_w[cur_y - 2][cur_x] --;
            add_w[cur_y - 2][cur_x + 1] --;
            add_w[cur_y - 2][cur_x + 2] --;
            add_w[cur_y - 1][cur_x + 2] --;
            add_w[cur_y][cur_x + 2] --;
        }
        add_w[cur_y + 1][cur_x - 1]++;
        if (map[cur_y + 1][cur_x - 1] == 'B')
        {
            add_w[cur_y + 1][cur_x + 1]--;        //다시 원상복귀
            add_w[cur_y + 2][cur_x] --;
            add_w[cur_y + 2][cur_x - 1] --;
            add_w[cur_y + 2][cur_x - 2] --;
            add_w[cur_y + 1][cur_x - 2] --;
            add_w[cur_y][cur_x - 2] --;
        }

        threestone_W();
    }
    
}
void score_b()
{
    if (map[cur_y][cur_x] == 'B')
    {
        add_b[cur_y][cur_x] += 10;            //돌
        add_b[cur_y - 1][cur_x]++;            //세로
        if (map[cur_y - 1][cur_x] == 'W')
        {
            add_b[cur_y - 1][cur_x]--;        //다시 원상복귀
            add_b[cur_y - 2][cur_x] --;
            add_b[cur_y - 2][cur_x - 1] --;
            add_b[cur_y - 2][cur_x + 1] --;
        }
        add_b[cur_y + 1][cur_x]++;
        if (map[cur_y + 1][cur_x] == 'W')
        {
            add_b[cur_y + 1][cur_x]--;        //다시 원상복귀
            add_b[cur_y + 2][cur_x] --;
            add_b[cur_y + 2][cur_x - 1] --;
            add_b[cur_y + 2][cur_x + 1] --;
        }

        add_b[cur_y][cur_x - 1]++;            //가로
        if (map[cur_y][cur_x - 1] == 'W')
        {
            add_b[cur_y][cur_x - 1]--;        //다시 원상복귀
            add_b[cur_y][cur_x - 2] --;
            add_b[cur_y - 1][cur_x - 2] --;
            add_b[cur_y + 1][cur_x - 2] --;
        }
        add_b[cur_y][cur_x + 1]++;
        if (map[cur_y][cur_x + 1] == 'W')
        {
            add_b[cur_y][cur_x + 1]--;        //다시 원상복귀
            add_b[cur_y][cur_x + 2] --;
            add_b[cur_y - 1][cur_x + 2] --;
            add_b[cur_y + 1][cur_x + 2] --;
        }

        add_b[cur_y - 1][cur_x - 1]++;        //대각
        if (map[cur_y - 1][cur_x - 1] == 'W')
        {
            add_b[cur_y - 1][cur_x - 1]--;        //다시 원상복귀
            add_b[cur_y - 2][cur_x] --;
            add_b[cur_y - 2][cur_x - 1] --;
            add_b[cur_y - 2][cur_x - 2] --;
            add_b[cur_y - 1][cur_x - 2] --;
            add_b[cur_y][cur_x - 2] --;
        }
        add_b[cur_y + 1][cur_x + 1]++;
        if (map[cur_y + 1][cur_x + 1] == 'W')
        {
            add_b[cur_y + 1][cur_x + 1]--;        //다시 원상복귀
            add_b[cur_y + 2][cur_x] --;
            add_b[cur_y + 2][cur_x + 1] --;
            add_b[cur_y + 2][cur_x + 2] --;
            add_b[cur_y + 1][cur_x + 2] --;
            add_b[cur_y][cur_x + 2] --;
        }

        add_b[cur_y - 1][cur_x + 1]++;        //역대각
        if (map[cur_y - 1][cur_x + 1] == 'W')
        {
            add_b[cur_y - 1][cur_x + 1]--;        //다시 원상복귀
            add_b[cur_y - 2][cur_x] --;
            add_b[cur_y - 2][cur_x + 1] --;
            add_b[cur_y - 2][cur_x + 2] --;
            add_b[cur_y - 1][cur_x + 2] --;
            add_b[cur_y][cur_x + 2] --;
        }
        add_b[cur_y + 1][cur_x - 1]++;
        if (map[cur_y + 1][cur_x - 1] == 'W')
        {
            add_b[cur_y + 1][cur_x + 1]--;        //다시 원상복귀
            add_b[cur_y + 2][cur_x] --;
            add_b[cur_y + 2][cur_x - 1] --;
            add_b[cur_y + 2][cur_x - 2] --;
            add_b[cur_y + 1][cur_x - 2] --;
            add_b[cur_y][cur_x - 2] --;
        }

        threestone_B();
    }
}




void threeB_hor()
{
    //돌이 연속 3개인 곳을 찾아 가중치 부여(가로방향)
    //흑돌
    for (int j = 0; j < 19; j++)
    {
        if (map[cur_y][j] == 'B')
        {
            thrstB++;
            if (thrstB == 3)
            {
                add_b[cur_y][j + 1] += 5;                       //세게돌 양쪽에 가중치부여
                add_b[cur_y][j - 3] += 5;
            }
        }
    }

}
void threeB_ver()
{
    for (int i = 0; i < 19; i++)
    {
        if (map[i][cur_x] == 'B')
        {
            thrstB++;
            if (thrstB == 3)
            {
                add_b[i + 1][cur_x] += 5;                       //가중치부여
                add_b[i - 3][cur_x] += 5;
            }
        }
        else if (map[i][cur_x] == 'W' || map[i][cur_x] == 0)
        {
            thrstB = 0;
        }
    }
}
void threeB_dia1()
{
   thrstB = 0;
   for (int i = 0; i < 19; i++)
   {
       for (int j = 0; j < 19; j++)
       {
           if (map[i][j] == 'B')
           {
               if (map[i + 1][j + 1] == 'B')
                   thrstB++;
               else if (map[i + 1][j + 1] != 'B')
                   thrstB = 0;

               if (map[i - 1][j - 1] == 'B')
                   thrstB++;
               else if (map[i - 1][j - 1] != 'B')
                   thrstB = 0;

               if (thrstB == 2)
               {
                   add_b[i + 2][j + 2] += 5;
                   add_b[i - 2][j - 2] += 5;
               }
           }
       }
   }
     
}
void threeB_dia2()
{
    thrstB = 0;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (map[i][j] == 'B')
            {
                if (map[i - 1][j + 1] == 'B')
                    thrstB++;
                else if (map[i - 1][j + 1] != 'B')
                    thrstB = 0;

                if (map[i + 1][j - 1] == 'B')
                    thrstB++;
                else if (map[i + 1][j - 1] != 'B')
                    thrstB = 0;

                if (thrstB == 2)
                {
                    add_b[i - 2][j + 2] += 5;
                    add_b[i + 2][j - 2] += 5;
                }
            }
        }
    }
}
void threestone_B()
{
    threeB_hor();
    threeB_ver();
    threeB_dia1();
    threeB_dia2();
}


void threeW_hor()
{
    //돌이 연속 3개인 곳을 찾아 가중치 부여(가로방향)
    //백돌
    for (int j = 0; j < 19; j++)
    {
        if (map[cur_y][j] == 'W')
        {
            thrstW++;
            if (thrstW == 3)
            {
                add_w[cur_y][j + 1] += 5;                       //세게돌 양쪽에 가중치부여
                add_w[cur_y][j - 3] += 5;
            }
        }
    }


}
void threeW_ver()
{
    for (int i = 0; i < 19; i++)
    {
        if (map[i][cur_x] == 'W')
        {
            thrstW++;
            if (thrstW == 3)
            {
                add_w[i + 1][cur_x] += 5;                       //가중치부여
                add_w[i - 3][cur_x] += 5;
            }
        }
        else if (map[i][cur_x] == 'W' || map[i][cur_x] == 0)
        {
            thrstW = 0;
        }
    }
}
void threeW_dia1()
{
    thrstW = 0;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (map[i][j] == 'W')
            {
                if (map[i + 1][j + 1] == 'W')
                    thrstW++;
                else if (map[i + 1][j + 1] != 'W')
                    thrstW = 0;

                if (map[i + 2][j + 2] == 'W')
                    thrstW++;
                else if (map[i + 2][j + 2] != 'W')
                    thrstW = 0;

                if (thrstW == 2)
                {
                    add_w[i + 3][j + 3] += 5;
                    add_w[i - 1][j - 1] += 5;
                }
            }
        }
    }
}
void threeW_dia2()
{
    thrstW = 0;
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 19; j++)
        {
            if (map[i][j] == 'W')
            {
                if (map[i - 1][j + 1] == 'W')
                    thrstW++;
                else if (map[i - 1][j + 1] != 'W')
                    thrstW = 0;

                if (map[i + 1][j - 1] == 'W')
                    thrstW++;
                else if (map[i + 1][j - 1] != 'W')
                    thrstW = 0;

                if (thrstW == 2)
                {
                    add_w[i - 2][j + 2] += 5;
                    add_w[i + 2][j - 2] += 5;
                }
            }
        }
    }
}
void threestone_W()
{
    threeW_hor();
    threeW_ver();
    threeW_dia1();
    threeW_dia2();
}


void fourstone()
{
    //돌이 연속 4개인 곳을 찾아 가중치 부여
}