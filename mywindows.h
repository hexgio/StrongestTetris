#ifndef MYWINDOWS_H_INCLUDED
#define MYWINDOWS_H_INCLUDED
//避免重定义错误，多个文件同时引用头文件，当程序进行时，容易发生重定义的情况
//头文件进行封装，其余文件可以快速调用，减少代码书写


/*系统调用模块*/
#include <windows.h>

//头文件函数声明
//初始化句柄
void initHandle();//小驼峰命名常用于函数和变量命名，大驼峰常用于类的命名

//设置颜色
void setColor(int color);

//设置光标位置
void setPos(int x,int y);

//隐藏光标
void hideCursor();

//提示undefine reference -> 头文件与源文件名称不对应

#endif // MYWINDOWS_H_INCLUDED
