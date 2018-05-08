#include<iostream.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<fstream.h>
#define XX cout<<"("<<ROW+1<<","<<COL+1<<")"<<"value="<<value[ROW+1][COL+1]<<"Fik"<<FiK[0]<<"."<<Space[0]<<","<<FiK[1]<<"."<<Space[1]<<","<<FiK[2]<<"."<<Space[2]<<","<<FiK[3]<<"."<<Space[3]<<","<<FiK[4]<<"."<<Space[4]<<","<<FiK[5]<<"."<<Space[5]<<","<<FiK[6]<<"."<<Space[6]<<","<<FiK[7]<<"."<<Space[7]<<"Death"<<Death[0]<<Death[1]<<Death[2]<<Death[3]<<Death[4]<<Death[5]<<Death[6]<<Death[7]<<endl;


#define Alive2 2
#define Alive3 4
#define Alive4 40
#define Alive5 160
#define Death2 1
#define Death3 3
#define Death4 5
#define Kong2 2
#define Kong3 3
#define Kong4 4
#define KS2 1
#define KS3 2
#define KS4 3
int NOW=1;
int count=0;
#define N 5
#define Depth 3
#define Double3 16
#define Double4 68
#define One3One4 68


struct lb
{
	int Value;
	int SUM;
	lb *next[N];
};

class CGobang
{
private:
	char chSort;
	char enchSort;
	int nWin;
	int nLose;
	static int nDraw;
	static char SaveachBoard[15][15][225];
	static int nSize;                
	static int SaveRow[225];
	static int SaveCol[225];
	

public: 
	static char virtualBoard[15][15][6];
	static int SpotsOnBoard;
	static int NewRow;
	static int NewCol;
	static int virtualNewRow;
	static int virtualNewCol;
	static char achBoard[15][15];
	CGobang(char,char);
	void PlayTurn(int x,int y);
	void AITurn(int K);
	void virtualTurn(int returnvalue,int t);

	void AIJudge(int ReturnV[20],int n,int deep); 
	static int AIthink(CGobang AI);
	static int Judge();
	void Win(void);
	void Lose(void);
	static void Draw(void);
	void PrintInfo(void);
	static void PrintBoard(void);
	static int GetFull();
	static void InitialBoard(void);
	static void SaveBoard();
	static void Match(int value[][16],int specificvalue[][16]);
	static void UndoAI(void);
	static void UndoyouwhenAI();
};
int CGobang::SpotsOnBoard=0;
int CGobang::nSize=15;
int CGobang::nDraw=0;
int CGobang::NewCol=0;
int CGobang::NewRow=0;
int CGobang::SaveRow[225]={0};
int CGobang::SaveCol[225]={0};
char CGobang::achBoard[15][15]={0};     //静态二维数组的初始化
char CGobang::SaveachBoard[15][15][225]={0};//静态三维数组的初始化
void OperatingFunction(int i);
int Menu();
int CGobang::virtualNewCol=0;
int CGobang::virtualNewRow=0;
char CGobang::virtualBoard[15][15][6]={0};
void getchoice(int& choice,int ,int);

void main()
{
	OperatingFunction(Menu());
}


CGobang::CGobang(char chsort,char enchsort)
{chSort=chsort;enchSort=enchsort;nWin=0;nLose=0;nDraw=0;nSize=15;}
void CGobang::PlayTurn(int x,int y)
{   
	
	
	CGobang::achBoard[x-1][y-1]=chSort;
	for(int row=0;row<15;row++)
		for(int col=0;col<15;col++)
		{
		     SaveachBoard[row][col][SpotsOnBoard]=achBoard[row][col];
		}
	CGobang::SaveRow[SpotsOnBoard]=x;
	CGobang::SaveCol[SpotsOnBoard]=y;
	CGobang::NewRow=x;
	CGobang::NewCol=y;
	SpotsOnBoard++;
}

void CGobang::AITurn(int K)
{
	int D;
	CGobang AI(chSort,enchSort);
	int ReturnV[20];
		for(int i=0;i<20;i++)
			ReturnV[i]=-1;
	int x,y;
	if(SpotsOnBoard==1)
	{
		srand(time(NULL));
		int randnum=rand();
		if(randnum%8==0)
		{
			x=NewRow-1;
	        y=NewCol-1;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==1)
		{
			x=NewRow-1;
	        y=NewCol;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==2)
		{
			x=NewRow-1;
	        y=NewCol+1;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==3)
		{
			x=NewRow;
	        y=NewCol-1;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==4)
		{
			x=NewRow-1;
	        y=NewCol+1;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==5)
		{
			x=NewRow+1;
	        y=NewCol-1;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==6)
		{
			x=NewRow+1;
	        y=NewCol;
	        achBoard[x-1][y-1]=chSort;
		}
		else if(randnum%8==7)
		{
			x=NewRow+1;
	        y=NewCol+1;
	        achBoard[x-1][y-1]=chSort;
		}
	}
	else if(SpotsOnBoard<=2||K==0)
	{
	AIJudge(ReturnV,0,0);
    x=ReturnV[0]/100000000;
	y=ReturnV[0]/1000000%100;
	achBoard[x-1][y-1]=chSort;
	}
	else
	{
		D=CGobang::AIthink(AI);
		//cout<<SpotsOnBoard<<"aaaaaaaaaaaaaaaa";
	x=D/100000000;
	y=D/1000000%100;
	achBoard[x-1][y-1]=chSort;
	}
	for(int row=0;row<15;row++)
		for(int col=0;col<15;col++)
		{
		     SaveachBoard[row][col][SpotsOnBoard]=achBoard[row][col];
		}
	CGobang::SaveRow[SpotsOnBoard]=x;
	CGobang::SaveCol[SpotsOnBoard]=y;
	CGobang::NewRow=x;
	CGobang::NewCol=y;
	SpotsOnBoard++;
	//cout<<x+1<<endl<<y+1<<"??????????????????????????????????????????";
	
}
void CGobang::virtualTurn(int ReturnV,int t)
{
	int x,y;
	//cout<<"aaaaaaaaaaaaaaaaaaaaaaa";
	x=ReturnV/100000000;
	y=ReturnV/1000000%100;
	CGobang::virtualBoard[x-1][y-1][t]=chSort;
	CGobang::virtualNewRow=x;
	CGobang::virtualNewCol=y;
}
int CGobang::Judge()
{
	int k;
	k=1;
	//cout<<k<<endl;cout<<NewRow<<' '<<NewCol;             /////////////////////////////////////
	for(int i=1;i<=4;i++)
		{
			if((CGobang::NewRow-i)>=1&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1-i][CGobang::NewCol-1])
				k++;
			else
				break;
		}
		for(i=1;i<=4;i++)
		{
			if((CGobang::NewRow+i)<=nSize&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1+i][CGobang::NewCol-1])
				k++;
			else
				break;
		}
		if(k>=5)
		{return 1;}
	
		
		
		
		
		
    k=1;
	for(i=1;i<=4;i++)
		{
			if((CGobang::NewCol-i)>=1&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1][CGobang::NewCol-1-i])
				k++;
			else
				break;
		}
		for(i=1;i<=4;i++)
		{
			if((CGobang::NewCol+i)<=nSize&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1][CGobang::NewCol-1+i])
				k++;
			else
				break;
		}
		if(k>=5)
			return 1;




	k=1;
	for(i=1;i<=4;i++)
		{
			if((CGobang::NewRow-i)>=1&&(CGobang::NewCol-i)>=1&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1-i][CGobang::NewCol-1-i])
				k++;
			else
				break;
		}
		for(i=1;i<=4;i++)
		{
			if((CGobang::NewRow+i)<=nSize&&(CGobang::NewCol+i)<=nSize&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1+i][CGobang::NewCol-1+i])
				k++;
			else
				break;
		}
		if(k>=5)
			return 1;


	k=1;
	for(i=1;i<=4;i++)
		{
			if((CGobang::NewRow-i)>=1&&(CGobang::NewCol+i)<=nSize&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1-i][CGobang::NewCol-1+i])
				k++;
			else
				break;
		}
		for(i=1;i<=4;i++)
		{
			if((CGobang::NewRow+i)<=nSize&&(CGobang::NewCol-i)>=1&&achBoard[CGobang::NewRow-1][CGobang::NewCol-1]==achBoard[CGobang::NewRow-1+i][CGobang::NewCol-1-i])
				k++;
			else
				break;
		}
		if(k>=5)
			return 1;
		return 0;
}

