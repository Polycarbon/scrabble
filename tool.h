#include<stdio.h>
#include"stdio.h"
#include"conio.h"
#include"windows.h"
#include"color.h"
#include"time.h"
void walk(int x,int y){
    COORD walk;
    walk.X =x;
    walk.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),walk);
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
