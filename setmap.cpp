#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
const int XPOS = 12,YPOS = 6;
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
	room[0][0] = XPOS - 8;
	room[0][1] = YPOS - 2;
	room[0][2] = XPOS + 7;
	room[0][3] = YPOS + 2;
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
	//for(int i=0;i<5;i++)
	//	cout<<i<<' '<<channel[i]<<endl;
	for(int i=0;i<4;i++)
	{
		//cout<<i<<endl;
		int a = i+1;
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
	int coin = 0,heart = 0,monster = 0;
	int space = 0;
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<80;j++)
		{
			int temp = rand() % 60;
			if(map[i][j] == ' ')
			{
				space++;
				if((temp == 1) && coin < 30)
				{
					map[i][j] = 'C';
					coin++;
				}
				else if(temp == 3 && heart < 10)
				{
					map[i][j] = 'H';
					heart++;
				}
				else if(temp >= 4 && temp <= 8)
				{
					map[i][j] = 'M';
					monster++;
				}
			}
		}
	}
	//cout<<"spaces:"<<space<<" coins:"<<coin<<" hearts:"<<heart<<" monsters:"<<monster<<endl;
	//exit
	for(int j=room[4][0];j<=room[4][2];j++)
	{
		for(int k=room[4][1];k<=room[4][3];k++)
			map[k][j] = '`';
	}
	map[room[4][1]+2][room[4][0]+7] = 'O';
	map[room[4][1]+2][room[4][0]+5] = 'D';
	for(int i=YPOS-1;i<=YPOS+1;i++)				//safe area
	{
		for(int j=XPOS-1;j<=XPOS+1;j++)
			map[i][j] = ' ';
	}
	//write map
	for(int i=0;i<25;i++)
		fout<<map[i]<<endl;
	return 0;
}