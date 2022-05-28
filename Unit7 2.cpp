#define MAP_MAXSIZE_X 100
#define MAP_MAXSIZE_Y 100
#define MAX_STACK (MAP_MAXSIZE_X*MAP_MAXSIZE_Y)/2
#include <vcl.h>
#pragma hdrstop
#include<string>
#include<sstream>
#include "Unit7.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm7 *Form7;
//---------------------------------------------------------------------------
__fastcall TForm7::TForm7(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
int **matrix;
 //int max_m = StrToInt(Edit1->Text);
//int max_n = StrToInt(Edit2->Text);
void __fastcall TForm7::Button1Click(TObject *Sender)
{
std::stringstream ss;
 int i,j;
 int max_m = StrToInt(Edit1->Text);
int max_n = StrToInt(Edit2->Text);

  matrix = new int *[max_n];
  for(i=0;i<max_n;i++){
  matrix[i] = new int[max_m];
  }

  for(i=0;i<max_m;i++){
	  for(j=0;j<max_n;j++){
	  matrix[i][j]=rand() % 2;
	  }
  }

  for(i=2;i<max_m;i++){
  matrix[i][0]=2;
  }

  for(i=0;i<max_n;i++){
  matrix[0][i]=2;
  }

  for(i=0;i<max_m-2;i++){
  matrix[i][max_n-1]=2;
  }

  for(i=0;i<max_n;i++){
   matrix[max_m-1][i]=2;
  }
	  matrix[0][0]=-1;
	  matrix[max_m-1][max_n-1]=-2;
				for (i = 0; i < max_m; i++) {

					for (j=0; j < max_n; j++) {

										ss << matrix[i][j] << " ";

					}

					//ss >> buf;
				Form7->Memo1->Lines->Add(ss.str().c_str()) ;
				ss.str("");
				}

  for (int i=0; i<max_n; i++){
	delete [] matrix[i];
  }
	delete [] matrix;
}




//char map[MAP_MAXSIZE_X][MAP_MAXSIZE_Y]=1;
//bool passed[MAP_MAXSIZE_X][MAP_MAXSIZE_Y]=0;

struct _POSITION { // coordinate data
	int m;
	int n;
};
typedef struct _POSITION POSITION;

POSITION stack[MAX_STACK]; // stack declaration
int top = -1; // top of the stack

// To know whether stack is empty
bool IsEmpty()
{
	if(top == -1)
        return true;
	return false;
}

// To know whether stack is full
bool IsFull()
{
	if(top < MAX_STACK-1)
		return false;
	return true;
}

// pop data from stack
POSITION Pop()
{
	return stack[top--];
}

// push data into stack
void Push(POSITION posData)
{
    stack[++top]=posData;
}

void run(int m, int n, int max_m, int max_n)
{

	POSITION last; // last position data
	int branch = 0; // branch numbers
	int direction = 1; // 1:east, 2:south, 3:west, 4:north
	//int max_m = StrToInt(Edit1->Text);
   //	int max_n = StrToInt(Edit2->Text);

	while(matrix[m][n] != -2) // loop until reach the goal
	{
		branch = 0; // reset branch to 0


			if((n+1<max_n) && ((matrix[m][n+1] == -2) || (matrix[m][n+1] == 0))
			&& (matrix[m][n+1] != 5) && (matrix[m][n+1] !=4) )
			{  // if east can go, and hasn't passed yet
			branch++; // increase the branch, if this way can go
			direction = 1;
			}
			if((m+1<max_m) && ((matrix[m+1][n] == -2) || (matrix[m+1][n] == 0))
			&& (matrix[m+1][n] != 5) && (matrix[m+1][n] !=4))
			{
			branch++;
			direction = 2;
			}
			if((n-1>=0) && ((matrix[m][n-1] == -2) || (matrix[m][n-1] == 0))
			&& (matrix[m][n-1] != 5) && ( matrix[m][n-1] != 4 ))
			{
			branch++;
			direction = 3;
			}
			if((m-1>=0) && ((matrix[m-1][n] == -2) || (matrix[m-1][n] == 0))
			&& (matrix[m-1][n] != 5) && (matrix[m][n+1] !=4))
			{
			branch++;
			direction = 4;
			}


		// TODO: move forward
		if(branch > 1) // if there are many ways can go
		{
			if(!IsFull())
			{ // if stack is not full, push the branch position into the stack
				last.m = m;
				last.n = n;
				Push(last);
			   /*	printf("Push(%d,%d), ", last.x+1, last.y+1);
				fprintf(fptr, "Push(%d,%d), ", last.x+1, last.y+1); */
			}
		}
		else if(branch == 0) // if there is no route, is a dead end
		{

			if(!IsEmpty())
			{
				last = Pop();
				m = last.m;
				n = last.n;
			}
			else
			{

				return;
			}
			continue;
		}

		// TODO: choose a way from last one direction, and move forward
		switch(direction)
		{
			case 1:
				n = n + 1;
				//matrix[m][n]=5;
				break;
			case 2:
				m = m + 1;
				//matrix[m][n]=5;
				break;
			case 3:
				n = n - 1;
				//matrix[m][n]=5;
				break;
			case 4:
				m = m - 1;
				//matrix[m][n]=5;
				break;
		}
			if(matrix[m][n]==0){
				matrix[m][n]=5;
			}
		else if(matrix[m][n]==5){
			matrix[m][n]=4;
		}
	}
}




//---------------------------------------------------------------------------
void __fastcall TForm7::Button2Click(TObject *Sender)
{
	 std::stringstream ss;
	int max_m,max_n,i,j;
	max_m = StrToInt(Edit1->Text);
	max_n = StrToInt(Edit2->Text);
 //m = StrToInt(Edit1->Text);
 //n = StrToInt(Edit2->Text);

	run(1,0,StrToInt(Edit1->Text),StrToInt(Edit2->Text)); // run maze
		for (i = 0; i < max_m; i++) {

					for (j=0; j < max_n; j++) {
					ss << matrix[i][j] << " ";

					}
				Form7->Memo1->Lines->Add(ss.str().c_str()) ;
				ss.str("");
		}
		if(matrix[max_m-2][max_n]==0)
		Form7->Memo1->Lines->Add("There is no solution!") ;
		else if(matrix[max_m-2][max_n]==5)
		Form7->Memo1->Lines->Add("Congradulations! You got it!") ;
	for (int i=0; i<max_n; i++){
	delete [] matrix[i];
  }
	delete [] matrix;
}
//---------------------------------------------------------------------------
