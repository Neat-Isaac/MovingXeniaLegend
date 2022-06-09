#include <iostream>						//libraries
#include <cstdlib>						//if you understand that,you can understand that
#include <conio.h>						//get the keyboard value
#include <fstream>						//read the map file
#include <cmath>						//abs() function
using namespace std;
int main()
{
	string map[25],imap[25],pmap[25];		//map:game map;imap:background map;pmap:front map
	int coin = 0,kill = 0,level = 1,lives = 5;		//if you do not understand that,you can not understand that
	int x,y;								//init the position
	while(true)
	{
		bool bool1 = false;
		x = 40;y = 12;
		system("setmap");
		ifstream fin("map1.txt");			//file pointer
		for(int i=0;i<25;i++)				//this loop read the map file
		{
			getline(fin,map[i]);			//put a line in the array:map
			pmap[i] = imap[i] = map[i];		//put a line in the arrays:imap,pmap
			//cout<<map[i]<<endl;				//help programmers to check the map
		}
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<80;j++)
			{
				if(pmap[i][j] != '*')
					pmap[i][j] = '.';
			}
		}	
		//for(int i=0;i<25;i++)
		//	cout<<pmap[i]<<endl;
		system("cls");
		cout<<"Load successful!"<<endl<<"Press any key to enter the game.";
		while(true)
		{
			map[y][x] = imap[y][x];			//clear the place before moving
			for(int i=y-1;i<=y+1;i++)
			{
				for(int j=x-1;j<=x+1;j++)
				{
					if(pmap[i][j] != '*')
						pmap[i][j] = '.';
				}
			}
			int tempx = x,tempy = y;		//member the place
			switch(getch())					//control the player
			{								//move
				case 'w':
					if(y > 0)
						y--;
					break;
				case 's':
					if(y < 24)
						y++;
					break;
				case 'a':
					if(x > 0)
						x--;
					break;
				case 'd':
					if(x < 78)
						x++;
					break;
				case 'k':					//kill the monster
					for(int i=y-1;i<=y+1;i++)
					{
						for(int j=x-1;j<=x+1;j++)
						{
							if(abs(y-i) == abs(x-j))
								continue;
							if(map[i][j] == 'M')
							{
								kill++;
								map[i][j] = imap[i][j] = ' ';
							}
						}
					}
					break;
				case 'h':					//help menu
					system("cls");
					cout<<"===============Help Menu==============="<<endl;
					cout<<"Control:"<<endl;
					cout<<"Move:W,A,S,D;"<<endl;
					cout<<"Kill Monsters:K;"<<endl;
					cout<<"Symbol:"<<endl;
					cout<<"X:Xenia(Yourself);"<<endl;
					cout<<"M:Monster(You need to kill them);"<<endl;
					cout<<"C:Coin(Collect them to increase your coins);"<<endl;
					cout<<"H:Heart(Collect them to ncrease your lives);"<<endl;
					cout<<"O:Out(The end of the level);"<<endl;
					cout<<"======================================="<<endl<<endl<<endl;
					system("pause");
					break;
			}
			if(map[y][x] != ' ')
			{
				if(map[y][x] == 'C')		//collect coins
				{
					coin++;
					imap[y][x] = ' ';
				}
				else if(map[y][x] == 'H')	//collect hearts
				{
					lives++;
					imap[y][x] = ' ';
				}
				else if(map[y][x] == 'O')	//win the game
				{
					system("cls");
					cout<<"You Win."<<endl;
					system("pause");
					bool1 = true;
					break;
				}
											//open the door(not developed)
				else{
					if(map[y][x] == 'M')	//meet the monster
						lives--;
					x = tempx;				//(go back to the place we met)
					y = tempy;
				}
			}
			map[y][x] = 'X';				//change the game map after moving
			for(int i=y-1;i<=y+1;i++)
			{
				for(int j=x-1;j<=x+1;j++)
				{
					if(pmap[i][j] == '.')
						pmap[i][j] = map[i][j];
				}
			}
			system("cls");					//if you can not understand that,you will never understand that
			if(lives <= 0)					//die
			{
				cout<<"You Died."<<endl;
				system("pause");
				return 0;
			}
											//print status
			cout<<"x:"<<x<<" y:"<<y<<" coin:"<<coin<<" kill:"<<kill<<" lives:"<<lives<<" level:"<<level<<endl;
			for(int i=0;i<25;i++)			//print the map
				cout<<pmap[i]<<endl;
			//cout<<endl;
			//for(int i=0;i<25;i++)			//print the map
			//	cout<<map[i]<<endl;
		}
		if(bool1)
		{
			bool1 = 0;
			level++;
			continue;
		}
	}
	return 0;							//I do not know why I put it here
}
