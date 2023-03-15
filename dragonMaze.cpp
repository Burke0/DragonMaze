#include<iostream>
#include<iomanip>
#include<fstream>
#include<ctype.h>
#include<cstring>
#include<time.h>

using namespace std;

void loadMazeFile(char** ,int[], int[] , int[]);
void printMaze(char**,int[]);
bool moveHero(char** ,int[] , int[]);
void moveDragon(char**, int[],int[]);

int main()
{
	int size[2]={0,0};		//size of maze initialized
	int dragonAt[2]={0,0}; //dragon location initialized
	int heroAt[2]={0,0};	//hero location initialized
	char* mazeArray[20];	//max column size 20: increase for larger maze files
	bool gameOver=false;	//Game Over?

	loadMazeFile(mazeArray, size, heroAt, dragonAt );

	while(gameOver==false)//each loop is one turn
	{
		printMaze(mazeArray, size);
		gameOver=moveHero(mazeArray, heroAt, dragonAt);
		if(gameOver==false)
			moveDragon(mazeArray,heroAt, dragonAt);
		if ((heroAt[0]-1==dragonAt[0] && heroAt[1]==dragonAt[1]) || (heroAt[0]+1==dragonAt[0] && heroAt[1]==dragonAt[1]) || (heroAt[0]==dragonAt[0] && heroAt[1]+1==dragonAt[1]) || (heroAt[0]==dragonAt[0] && heroAt[1]-1==dragonAt[1]))
		{
			printMaze(mazeArray, size);
			cout<<"YOU ARE INCINERATED TO ASH BY DRAGON FIRE."<<'\n'<<"EPIC FAIL.";
			gameOver=true;
		}
	}

	for(int i=0; i<size[1]+1; i++) // memory cleanup loop
	{
		delete mazeArray[i];
		mazeArray[i]=nullptr;
	}
	return 0;

}


void loadMazeFile(char** mazeArray ,int* size, int* hero, int* dragon)
{
	int count=0, i=0;
	ifstream mazedata;

	mazedata.open("maze.txt");
	if(!mazedata)
		cerr<<"file not found"<<endl;
	char*line=new char[100];

	mazedata.getline(line,100);           //max row size 100
	size[1]=strlen(line);                 //stores size of row in size[1]

	while(mazedata.peek()!=EOF)          //counts columns
	{
		mazedata.getline(line,100);
		count++;
	}
	size[0]=count+1;					//save # of columns to size[0]
	delete line;
	line=nullptr;

	mazedata.close();
	mazedata.open("maze.txt");
	if(!mazedata)
		cerr<<"file not found"<<endl;


	while(mazedata.peek()!=EOF)
	{
		mazeArray[i]=new char[size[1]];
		mazedata.get(mazeArray[i],22);
		mazedata.ignore(99,'\n');

		if(strchr(mazeArray[i],'h') != NULL) //finds hero location if lower case h
		{

			hero[0]=(strchr(mazeArray[i], 'h')-mazeArray[i]);
			hero[1]=i;
		}
		if(strchr(mazeArray[i],'H') != NULL) //finds hero location if upper case H
		{
			hero[1]=(strchr(mazeArray[i], 'H')-mazeArray[i]);
			hero[0]=i;
		}
		if(strchr(mazeArray[i],'D') != NULL)//finds dragon location
		{
			dragon[1]=(strchr(mazeArray[i], 'D')-mazeArray[i]);
			dragon[0]=i;
		}
		i++;

	}
	mazedata.close();

}

void printMaze(char** mazeArray,int* size)//prints maze
{
	for(int i=0; i<size[0];i++)
		cout<<mazeArray[i]<<endl;
}

