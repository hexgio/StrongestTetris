#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <time.h>

/*游戏逻辑模块*/

#include <stdio.h>

///方块结构体
typedef struct{
    int x;
    int y;
    int shape;
    int status;
    int color;
}BLOCK;

//绘制游戏池边框
void windowPrint(int x,int y);

//游戏所有初始化
void gameInit();

//打印操作说明
void printInfo();
void printInfoStandard();
//打印分数等级
void printGradelevel(int num);

//游戏计时
void gameTime(clock_t start_time);

//打印方块
void printBlock(int x,int y,int shape,int status,int color);

//删除方块
void deleteBlock(int x,int y,int shape,int status);

//产生游戏的第一个方块
void startBlock();

//产生游戏的下一个方块
void nextBlock();

//拷贝方块
void copyBlock();

///方块下移
///返回值：标识方块是否到游戏池底部
int downBlock();

///方块左移
///无返回值
void leftBlock();


///方块右移
///无返回值
void rightBlock();

///方块方向改变
void changeStatusBlock();

///方块形状改变
void changeShapeBlock();

///方块炫彩效果
void coolColor();

///碰撞检测函数
int crash(int x,int y,int shape,int status);

///保存方块
void save();

///刷新游戏池
void updateGame();

///消行
void removeLine();

///暂停
void pause();

///方块直接落底
void bottomBlock();

///更改计时器
void setClock();

///消行检测
void lineClear();

///消行下移
void lineDown(int line);

///游戏结束动画
void printOver1();

///重新开始提示
void printFinish1();

///重新开始游戏
void againGame1();

///打印开始图案
void printStart(int x,int y);

///清除开始图案
void clearStart(int x,int y);

///动画效果 ->定时(边界控制)
void printAnimation();

//打开音乐文件
void openMusic();

//关闭音乐文件
void closeMusic();

#endif // GAME_H_INCLUDED