void CGobang::Win(void)
{
	cout<<chSort<<" player wins the game!"<<endl;
	nWin++;
}
void CGobang::Lose(void)
{
	nLose++;
}
void CGobang::Draw()
{
	CGobang::nDraw++;
	cout<<"Draw!"<<endl;
}
void CGobang::PrintInfo(void)
{
	cout<<chSort<<" wins "<<nWin<<" times,loses "<<nLose<<" times,draws "<<nDraw<<" times."<<endl;
}
void CGobang::PrintBoard()
{
	cout<<endl;
	cout<<"  ";
	for(int j=1;j<=nSize;j++)
		if(j<10)
		cout<<j<<"   ";
		else
			cout<<j<<"  ";
	cout<<endl;
	for(int m=1;m<=nSize;m++)
	{
		if(m<10)
		cout<<' '<<m<<' '<<achBoard[m-1][0];
		else
		cout<<m<<' '<<achBoard[m-1][0];
        for(int n=1;n<nSize;n++)
			cout<<" | "<<achBoard[m-1][n];
		cout<<endl;
		cout<<"  ---";
		for(int d=1;d<nSize;d++)
			cout<<"|---";
		cout<<endl;
	}
	cout<<endl<<endl;
}
int CGobang::GetFull()
{
	for(int ROW=0;ROW<nSize;ROW++)
			for(int COLUMN=0;COLUMN<nSize;COLUMN++)
			{
				if(CGobang::achBoard[ROW][COLUMN]==' ')
					return 0;
			}
			return 1;
}
void CGobang::InitialBoard(void)
{
	for(int ROW=0;ROW<nSize;ROW++)
			for(int COLUMN=0;COLUMN<nSize;COLUMN++)
			{
				CGobang::achBoard[ROW][COLUMN]=' ';
				for(int i=0;i<225;i++)
			    SaveachBoard[ROW][COLUMN][i]=' ';
			}

	SpotsOnBoard=0;
}
void CGobang::AIJudge(int ReturnV[20],int n,int deep=0)             ///////////////////////////////////
{
	int specificValue[16][16];
	int VALUE=-99999999;
	int value[16][16];
	for(int count1=1;count1<=15;count1++)
		for(int count2=1;count2<=15;count2++)
			value[count1][count2]=-9999;
	int k[2],FiK[8];
	int Death[8];
	int space[2];
	int TIME=0;
	int Space[8]={0,0,0,0,0,0,0,0};
    int flag;
	char Board[15][15];
	if(n)
	{
		for(int ii=0;ii<15;ii++)
			for(int jj=0;jj<15;jj++)
				Board[ii][jj]=virtualBoard[ii][jj][deep];
	}
	else
	{
		for(int ii=0;ii<15;ii++)
			for(int jj=0;jj<15;jj++)
				Board[ii][jj]=achBoard[ii][jj];
	}


	for(int ROW=0;ROW<nSize;ROW++)
		for(int COL=0;COL<nSize;COL++)
		{
			if(Board[ROW][COL]!=' ')
			{//cout<<endl<<"("<<ROW<<","<<COL<<")"<<endl;
				continue;}
				value[ROW+1][COL+1]=0;





			flag=1;
			Death[0]=0;
			k[0]=1;
			k[1]=1;
		
			space[0]=0;
			space[1]=0;
			Space[0]=0;
			for(int i=1;i<=4;i++)
			{
				if(ROW-i>=0&&Board[ROW-i][COL]==chSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[0]++;
						flag=0;
					}
				}
				else if(ROW-i<0)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[0]++;
						break;
					}
				}
				else if(Board[ROW-i][COL]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW-i][COL]!=chSort&&Board[ROW-i][COL]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW+1-i][COL]==chSort)
						{Death[0]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[0]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(ROW+i<15&&Board[ROW+i][COL]==chSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[0]++;
						flag=0;
					}
				}
				else if(ROW+i>=15)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[0]++;
						break;
					}
				}
				else if(Board[ROW+i][COL]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW+i][COL]!=chSort&&Board[ROW+i][COL]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW-1+i][COL]==chSort)
						{Death[0]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[0]++;
						break;
					}
				}
				//Space[0]=space[0]+space[1];
				if(Space[0]==2)
					FiK[0]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[0]=k[0]+k[1]-1;





		    flag=1;
			Death[1]=0;
			k[0]=1;
			k[1]=1;
			space[0]=0;
			space[1]=0;
			Space[1]=0;
			for(i=1;i<=4;i++)
			{
				if(ROW-i>=0&&Board[ROW][COL-i]==chSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[1]++;
						flag=0;
					}
				}
				else if(COL-i<0)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[1]++;
						break;
					}
				}
				else if(Board[ROW][COL-i]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW][COL-i]!=chSort&&Board[ROW][COL-i]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW][COL+1-i]==chSort)
						{Death[1]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[1]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(COL+i<15&&Board[ROW][COL+i]==chSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[1]++;
						flag=0;
					}
				}
				else if(COL+i>=15)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[1]++;
						break;
					}
				}
				else if(Board[ROW][COL+i]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW][COL+i]!=chSort&&Board[ROW][COL+i]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW][COL-1+i]==chSort)
						{Death[1]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[1]++;
						break;
					}
				}
				//Space[1]=space[0]+space[1];
				if(Space[1]==2)
					FiK[1]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[1]=k[0]+k[1]-1;
		







		    flag=1;
			Death[2]=0;
			k[0]=1;
			k[1]=1;
			space[0]=0;
			space[1]=0;
			Space[2]=0;
			for(i=1;i<=4;i++)
			{
				if(COL-i>=0&&ROW-i>=0&&Board[ROW-i][COL-i]==chSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[2]++;
						flag=0;
					}
				}
				else if(COL-i<0||ROW-i<0)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[2]++;
						break;
					}
				}
				else if(Board[ROW-i][COL-i]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW-i][COL-i]!=chSort&&Board[ROW-i][COL-i]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW+1-i][COL+1-i]==chSort)
						{Death[2]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[2]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(COL+i<15&&ROW+i<15&&Board[ROW+i][COL+i]==chSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[2]++;
						flag=0;
					}
				}
				else if(COL+i>=15||ROW+i>=15)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[2]++;
						break;
					}
				}
				else if(Board[ROW+i][COL+i]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW+i][COL+i]!=chSort&&Board[ROW+i][COL+i]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW-1+i][COL-1+i]==chSort)
						{Death[2]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[2]++;
						break;
					}
				}
				if(Space[2]==2)
					FiK[2]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[2]=k[0]+k[1]-1;



		  flag=1;
			Death[3]=0;
			k[0]=1;
			k[1]=1;
			space[0]=0;
			space[1]=0;
			Space[3]=0;
			for(i=1;i<=4;i++)
			{
				if(COL-i>=0&&ROW+i<15&&Board[ROW+i][COL-i]==chSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[3]++;
						flag=0;
					}
				}
				else if(COL-i<0||ROW+i>=15)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[3]++;
						break;
					}
				}
				else if(Board[ROW+i][COL-i]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW+i][COL-i]!=chSort&&Board[ROW+i][COL-i]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW-1+i][COL+1-i]==chSort)
						{Death[3]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[3]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(COL+i<15&&ROW-i>=0&&Board[ROW-i][COL+i]==chSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[3]++;
						flag=0;
					}
				}
				else if(COL+i>=15||ROW-i<0)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[3]++;
						break;
					}
				}
				else if(Board[ROW-i][COL+i]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW-i][COL+i]!=chSort&&Board[ROW-i][COL+i]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW-i+1][COL-1+i]==chSort)
						{Death[3]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[3]++;
						break;
					}
				}
				if(Space[3]==2)
					FiK[3]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[3]=k[0]+k[1]-1;
				
				
				
		



			flag=1;
			Death[4]=0;
			k[0]=1;
			k[1]=1;
		
			space[0]=0;
			space[1]=0;
			Space[4]=0;
			for(i=1;i<=4;i++)
			{
				if(ROW-i>=0&&Board[ROW-i][COL]==enchSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[4]++;
						flag=0;
					}
				}
				else if(ROW-i<0)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[4]++;
						break;
					}
				}
				else if(Board[ROW-i][COL]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW-i][COL]!=enchSort&&Board[ROW-i][COL]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW+1-i][COL]==enchSort)
						{Death[4]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[4]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(ROW+i<15&&Board[ROW+i][COL]==enchSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[4]++;
						flag=0;
					}
				}
				else if(ROW+i>=15)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[4]++;
						break;
					}
				}
				else if(Board[ROW+i][COL]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW+i][COL]!=enchSort&&Board[ROW+i][COL]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW-1+i][COL]==enchSort)
						{Death[4]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[4]++;
						break;
					}
				}
				//Space[4]=space[0]+space[1];
				if(Space[4]==2)
					FiK[4]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[4]=k[0]+k[1]-1;
					




	    flag=1;
			Death[5]=0;
			k[0]=1;
			k[1]=1;
			space[0]=0;
			space[1]=0;
			Space[5]=0;
			for(i=1;i<=4;i++)
			{
				if(ROW-i>=0&&Board[ROW][COL-i]==enchSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[5]++;
						flag=0;
					}
				}
				else if(COL-i<0)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[5]++;
						break;
					}
				}
				else if(Board[ROW][COL-i]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW][COL-i]!=enchSort&&Board[ROW][COL-i]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW][COL+1-i]==enchSort)
						{Death[5]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[5]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(COL+i<15&&Board[ROW][COL+i]==enchSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[5]++;
						flag=0;
					}
				}
				else if(COL+i>=15)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[5]++;
						break;
					}
				}
				else if(Board[ROW][COL+i]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW][COL+i]!=enchSort&&Board[ROW][COL+i]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW][COL-1+i]==enchSort)
						{Death[5]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[5]++;
						break;
					}
				}
				//Space[5]=space[0]+space[1];
				if(Space[5]==2)
					FiK[5]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[5]=k[0]+k[1]-1;
				if(FiK[5]==2&&Death[5]==0&&Space[5]==0)





		   flag=1;
			Death[6]=0;
			k[0]=1;
			k[1]=1;
			space[0]=0;
			space[1]=0;
			Space[6]=0;
			for(i=1;i<=4;i++)
			{
				if(COL-i>=0&&ROW-i>=0&&Board[ROW-i][COL-i]==enchSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[6]++;
						flag=0;
					}
				}
				else if(COL-i<0||ROW-i<0)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						Death[6]++;
						break;
					}
				}
				else if(Board[ROW-i][COL-i]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW-i][COL-i]!=enchSort&&Board[ROW-i][COL-i]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW+1-i][COL+1-i]==enchSort)
						{Death[6]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[6]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(COL+i<15&&ROW+i<15&&Board[ROW+i][COL+i]==enchSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[6]++;
						flag=0;
					}
				}
				else if(COL+i>=15||ROW+i>=15)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[6]++;
						break;
					}
				}
				else if(Board[ROW+i][COL+i]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW+i][COL+i]!=enchSort&&Board[ROW+i][COL+i]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW-1+i][COL-1+i]==enchSort)
						{Death[6]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[6]++;
						break;
					}
				}
				if(Space[6]==2)
					FiK[6]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[6]=k[0]+k[1]-1;



		  flag=1;
			Death[7]=0;
			k[0]=1;
			k[1]=1;
			space[0]=0;
			space[1]=0;
			Space[7]=0;
			for(i=1;i<=4;i++)
			{
				if(COL-i>=0&&ROW+i<15&&Board[ROW+i][COL-i]==enchSort)
				{
					k[0]++;
					if(space[0]&&flag)
					{
						Space[7]++;
						flag=0;
					}
				}
				else if(COL-i<0||ROW+i>=15)
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					else
					{
						
						Death[7]++;
						break;
					}
				}
				else if(Board[ROW+i][COL-i]==' ')
				{
					if(space[0])
					{
						space[0]--;
						break;
					}
					space[0]++;
				}
				else  if(Board[ROW+i][COL-i]!=enchSort&&Board[ROW+i][COL-i]!=' ')
				{
					if(space[0])
					{
						if(Board[ROW-1+i][COL+1-i]==enchSort)
						{Death[7]++;space[0]--;break;}
						else
						{
						space[0]--;
						break;
						}
					}
					else
					{
						Death[7]++;
						break;
					}
				}
			}
			flag=1;
				for(i=1;i<=4;i++)
				if(COL+i<15&&ROW-i>=0&&Board[ROW-i][COL+i]==enchSort)
				{
					k[1]++;
					if(space[1]&&flag)
					{
						Space[7]++;
						flag=0;
					}
				}
				else if(COL+i>=15||ROW-i<0)
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					else
					{
						Death[7]++;
						break;
					}
				}
				else if(Board[ROW-i][COL+i]==' ')
				{
					if(space[1])
					{
						space[1]--;
						break;
					}
					space[1]++;
				}
				else  if(Board[ROW-i][COL+i]!=enchSort&&Board[ROW-i][COL+i]!=' ')
				{
					if(space[1])
					{
						if(Board[ROW-i+1][COL-1+i]==enchSort)
						{Death[7]++;space[1]--;break;}
						else
						{
						space[1]--;
						break;
						}
					}
					else
					{
						Death[7]++;
						break;
					}
				}
				if(Space[7]==2)
					FiK[7]=k[0]>k[1]?k[0]:k[1];
				else
					FiK[7]=k[0]+k[1]-1;


				int F3=0,F4=0,F5=0,E3=0,E4=0,E5=0;
				
				for(int j=0;j<=7;j++)
				{
				if(j==4)
				{
					specificValue[ROW+1][COL+1]=value[ROW+1][COL+1]*1000;
				}
				if(FiK[j]==2&&Death[j]==0&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Alive2;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==3&&Death[j]==0&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Alive3;
					if(j<=3)
					{value[ROW+1][COL+1]++;F3++;}
					else
						E3++;
				}
				else if(FiK[j]==4&&Death[j]==0&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Alive4;
					if(j<=3)
					{value[ROW+1][COL+1]++;F4++;}
					else
						E4++;
				}
				else if(FiK[j]==5&&Death[j]==0&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Alive5;
				    if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==2&&Death[j]==1&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Death2;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==3&&Death[j]==1&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Death3;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==4&&Death[j]==1&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Death4;
					if(j<=3)
					{value[ROW+1][COL+1]++;F4++;}
					else
						E4++;
				}
				else if(FiK[j]==5&&Death[j]>=1&&Space[j]==0)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Alive5;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==2&&Death[j]==0&&Space[j]>=1)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Kong2;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==3&&Death[j]==0&&Space[j]>=1)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Kong3;
					if(j<=3)
					{value[ROW+1][COL+1]++;F3++;}
					else
						E3++;
				}
				else if(FiK[j]==4&&Death[j]==0&&Space[j]>=1)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+Kong4;
					if(j<=3)
					{value[ROW+1][COL+1]++;F4++;}
					else
						E4++;
				}
				else if(FiK[j]==2&&Death[j]>=1&&Space[j]>=1)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+KS2;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==3&&Death[j]>=1&&Space[j]>=1)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+KS3;
					if(j<=3)
						value[ROW+1][COL+1]++;
				}
				else if(FiK[j]==4&&Death[j]>=1&&Space[j]>=1)
				{
					value[ROW+1][COL+1]=value[ROW+1][COL+1]+KS4;
					if(j<=3)
					{value[ROW+1][COL+1]++;F4++;}
					else
					{E4++;}
				}
				}
			
                specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]+value[ROW+1][COL+1]-specificValue[ROW+1][COL+1]/1000;
				if(F4>=2)
				{specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]%1000+Double4*1000;value[ROW+1][COL+1]=value[ROW+1][COL+1]+Double4;}
				else if(F4==1&&F3>=1)
				{specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]%1000+One3One4*1000;value[ROW+1][COL+1]=value[ROW+1][COL+1]+One3One4;}
				else if(F3>=2)
				{specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]%1000+Double3*1000;value[ROW+1][COL+1]=value[ROW+1][COL+1]+Double3;}
				


				if(E4>=2)
				{specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]/1000+Double4;value[ROW+1][COL+1]=value[ROW+1][COL+1]+Double4;}
				else if(E4==1&&E3>=1)
				{specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]/1000+One3One4;value[ROW+1][COL+1]=value[ROW+1][COL+1]+One3One4;}
				else if(E3>=2)
				{specificValue[ROW+1][COL+1]=specificValue[ROW+1][COL+1]/1000+Double3;value[ROW+1][COL+1]=value[ROW+1][COL+1]+Double3;}
				//cout<<specificValue[ROW+1][COL+1];
		
			

	

				//XX;//还未匹配过的初始值

          }
		    

			CGobang::Match(value,specificValue);//匹配已经保存的棋局，并且改变value值
			
		

			
				


				for(ROW=0;ROW<15;ROW++)
					for(int COL=0;COL<15;COL++)
					{
						//for(int d=0;d<20;d++)
						//	cout<<ReturnV[d]<<'\t';
						//cout<<endl;
						int j=0;
						for(;j<20;j++)
							if(value[ROW+1][COL+1]>ReturnV[j]%1000+ReturnV[j]/1000%1000)
							{
								for(int m=19;m>j;m--)
								{ReturnV[m]=ReturnV[m-1];}
								ReturnV[j]=(ROW+1)*10*10*10*10*10*10*10*10+(COL+1)*10*10*10*10*10*10+specificValue[ROW+1][COL+1];
								break;
							}
							else if(value[ROW+1][COL+1]==ReturnV[j]%1000+ReturnV[j]/1000%1000)
							{
								//cout<<j<<endl;
							    
								if((ROW-7)*(ROW-7)+(COL-7)*(COL-7)<(ReturnV[j]/100000000-8)*(ReturnV[j]/100000000-8)+(ReturnV[j]/1000000%100-8)*(ReturnV[j]/1000000%100-8))
								{//	cout<<"("<<ReturnV[j]/100000<<","<<ReturnV[j]/1000%100<<")"<<"大于("<<ROW+1<<","<<COL+1<<")"<<endl;
							     for(int m=19;m>j;m--)
								{ReturnV[m]=ReturnV[m-1];}
								ReturnV[j]=(ROW+1)*10*10*10*10*10*10*10*10+(COL+1)*10*10*10*10*10*10+specificValue[ROW+1][COL+1];
								break;
								}
						        else if((ROW-7)*(ROW-7)+(COL-7)*(COL-7)==(ReturnV[j]/100000000-8)*(ReturnV[j]/100000000-8)+(ReturnV[j]/1000000%100-8)*(ReturnV[j]/1000000%100-8))
								{
								//	cout<<"("<<ReturnV[j]/100000<<","<<ReturnV[j]/1000%100<<")"<<"等于("<<ROW+1<<","<<COL+1<<")"<<endl;
							     srand(time(NULL));
						             if(rand()%2)
									 {
										//cout<<"("<<ReturnV[j]/100000<<","<<ReturnV[j]/1000%100<<")"<<"排在("<<ROW+1<<","<<COL+1<<")"<<"后面"<<endl;
							          for(int m=19;m>j;m--)
									  {ReturnV[m]=ReturnV[m-1];}
								       ReturnV[j]=(ROW+1)*10*10*10*10*10*10*10*10+(COL+1)*10*10*10*10*10*10+specificValue[ROW+1][COL+1];
									   break;
									 }
							     continue;
									 
								}
								else
									//cout<<"("<<ReturnV[j]/100000<<","<<ReturnV[j]/1000%100<<")"<<"小于("<<ROW+1<<","<<COL+1<<")"<<endl;
									;

							}
					
					}

       
}












