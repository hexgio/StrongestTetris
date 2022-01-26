#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "mywindows.h"
#include <conio.h>

#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

void chooseMode(){
   if(kbhit()){
         mciSendString("close g",NULL,0,NULL);
        switch(getch()){
        case 49:
        case 97: gameInit(1);break;
        case 50:
        case 98: gameInit(2);break;
         case 51:
        case 99: gameInit(3);break;
        }
   }
}

void chooseMode2(){
    if(kbhit()){
             mciSendString("close g",NULL,0,NULL);
        switch(getch()){
        case 49:
        case 97: gameInit1(1);break;
        case 50:
        case 98: gameInit1(2);break;
         case 51:
        case 99: gameInit1(3);break;
        }
   }
}

int main()
{

    ///初始化句柄，必须放在最开始
    initHandle();
    ///开始动画
    mciSendString("open 俄罗斯方块进入音乐.mp3 alias g",NULL,0,NULL);
     mciSendString("play g repeat",NULL,0,NULL);
    printAnimation();

    if(kbhit()){
            getch();
        chooseWindow();

    }
    if(kbhit()){
        switch(getch()){
        case 49:
        case 97: chooseWindow2();chooseMode();break;
        case 50:
        case 98: chooseWindow3();chooseMode2();break;

        }
    }

   return 0;
}
