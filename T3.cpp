#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

//two matrices, A and B, both of size 3x3
int A[3][3];
int B[3][3];
int row = 0, col = 0, currValNo = 0; //to iterate through matrices

void* calculate(void* arg); //function to multiply matrix values

int main()
{
	//declare required variables
	pthread_t threads[9]; //one thread for each value of result
	//resultant matrix
	int result[3][3];
	int resRow = 0, resCol = 0, resCurr = 0; //to iterate through current matrix
	int* value; //to store resultant
	//end declaration
	
	//----- input values from user -----
	//take values of matrix A from user
	cout << "--------------- FIRST MATRIX ---------------" << endl;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << "Enter A[" << i << "][" << j << "]: ";
			cin >> A[i][j];
		}
	}
	
	//take values of matrix B from user
	cout << "--------------- SECOND MATRIX --------------" << endl;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << "Enter B[" << i << "][" << j << "]: ";
			cin >> B[i][j];
		}
	}
	//----------- end input ------------
	
	for(int i = 0; i < 9; i++)
	{
		pthread_create(&threads[i], NULL, calculate, NULL); //each thread calculates one value of resultant
		pthread_join(threads[i], (void**)&value); //return value from multiplication function
		
		result[resRow][resCol++] = *(value); //store returned value in result matrix
		
		//iterate through matrix
		if(++resCurr == 3 || resCurr == 6)
			resRow++;
		if(resCol > 2)
			resCol = 0;
	}
	
	//output result of multiplication
	cout << endl << "-------------- RESULTANT MATRIX --------------" << endl;
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			cout << "Element [" << i << "][" << j << "] of result = "
			<< result[i][j] << endl;
		}
	}

	return 0;	
}

void* calculate(void* arg)
{
	int* val = new int;
	*val = 0;
	
	//calculate value
	for(int i = 0; i < 3; i++)
	{
		*val += (A[row][i] * B[i][col]);
	}
	
	//iterate through matrix
	currValNo++;
	col++;
	
	if(currValNo == 3 || currValNo == 6)
	{	row++;
		col = 0;
	}
	
	//return calculated multiplication value
	pthread_exit((void*)val);
}

