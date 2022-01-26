#include "mywindows.h"  //尖括号常用于引入系统头文件，双引号常用于引入自己定义的头文件   默认检索顺序不同

HANDLE handle;

//函数定义

void initHandle(){
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();//游戏启动后隐藏光标位置
    //
}

void setColor(int color){
    SetConsoleTextAttribute(handle,color);
}

void setPos(int x,int y){
    COORD coord = {x*2,y};    //字母abcd:一个字符，汉字：两个字符
    SetConsoleCursorPosition(handle,coord); //设置句柄位置
}

void hideCursor(){
    CONSOLE_CURSOR_INFO info;        //系统的结构体变量名字都是大写
    info.bVisible = FALSE;           //设置光标是否可见
    info.dwSize = 1;                 //设置光标宽度(1-100)
    SetConsoleCursorInfo(handle,&info);//指针取地址符
}