void CGobang::Match(int value[][16],int specificvalue[][16])
{
	
	ifstream infile1("learn.txt",ios::nocreate);
	while(!infile1.eof())
	{
		int decrease;
     	int flag=0;
	    int spotsonboard;
	    int Lastrow,Lastcol;//16*16
		char SavedBoard[16][16];
		infile1>>spotsonboard;
		infile1>>Lastrow>>Lastcol>>decrease;
		for(int row=1;row<=15;row++)
			for(int col=1;col<=15;col++)
				infile1>>SavedBoard[row][col];
		if(spotsonboard==SpotsOnBoard)
		{
			//cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		for(row=1;row<=15;row++)
			for(int col=1;col<=15;col++)
				if(SavedBoard[row][col]=='#')
					SavedBoard[row][col]=' ';
		for(row=0;row<15;row++)
			for(int col=0;col<15;col++)
			{
				if(SavedBoard[1+row][1+col]!=achBoard[row][col])
				{
					flag=1;
					//cout<<"["<<1+row<<"]["<<1+col<<"]"<<"dont match,because formal is:"<<SavedBoard[1+row][1+col]<<"but the later is"<<achBoard[row][col]<<endl;
				}
				
			}
		}
		else
			flag=1;


		if(!flag)
		{

			value[Lastrow][Lastcol]=value[Lastrow][Lastcol]-decrease;
			specificvalue[Lastrow][Lastcol]=specificvalue[Lastrow][Lastcol]-decrease*1000;
		    //cout<<"done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		}
	}
	infile1.close();

}
void CGobang::SaveBoard()
{
	ofstream outfile("learn.txt",ios::app);
	outfile<<SpotsOnBoard-1<<' '<<NewRow<<' '<<NewCol<<' '<<1<<endl;
	for(int i=0;i<15;i++)
	{
		for(int j=0;j<15;j++)
		{
			if(i==NewRow-1&&j==NewCol-1)
			{outfile<<'#';continue;}
			if(achBoard[i][j]==' ')
				outfile<<'#';
			else
				outfile<<achBoard[i][j];
		}
		outfile<<endl;
	}
	outfile.close();
}
void CGobang::UndoAI()
{
	--SpotsOnBoard;
	for(int row=0;row<15;row++)
		for(int col=0;col<15;col++)
		{achBoard[row][col]=SaveachBoard[row][col][SpotsOnBoard-1];}
	NewRow=SaveRow[SpotsOnBoard-1];
	NewCol=SaveCol[SpotsOnBoard-1];
}
void CGobang::UndoyouwhenAI()
{
	--SpotsOnBoard;
	--SpotsOnBoard;
	for(int row=0;row<15;row++)
		for(int col=0;col<15;col++)
		{achBoard[row][col]=SaveachBoard[row][col][SpotsOnBoard-1];}
	NewRow=SaveRow[SpotsOnBoard-1];
	NewCol=SaveCol[SpotsOnBoard-1];
}
void OperatingFunction(int i)
{
	system("cls");
	char choice='Y';
	CGobang O('O','X'),X('X','O');
	if(i==2)
	{
	int K;
	cout<<"请选择电脑难度："<<endl;
	cout<<"1.简单"<<endl;
	cout<<"2.中等"<<endl;
	getchoice(K,1,2);
	K--;
	system("cls");
	int xianshou;
	cout<<"请选择先手方："<<endl;
	cout<<"1.你"<<endl;
	cout<<"2.电脑"<<endl;
	getchoice(xianshou,1,2);
	
	if(xianshou==2)
	{
	
	while(choice=='Y')           //
	{
		int flag=0,flag2=0,flag3=0;
		CGobang::InitialBoard();
        CGobang::PrintBoard();
		
		do
		{
			
			if(!flag)
			{
			
			O.AITurn(K);
			CGobang::PrintBoard();
			flag=0;
			if(CGobang::Judge())
			{
				O.Win();
				X.Lose();
				break;
			}
			else if(CGobang::GetFull())
			{
				CGobang::Draw();
				break;
			}
			}
			else
			{
				flag2=1;
			}
			
			if(flag2)
				{CGobang::PrintBoard();flag2=0;}
			cout<<"最新的棋子位于("<<CGobang::NewRow<<","<<CGobang::NewCol<<")"<<endl;
			int x,y;
	        cout<<"Turn of "<<" X "<<",enter the coordinates,cin row = 99 UndoAI,row = 100 Undoyou,row = 0 to save "<<endl;
	        cout<<"row: ";
			getchoice(x,-9999,9999);
         	cout<<"colume: ";
			getchoice(y,-9999,9999);
			while(1)
			{
			if(flag2)
				{CGobang::PrintBoard();flag2=0;}

		    if(x==0)
			{
			cout<<"已保存";
			CGobang::SaveBoard();
			cout<<"row: ";
		    getchoice(x,-9999,9999);
		    cout<<"colume: ";
	     	getchoice(y,-9999,9999);
			continue;
			}
			if(x==99)
			{
				CGobang::UndoAI();
				flag3=1;
				flag=0;
				break;
				
			}
			else if(x==100)
			{
				if(CGobang::SpotsOnBoard==1)
				{
					cout<<"非法操作！请重新输入"<<endl;
					cout<<"row: ";
			        getchoice(x,-9999,9999);
		            cout<<"colume: ";
			        getchoice(y,-9999,9999);
			        continue;
				}
				else
				{
				CGobang::UndoyouwhenAI();
				flag=1;
				break;
				}

			}
			if(x>15||x<1||y>15||y<1||('O'==CGobang::achBoard[x-1][y-1]||'X'==CGobang::achBoard[x-1][y-1]))
			{cout<<"This coordinate is not allowed,try again"<<endl;
		    cout<<"row: ";
			getchoice(x,-9999,9999);
		    cout<<"colume: ";
			getchoice(y,-9999,9999);
			continue;
			}
			X.PlayTurn(x,y);flag=0;break;
			}//end while
		
			
			if(!flag&&flag3!=1)
			{
			CGobang::PrintBoard();
			if(CGobang::Judge())
			{
				X.Win();
				O.Lose();
				break;
			}
			else if(CGobang::GetFull())
			{
				CGobang::Draw();
				break;
			}
			}
			


		}while(!CGobang::GetFull());
		cout<<"continue please input 'Y'";/////////////////////////////////////////////////////////////////////////
		cin>>choice;
	}
	O.PrintInfo();
	X.PrintInfo();
	system("PAUSE");
	}
	else if(xianshou==1)
	{
	 
	while(choice=='Y')           //
	{
		int flag=0,flag2=0,flag3=0,flag4=0;
		CGobang::InitialBoard();
        CGobang::PrintBoard();
		do
		{
			int x,y;
			cout<<"Turn of "<<" O "<<",enter the coordinates,cin row = 99 UndoAI,row = 100 Undoyou,row = 0 to save "<<endl;
	        cout<<"row: ";
			getchoice(x,-9999,9999);
         	cout<<"colume: ";
			getchoice(y,-9999,9999);
			while(1)
			{
			cout<<"a";
			if(flag2)
				{CGobang::PrintBoard();flag2=0;}

		    if(x==0)
			{
			cout<<"已保存";
			CGobang::SaveBoard();
			cout<<"row: ";
		    cin>>x;
		    cout<<"colume: ";
	     	cin>>y;
			continue;
			}
			if(x==99)
			{
				CGobang::UndoAI();
				flag=0;
				break;
				
			}
			else if(x==100)
			{
				CGobang::UndoyouwhenAI();
				flag3=1;
				flag2=1;
				break;

			}
			if(x>15||x<1||y>15||y<1||('O'==CGobang::achBoard[x-1][y-1]||'X'==CGobang::achBoard[x-1][y-1]))
			{cout<<"This coordinate is not allowed,try again"<<endl;
		    cout<<"row: ";
		    cin>>x;
		    cout<<"colume: ";
		    cin>>y;
			continue;
			}
			
			O.PlayTurn(x,y);flag4=1;break;
			}//end while
			if(flag4)
			{
			CGobang::PrintBoard();
			if(CGobang::Judge())
			{
				O.Win();
				X.Lose();
				break;
			}
			else if(CGobang::GetFull())
			{
				CGobang::Draw();
				break;
			}
			}
			if(!flag&&!flag3||flag4)
			{
			X.AITurn(K);
			CGobang::PrintBoard();
			flag2=0;
			    if(CGobang::Judge())
				{
				X.Win();
				O.Lose();
				break;
				}
			    else if(CGobang::GetFull())
				{
				CGobang::Draw();
				break;
				}		   
				 flag4=0;
			}
			else 
			    flag3=0;
			if(flag2)
				{CGobang::PrintBoard();flag2=0;}
			if(CGobang::SpotsOnBoard)
			{cout<<"最新的棋子位于("<<CGobang::NewRow<<","<<CGobang::NewCol<<")"<<endl;}
			
	        
		
			
			
			


		}while(!CGobang::GetFull());
		cout<<"continue please input 'Y'";/////////////////////////////////////////////////////////////////////////
		cin>>choice;
	}
	O.PrintInfo();
	X.PrintInfo();
	system("PAUSE");
	}
	}
	else if(i==1)
	{
	while(choice=='Y')
	{
		int flag=0;
		CGobang::InitialBoard();
        CGobang::PrintBoard();
		do
		{
			int x,y;
			if(CGobang::SpotsOnBoard)
			{cout<<"最新的棋子位于("<<CGobang::NewRow<<","<<CGobang::NewCol<<")"<<endl;}
	        cout<<"Turn of "<<" O "<<",enter the coordinates,Undo row = 99"<<endl;
	        cout<<"row: ";
         	cin>>x;
         	cout<<"colume: ";
        	cin>>y;
			while(1)
			{
			
			if(x==99)
			{
				CGobang::UndoAI();
				CGobang::PrintBoard();
				break;
				
			}
			if(x>15||x<1||y>15||y<1||('O'==CGobang::achBoard[x-1][y-1]||'X'==CGobang::achBoard[x-1][y-1]))
			{cout<<"This coordinate is not allowed,try again"<<endl;
			cout<<"row: ";
		    cin>>x;
		    cout<<"colume: ";
		    cin>>y;
			continue;
			}
			O.PlayTurn(x,y);
			flag=1;
			CGobang::PrintBoard();
			
			break;
			}
			if(flag)
			{
			   if(CGobang::Judge())
			   {
				O.Win();
				X.Lose();
				break;
			   }
			   else if(CGobang::GetFull())
			   {
				CGobang::Draw();
				break;
			   }
			   flag=0;
			}
		
            int flag1=0;
            if(CGobang::SpotsOnBoard)
			{cout<<"最新的棋子位于("<<CGobang::NewRow<<","<<CGobang::NewCol<<")"<<endl;}
			int x1,y1;
	        cout<<"Turn of "<<" X "<<",enter the coordinates,Undo row = 99"<<endl;
	        cout<<"row: ";
         	cin>>x1;
         	cout<<"colume: ";
        	cin>>y1;
			while(1)
			{
				
			if(x1==99)
			{
				CGobang::UndoAI();
				CGobang::PrintBoard();
				break;
				
			}
			if(x1>15||x1<1||y1>15||y1<1||('O'==CGobang::achBoard[x1-1][y1-1]||'X'==CGobang::achBoard[x1-1][y1-1]))
			{cout<<"This coordinate is not allowed,try again"<<endl;
			cout<<"row: ";
		    cin>>x1;
		    cout<<"colume: ";
		    cin>>y1;
			continue;
			}
			X.PlayTurn(x1,y1);
			flag1=1;
			CGobang::PrintBoard();
			
			break;
			}
			if(flag1)
			{
			    if(CGobang::Judge())
				{
				X.Win();
				O.Lose();
				break;
				}
		    	else if(CGobang::GetFull())
				{
				CGobang::Draw();
				break;
				}
				flag1=0;
			}
			


		}while(!CGobang::GetFull());
		cout<<"continue please input 'Y'";
		cin>>choice;
	}
	O.PrintInfo();
	X.PrintInfo();
	system("PAUSE");
	}
	else if(i==1)
	{
	while(choice=='Y')
	{
		CGobang::InitialBoard();
        CGobang::PrintBoard();
		do
		{
			int x,y;
			cout<<"最新的棋子位于("<<CGobang::NewRow<<","<<CGobang::NewCol<<")"<<endl;
	        cout<<"Turn of "<<" O "<<",enter the coordinates,Undo row = 99"<<endl;
	        cout<<"row: ";
         	cin>>x;
         	cout<<"colume: ";
        	cin>>y;
			while(1)
			{
			
			if(x==99)
			{
				CGobang::UndoAI();
				CGobang::PrintBoard();
				break;
				
			}
			if(x>15||x<1||y>15||y<1||('O'==CGobang::achBoard[x-1][y-1]||'X'==CGobang::achBoard[x-1][y-1]))
			{cout<<"This coordinate is not allowed,try again"<<endl;
			cout<<"row: ";
		    cin>>x;
		    cout<<"colume: ";
		    cin>>y;
			continue;
			}
			O.PlayTurn(x,y);
			CGobang::PrintBoard();
			if(CGobang::Judge())
			{
				O.Win();
				X.Lose();
				break;
			}
			else if(CGobang::GetFull())
			{
				CGobang::Draw();
				break;
			}
			break;
			}
		

            cout<<"最新的棋子位于("<<CGobang::NewRow<<","<<CGobang::NewCol<<")"<<endl;
			int x1,y1;
	        cout<<"Turn of "<<" X "<<",enter the coordinates,Undo row = 99"<<endl;
	        cout<<"row: ";
         	cin>>x1;
         	cout<<"colume: ";
        	cin>>y1;
			while(1)
			{
				
			if(x1==99)
			{
				CGobang::UndoAI();
				CGobang::PrintBoard();
				break;
				
			}
			if(x1>15||x1<1||y1>15||y1<1||('O'==CGobang::achBoard[x1-1][y1-1]||'X'==CGobang::achBoard[x1-1][y1-1]))
			{cout<<"This coordinate is not allowed,try again"<<endl;
			cout<<"row: ";
		    cin>>x1;
		    cout<<"colume: ";
		    cin>>y1;
			continue;
			}
			X.PlayTurn(x1,y1);
			CGobang::PrintBoard();
			if(CGobang::Judge())
			{
				X.Win();
				O.Lose();
				break;
			}
			else if(CGobang::GetFull())
			{
				CGobang::Draw();
				break;
			}
			break;
			}
			


		}while(!CGobang::GetFull());
		cout<<"continue please input 'Y'";
		cin>>choice;
	}
	O.PrintInfo();
	X.PrintInfo();
	system("PAUSE");
	}
	else if(i==3)
	{
		cout<<"3Q for  using";
	}
}
int Menu()
{
	cout<<"**************************************"<<endl;
	cout<<"            五子棋游戏"<<endl;
	cout<<"            1.人VS人"<<endl;
	cout<<"            2.人VS机"<<endl;
	cout<<"            3.退出"<<endl;
	cout<<"**************************************"<<endl;
	int choice;
	cin>>choice;
	while(!cin||choice<1||choice>3)
	{
		char str[100];
		cin.clear();
		cin.getline(str,100);

		cout<<"invalid,please try again!"<<endl;
		
		cin>>choice;
	}
	return choice;

}
void printBoard(char achBoard[15][15])
{
	cout<<endl;
	cout<<"  ";
	for(int j=1;j<=15;j++)
		if(j<10)
		cout<<j<<"   ";
		else
			cout<<j<<"  ";
	cout<<endl;
	for(int m=1;m<=15;m++)
	{
		if(m<10)
		cout<<' '<<m<<' '<<achBoard[m-1][0];
		else
		cout<<m<<' '<<achBoard[m-1][0];
        for(int n=1;n<15;n++)
			cout<<" | "<<achBoard[m-1][n];
		cout<<endl;
		cout<<"  ---";
		for(int d=1;d<15;d++)
			cout<<"|---";
		cout<<endl;
	}
	cout<<endl<<endl;
}

lb *create(int a[N],lb *head,int n,CGobang AI,CGobang simulatedPlayer,int AIorPlayer,int depth)
{
	lb *p1,*p2;
	p1=new lb;
	p1->Value=NOW;
	head=p1;
	n--;
	for(int i=0;i<N;i++)
	{
		p2=head;
		p1=new lb;
		p1->Value=a[i];
		p2->next[i]=p1;
		if(n==0)
		{
			for(int m=0;m<N;m++)
			{p1->next[m]=NULL;}
		}
		//cout<<head->next[i]->Value;//没有从1开始

	}
	//cout<<endl;

	if(n)
	{
		lb *p3[20]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},*p4[20]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
		
		for(int i=0;i<N;i++)
		{
            
			for(int count1=0;count1<15;count1++)
	    	   for(int count2=0;count2<15;count2++)
				 CGobang::virtualBoard[count1][count2][depth-n]=CGobang::virtualBoard[count1][count2][depth-n-1];
			   //cout<<depth-n<<endl;
			
			


			
		  //cout<<head->next[i]->Value;
		  if(AIorPlayer)
		  {AI.virtualTurn(a[i],depth-n);}//cout<<"AITURN"<<endl;}
		  else
		  {simulatedPlayer.virtualTurn(a[i],depth-n);}//cout<<"playerturn"<<endl;}
		  if(0)  //检查
			{char WW[15][15];
			for(int count1=0;count1<15;count1++)
	    	   for(int count2=0;count2<15;count2++)
				 WW[count1][count2]=CGobang::virtualBoard[count1][count2][depth-n];
			printBoard(WW);
			}
		  int nvalue[N];
		  for(int ii=0;ii<N;ii++)
			  nvalue[ii]=-1;
		  if(AIorPlayer)///////
		  {simulatedPlayer.AIJudge(nvalue,1,depth-n);}
		  else
		  {AI.AIJudge(nvalue,1,depth-n);}
		 if(AIorPlayer)
			AIorPlayer=0;
		else
			AIorPlayer=1;
	      p4[i]=head->next[i];
	      p3[i]=create(nvalue,p3[i],n,AI,simulatedPlayer,AIorPlayer,depth);
	      p3[i]->Value=p4[i]->Value;
	      head->next[i]=p3[i];
		if(AIorPlayer)
			AIorPlayer=0;
		else
			AIorPlayer=1;
		  //for(int j=0;i<N;j++)
			//  cout<<head->next[i]->next[j]->Value;
		 
	      //print(p3[i]);
		}
		
		



		
	}

	
	return head;

}
void print(lb *head)
{
	
	lb *p=head,*p1=NULL;
	cout<<p->Value;
	if(p->next[0]==NULL&&count!=N-1)
	{cout<<'\t';count++;}
	else if(p->next[0]!=NULL)
	{cout<<endl;}
	else
	{cout<<endl;count=0;}

		if(p->next[0]!=NULL)
		{
			
			for(int i=0;i<N;i++)
			{
				p1=p->next[i];
				print(p1);
				
			
				
			}
		}
	    
		//for(int i=0;i<N;i++)
		//{
		//	p=head;
		//	p=p->next[i];
		//	cout<<p->Value<<' ';
		//}
		
	

}
int bestvalue=-99999;
void PDvalue(lb *head,lb *Head,int n)
{
	//cout<<head->Value<<endl;
	int record;
	lb *p=head,*p1=NULL;
	if(n)
	{
		Head->SUM=Head->SUM+p->Value/1000%1000-p->Value%1000;
		n=0;
		//cout<<sum<<endl;
	}
	else
	{
		Head->SUM=Head->SUM-p->Value/1000%1000+p->Value%1000;
		n=1;
		//cout<<sum<<endl;
	}
	if(p->next[0]!=NULL)
		{
	
			for(int i=0;i<N;i++)
			{
				p1=p->next[i];
				PDvalue(p1,Head,n);
				
			
				
			}
		}
	else
	{
		if(Head->SUM>bestvalue)
		{bestvalue=Head->SUM;record=Head->Value/1000000*1000000+Head->SUM+10000;cout<<"aAAAAAAAAAA"<<"record"<<record<<'\t'<<"HEad"<<Head->Value<<endl;}
	}
}

