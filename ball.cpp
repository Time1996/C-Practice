#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//������ȫ�ֱ�������
static int speed = 0;
int high,width;
int position_x,position_y;//С������ 
int ball_vx,ball_vy;//С���ٶ� 
int blank_x,blank_y;//������������ 
int radius;//����뾶��С
int left,right;//�������ұ߽� 
int ballnumber;//С�򷴵����� 
int brick_x,brick_y;//ש������ 
int flag = 1;
void gotoxy(int x, int y) {
    COORD pos = {x,y};
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
    SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}

void HideCursor() // �������ع��
{
        CONSOLE_CURSOR_INFO cursor_info = {1, 0};  // �ڶ���ֵΪ0��ʾ���ع��
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void startup(){//���ݳ�ʼ��
	HideCursor();//���ع�� 
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
void show(){//��ʾ����
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
	printf("С�򷴵�����%d\n",ballnumber);
}
void updateWithoutInput(){//���û������޹صĸ���
	speed++;
	if(speed==5){
		if(position_x == high){
				printf("Game Over!");
				exit(0);
		}
		if(blank_y<=0)blank_y=0;//�������ұ߽�(δ�Ż�) 
		if(blank_y>=width)blank_y=width;
		if(position_x == blank_x-1){//С���������� 
			if(position_y>=left&&position_y<=right){
				ballnumber++;
				ball_vx = -ball_vx;
			}
		}
		if(position_x == brick_x-1||position_x == brick_x+1){//С������ש�� (δ�����...) 
				flag = 0;
				brick_x = -1; 
				ballnumber++;
				ball_vx = -ball_vx;
		}
		position_x = position_x+ball_vx;//�����ٶȸ���С��λ�� 
		position_y = position_y+ball_vy;
		
		//�����߽�󣬸ı��ٶȵķ���
		if(position_x==0)
			ball_vx = -ball_vx; 
		if(position_y==0 || position_y==width-1)
			ball_vy = -ball_vy; 
		speed = 0;
	}


	
}
void updateWithInput(){//���û������йصĸ��� 
	char input;
	
	if(kbhit()){//�����¼���ʱ 
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
	startup();//���ݳ�ʼ��
	while(1){//��Ϸѭ��ִ��
		show();//��ʾ����
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ��� 
		
	} 
    return 0;
}
