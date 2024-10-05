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
    draw_init_snake();
    draw_init_food();

    int direction = Right;  // 初始方向
    while(1)
    {
        int new_dir = getkey();
        // 输入方向与蛇行进方向不同
        if(new_dir==0 || new_dir==Enter) ;
        else if(new_dir==Up && direction==Down) ;
        else if(new_dir==Down && direction==Up) ;
        else if(new_dir==Right && direction==Left) ;
        else if(new_dir==Left && direction==Right) ;
        else direction = new_dir;

        COORD pos;      // 新蛇头位置
        switch (direction){
        case Up:
            pos.X = snake[0].X;
            pos.Y = snake[0].Y - 1;
            break;
        case Down:
            pos.X = snake[0].X;
            pos.Y = snake[0].Y + 1;
            break;
        case Right:
            pos.X = snake[0].X + 1;
            pos.Y = snake[0].Y;
            break;
        case Left:
            pos.X = snake[0].X - 1;
            pos.Y = snake[0].Y;
            break;
        default:
            break;
        }


//        COORD tail_pos;        // 保存尾巴位置
//        tail_pos.X = snake[snake_body_length].X;
//        tail_pos.Y = snake[snake_body_length].Y;
//        tail_pos = snake[snake_body_length];


        // 移动
        gotoxy(snake[snake_body_length].X, snake[snake_body_length].Y);
        putchar(' ');
        for(int i=snake_body_length; i>0; i--)
        {
            snake[i].X = snake[i-1].X;
            snake[i].Y = snake[i-1].Y;
            gotoxy(snake[i].X, snake[i].Y);
            putchar('+');
        }
        snake[0].X = pos.X;
        snake[0].Y = pos.Y;
        gotoxy(snake[0].X, snake[0].Y);
        putchar('O');

        // 吃到食物
        if(pos.X==food_pos.X && pos.Y==food_pos.Y)
        {
            snake_body_length++;
            snake[snake_body_length] = snake[snake_body_length-1];
            gotoxy(snake[snake_body_length].X, snake[snake_body_length].Y);
            putchar('+');
            draw_init_food();
            food_refresh_time = 0;
        }

        // 判断蛇是否死亡
        if(pos.X ==0 || pos.X==WIDTH || pos.Y==0 || pos.Y==HEIGHT)  // 撞墙
        {
            gotoxy(0, HEIGHT+2);
            printf("Game Over!\r\n");
            return -1;
        }
        for(int i=snake_body_length; i>0; i--)          // 撞身体
        {
            if(pos.X==snake[i].X && pos.Y==snake[i].Y)
            {
                gotoxy(0, HEIGHT+2);
                printf("Game Over!\r\n");
                return -1;
            }
        }
        Sleep(200);
        food_refresh_time++;
        if(food_refresh_time == 50)
        {
            gotoxy(food_pos.X, food_pos.Y);
            putchar(' ');
            draw_init_food();
            food_refresh_time = 0;
        }
    }
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
                putchar('|');
            else if(y==0 || y==HEIGHT)
                putchar('-');
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

void draw_init_snake(void)
{
    snake[0].X = WIDTH/2;
    snake[0].Y = HEIGHT/2;
    gotoxy(snake[0].X, snake[0].Y);
    putchar('O');
    snake[1].X = WIDTH/2 - 1;
    snake[1].Y = HEIGHT/2;
    gotoxy(snake[1].X, snake[1].Y);
    putchar('+');
    snake_body_length = 1;
}

void generate_food_pos(int *posx, int *posy)
{
    while(1)
    {
        int is_useful = 1;
        int x = rand() % (WIDTH - 2) + 1;  // 防止食物生成在边框上
        int y = rand() % (HEIGHT - 2) + 1;
        for (int i = 0; i < snake_body_length; i++) {
            if (x == snake[i].X && y == snake[i].Y) {  // 判断食物与蛇是否重合
                is_useful = 0;
                break;
            }
        }
        if (is_useful) {
            *posx = x;
            *posy = y;
            break;
        }
    }
}

void draw_init_food(void)
{
    int x;
    int y;
    generate_food_pos(&x, &y);
    gotoxy(x, y);
    putchar('*');
    food_pos.X = x;
    food_pos.Y = y;
}


