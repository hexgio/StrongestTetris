//游戏逻辑
#include "game.h"
#include "data.h"
#include "mywindows.h"
#include <conio.h>

#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

int k = 0;
int grade = 0;  //分数
int level = 1;    //等级
float speed = 0.45;
int l1=0,k;
BLOCK cur_block;   ///当前方块
BLOCK next_block;  ///下一个方块

void windowPrint1(int x,int y){
    //绘制游戏池边框
    int i,j;  //用来遍历二维数组
    for(i=0;i<25;i++){
        for(j=0;j<26;j++){
            if(windowShape[i][j] == 1){
                setColor(0xc0);
                setPos(x+j,y+i);  //x是列，y是行
                printf("%2s","");  // <-->  printf("  ");
            }
        }
    }

}

//操作规则框架
void printInfo1(){
    setColor(0x01);
    setPos(31,9);
    printf("操作规则");
    setPos(31,10);
    printf("按 a 或 A 左移");
    setPos(31,11);
    printf("按 d 或 D 右移");
    setPos(31,12);
    printf("按 s 或 S 下移");
    setPos(31,13);
    printf("按 w 或 W 变方向");
    setPos(31,14);
    printf("按 回车 直接下落");
    setPos(31,15);
    printf("按 空格 暂停");
    setPos(31,16);
    printf("按 q 加速");
    setPos(31,17);
    printf("按 e 减速");
    setPos(31,18);
    printf("按 z 变形");
    setPos(31,19);
    printf("按 x 进入炫彩模式");
}


void printGradeLevel(int num){
    switch(num){
        case 1:
            grade+=10; break;
        case 2:
            grade+=30; break;
        case 3:
            grade+=50; break;
        case 4:
            grade+=80; break;
    }

    if(grade < 100){
        level = 1;
    }
    else if(grade >= 100 && grade < 300){
        level =2;
    }

    setColor(0x09);
    setPos(3,6);
    printf("分数:%d",grade);

    setPos(3,7);
    printf("等级:%d",level);
}

void gameTime(clock_t start_time){
    setColor(0x0b);
    setPos(3,3);
    printf("本次游戏已运行 %d s",(clock()-start_time)/CLOCKS_PER_SEC);
}

void printBlock(int x,int y,int shape,int status,int color){
    int i,j;
    for(i = 0;i<4;i++){
        for(j = 0;j<4;j++){
            if(block[shape][status][i][j] == 1){
                setColor(color);
                setPos(x+j,y+i);
                printf("■");
            }
        }
    }
}

/**结构体：是一种集合，可以包含多个变量货值数组（成员）
    模板：
        struct 结构体名{
            结构体包含的变量或者数组;
        }; -->分号不能少
1.先定义结构体类型，在定义结构体变量
    struct stu{
        char *name;
        int age;
        float score;
    };
    struct stu stu1,stu2; //stu1,stu2是结构体变量
2.定义结构体类型的同时定义结构体变量
    struct stu{
        char *name;
        int age;
        float score;
    }stu1,stu2;
    struct stu stu3,stu4;
3.直接定义结构体变量
    struct{
        char *name;
        int age;
        float score;
    }stu1,stu2;
    没有结构体名称，后面无法定义结构体变量。

    typedef struct stu{
        char *name;
        int age;
        float score;
    }STU;
    STU stu1,stu2;
**/

void deleteBlock(int x,int y,int shape,int status){
    int i,j;
    for(i = 0;i<4;i++){
        for(j = 0;j<4;j++){
            if(block[shape][status][i][j] == 1){
                setPos(x+j,y+i);
                printf("  ");
            }
        }
    }
}

void startBlock(){
    ///第一个方块：形状/形态/颜色->随机 位置(x,y)固定的
    ///初始化cur_block
    ///设置随机数种子（时间永远不一样）
    srand((unsigned)time(NULL));
    cur_block.x = 22;
    cur_block.y = 1;
    cur_block.shape = rand()%7;
    cur_block.status = rand()%4;
    cur_block.color = rand()%0x10;
    ///如果随机产生的颜色是黑色，把颜色设置成白色
    if(cur_block.color == 0x00){
        cur_block.color = 0x0f;
    }
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);

}

void nextBlock(){
    ///形状/形态/颜色->随机 位置(x,y)固定
    ///初始化next_block值
    deleteBlock(next_block.x,next_block.y,next_block.shape,next_block.status);
    next_block.x = 35;
    next_block.y = 2;
    next_block.shape = rand()%7;
    next_block.status = rand()%4;
    next_block.color = rand()%0x10;
    ///如果随机产生的颜色是黑色，把颜色设置成白色
    if(next_block.color == 0x00){
        next_block.color = 0x0f;
    }
    printBlock(next_block.x,next_block.y,next_block.shape,next_block.status,next_block.color);
}

void copyBlock(){
    ///当前方块 = 下一个方块，并产生新的“下一个方块”
    cur_block = next_block;
    cur_block.x = 22;
    cur_block.y = 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    nextBlock();
}

