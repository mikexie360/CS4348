/**********************************************************************
 * File: main.cpp
 * Author: Mork
 * Procedures	- a program that simulates the producer-consumer problem
 * 			with fork() and with one producer and ten
 * 			consumers.
 * ********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <semaphore.h>
#include <iostream>
#include <vector>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

// max size of the buffer
const int sizeOfBuffer = 1000;
// the buffer is a vector of ints. Will be shared across all processes
std::vector<int> *buffer = (std::vector<int> *)mmap(NULL,sizeOfBuffer*sizeof(std::vector<int>),
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1 ,0);
// the maximum items the producer can generate. shared in memory
int *maxItemsGenerated = (int *)mmap(NULL, sizeof(int),
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1 ,0);
// semaphore that keeps track of full
sem_t *full = (sem_t *)mmap(NULL, sizeof(sem_t),
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1 ,0);
// semaphore that keeps track of empty
sem_t *empty = (sem_t *)mmap(NULL, sizeof(sem_t),
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1 ,0);
// semaphore that keeps track of when it is possible to access the memory.
sem_t *mutex = (sem_t *)mmap(NULL, sizeof(sem_t),
				PROT_READ | PROT_WRITE,
				MAP_SHARED | MAP_ANONYMOUS, -1 ,0);

//sem_t full, empty, mutex;

// not used in the program
int *counter = (int *)mmap(NULL, sizeof(int),
			PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
/************************************************************************
 * int main()
 * Author: Mork
 * Date: 4 October 2020
 * Description: simulates the producer-consumer problem with one producer
 * 		and ten consumers. Has a buffer size of 1000 and the producer
 * 		produces 1000000 items.
 * Parameters: N/A
 * ***********************************************************************/
int main() {
	// initialize variables
	*maxItemsGenerated = 1000000;
	*counter = 0;
	sem_init(full,  1, 0);
	sem_init(empty, 1, sizeOfBuffer);
	sem_init(mutex, 1, 1);
	// count will be keeping track of how much the producer produced and
	// how much the consumer consumed.
	int count = 0;

	// 11 processes. 1 producer + 10 consumers
	int pid[11];
	// create the processes in this for loop.
	for ( int i = 0; i <11; i++)
	{
		pid[i] = 0;
		pid[i] = fork();
	//retVal = shm_open();
	if(pid[i] ==0) //child process
	{
		if(pid[0] == 0 )            
		{
			for(;*maxItemsGenerated >0;)	// producer
			{
			sem_wait(empty);
			sem_wait(mutex);
			buffer->push_back(1);		// produce and append an item
			*maxItemsGenerated = *maxItemsGenerated - 1;
			*counter++;
			count++;
			sem_post(mutex);
			sem_post(full);
			std::cout << "producer ";
			std::cout << "\tbuffer size: " <<buffer->size();
			std::cout << "\tmax: " <<*maxItemsGenerated;
			std::cout << "\tproduced so far: " << count << "\n";
			}
			// killing the producer
			std::cout <<"kill producer \n";
			waitpid(-1,NULL,WNOHANG);
			exit(0);
		}
		else          	       			
		{
			
			for(;*maxItemsGenerated >0 || buffer->size() >0;)	// consumer
			{
				//before going through the semasphore. check if the consumer has something to consume
				if((*maxItemsGenerated + buffer->size()) <=9)
				{
					std::cout << "kill consumer id " << getpid() << "\n";
					exit(0);
				}
				sem_wait(full);
				sem_wait(mutex) ;
				buffer->pop_back();	// drop and consume
				count++;
				sem_post(mutex);
				sem_post(empty);
				std::cout << "consumer id "<< getpid();
				std::cout << "\tbuffer size: "<<buffer->size();
				std::cout << "\tmax: " << *maxItemsGenerated;
				std::cout << "\teaten so far: " << count <<"\n"; 
				// check if there is anything to consume first
				if((*maxItemsGenerated + buffer->size()) <=9)
				{
					std::cout << "kill consumer id " << getpid() << "\n";
					exit(0);

				}
			}
			// kill when done. this line of code shouldn't be reached but just in case.
			std::cout << "kill consumer id " << getpid() << "\n";
			exit(0);
		}
	}
	else //parent process
	{
		continue;
	}
	}
	
	// this line of code never gets reached
	std::cout <<"done"<<"\n";
	exit(0);
	return 0;
}