int CGobang::AIthink(CGobang AI)
{
	CGobang simulatedPlayer(AI.enchSort,AI.chSort);                
	for(int i=0;i<15;i++)
		for(int j=0;j<15;j++)
			virtualBoard[i][j][0]=achBoard[i][j];
	CGobang::virtualNewRow=NewRow;
	CGobang::virtualNewCol=NewCol;
	int value[20];
	for( i=0;i<20;i++)
		value[i]=-1;
	AI.AIJudge(value,1,0);
	lb *head=NULL;
	head=create(value,head,Depth,AI,simulatedPlayer,1,Depth);    //2要改
	//print(head);
	int Bestchoice;
	int t=0;
	for(i=0;i<N;i++)
	{
		//cout<<sum;
		PDvalue(head->next[i],head->next[i],1);
		if(head->next[i]->SUM>Bestchoice)
		{Bestchoice=head->next[i]->SUM;t=i;}
		else if(head->next[i]->SUM==Bestchoice)
		{
             srand(time(NULL));
			 if(rand()%2)
			 {Bestchoice=head->next[i]->SUM;t=i;}
		}
		//cout<<bestchoice[i]<<endl<<endl;

	}

    return head->next[t]->Value;
}


void getchoice(int& choice,int min=-99999,int max=99999)
{
	cin>>choice;
	while(!cin||choice>max||choice<min)
	{
		if(!cin)
		{
		cin.clear();
		char str[10];
		cin.getline(str,10);
		cout<<"输入非法，请重新输入！"<<endl;
		cin>>choice;
		}
		else
		{
		cout<<"请输入"<<min<<"~"<<max<<"的数字！"<<endl;
		cin>>choice;
		}
	}
}

