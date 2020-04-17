#include<stdio.h>;
#include<graphics.h>;	
#include<time.h>;

int arr[15] = { 0 };
int map[4][4] = { 0 };
//����ͼƬ
IMAGE img, blank;
//��ʼ������
void initMap() 
{
	//int length = 15;
	//rand()α�������
	//srand()������Ӻ���;��Ҫ����timeͷ�ļ�
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
			//�̶��׿�
			if (i==3 && j==3)
			{
				map[i][j] = 15;
				break;
			}
			//��������±�
			pos = rand() % length;
			map[i][j] = arr[pos];
			//����arr����
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
//����ƴͼ
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
//��ȡ�׿�������
int searchPos_i()
{
	//����Ѱ��
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
//��ȡ�׿������
int searchPos_j()
{
	//����Ѱ��
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
//������
void playGame()
{
	//��꽻��
	//���������Ϣ����
	MOUSEMSG m;
	while (1)
	{
		drawMap();
		//��λ�հ�λ��
		int post_i = searchPos_i();
		int post_j = searchPos_j();
		//������������±�
		int mouse_i = 0;
		int mouse_j = 0;
		//��ȡ�����Ϣ
		m = GetMouseMsg();
		//�����ϢΪ�������/���
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//drawMap();
			mouse_i = m.y / 100;
			mouse_j = m.x / 100;
			//��������
			//����հ��Ϸ��ĸ���
			if (mouse_i == post_i - 1 && mouse_j == post_j)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			//����հ��·��ĸ���
			if (mouse_i == post_i + 1 && mouse_j == post_j)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			//����հ���ߵĸ���
			if (mouse_i == post_i && mouse_j == post_j - 1)
			{
				map[post_i][post_j] = map[mouse_i][mouse_j];
				map[mouse_i][mouse_j] = 15;
			}
			//����հ��ұߵĸ���
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
	//����ͼƬ����
	//IMAGE img;
	//����ͼƬ
	loadimage(&img,name,400,400);//���Խ�������
	loadimage(&blank, "blank.png", 100, 100);
	//��ʼ��ͼ�ν���
	initgraph(400, 400);
	//��ʾͼƬ
	initMap();
	drawMap();
	playGame();
	//putimage(0,0,&img);

	while (1);//����
	//�رս���
	closegraph();
	return 0;
}