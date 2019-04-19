#pragma warning(disable : 4996)
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>


void init();	//初始化 边框
void addNum();	//添加数字
void win(int m);			//生成结束弹框
void fail(int n);				//判定是否还可以操作
void play();
void move(int dir, int &s);		//移动
void move(int a[4][4], int dir, int &s);
void mul(int dir, int &s);		//合并
//void mul(int a[4][4], int dir, int &s);
void renew();			//更新显示界面
				    
int map[4][4];

int main()
{
	
	init();
	play();
	getchar();
	return 0;
}

void init()	//界面
{
	for (int i = 0; i < 4; i++)		//初始化数组
	{
		for (int j = 0; j < 4; j++)
		{
			map[i][j] = 0;
		}
	}
	addNum();
	renew();
}

void addNum()
{
	int tem;
	int i, j;
	do									//生成随机数的位置
	{
		srand((unsigned int)time(NULL));
		tem = rand() % 16;				//生成0-15数字
		i = (tem + 1) / 4;				//1-16 除4得行 余4得列
		j = (tem + 1) % 4;
	} while (map[i][j] != 0);

	srand((unsigned int)time(NULL));	//91开生成2或4
	tem = rand() % 10;
	if(tem < 9)	map[i][j] = 2;
	else map[i][j] = 4;
}

void win(int m)
{
	//int t = 1;
	//for (int i = 0; i < 4; i++)		
	//{
	//	for (int j = 0; j < 4; j++)
	//	{
	//		if (map[i][j] == 0) t = 0;
	//	}
	//}
	//if (t = 1) exit(0);  //满数字则弹框结束
	if (m == 0)			//输
	{
		HWND hd;
		hd = GetHWnd();
		MessageBox(hd, L"欢迎下次光临", L"菜", MB_OK);
		exit(0);
		closegraph();
	}
	else if (m == 1)				//赢
	{
		HWND hd;
		hd = GetHWnd();
		MessageBox(hd, L"666", L"大佬", MB_OK);
		closegraph();
	}
	else if (m == 2)						// 仍可操作
	{
		HWND hd;
		hd = GetHWnd();
		MessageBox(hd, L"再给你一次机会", L"人品有问题", MB_OK);
		closegraph();
	}
}

void fail(int n)			//若某次操作未发生移动和数字叠加 进入失败判定
					//复制当前地图数组  进行上下左右四次判断 看是否能够移动
{					//n用于接收当前操作的方向 以至此处少判断一个方向
	int k;
	//int i, j;
	int ss = 0;
	//for (i = 0; i < 4; i++)		//复制原地图数组
	//{
	//	for (j = 0; j < 4; j++)
	//	{
	//		mmap[i][j] = map[i][j];
	//	}
	//}
	for (k = 1; k < 5; k++)		// 1 2 3 4 四个方向
	{
		if (k == n) continue;		
		move(map,k, ss);
		//mul(mmap,k, ss);
		if (ss == 1) win(2);		//还可以操作 再给一次机会
		else win(0);				//结束游戏
	}

}

void play()
{
	int s = 0;			//标志位 如果有移动则置1 反之一直为0  一个方向全部判定完毕后若仍为0则进入失败判定阶段
	int dir;
	while (1)
	{
		dir = getch();
		switch (dir)
		{
		case 224:			//getch()读取一次要输出两个字符 一个224 第二个才是输入的字符
		/*case 72: printf("The key you Pressed is : ↑ \n"); break;
		case 80: printf("The key you Pressed is : ↓ \n"); break;
		case 75: printf("The key you Pressed is : ← \n"); break;
		case 77: printf("The key you Pressed is : → \n"); break;
		default: printf("No direction keys detected  %d \n",dir); break;*/
			dir = getch();
			switch (dir)
			{
			case 72:	//上
			{
				move(1,s);
				mul(1,s);
				if (s == 0) fail(1);
				addNum();
				renew();
			}break;

			case 80:	//下
			{
				move(2,s);
				mul(2,s);
				if (s == 0) fail(2);
				addNum();
				renew();

			}break;
			case 75:	//左
			{
				move(3,s);
				mul(3,s);
				if (s == 0) fail(3);
				addNum();
				renew();

			}break;
			case 77:	//右
			{
				move(4,s);
				mul(4,s);
				if (s == 0) fail(4);
				addNum();
				renew();
			}break;
			}

		}
	}
}