bool moveHero(char** mazeArray, int* hero, int* dragon) //Moves hero 1 space each call for w,a,s,d input with validation checking
{														//Returns true for victory by maze exit w/ princess
	char choice;
	bool moveComplete=false;
	cout<<"What's your move tough guy?"<<'\n'<<"[w=up,s=down, a=left, d=right, f=wait]"<<endl;
	cin>>choice;
	while(moveComplete==false)
	{
//hero move up if possible
		if(tolower(choice)=='w'&& (mazeArray[hero[0]-1][hero[1]] == ' '|| mazeArray[hero[0]-1][hero[1]] == 'D'|| mazeArray[hero[0]-1][hero[1]] == 'F' || mazeArray[hero[0]-1][hero[1]] == 'P' ))
		{
			if(mazeArray[hero[0]-1][hero[1]] == 'P')
			{
				cout<<"My Hero!! Now let's get out of here!!"<<endl;
				mazeArray[hero[0]][hero[1]]=' ';
				mazeArray[hero[0]-1][hero[1]]='H';
				hero[0]--;
				moveComplete=true;
			}
			else if(mazeArray[hero[0]-1][hero[1]] == 'F'&& mazeArray[hero[0]][hero[1]] == 'H')
			{
				cout<<"EPIC WIN!!"<<'\n'<<"YOU ARE THE GREATEST HERO OF ALL TIME!!!";
				moveComplete=true;
				return true;
			}
			else if(mazeArray[hero[0]-1][hero[1]] == 'F'&& mazeArray[hero[0]][hero[1]] == 'h')
			{
				cout<<"invalid move try again"<<endl;
				cout<<"What's your move tough guy?"<<'\n'<<"[w=up,s=down, a=left, d=right, f=wait]"<<endl;
				cin>>choice;
			}
			else
			{
				swap(mazeArray[hero[0]-1][hero[1]],mazeArray[hero[0]][hero[1]]);
				hero[0]--;
				moveComplete=true;
			}

		}
//hero move down if possible
		else if(tolower(choice) =='s' && (mazeArray[hero[0]+1][hero[1]] == ' '|| mazeArray[hero[0]+1][hero[1]] == 'D'|| mazeArray[hero[0]+1][hero[1]] == 'F' || mazeArray[hero[0]+1][hero[1]] == 'P' ))
		{
			if(mazeArray[hero[0]+1][hero[1]] == 'P')
			{
				cout<<"My Hero!! Now let's get out of here!!"<<endl;
				mazeArray[hero[0]][hero[1]]=' ';
				mazeArray[hero[0]+1][hero[1]]='H';
				hero[0]++;
				moveComplete=true;
			}
			else if(mazeArray[hero[0]+1][hero[1]] == 'F'&& mazeArray[hero[0]][hero[1]] == 'H')
			{
				cout<<"EPIC WIN!!"<<'\n'<<"YOU ARE THE GREATEST HERO OF ALL TIME!!!";
				moveComplete=true;
				return true;
			}
			else if(mazeArray[hero[0]+1][hero[1]] == 'F'&& mazeArray[hero[0]][hero[1]] == 'h')
			{
				cout<<"invalid move try again"<<endl;
				cout<<"What's your move tough guy?"<<'\n'<<"[w=up,s=down, a=left, d=right, f=wait]"<<endl;
				cin>>choice;
			}
			else
			{
				swap(mazeArray[hero[0]+1][hero[1]],mazeArray[hero[0]][hero[1]]);
				hero[0]++;
				moveComplete=true;
			}


		}
//hero move left if possible
		else if(tolower(choice=='a')&& (mazeArray[hero[0]][hero[1]-1] == ' '||mazeArray[hero[0]][hero[1]-1] == 'D'||mazeArray[hero[0]][hero[1]-1] == 'F'||mazeArray[hero[0]][hero[1]-1] == 'P') )
		{
			if(mazeArray[hero[0]][hero[1]-1] == 'P')
			{
				cout<<"My Hero!! Now let's get out of here!!"<<endl;
				mazeArray[hero[0]][hero[1]]=' ';
				mazeArray[hero[0]][hero[1]-1]='H';
				hero[1]--;
				moveComplete=true;
			}
			else if(mazeArray[hero[0]][hero[1]-1] == 'F'&& mazeArray[hero[0]][hero[1]] == 'H')
			{
				cout<<"EPIC WIN!!"<<'\n'<<"YOU ARE THE GREATEST HERO OF ALL TIME!!!";
				moveComplete=true;
				return true;
			}
			else if(mazeArray[hero[0]][hero[1]-1] == 'F'&& mazeArray[hero[0]][hero[1]] == 'h')
			{
				cout<<"invalid move try again"<<endl;
				cout<<"What's your move tough guy?"<<'\n'<<"[w=up,s=down, a=left, d=right, f=wait]"<<endl;
				cin>>choice;
			}
			else
			{
				swap(mazeArray[hero[0]][hero[1]-1],mazeArray[hero[0]][hero[1]]);
				hero[1]--;
				moveComplete=true;
			}

		}
//hero move right if possible
		else if(tolower(choice)=='d' && (mazeArray[hero[0]][hero[1]+1] == ' '||mazeArray[hero[0]][hero[1]+1] == 'D'||mazeArray[hero[0]][hero[1]+1] == 'F'||mazeArray[hero[0]][hero[1]+1] == 'P') )
		{
			if(mazeArray[hero[0]][hero[1]+1] == 'P')
			{
				cout<<"My Hero!! Now let's get out of here!!"<<endl;
				mazeArray[hero[0]][hero[1]]=' ';
				mazeArray[hero[0]][hero[1]+1]='H';
				hero[1]++;
				moveComplete=true;
			}
			else if(mazeArray[hero[0]][hero[1]+1] == 'F'&& mazeArray[hero[0]][hero[1]] == 'H')
			{
				cout<<"EPIC WIN!!"<<'\n'<<"YOU ARE THE GREATEST HERO OF ALL TIME!!!";
				moveComplete=true;
				return true;
			}
			else if(mazeArray[hero[0]][hero[1]+1] == 'F'&& mazeArray[hero[0]][hero[1]] == 'h')
			{
				cout<<"invalid move try again"<<endl;
				cout<<"What's your move tough guy?"<<'\n'<<"[w=up,s=down, a=left, d=right, f=wait]"<<endl;
				cin>>choice;
			}
			else
			{
				swap(mazeArray[hero[0]][hero[1]+1],mazeArray[hero[0]][hero[1]]);
				hero[1]++;
				moveComplete=true;
			}

		}
		else if(tolower(choice=='f'))
			moveComplete=true;
		else
		{
			cout<<"invalid move try again"<<endl;
			cout<<"What's your move tough guy?"<<'\n'<<"[w=up,s=down, a=left, d=right, f=wait]"<<endl;
			cin>>choice;
		}
	}
	return false;
}

