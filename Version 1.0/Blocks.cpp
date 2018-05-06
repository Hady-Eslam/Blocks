#include<iostream>
#include<ctime>
#include<stdlib.h>
#include<windows.h>
#include<dos.h>
#include<conio.h>
using namespace std;

void start(int );
void show();
int check();
int play();
int check_cell(int ,int);
void remove(int ,int);
void back();
void SetColor(int );
char blocks[16][11];

int main()
{
	int revalue,heart=50,hard=3;
	for (int count=1;;count++)
	{
		start(hard);
		revalue=play();
		heart-=revalue;
		cout<<"heart = "<<heart<<endl<<endl;
		if (heart<=0)
			break;
		if (count%2==0)
			hard++;
	}
	return 0;
}

void start (int hard)
{
	int num;
	srand(time(NULL));
	for (int i=0;i<15;i++)
		for (int j=0;j<10;j++)
		{
			num=rand()%hard;
			blocks[i][j]=char (num+65);
		}
	for (int j=0;j<11;j++)
		blocks[15][j]='0';
	for (int i=0;i<16;i++)
		blocks[i][10]='0';
}

void show()
{
	cout<<"   ";
	for (int j=0;j<10;j++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<j+1<<"     ";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout<<endl<<"............................................................"<<endl;
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<10;j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout<<"|  ";
			if (int (blocks[i][j])>=65)
			{
				int num=int (blocks[i][j])-64;
				SetColor(num);
				cout<<blocks[i][j]<<"  ";
			}
			else 
				cout<<"   ";
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout<<"|  "<<i+1<<endl
			<<"............................................................"<<endl;
	}
}

int check()
{
	int no_problem=0,count=0;
	for (int i=0;i<15;i++)
	{
		for (int j=0;j<10;j++)
		{
			if (blocks[i][j]!='0')
			{
				if (i+1<15&&blocks[i][j]==blocks[i+1][j])
					no_problem=1;
				if (i-1>=0&&blocks[i][j]==blocks[i-1][j])
					no_problem=1;
				if (j+1<10&&blocks[i][j]==blocks[i][j+1])
					no_problem=1;
				if (j-1>=0&&blocks[i][j]==blocks[i][j-1])
					no_problem=1;
			}
			if (no_problem==1)
				break;
		}
		if (no_problem==1)
			break;
	}
	if (no_problem==1)
		return -1;
	else
	{
		for (int i=0;i<15;i++)
			for (int j=0;j<10;j++)
				if (blocks[i][j]!='0')
					count++;
		return count;
	}
}

int play()
{
	int revalue,row,col;
	for (;;)
	{
		show();
		revalue=check();
		if (revalue!=-1)
			return revalue;
		cout<<"Enter the row and the column"<<endl;
		for (;;)
		{
			cin>>row>>col;
			row--,col--;
			revalue=check_cell(row,col);
			if (revalue==0)
				break;
			cout<<"Wrong Play"<<endl;
		}
		remove(row,col);
	}
}

int check_cell(int row,int col)
{
	if (blocks[row+1][col]==blocks[row][col]||blocks[row-1][col]==blocks[row][col]||blocks[row][col+1]==blocks[row][col]||blocks[row][col-1]==blocks[row][col])
		return 0;
	else return 1;
}

void remove(int row,int col)
{
	int block,stop;
	block=blocks[row][col];
	blocks[row][col]='1';
	for (;;)
	{
		stop=0;
		for (int i=0;i<15;i++)
			for (int j=0;j<10;j++)
				if (blocks[i][j]==block&&(blocks[i+1][j]=='1'||blocks[i-1][j]=='1'||blocks[i][j+1]=='1'||blocks[i][j-1]=='1'))
					blocks[i][j]='1',stop=1;
		if (stop==0)
			break;
	}
	for (int i=0;i<15;i++)
		for (int j=0;j<10;j++)
			if (blocks[i][j]=='1')
				blocks[i][j]='0';
	back();
}

void back()
{
	int indix,replace[16],stop,stop1,count=0;
	for (int j=0;j<10;j++)
	{
		indix=0;
		for (int i=14;i>=0;i--)
			if (blocks[i][j]!='0')
				replace[indix]=blocks[i][j],indix++;
		if (indix!=0)
		{
			for (int i=14,l=0;l<indix;l++,i--)
				blocks[i][j]=replace[l];
			for (int i=14-indix;i>=0;i--)
				blocks[i][j]='0';
		}
	}

	for (int i=14;i>=0;i--)
	{
		indix=0;
		if (i==14)
		{
			count=0,stop=stop1=-1;
			for (int j=0;j<10;j++)
			{
				if (blocks[i][j]=='0')
					stop=j;
				if (stop!=-1)
					break;
			}
			if (stop!=-1)
			{
				for (int j=stop+1;j<10;j++)
				{
					if (blocks[i][j]!='0')
						stop1=j;
					if (stop1!=-1)
						break;
				}
				if (stop1!=-1)
				{
					count=stop1-stop;
					for (int j=0;j<10;j++)
						if (blocks[i][j]!='0')
							replace[indix]=blocks[i][j],indix++;
					for (int j=0,l=0;l<indix;j++,l++)
						blocks[i][j]=replace[l];
					for (int j=indix;j<10;j++)
						blocks[i][j]='0';
				}
			}
		}
		else 
		{
			if (count!=0)
			{
				for (int j=stop;j<10;j++)
						replace[indix]=blocks[i][j],indix++;
				if (indix!=0)
				{
					for (int j=stop;j<10;j++)
						blocks[i][j]='0';
					for (int j=stop,l=count;l<indix;l++,j++)
						blocks[i][j]=replace[l];
				}
			}
		}
	}
}

void SetColor(int num)

{
	if (num==1)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
	else if (num==2)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	else if (num==3)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	else if (num==4)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	else if (num==5)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
	else if (num==6)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
	else if (num==7)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	else if (num==8)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	else if (num==9)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
	else if (num==10)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	else if (num==11)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	else if (num==12)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	else if (num==13)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
	else if (num==14)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	else if (num==15)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}
