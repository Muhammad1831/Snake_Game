#include <iostream>
#include <vector>
#include <time.h>
#include <conio.h>
#include "snake.hpp"
using namespace std;

#define column 75
#define row 15

snake::snake() { food(); }

void snake::delay()//جهت تنظیم سرعت مار استفاده می شود
{
    clock_t start = clock();
    while (clock() < start + 150);
}

void snake::disply()// صفحه بازی را نمایش می دهد
{
    system("cls");
    for (size_t i = 0; i < column; i++)
    {
        cout << '#';
    }
    cout << endl;
    for (size_t i = 1; i <= row - 2; i++)
    {
        cout << '#';
        for (size_t j = 1; j <= column - 2; j++)
        {
            bool status = false;                           //در صورت برابر بودن مختصات
            if ((i == y_head_snake) && (j == x_head_snake))//(i,j) با (x_head_snake, y_head_snake)
            {                                              //سر مار را چاپ می کند
                cout << "\033[1;33m" << static_cast<char>(254) << "\033[0m";
                status = true;
            }
                                                    //در صورت برابر بودن مختصات 
            else if ((i == y_food) && (j == x_food))//(i,j) با (x_food, y_food)
            {                                       //غذا را چاپ می کند
                cout << "\033[1;31m" << 'O' << "\033[0m";
                status = true;
            }
            
            for (size_t k = 0; k < len; k++)
            {                                                      //در صورت برابر بودن مختصات
                if ((i == y_len_snake[k]) && (j == x_len_snake[k]))//(i,j) با (x_len_snake, y_len_snake)
                {                                                  //بدن مار را چاپ می کند
                    cout << "\033[1;33m" << static_cast<char>(254) << "\033[0m";
                    status = true;
                    break;
                }
            }
            
            if (!status)
            {
                cout << ' ';
            }    
        }
        cout << '#' << endl;
    }
    for (size_t i = 0; i < column; i++)
    {
        cout << '#';
    }
    delay();
}

void snake::food()// محل قرار گیری غذا را به صورت رندوم انتخاب می کند
{
    srand((unsigned)time(NULL));
    x_food = rand() % (column - 2) + 1;
    y_food = rand() % (row - 2) + 1;
}

bool snake::eat()//اگر غذا خورده شود یک واحد به طول مار اضافه می شود 
{
    if ((x_head_snake == x_food) && (y_head_snake == y_food))
    {
        len++;
        x_len_snake[len] = x_food;
        y_len_snake[len] = y_food;
        
        return true;
    }
    return false;
}

void snake::move()//کار حرکت به جهت های مختلف را بر عهده دارد
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'A':
        case 'a':

            dir = LEFT;
            break;
        case 'D':
        case 'd':

            dir = RIGHT;
            break;
        case 'S':
        case 's':

            dir = DOWN;
            break;
        case 'W':
        case 'w':

            dir = UP;
            break;
        }
    }


    for (size_t i = len - 1; (len != 0) && (i > 0); --i)//این حلقه مار را یک واحد به جهت وارد شده انتقال می دهد در واقع بدن مار را به دنبال سر ان به حرکت در می اورد
    {
        x_len_snake[i] = x_len_snake[i - 1];
        y_len_snake[i] = y_len_snake[i - 1];

    }
    x_len_snake[0] = x_head_snake;
    y_len_snake[0] = y_head_snake;

    switch (dir)
    {
    case LEFT:
        (x_head_snake)--;
        break;
    case RIGHT:
        (x_head_snake)++;
        break;
    case DOWN:
        (y_head_snake)++;
        break;
    case UP:
        (y_head_snake)--;
        break;
    }
}

void snake::check()//اگر مار خودش را بخورد gmaeover true میشود و از بازی خارج می شود
{                  //همچنین اگر مار به سمت دیوار ها برود از طرف دیگر در می آید
    for (size_t i = 0; i < len; i++)
    {
        if ((x_head_snake == x_len_snake[i]) && (y_head_snake == y_len_snake[i]))
        {
            gameover = true;
        }
    }

    if ((x_head_snake == 0)) {x_head_snake = column - 1;}
    if ((x_head_snake == column)) {x_head_snake = 0;}
    if ((y_head_snake == -1)) {y_head_snake = row - 1;}
    if ((y_head_snake == row)) {y_head_snake = 0;}
}

void snake::run()//کنترل بازی را در دست دارد و تابع های مورد نظر را فراخوانی می کند
{
    while (!gameover)
    {
        disply();
        move();

        if (eat())
        {
            food();
        }

        check();
    }
}