void move(int dir, int &s)
{
	int i, j;
	int tem ;
	switch (dir)
	{
		case 1://上  依次判断每列	(快速排序思想？)
		{
			for (j = 0; j < 4; j++)
			{	
				i = 0;
				tem = 0;
				while (i < 4)
				{
					if (map[i][j] == 0)
						++i;
					else
					{
						map[tem][j] = map[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
						s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
						if(i != tem)	map[i][j] = 0;				//原位置置零
						++tem;
						++i;
					}
				}
			
			}
		}break;

		case 2://下
		{
			for (j = 0; j < 4; j++)
			{
				i = 3;
				tem = 3;
				while (i >= 0)
				{
					if (map[i][j] == 0)
						--i;
					else
					{
						map[tem][j] = map[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
						s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
						if (i != tem)	map[i][j] = 0;				//原位置置零
						--tem;
						--i;
					}
				}
			}
		}break;

		case 3://左
		{
			for (i = 0; i < 4; i++)		//依次判断每行
			{
				j = 0;
				tem = 0;
				while (j < 4)
				{
					if (map[i][j] == 0)
						++j;
					else
					{
						map[i][tem] = map[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
						s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
						if (j != tem)	map[i][j] = 0;				//原位置置零
						++tem;
						++j;
					}
				}
			}
		}break;

		case 4://右
		{
			for (i = 0; i < 4; i++)
			{
				j = 3;
				tem = 3;
				while (j >= 0)
				{
					if (map[i][j] == 0)
						--j;
					else
					{
						map[i][tem] = map[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
						s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
						if (j != tem)	map[i][j] = 0;				//原位置置零
						--tem;
						--j;
					}
				}
			}
		}break;
	}
}

void move(int a[4][4], int dir, int &s)	
{
	int i, j;
	int tem;
	switch (dir)
	{
	case 1://上  依次判断每列	(快速排序思想？)
	{
		for (j = 0; j < 4; j++)
		{
			i = 0;
			tem = 0;
			while (i < 4)
			{
				if (a[i][j] == 0)
					++i;
				else
				{
					a[tem][j] = a[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
					s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
					if (i != tem)	a[i][j] = 0;				//原位置置零
					++tem;
					++i;
				}
			}

		}
	}break;

	case 2://下
	{
		for (j = 0; j < 4; j++)
		{
			i = 3;
			tem = 3;
			while (i >= 0)
			{
				if (a[i][j] == 0)
					--i;
				else
				{
					a[tem][j] = a[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
					s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
					if (i != tem)	a[i][j] = 0;				//原位置置零
					--tem;
					--i;
				}
			}
		}
	}break;

	case 3://左
	{
		for (i = 0; i < 4; i++)		//依次判断每行
		{
			j = 0;
			tem = 0;
			while (j < 4)
			{
				if (a[i][j] == 0)
					++j;
				else
				{
					a[i][tem] = a[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
					s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
					if (j != tem)	a[i][j] = 0;				//原位置置零
					++tem;
					++j;
				}
			}
		}
	}break;

	case 4://右
	{
		for (i = 0; i < 4; i++)
		{
			j = 3;
			tem = 3;
			while (j >= 0)
			{
				if (a[i][j] == 0)
					--j;
				else
				{
					a[i][tem] = a[i][j];	//遇到非零的数就移动到tem标记的第一个零位置
					s = 1;						//发生移动则标志位置1 表示还有空位置可以操作 
					if (j != tem)	a[i][j] = 0;				//原位置置零
					--tem;
					--j;
				}
			}
		}
	}break;
	}

	switch (dir)
	{
	case 1://上
	{
		for (j = 0; j < 4; j++)			//判断每一列的前三个数 
		{
			for (i = 0; i < 3; i++)
			{
				if (a[i][j] != 0)		//如果非零就判断是否跟下一个数字相同 
				{
					while (a[i][j] == a[i + 1][j])
					{
						a[i][j] += a[i + 1][j];
						s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作 
						for (tem = i + 1; tem < 3; tem++)	//后面的数字前移一格
						{
							a[tem][j] = a[tem + 1][j];
						}
						a[tem][j] = 0;			//最后一位置零
					}
				}
			}
		}
	}break;

	case 2://下
	{
		for (j = 0; j < 4; j++)			//判断每一列的前三个数 
		{
			for (i = 3; i >= 0; i--)
			{
				if (a[i][j] != 0)		//如果非零就判断是否跟下一个数字相同 
				{
					while (a[i][j] == a[i - 1][j])
					{
						a[i][j] += a[i - 1][j];
						s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作
						for (tem = i - 1; tem >= 0; tem--)	//后面的数字前移一格
						{
							a[tem][j] = a[tem - 1][j];
						}
						a[tem][j] = 0;			//最后一位置零
					}
				}
			}
		}
	}break;

	case 3://左
	{
		for (i = 0; i < 4; i++)			//判断每一行的前三个数 
		{
			for (j = 0; j < 3; j++)
			{
				if (a[i][j] != 0)		//如果非零就判断是否跟后一个数字相同 
				{
					while (a[i][j] == a[i][j + 1])
					{
						a[i][j] += a[i][j + 1];
						s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作
						for (tem = j + 1; tem < 3; tem++)	//后面的数字前移一格
						{
							a[i][tem] = a[i][tem + 1];
						}
						a[i][tem] = 0;			//最后一位置零
					}
				}
			}
		}
	}break;

	case 4://右
	{
		for (i = 0; i < 4; i++)			//判断每一列的前三个数 
		{
			for (j = 3; j >= 0; j--)
			{
				if (a[i][j] != 0)		//如果非零就判断是否跟下一个数字相同 
				{
					while (a[i][j] == a[i][j - 1])
					{
						a[i][j] += a[i][j - 1];
						s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作
						for (tem = j - 1; tem >= 0; tem--)	//后面的数字前移一格
						{
							a[i][tem] = a[i][tem - 1];
						}
						a[i][tem] = 0;			//最后一位置零
					}
				}
			}
		}
	}break;
	}

}

void mul(int dir, int &s)
{
	int i, j;
	int tem;
	switch (dir)
	{
		case 1://上
		{
			for (j = 0; j < 4; j++)			//判断每一列的前三个数 
			{
				for (i = 0; i < 3; i++)		
				{
					if (map[i][j] != 0)		//如果非零就判断是否跟下一个数字相同 
					{
						while (map[i][j] == map[i + 1][j])
						{
							map[i][j] += map[i + 1][j];
							if (map[i][j] == 2048) win(1);
							s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作 
							for (tem=i+1; tem < 3; tem++)	//后面的数字前移一格
							{
								map[tem][j] = map[tem + 1][j];
							}
							map[tem][j] = 0;			//最后一位置零
						}
					}
				}
			}
		}break;

		case 2://下
		{
			for (j = 0; j < 4; j++)			//判断每一列的前三个数 
			{
				for (i = 3; i >=0; i--)
				{
					if (map[i][j] != 0)		//如果非零就判断是否跟下一个数字相同 
					{
						while (map[i][j] == map[i - 1][j])
						{
							map[i][j] += map[i - 1][j];
							if (map[i][j] == 2048) win(1);
							s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作
							for (tem = i - 1; tem >= 0; tem--)	//后面的数字前移一格
							{
								map[tem][j] = map[tem - 1][j];
							}
							map[tem][j] = 0;			//最后一位置零
						}
					}
				}
			}
		}break;

		case 3://左
		{
			for (i = 0; i < 4; i++)			//判断每一行的前三个数 
			{
				for (j = 0; j < 3; j++)
				{
					if (map[i][j] != 0)		//如果非零就判断是否跟后一个数字相同 
					{
						while (map[i][j] == map[i][j + 1])
						{
							map[i][j] += map[i][j + 1];
							if (map[i][j] == 2048) win(1);
							s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作
							for (tem = j + 1; tem < 3; tem++)	//后面的数字前移一格
							{
								map[i][tem] = map[i][tem + 1];
							}
							map[i][tem] = 0;			//最后一位置零
						}
					}
				}
			}
		}break;

		case 4://右
		{
			for (i = 0; i < 4; i++)			//判断每一列的前三个数 
			{
				for (j = 3; j >= 0; j--)
				{
					if (map[i][j] != 0)		//如果非零就判断是否跟下一个数字相同 
					{
						while (map[i][j] == map[i][j - 1])
						{
							map[i][j] += map[i][j - 1];
							if (map[i][j] == 2048) win(1);
							s = 1;						//发生数字叠加则标志位置1 表示还有空位置可以操作
							for (tem = j - 1; tem >= 0; tem--)	//后面的数字前移一格
							{
								map[i][tem] = map[i][tem - 1];
							}
							map[i][tem] = 0;			//最后一位置零
						}
					}
				}
			}
		}break;
	}
}

void renew()
{
	system("cls");

	printf("\n\n\n\n\n");
	printf("\t\t\t┏━━━━━━┳━━━━━━┳━━━━━━┳━━━━━━┓\n");
	printf("\t\t\t┃      ┃      ┃      ┃      ┃\n");
	printf("\t\t\t┃%6d┃%6d┃%6d┃%6d┃\n", map[0][0], map[0][1], map[0][2], map[0][3]);
	printf("\t\t\t┣━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━┫\n");
	printf("\t\t\t┃      ┃      ┃      ┃      ┃\n");
	printf("\t\t\t┃%6d┃%6d┃%6d┃%6d┃\n", map[1][0], map[1][1], map[1][2], map[1][3]);
	printf("\t\t\t┣━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━┫\n");
	printf("\t\t\t┃      ┃      ┃      ┃      ┃\n");
	printf("\t\t\t┃%6d┃%6d┃%6d┃%6d┃\n", map[2][0], map[2][1], map[2][2], map[2][3]);
	printf("\t\t\t┣━━━━━━╋━━━━━━╋━━━━━━╋━━━━━━┫\n");
	printf("\t\t\t┃      ┃      ┃      ┃      ┃\n");
	printf("\t\t\t┃%6d┃%6d┃%6d┃%6d┃\n", map[3][0], map[3][1], map[3][2], map[3][3]);
	printf("\t\t\t┗━━━━━━┻━━━━━━┻━━━━━━┻━━━━━━┛\n");
}
