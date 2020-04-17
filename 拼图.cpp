#include<stdio.h>;
#include<graphics.h>;	
#include<time.h>;

int arr[15] = { 0 };
int map[4][4] = { 0 };
//定义图片
IMAGE img, blank;
//初始化数组
void initMap() 
{
	//int length = 15;
	//rand()伪随机函数
	//srand()随机种子函数;需要引入time头文件
	srand((unsigned)time(NULL));
	int i, j;
	int pos , length = 15;
	int start = 0;
	for ( i = 0; i < 15; i++)
	{
		arr[i] = i;

	}
	for ( i = 0; i < 4; i++)
	{
		for ( j = 0; j < 4; j++)
		{
			//固定白块
			if (i==3 && j==3)
			{
				map[i][j] = 15;
				break;
			}
			//随机产生下标
			pos = rand() % length;
			map[i][j] = arr[pos];
			//更新arr数组
			for (int k = pos; k < length; k++)
			{
				arr[k] = arr[k + 1];
			}
			length--;
		}
		if (i == 3 && j == 3)
		{
			map[3][3] = 15;
			break;
		}
	}
	
}
//生成拼图
void drawMap()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int x = j * 100;
			int y = i * 100;
			//printf("%d\t", map[i][j]);
			switch (map[i][j])
			{
			case 0:
			case 1:
			case 2:
			case 3:
				putimage(x, y, 100, 100, &img, map[i][j] * 100,0);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
				putimage(x, y, 100, 100, &img, (map[i][j] - 4) * 100, 100);
				break;
			case 8:
			case 9:
			case 10:
			case 11:
				putimage(x, y, 100, 100, &img, (map[i][j] - 8) * 100, 200);
				break;
			case 12:
			case 13:
			case 14:
				putimage(x, y, 100, 100, &img, (map[i][j] - 12) * 100, 300);
				break;
			case 15:
				putimage(x, y, &blank);
				break;
			}
		}
		//printf("\n");
	}
}
//获取白块纵坐标
int searchPos_i()
{
	//遍历寻找
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 15) {
				return i;
			}
		}
	}
	return -1;
}
//获取白块横坐标
int searchPos_j()
{
	//遍历寻找
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (map[i][j] == 15) {
				return j;
			}
		}
	}
	return -1;
}
//鼠标操作
void playGame()
{
	//鼠标交互
	//定义鼠标消息变量
	MOUSEMSG m;
	while (1)
	{
		drawMap();
		//定位空白位置
		int post_i = searchPos_i();
		int post_j = searchPos_j();
		//定义鼠标点击的下标
		int mouse_i = 0;
		int mouse_j = 0;
		//获取鼠标消息
		m = GetMouseMsg();
		//鼠标消息为左键按下/点击
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//drawMap();
			mouse_i = m.y / 100;
			mouse_j = m.x / 100;
			//交换处理
			//点击空白上方的格子
			if (mouse_i == post_i - 1 && mouse_j == post_j)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			//点击空白下方的格子
			if (mouse_i == post_i + 1 && mouse_j == post_j)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			//点击空白左边的格子
			if (mouse_i == post_i && mouse_j == post_j - 1)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			//点击空白右边的格子
			if (mouse_i == post_i && mouse_j == post_j + 1)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			
		}
	}
}
int main()
{
	int i;
	char name[6];
	srand((unsigned)time(NULL));
	i = rand() % 7;	//
	sprintf_s(name,"%d.jpg",i);
	//定义图片变量
	//IMAGE img;
	//加载图片
	loadimage(&img,name,400,400);//可以进行缩放
	loadimage(&blank, "blank.png", 100, 100);
	//初始化图形界面
	initgraph(400, 400);
	//显示图片
	initMap();
	drawMap();
	playGame();
	//putimage(0,0,&img);

	while (1);//卡屏
	//关闭界面
	closegraph();
	return 0;
}