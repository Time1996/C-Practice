#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
//������ȫ�ֱ�������
int position_x,position_y;//�ɻ�����
int high,width;//��Ϸ����ߴ� 
int bullet_x,bullet_y;//�ӵ�λ�� 
int enemy_x,enemy_y;//�л�λ�� 
int score;//��Ϸ�÷� 
int score_x,score_y;//��Ϸ�÷���ʾλ�� 
int arm;//װ��ģʽ 
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
void show(){//��ʾ����
	gotoxy(0,0);
	for(int i = 0; i < high; i++){
		for(int j = 0; j < width; j++){
			if(i==position_x&&j==position_y)printf("*");//����ɻ�����
			else if(i==position_x-1&&j==position_y&&arm)printf("*");
			else if(i==position_x&&j==position_y-1&&arm)printf("*");
			else if(i==position_x&&j==position_y+1&&arm)printf("*");//װ�׿��� 
			else if(i==bullet_x&&j==bullet_y)printf(".");
			else if(i==bullet_x&&j==bullet_y+1&&arm)printf(".");
			else if(i==bullet_x&&j==bullet_y-1&&arm)printf(".");//�ӵ���ǿ 
			else if(i==enemy_x&&j==enemy_y)printf("@");
			else if(i==score_x&&j==score_y)printf("�÷֣�%d",score);
			else printf(" ");//����ո� 
		}
		printf("\n");//������� 
	}
}
void updateWithoutInput(){//���û������޹صĸ���
	
	static int speed = 0;
	//�߽��� 
	if(position_x<=0)position_x = 0;
	if(position_x>=high-1)position_x = high-1;
	if(position_y<0)position_y = width-1;
	if(position_y>width-1)position_y = 0;
	//�߽��� 
	
	if(bullet_x==enemy_x&&bullet_y==enemy_y||enemy_x==bullet_x&&enemy_y==bullet_y+1||bullet_x==enemy_x&&enemy_y==bullet_y-1){//�ӵ����ел��� 
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
	if(bullet_x>-1)//�ӵ����Ϸ��� 
		bullet_x--;
	if(enemy_x>high){//�л����� 
		enemy_x = 0;
		enemy_y = rand() % width;
	}
	else {
		if(speed==20){//ÿ10��ʱ������һ�����������ٶ� 
			enemy_x++;
			speed = 0;
		}
	}
	
	
}
void updateWithInput(){//���û������йصĸ��� 
	char input;
	
	if(kbhit()){//�����¼���ʱ 
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
	startup();//���ݳ�ʼ��
	while(1){//��Ϸѭ��ִ��
		show();//��ʾ����
		updateWithoutInput();//���û������޹صĸ���
		updateWithInput();//���û������йصĸ��� 
		
	} 
    return 0;
}