int downBlock(){
    //原理：删除正在显示的图层，纵坐标加一，重新打印

    if(l1%2!=0){
            coolColor();
           }
    if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -1){
     ///发生碰撞：方块落到游戏池底部
            ///产生新的方块：下一个方块值 -> 当前正在下落的方块，重新产生下一个方块
            ///保存方块->检测消行->打印游戏池->产生新方块
            save();
//            lineClear();
            removeLine();
            updateGame();

            copyBlock();
            return -1;
    }

    else if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -2){

///游戏结束
            return -2;
    }

    else{
         deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.y += 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    return 1;
    }
}

void leftBlock(){
    //原理：删除正在显示的图层，横坐标减一，重新打印
    ///发生碰撞：方块碰到左边框，无法继续向左移动，向下移动
    if(crash(cur_block.x-1,cur_block.y,cur_block.shape,cur_block.status) != -1){
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.x -= 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    }

}

void rightBlock(){
    //原理：删除正在显示的图层，横坐标加一，重新打印
    if(crash(cur_block.x+1,cur_block.y,cur_block.shape,cur_block.status) != -1){
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    cur_block.x += 1;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    }

}

void changeStatusBlock(){
     if(crash(cur_block.x,cur_block.y,cur_block.shape,(cur_block.status+1)%4) != -1){
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    if(cur_block.status==3)cur_block.status = 0;
    else cur_block.status++;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
     }
    //cur_block.status = (cur_block.status+1)%4;
}

void changeShapeBlock(){
    if(crash(cur_block.x,cur_block.y,(cur_block.shape+1)%7,cur_block.status) != -1){
    deleteBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status);
    if(cur_block.shape==6)cur_block.shape = 0;
    else cur_block.shape++;
    printBlock(cur_block.x,cur_block.y,cur_block.shape,cur_block.status,cur_block.color);
    }
}

void coolColor(){
    int i;

           cur_block.color = rand()%0x10;
    ///如果随机产生的颜色是黑色，把颜色设置成白色
    if(cur_block.color == 0x00){
        cur_block.color = 0x0f;
    }
    }

    //碰撞检测基于下一个位置的检测,数组与界面坐标的对应
int crash(int x,int y,int shape,int status){
    int i,j;
    for(i = 0;i<4;i++){
        for(j = 0;j<4;j++){
            if(block[shape][status][i][j] == 1){
                if(windowShape[y+i][x+j-15] == 1){
                      ///发生碰撞
                      if(cur_block.x == 22 && cur_block.y == 1){
                        ///游戏结束
                        return -2;
                      }
                      ///方块落到游戏池底部，发生碰撞


                    return -1;
                }

            }
        }

    }
    return 0;
}

void save(){
    ///根据方块在界面上的坐标，把坐标对应到游戏池下标的对应位置
    ///方块为1的保存到windowShape数组
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(block[cur_block.shape][cur_block.status][i][j] == 1){
                windowShape[i+cur_block.y][j+cur_block.x-15] = 1;
            }

        }
    }
}

void updateGame(){
    int i,j;
    for(i=23;i>0;i--){
        for(j=1;j<15;j++){
                if(windowShape[i][j] == 1){
            setColor(0x0e);
            setPos(15+j,i);
            printf("■");
                }else{
                setColor(0x00);
                setPos(15+j,i);
                printf("  ");
                }
        }
    }
}

void removeLine(){
    int i,j,m,n;
    int number = 0;
    for(i=23;i>1;i--){
            int total = 0;
        for(j=1;j<15;j++){
            if(windowShape[i][j] == 1){
              total++;
            }
            if(total == 14){
                    number++;
                for(m = i;m>1;m--){   ///m>1,保证边界不被下移
        for(n=1;n<15;n++){
            windowShape[m][n] = windowShape[m-1][n];
        }
    }
        i++;
        ///统计一次消了几行

                }

            }

        }
        printGradeLevel(number);
    }



//void lineClear(){
//    ///遍历windowShape,判断是否有满行：这行所有值加起来为14
//    int i,j;
//    for(i=23;i>0;i--){
//          int total = 0;
//        for(j=1;j<15;j++){
//            total += windowShape[i][j];
//        }
//        if(total == 14){
//            lineDown(i);
//            i += 1; //保证能对所有行进行检测
//        }
//    }
//
//}
//
//void lineDown(int line){
//    ///从第line行开始，i= i-1
//    int i,j;
//    for(i = line;i>1;i--){   ///i>1,保证边界不被下移
//        for(j=1;j<15;j++){
//            windowShape[i][j] = windowShape[i-1][j];
//        }
//    }
//}

void pause(){
    clock_t time1;
    time1 = clock();
    ///暂停，程序去执行另一件事情
    while(1){
        if(getch() == 32){
            break;
        }
    }
    k +=  (clock()-time1)/CLOCKS_PER_SEC;
}