void moveDragon(char** mazeArray, int* hero, int* dragon)//Each call this function moves the dragon 1 space if it rolls a number for an available space
{
	srand (time(NULL));
	int* dragonMove=new int(rand()%4);
//dragon move up if space is available
	if (*dragonMove==0 && ( mazeArray[dragon[0]-1][dragon[1]]==' ' ))
	{
		swap(mazeArray[dragon[0]-1][dragon[1]], mazeArray[dragon[0]][dragon[1]]);
		dragon[0]--;
	}
// dragon move down if space is available
	else if (*dragonMove==1 && ( mazeArray[dragon[0]+1][dragon[1]]==' '))
	{
		swap(mazeArray[dragon[0]+1][dragon[1]], mazeArray[dragon[0]][dragon[1]]);
		dragon[0]++;
	}
//dragon move left if space is available
	else if (*dragonMove==2 && ( mazeArray[dragon[0]][dragon[1]-1]==' ' ))
	{
		swap(mazeArray[dragon[0]][dragon[1]-1], mazeArray[dragon[0]][dragon[1]]);
		dragon[1]--;
	}
//dragon move right if space is available
	else if (*dragonMove==3 && ( mazeArray[dragon[0]][dragon[1]+1]==' '))
	{
		swap(mazeArray[dragon[0]][dragon[1]+1], mazeArray[dragon[0]][dragon[1]]);
		dragon[1]++;
	}

}
