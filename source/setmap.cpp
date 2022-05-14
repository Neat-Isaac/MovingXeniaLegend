#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
	string map[25];
	ofstream fout("map1.txt");
	srand(time(NULL));
	for(int i=0;i<25;i++)
		map[i] = "********************************************************************************";
	//rooms
	int room[5][4];
	int distance = 4;
	room[0][0] = 32;
	room[0][1] = 10;
	room[0][2] = 47;
	room[0][3] = 14;
	for(int i=1;i<5;i++)
	{
		bool flag = true;
		int count = 0;									//true:wrong;false:correct
		while(flag)
		{
			room[i][0] = rand() % 63 + 1;				//x1
			room[i][1] = rand() % 19 + 1;					//y1
			room[i][2] = room[i][0] + 15;				//x2
			room[i][3] = room[i][1] + 4;				//y2
			for(int j=0;j<i;j++)						//j < i!
			{
				if((room[i][2] < room[j][0] - distance || room[i][0] > room[j][2] + distance) || (room[i][3] < room[j][1] - distance || room[i][1] > room[j][3] + distance))
					flag = false;
				else
				{
					flag = true;
					break;								//this sentence is very important!
				}
			}
			count++;
		}
	}
	for(int i=0;i<5;i++)
	{
		for(int j=room[i][0];j<=room[i][2];j++)
		{
			for(int k=room[i][1];k<=room[i][3];k++)
				map[k][j] = ' ';
		}
	}
	
	//channels
	//1.define
	int channel[5];
	for(int i=0;i<5;i++)
		channel[i] = -1;
	int point = 0;
	while(true)
	{
		int see = 1;
		bool flag = true;
		while(flag)
		{
			channel[point] = rand() % 5;
			if(point == channel[point])
				continue;
			if(point != channel[point])
				flag = false;
			if(channel[channel[point]] == -1)
				flag = false;
			else
			{
				bool b = true;
				for(int i=0;i<5;i++)
				{
					if(channel[i] == -1)
					{
						b = false;
						break;
					}
				}
				if(b)
				{
					channel[point] = 0;
					see = 2;
					break;
				}
				else
				{
					see = 0;
					continue;
				}
			}
		}
		if(see == 1)
			point = channel[point];
		if(see == 2)
			break;
		see = 1;
	}
	
	//2.change
	for(int i=0;i<5;i++)
	cout<<i<<' '<<channel[i]<<endl;
	for(int i=0;i<5;i++)
	{
		cout<<i<<endl;
		int a = channel[i];
		if(a == 0)
			continue;
		//x
		if(room[i][0] <= room[a][0])
		{
			for(int j=room[i][0];j<=room[a][0]+5;j++)
				map[room[i][1] + 2][j] = ' ';
		}
		else
		{
			for(int j=room[i][0];j>=room[a][0]+5;j--)
				map[room[i][1] + 2][j] = ' ';
		}
		//y
		if(room[i][1] <= room[a][1])
		{
			for(int j=room[i][1]+2;j<=room[a][1];j++)
				map[j][room[a][0] + 5] = ' ';
		}
		else
		{
			for(int j=room[i][1]+2;j>=room[a][1];j--)
				map[j][room[a][0] + 5] = ' ';
		}
	}
	
	//prop
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<80;j++)
		{
			int temp = rand() % 30;
			if(map[i][j] == ' ')
			{
				if(temp == 1 || temp == 2)
					map[i][j] = 'C';
				else if(temp == 3)
					map[i][j] = 'H';
				else if(temp == 4 || temp == 5)
					map[i][j] = 'M';
			}
		}
	}
	
	//exit
	bool f = true;
	int x1,y1,x2,y2;
	for(int i=0;i<5;i++)
	{
		if(channel[i] == 0)
		{
			x1 = room[i][0];
			y1 = room[i][1];
			x2 = room[i][2];
			y2 = room[i][3];
		}
	}
	for(int i=x1;i<=x2;i++)
	{
		if(f)
		{
			for(int j=y1;j<=y2;j++)
			{
				int temp = rand() % 10;
				if(temp == 0)
				{
					map[j][i] = 'O';
					f = false;
					break;
				 } 
			}
		}
		else
			break;
	}
	map[12][40] = ' ';
	
	//write map
	for(int i=0;i<25;i++)
		fout<<map[i]<<endl;
	return 0;
}