void bottomBlock(){
    while(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) != -1&&crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) != -2){

    cur_block.y += 1;


    }

        if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -1){
            ///发生碰撞：方块落到游戏池底部
            ///产生新的方块：下一个方块值 -> 当前正在下落的方块，重新产生下一个方块
            save();
            removeLine();
//            lineClear();
            updateGame();
            copyBlock();

    }
    else if(crash(cur_block.x,cur_block.y+1,cur_block.shape,cur_block.status) == -2){
        ///游戏结束
        printOver();
    }
}

void printOver1(){
    int i,j;
    for(i=23;i>0;i--){
        for(j=1;j<15;j++){
            setColor(0x76);
            setPos(j+15,i);
            printf("★");
            Sleep(5);
        }
    }

}

void printFinish1(){
    setColor(0x10);
    setPos(21,10);
    printf("游戏结束！ ");
    setPos(18,11);
    printf("按Y重新开始 ");
    setPos(24,11);
    printf("按N结束游戏");

    ///检测用户按键
    switch(getch()){
    {
        case 'y':
        case 'Y':
            againGame();break;
        case 'n':
        case 'N':
            mciSendString(TEXT("stop a"),NULL,0,NULL);break;
        default:
            printFinish();break;
    }
    }
}

void againGame1(){
    ///重置分数/等级/游戏池数据->开始游戏
    level = 1;
    grade =0;
    int i,j;
    for(i=1;i<24;i++){
        for(j=1;j<15;j++){
            windowShape[i][j] = 0;
        }
    }
    setColor(0x00);
    system("cls");  ///清屏
    gameInit();
}

void printStart(int x,int y){
     //随机产生颜色
    int color = rand()%0x10;
    //处理黑色的情况
    if(color == 0x00)
    {
        color = 0x0f;
    }

    setColor(color);
    setPos(x,y);
    printf("■■■■■  ■■■■■  ■■■■■  ■■■■  ■■■  ■■■■");
    setPos(x,y+1);
    printf("    ■      ■              ■      ■    ■    ■    ■");
    setPos(x,y+2);
    printf("    ■      ■■■■        ■      ■■■      ■      ■■■");
    setPos(x,y+3);
    printf("    ■      ■              ■      ■  ■      ■          ■");
    setPos(x,y+4);
    printf("    ■      ■■■■■      ■      ■    ■  ■■■  ■■■");

    setPos(25,14);
    printf("按任意键开始游戏!");
    }

void deleteStart(int x,int y){
    int i,j;
    for(i = y;i<=y+4;i++){
        for(j = x;j<=x+33;j++){
            setPos(j,i);
            printf("%2s","");
        }
    }

}

void printAnimation(){
    clock_t time1,time2;
    time1 = clock();
    int x = 5;
    printStart(x,5);
    while(1){
        time2 = clock();
    if(time2 - time1 > 150) {  ///时间间隔300毫秒
        time1 = time2;
        deleteStart(x,5);
        printStart(++x,5);
        if(25 == x){
            deleteStart(x,5);
            x=5;
        }
    }
    ///按任意键退出
    if(kbhit()){
        break;
    }
    }
    system("cls");
}

void gameInit(){
    ///初始化句柄，必须放在最开始
    initHandle();
    ///打开音乐文件
    mciSendString("open E:\\20200705\\bin\\Debug\\res\\俄罗斯方块游戏背 景音乐.mp3 alias a",NULL,0,NULL);//alias a:为这个路径起一个别名 a
    ///播放音乐
    mciSendString(TEXT("play a"),NULL,0,NULL);
    ///开始动画
    printAnimation();
    windowPrint1(15,0);
    printInfo();
    printGradeLevel(0);

    ///游戏开始时间
    clock_t startTime = clock();
    gameTime(startTime);


    ///定时器
    clock_t time1,time2;
    time1 = clock();


    //打印其余边框
    setPos(1,24);
    setColor(0x80);
    printf("                            ");
    setColor(0x40);
    setPos(1,0);
    printf("                            ");
    int i;

    startBlock();
    nextBlock();
    setColor(0x30);
    for(i=0;i<25;i++){
        setPos(1,i);
        printf("  ");
    }
    setPos(40,25);


    while(1){
        //按键驱动
        ///检测是否有按键按下
        if(kbhit()){
            switch(getch()){
            case 'w':
            case 'W':
            case 72:
               changeStatusBlock();break;
            case 'a':
            case 'A':
            case 75:
                leftBlock();break;
            case 'd':
            case 'D':
            case 77:
                rightBlock();break;
            case 's':
            case 'S':
            case 80:
                downBlock();break;
            case 'q':
            case 'Q':
                speed-=0.01;break;
            case 'e':
            case 'E':
                speed+=0.01;break;
            case 'z':
            case 'Z':
                changeShapeBlock();break;
            case 'x':
            case 'X':
                l1++;break;
            case 32:
                pause();break;
            case 13:
                bottomBlock();break;
            }
        }

        time2 = clock();

        ///每0.45秒下落一次
        if((time2-time1)/CLOCKS_PER_SEC > speed){
            gameTime(startTime + k*CLOCKS_PER_SEC);
            if(downBlock() == -2) break;

            time1 = time2;


    }

}
printOver();
printFinish();
}
