#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//函数外全局变量定义
int position_x,position_y;//飞机坐标
int high,width;//游戏画面尺寸 
int bullet_x,bullet_y;//子弹位置 
int enemy_x,enemy_y;//敌机位置 
int score;//游戏得分 
int score_x,score_y;//游戏得分显示位置 
int arm;//装甲模式 
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
	width = 20;
	arm = 0;
	
	position_x = high/2;
	position_y = width/2;
	bullet_y = position_y;
	bullet_x = -1;
	enemy_x = 0;
	enemy_y = width/2;
	score = 0;
	score_x = 0;
	score_y = width-1;
} 
void show(){//显示画面
	gotoxy(0,0);
	for(int i = 0; i < high; i++){
		for(int j = 0; j < width; j++){
			if(i==position_x&&j==position_y)printf("*");//输出飞机机体
			else if(i==position_x-1&&j==position_y&&arm)printf("*");
			else if(i==position_x&&j==position_y-1&&arm)printf("*");
			else if(i==position_x&&j==position_y+1&&arm)printf("*");//装甲开启 
			else if(i==bullet_x&&j==bullet_y)printf(".");
			else if(i==bullet_x&&j==bullet_y+1&&arm)printf(".");
			else if(i==bullet_x&&j==bullet_y-1&&arm)printf(".");//子弹加强 
			else if(i==enemy_x&&j==enemy_y)printf("@");
			else if(i==score_x&&j==score_y)printf("得分：%d",score);
			else printf(" ");//输出空格 
		}
		printf("\n");//输出换行 
	}
}
void updateWithoutInput(){//与用户输入无关的更新
	
	static int speed = 0;
	//边界检测 
	if(position_x<=0)position_x = 0;
	if(position_x>=high-1)position_x = high-1;
	if(position_y<0)position_y = width-1;
	if(position_y>width-1)position_y = 0;
	//边界检测 
	
	if(bullet_x==enemy_x&&bullet_y==enemy_y||enemy_x==bullet_x&&enemy_y==bullet_y+1||bullet_x==enemy_x&&enemy_y==bullet_y-1){//子弹击中敌机后 
		score++;
		printf("\a"); 
		enemy_x = 0;
		enemy_y = rand() % width;
		bullet_x = -1;
		if(score>=5){
			arm = 1;
		}else arm = 0;
	}
	if(position_x==enemy_x&&position_y==enemy_y){
		score--;
		position_x = high/2;
		position_y = width/2;
		enemy_x = 0;
		enemy_y = rand() % width;
	}
	if(speed<20)
		speed++;
	if(bullet_x>-1)//子弹向上发射 
		bullet_x--;
	if(enemy_x>high){//敌机生成 
		enemy_x = 0;
		enemy_y = rand() % width;
	}
	else {
		if(speed==20){//每10次时钟下落一格，用来控制速度 
			enemy_x++;
			speed = 0;
		}
	}
	
	
}
void updateWithInput(){//与用户输入有关的更新 
	char input;
	
	if(kbhit()){//当按下键盘时 
		input = getch();
		if(input == 'a')position_y--;
		if(input == 'd')position_y++;
		if(input == 'w')position_x--;
		if(input == 's')position_x++;
		if(input == ' '){
			bullet_x = position_x-1;
			bullet_y = position_y;
		}
		if(input ==0x1b)system("Pause");
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
