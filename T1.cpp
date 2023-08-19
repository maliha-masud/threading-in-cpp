#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

string fname;

void* count(void* ch);

int main()
{
	//---declare required variables
	pthread_t threads[26]; //26 threads, one for each char
	char arr[26];
	int n = 97; //to help store all characters into char arr[26]
	int ret; //check for successful thread creation
	void* total = NULL; //store value returned from thread function
	long int totalChars = 0; //store total number of characters
	//---end declaration
	
	//store characters into arr
	for(int i = 0; i < 26; i++)
	{
		arr[i] = (char)n++;
	}
	
	//take file name as input
	cout << "Enter a file name: ";
	cin >> fname;
	
	fstream file;
	file.open(fname);
	
	if(!file) //file couldn't be opened
		cout << "File could not be opened" << endl;
	else //file opened successfully
	{
		//create 26 threads
		for(int i = 0; i < 26; i++) {
			//one thread responsible to count one letter
			//pass character that thread has to count as input parameter, type cast as void
			ret = pthread_create(&threads[i], NULL, count, (void *)&arr[i]); //store return value of each thread creation
			
			if(ret != 0) //an error occurred in creation
			{
				cout << "Error: could not create thread" << endl;
				exit(1);
			}
			
			//receive count of each thread
			pthread_join(threads[i], &total); //wait for thread and store its ret value in total

			//cout << "Count of '" << arr[i] << "': " << (long int) total << "  (returned by thread " << i + 1 << ')' << endl;
			
			totalChars += (long int) total; //add value returned by thread function to var that stores total chars of file
		}
		
		//print sum of all counts, i.e. no of characters in file
		cout << "Total characters in file = " << totalChars << endl;
	}
	
	return 0;	
}

void* count(void* ch)
{
	long int count = 0;
	char readChar; //read from file
	
	fstream file;
	file.open(fname);
	
	while(file >> readChar) //read file char by char
	{		
		if(readChar == *((char*)ch))
			count++; //increment count if file character is current character being counted
	}
	
	//print character count of thread's particular letter
	cout << "Count of " << *((char*)ch) << ": " << count << endl;
	
	//return the count, type cast as void*
	pthread_exit( (void*) count );
}

