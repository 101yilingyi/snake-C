#include "snake.h"


#define WIDTH 60
#define HEIGHT 20

COORD start_game_pos = {.X = WIDTH/2 - strlen(start_game)/2, .Y = HEIGHT/2};
COORD  exit_game_pos = {.X = WIDTH/2 - strlen(start_game)/2, .Y = HEIGHT/2 + 1};



int main(void)
{
    draw_wall();
    draw_menu();
    //select_menu();
    if(select_menu() == 1) return 1;
    draw_wall();

    return 0;
}



static void gotoxy(int x, int y)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {.X = x, .Y = y};
    SetConsoleCursorPosition(handle, pos);
}

int getkey(void)
{
    int kb = kbhit();    // 非阻塞等待
    if(kb == 0) return 0;
    int key = getch();
    if(key == 224)
        key = getch();
    if(key=='w' || key=='W' || key==72) // Turn up
        return Up;   // Up
    else if(key=='s' || key=='S' || key==80)    // Turn down
        return Down;
    else if(key=='a' || key=='A' || key==75)    // Turn left
        return Left;
    else if(key=='d' || key=='D' || key==77)    // Turn right
        return Right;
    else if(key == 13)
        return Enter;

    return 0;
}


void draw_wall(void)
{
    gotoxy(0, 0);
    for(int y=0; y<=HEIGHT; y++)
    {
        for(int x=0; x<=WIDTH; x++)
        {
            if(x==0 || x==WIDTH)
                putchar('#');
            else if(y==0 || y==HEIGHT)
                putchar('#');
            else
                putchar(' ');
        }
        puts("");
    }
}

void draw_menu(void)
{
    gotoxy(start_game_pos.X, start_game_pos.Y);
    puts(start_game);
    gotoxy(exit_game_pos.X, exit_game_pos.Y);
    puts(exit_game);
}


int select_menu(void)
{
    COORD select_pos = start_game_pos;
    gotoxy(select_pos.X - 2, select_pos.Y);
    putchar('>');

    while(1)
    {
        int select = getkey();
        if(select == Up || select == Down)  // 按下上下键
        {
            if(select_pos.Y == start_game_pos.Y){
                gotoxy(start_game_pos.X - 2, start_game_pos.Y);
                putchar(' ');
                gotoxy(exit_game_pos.X - 2, exit_game_pos.Y);
                putchar('>');
                select_pos = exit_game_pos;
            }
            else{
                gotoxy(exit_game_pos.X - 2, exit_game_pos.Y);
                putchar(' ');
                gotoxy(start_game_pos.X - 2, start_game_pos.Y);
                putchar('>');
                select_pos = start_game_pos;
            }
        }
        if(select == Enter)
        {
            if(select_pos.Y == start_game_pos.Y) return 0;
            else return 1;
        }
    }
}
