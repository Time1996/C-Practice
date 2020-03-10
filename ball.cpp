#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//函数外全局变量定义
static int speed = 0;
int high,width;
int position_x,position_y;//小球坐标 
int ball_vx,ball_vy;//小球速度 
int blank_x,blank_y;//挡板中心坐标 
int radius;//挡板半径大小
int left,right;//挡板左右边界 
int ballnumber;//小球反弹次数 
int brick_x,brick_y;//砖块坐标 
int flag = 1;
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
    SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}

void HideCursor() // 用于隐藏光标
{
        CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // 第二个值为0表示隐藏光标
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup(){//数据初始化
	HideCursor();//隐藏光标 
	high = 20;
	width = 30;
	
	position_x = 5;
	position_y = width/2;
	ball_vx = 1;
	ball_vy = 1;
	blank_x = high-1;
	blank_y = width/2;
	radius = 5;
	left = blank_y - radius;
	right = blank_y + radius;
	brick_x = 0;
	brick_y = width/2;
} 
void show(){//显示画面
	gotoxy(0,0);
	for(int i = 0; i <= high; i++){
		for(int j = 0; j <= width; j++){
			if(i==position_x&&j==position_y)printf("O");
			else if(i==1&&j!=0&&j!=width&&flag)printf("B");
			else if(i==high)printf("-");
			else if(j==width)printf("|");
			else if(i==blank_x&&j>=left&&j<=right)printf("*");
			else printf(" ");
		}
		printf("\n");
	}
	printf("小球反弹数：%d\n",ballnumber);
}
void updateWithoutInput(){//与用户输入无关的更新
	speed++;
	if(speed==5){
		if(position_x == high){
				printf("Game Over!");
				exit(0);
		}
		if(blank_y<=0)blank_y=0;//挡板左右边界(未优化) 
		if(blank_y>=width)blank_y=width;
		if(position_x == blank_x-1){//小球碰到挡板 
			if(position_y>=left&&position_y<=right){
				ballnumber++;
				ball_vx = -ball_vx;
			}
		}
		if(position_x == brick_x-1||position_x == brick_x+1){//小球碰到砖块 (未完待续...) 
				flag = 0;
				brick_x = -1; 
				ballnumber++;
				ball_vx = -ball_vx;
		}
		position_x = position_x+ball_vx;//根据速度更新小球位置 
		position_y = position_y+ball_vy;
		
		//碰到边界后，改变速度的方向
		if(position_x==0)
			ball_vx = -ball_vx; 
		if(position_y==0 || position_y==width-1)
			ball_vy = -ball_vy; 
		speed = 0;
	}


	
}
void updateWithInput(){//与用户输入有关的更新 
	char input;
	
	if(kbhit()){//当按下键盘时 
		input = getch();
		if(input == 'a'){
			blank_y--;
			left = blank_y - radius;
			right = blank_y + radius;
		}
		if(input == 'd'){
			blank_y++;
			left = blank_y - radius;
			right = blank_y + radius;
		}
	}
}
int main(){
	startup();//数据初始化
	while(1){//游戏循环执行
		show();//显示画面
		updateWithoutInput();//与用户输入无关的更新
		updateWithInput();//与用户输入有关的更新 
		
	} 
    return 0;
}
