# Threads in C++

### T1
Takes a filename as input and counts the number of alphabets in the mentioned file. Twenty-six threads are created; each thread is responsible for the counting of a particular letter in the file. All threads print and return their character count. Main thread receives the count of each thread and prints the sum (which is equivalent to the total number of characters in the file). The character that the thread has to count is passed as input parameter to it.
**Note: Does not consider upper and lower case**

### T2
The performance of merge sort, which is a divide-and-conquer technique, can be improved using multithreading. Four threads are created and the array is divided among these threads and sorted using merge sort. The size of the array and array elements are input by the user. 
> [Helping merge sort code](//https://www.geeksforgeeks.org/merge-sort/)
**Note: The number of threads is equivalent to the number of cores in the system this project was created on.**

### T3
The performance of matrix multiplication can be improved using multithreading. Each created thread evaluates one element of
resultant matrix.

<img width="301" alt="image" src="https://github.com/maliha-masud/threading-in-cpp/assets/121713404/6f22381b-8fca-4d29-9f56-f703ce62d857">

The value 8 is calculated using only one thread.

Two matrices, A and B of size 3x3 both, are taken from the user and nine threads are created to calculate each value of the resultant matrix.
