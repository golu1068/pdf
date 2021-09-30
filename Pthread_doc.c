/*
1. A thread is a semi-process, that has its own stack, and executes a given piece of code. Unlike a real process, the thread normally shares its memory with other threads (where as for processes we usually have a different memory area for each one of them).

2. Thread Group is a set of threads all executing inside the same process. They all share the same memory, and thus can access the same global variables, same heap memory, same set of file descriptors, etc.

3. The advantage of using a thread group over using a process group is that context switching between threads is much faster then context switching 
between processes (context switching means that the system switches from running one thread or process, to running another thread or process). Also, communications between two threads is usually faster and easier to implement then communications between two processes.

4. On the other hand, because threads in a group all use the same memory space, if one of them corrupts the contents of its memory, other threads might suffer as well. With processes, the operating system normally protects processes from one another, and thus if one corrupts its own memory space, other processes won't suffer. Another advantage of using processes is that they can run on different machines, while all the threads have to run on the same machine.

 CREATING AND DESTROYING THREADS
 ///////////////////////////////////////////////////////////////////////////////
#include <stdio.h> /* standard I/O routines */
#include <pthread.h> /* pthread functions and data structures */
/* function to be executed by the new thread */
void*do_loop(void* data)
{
	int i;
	int i; /* counter, to print numbers */
	int j; /* counter, for delay */
	int me = *((int*)data); /* thread identifying number */
	for (i=0; i<10; i++) 
	{
		for (j=0; j<500000; j++) /* delay loop */
			;
		printf("'%d' - Got '%d'\n", me, i);
	}
	/* terminate the thread */
	pthread_exit(NULL);
}
/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
	int thr_id; /* thread ID for the newly created thread */
	pthread_t p_thread; /* thread's structure */
	int a = 1; /* thread 1 identifying number */
	int b = 2; /* thread 2 identifying number */
	/* create a new thread that will execute 'do_loop()' */
	thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)&a);
	/* run 'do_loop()' in the main thread as well */
	do_loop((void*)&b);
	/* NOT REACHED */
	return 0;
}
////////////////////////////////////////////////////////////////////////////

HOW TO COMPILE
	gcc pthread_create.c -o pthread_create -lpthread

SYNCHRONIZING THREADS WITH MUTEXES
For instance, consider the case where two threads try to update two variables. One tries to set both to 0, and the other
tries to set both to 1. If both threads would try to do that at the same time, we might get with a situation where one
variable contains 1, and one contains 0. This is because a context-switch (we already know what this is by now, right?)
might occur after the first tread zeroed out the first variable, then the second thread would set both variables to 1, and
when the first thread resumes operation, it will zero out the second variable, thus getting the first variable set to '1', and
the second set to '0'.
