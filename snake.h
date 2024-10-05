#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <conio.h>


enum KeyDir{Up = 1, Down = 2, Left = 3, Right = 4, Enter = 5,};

// 菜单选项信息
const char start_game[] = "Start Game";
const char exit_game[]  = "Exit Game";


static void gotoxy(int x, int y);       // 定位坐标
int getkey(void);                        // 获取键值
void draw_wall(void);                    // 画墙
void draw_menu(void);
int select_menu(void);
#endif // SNAKE_H_INCLUDED
