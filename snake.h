#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <conio.h>


enum KeyDir{Up = 1, Down = 2, Left = 3, Right = 4, Enter = 5,};

// 菜单选项信息
const char start_game[] = "Start Game";
const char exit_game[]  = "Exit Game";

static COORD snake[1024];
static int snake_body_length = 0;
COORD food_pos;
static unsigned int food_refresh_time = 0;  // 一段时间内没吃食物，食物再次刷新

static void gotoxy(int x, int y);       // 定位坐标
int getkey(void);                        // 获取键值
void draw_wall(void);                    // 画墙
void draw_menu(void);
int select_menu(void);
void draw_init_snake(void);             // 初始化蛇身
void generate_food_pos(int *posx, int *posy);       // 随机产生食物坐标
void draw_init_food(void);                          // 第一个食物

#endif // SNAKE_H_INCLUDED
