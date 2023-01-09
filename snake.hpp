#ifndef SNAKE_HPP
#define SNAKE_HPP

#define column 75
#define row 15

enum dirction {STOPE, LEFT, RIGHT, UP, DOWN };//جهت نشان دادن وضعیت مار استفاده می شود

class snake
{
private:
    dirction dir = STOPE;//وضعیت حرکت مار را نگه می دارد
    bool gameover = false;//اگر  true شود بازی خاتمه می یابد
    int len = 0;//طول بدن مار است

    int x_len_snake[1000];// x های بدن مار را نگه می دارد
    int y_len_snake[1000];// y های بدن مار را نگه می دارد
    int x_head_snake = column / 2;// x سر مار را نگه می دارد
    int y_head_snake = row / 2;// y سر مار را نگه می دارد
    int x_food;// x محل غذا را نگه می دارد
    int y_food;// y محل غذا را نگه می دارد
public:
    snake();
    void delay();
    void disply();
    void food();
    bool eat();
    void move();
    void check();
    void run();
};

#endif