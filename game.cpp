#include "game.h"
int mpos[25][80];
char map[25][80],imap[25][80],pmap[25][80],lpmap[25][80];										//map:game map;imap:background map;pmap:front map
void gotoxy(short xx, short yy)
{
 	COORD coord = {xx, yy}; 
 	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void menu()
{
	system("cls");
	printf("=========Welcome to Tauren Legend=========\n");
	getch();
	printf("Get out of here!\n");
	printf("Press any key to enter the game.");
	getch();
}
void setmap()
{
	srand(time(NULL));
	for(int i=0;i<25;i++)
	{
		for(int j=0;j<80;j++)
			map[i][j] = '*';
	}
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
	for(int i=0;i<4;i++)
	{
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
	//exit
	map[room[4][1]+2][room[4][0]+7] = 'O';
	for(int i=YPOS-1;i<=YPOS+1;i++)				//safe area
	{
		for(int j=XPOS-1;j<=XPOS+1;j++)
			map[i][j] = ' ';
	}
}
void game()
{
	int weapon=1;
	int x,y,counter1 = 0;												//init the position
	int coin = 0,kill = 0,level = 1,lives = 5,wk = 1,wp = 1,power = FULL;	//if you do not understand that,you can not understand that
	srand(time(NULL));
	while(true)
	{
		int mlives = -1,dlives = 15 + level * 20;
		x = XPOS;y = YPOS;
		setmap();
		for(int i=0;i<25;i++)				//this loop read the map file
		{
			for(int j=0;j<80;j++)
				lpmap[i][j] = pmap[i][j] = imap[i][j] = map[i][j];		//put a line in the arrays:imap,pmap
		}
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<80;j++)
			{
				if(pmap[i][j] != '*')
					pmap[i][j] = '.';
			}
		}	
		system("cls");
		printf("Loading was succesful!Press W,A,S or D key to enter the game.\n");
		for(int i=y-yview;i<=y+yview;i++)
		{
			for(int j=x-xview;j<=x+xview;j++)
			{
				if(pmap[i][j] == '.')
					pmap[i][j] = map[i][j];
			}
		}
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<80;j++)
				printf("%c",pmap[i][j]);
			printf("\n");
		}
		int posc = 0;
		for(int i=0;i<25;i++)
		{
			for(int j=0;j<80;j++)
			{
				if(map[i][j] == 'M')
					mpos[i][j] = rand() % 5 + level*3;
			}
		}
		

		while(true)
		{
			map[y][x] = imap[y][x];			//clear the place before moving
			int tempx = x,tempy = y;		//memorize the place
			int newdx,newdy;
			for(int i=y-yview;i<=y+yview;i++)
			{
				for(int j=x-xview;j<=x+xview;j++)
				{
					if(pmap[i][j] != '*')
						pmap[i][j] = '.';
				}
			}
			char c;
			switch(getch())					//control the player
			{								//move
				case 'w':
					if(map[y-1][x] != '*')
						y--;
					else
						continue;
					break;
				case 's':
					if(map[y+1][x] != '*')
						y++;
					else
						continue;
					break;
				case 'a':
					if(map[y][x-1] != '*')
						x--;
					else
						continue;
					break;
				case 'd':
					if(map[y][x+1] != '*')
						x++;
					else
						continue;
					break;
				case 'k':					//kill the monster
					if(power>=wp)
					{
						power -= wp;
						for(int i=y-1;i<=y+1;i++)
						{
							for(int j=x-1;j<=x+1;j++)
							{
								if(abs(y-i) == abs(x-j))
									continue;
								if(map[i][j] == 'M')
								{
									mpos[i][j] -= wk;
									mlives = mpos[i][j];
									if(mpos[i][j] <= 0)
									{
										map[i][j] = ' ';
										kill++;
										coin++;
									}
								}
							}
						}
					}
					else
						continue;
					break;
				case 'h':					//help menu
					help();
					getch();
					system("cls");
					printf("\n");
					for(int i=0;i<25;i++)
					{
						for(int j=0;j<80;j++)
							printf("%c",pmap[i][j]);
						printf("\n");
					}
					break;
				case 't':
					system("cls");
					printf("===============Shop Menu===============\n");
					printf("Press number keys to buy those things.\n");
					printf("1 Heart\t\t3 coins\n");
					printf("2 Stick\t\t10 coins\n");
					printf("3 Energy Drink\t5 coins\n");
					printf("4 Knife\t\t20 coins\n");
					/*add other things here*/
					c = getch();
					switch(c)
					{
						case '1':
							if(coin >= 3)
							{
								coin -= 3;
								lives++;
							}
							break;
						case '2':
							if(coin >= 10)
							{
								coin -= 10;
								weapon = 2;
								wk = 3;
								wp = 2;
							}
							break;
						case '3':
							if(coin >= 5)
							{
								coin -= 5;
								power += 50;
							}
							break;
						case '4':
							if(coin >= 20)
							{
								coin -= 20;
								weapon = 3;
								wk = 8;
								wp = 3;
							}
							break;
					}
					system("cls");
					printf("\n");
					for(int i=0;i<25;i++)
					{
						for(int j=0;j<80;j++)
							printf("%c",pmap[i][j]);
						printf("\n");
					}
					break;
				default:
					continue;
			}
			
			if(map[y][x] != ' ' && map[y][x] != '`')
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
					printf("You win.\n");
					printf("Press any key to enter the next level.");
					getch();
					break;
				}
				else{
					if(map[y][x] == 'M')	//meet the monster
						lives--;
					x = tempx;				//(go back to the place we met)
					y = tempy;
				}
			}
			
			map[y][x] = '@';				//change the game map after moving
			
			for(int i=0;i<25;i++)
			{
				for(int j=0;j<80;j++)
				{
					if(map[i][j] == 'M')
					{
						if(mpos[i][j] <= 0)
						{
							mpos[i][j] = 0;
							map[i][j] = ' ';
						}
					}
				}
			}
			//monsters' move
			for(int i=0;i<25;i++)
			{
				for(int j=0;j<80;j++)
				{
					if(map[i][j] == 'M')
					{
						int temp = rand() % 10;
						switch(temp)
						{
							case 0:
								if(map[i+1][j] != '*' && map[i+1][j] != '@' && map[i+1][j] != 'M' && map[i+1][j] != 'O')
								{
									mpos[i+1][j] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i+1][j] = 'M';
									break;
								}
							case 1:
								if(map[i-1][j] == ' ')
								{
									mpos[i-1][j] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i-1][j] = 'M';
									break;
								}
							case 2:
								if(map[i][j+1] == ' ')
								{
									mpos[i][j+1] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i][j+1] = 'M';
									break;
								}
							case 3:
								if(map[i][j-1] == ' ')
								{
									mpos[i][j-1] = mpos[i][j];
									mpos[i][j] = 0;
									if(imap[i][j] == 'M')
										map[i][j] = ' ';
									else
										map[i][j] = imap[i][j];
									map[i][j-1] = 'M';
									break;
								}
						}
					}
				}
			}
			for(int i=y-yview;i<=y+yview;i++)
			{
				for(int j=x-xview;j<=x+xview;j++)
				{
					if(pmap[i][j] == '.')
						pmap[i][j] = map[i][j];
				}
			}
			//system("cls");				//if you can not understand that,you will never understand that
			if(lives <= 0)					//die
			{
				system("cls");
				printf("You died at level %d.\n",level);
				printf("You realize that you will never get out of here.");
				getch();
				return;
			}
			gotoxy(0,0);
			printf("                                                                                                                     \n");
			gotoxy(0,0);								//print status
			printf("x:%d y:%d\tlives:%d energy:%d\tweapon:",x,y,lives,power);
			switch(weapon)
			{
				case 1:
					printf("fist");
					break;
				case 2:
					printf("rod");
					break;
				case 3:
					printf("knife");
					break;
			}
			printf(" coin:%d kill:%d enemy 's lives:%d level:%d\n",coin,kill,mlives,level);
			//print the map
			for(int i=0;i<25;i++)
			{
				for(int j=0;j<80;j++)
				{
					if(lpmap[i][j]!=pmap[i][j])
					{
						gotoxy(j,i+1);
						printf("%c",pmap[i][j]);
						lpmap[i][j] = pmap[i][j];
					}
				}
			}
			if(counter1 >= 5 && power < FULL)
			{
				power++;
				counter1 -= 5;
			}
			counter1++;
		}
		level++;							//(start this up a second time)
	}
}
void help()
{
	system("cls");
	printf("===============Help Menu===============\n");
	printf("Control:\n");
	printf("Move:W,A,S,D;\n");
	printf("Kill Monsters:K\n;");
	printf("Shop:T\n");
	printf("Symbol:\n");
	printf("@:Yourself;\n");
	printf("M:Monster(You need to kill them);\n");
	printf("C:Coin(Collect them to increase your coins);\n");
	printf("H:Heart(Collect them to ncrease your lives);\n");
	printf("O:Out(The end of the level);\n");
	printf("=======================================\n\n\n");
}