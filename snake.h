#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <conio.h>


enum KeyDir{Up = 1, Down = 2, Left = 3, Right = 4, Enter = 5,};

// �˵�ѡ����Ϣ
const char start_game[] = "Start Game";
const char exit_game[]  = "Exit Game";

static COORD snake[1024];
static int snake_body_length = 0;
COORD food_pos;
static unsigned int food_refresh_time = 0;  // һ��ʱ����û��ʳ�ʳ���ٴ�ˢ��

static void gotoxy(int x, int y);       // ��λ����
int getkey(void);                        // ��ȡ��ֵ
void draw_wall(void);                    // ��ǽ
void draw_menu(void);
int select_menu(void);
void draw_init_snake(void);             // ��ʼ������
void generate_food_pos(int *posx, int *posy);       // �������ʳ������
void draw_init_food(void);                          // ��һ��ʳ��

#endif // SNAKE_H_INCLUDED
