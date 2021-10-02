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
/*
HOW TO COMPILE
	gcc pthread_create.c -o pthread_create -lpthread

SYNCHRONIZING THREADS WITH MUTEXES
	For instance, consider the case where two threads try to update two variables. One tries to set both to 0, and the other
	tries to set both to 1. If both threads would try to do that at the same time, we might get with a situation where one
	variable contains 1, and one contains 0. This is because a context-switch (we already know what this is by now, right?)
	might occur after the first tread zeroed out the first variable, then the second thread would set both variables to 1, and
	when the first thread resumes operation, it will zero out the second variable, thus getting the first variable set to '1', and
	the second set to '0'.
	
CREATING AND INITIALIZING A MUTEX
	we first need to declare a variable of type pthread_mutex_t, and then initialize it.
	
	pthread_mutex_t a_mutex = PTHREAD_MUTEX_INITIALIZER;
	
	One note should be made here: This type of initialization creates a mutex called 'fast mutex'. This means that if a thread
	locks the mutex and then tries to lock it again, it'll get stuck - it will be in a deadlock.
	
	There is another type of mutex, called 'recursive mutex', which allows the thread that locked it, to lock it several more
	times, without getting blocked (but other threads that try to lock the mutex now will get blocked). If the thread then
	unlocks the mutex, it'll still be locked, until it is unlocked the same amount of times as it was locked. This is similar to
	the way modern door locks work - if you turned it twice clockwise to lock it, you need to turn it twice
	counter-clockwise to unlock it. This kind of mutex can be created by assigning the constant
	PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP to a mutex variable.
	
LOCKING AND UNLOCKING A MUTEX
	In order to lock a mutex, we may use the function pthread_mutex_lock(). This function attempts to lock the
	mutex, or block the thread if the mutex is already locked by another thread. In this case, when the mutex is unlocked by
	the first process, the function will return with the mutex locked by our process.
	After the thread did what it had to (change variables or data structures, handle file, or whatever it intended to do), it
	should free the mutex, using the pthread_mutex_unlock() function.
	
DESTROYING A MUTEX
	After we finished using a mutex, we should destroy it. Finished using means no thread needs it at all. If only one thread
	finished with the mutex, it should leave it alive, for the other threads that might still need to use it. Once all finished
	using it, the last one can destroy it using the pthread_mutex_destroy() function:

	pthread_mutex_destroy(&a_mutex);
	
STARVATION AND DEADLOCK SITUATIONS
	pthread_mutex_lock() might block for a non-determined duration, in case of
	the mutex being already locked. If it remains locked forever, it is said that our poor thread is "starved" - it was trying to
	acquire a resource, but never got it.
	A deadlock is a situation in which a set of threads are all
	waiting for resources taken by other threads, all in the same set. Naturally, if all threads are blocked waiting for amutex, none of them will ever come back to life again.
	
REFINED SYNCHRONIZATION - CONDITION VARIABLES
	What Is A Condition Variable?
	A condition variable is a mechanism that allows threads to wait (without wasting CPU cycles) for some even to occur.
	Several threads may wait on a condition variable, until some other thread signals this condition variable (thus sending a
	notification). At this time, one of the threads waiting on this condition variable wakes up, and can act on the event. It is
	possible to also wake up all threads waiting on this condition variable by using a broadcast method on this variable.
	
CREATING AND INITIALIZING A CONDITION VARIABLE

	pthread_cond_t got_request = PTHREAD_COND_INITIALIZER;
	
SIGNALING A CONDITION VARIABLE
	In order to signal a condition variable, one should either the pthread_cond_signal() function (to wake up a
	only one thread waiting on this variable), or the pthread_cond_broadcast() function (to wake up all threads
	waiting on this variable). Here is an example using signal, assuming 'got_request' is a properly initialized condition
	variable:
	
	int rc = pthread_cond_signal(&got_request);
	
	Or by using the broadcast function:
	
	int rc = pthread_cond_broadcast(&got_request);
	
WAITING ON A CONDITION VARIABLE
	If one thread signals the condition variable, other threads would probably want to wait for this signal. They may do so
	using one of two functions, pthread_cond_wait() or pthread_cond_timedwait(). Each of these
	functions takes a condition variable, and a mutex (which should be locked before calling the wait function), unlocks the
	mutex, and waits until the condition variable is signaled, suspending the thread's execution. If this signaling causes the
	thread to awake (see discussion of pthread_cond_signal() earlier), the mutex is automagically locked again by
	the wait funciton, and the wait function returns.
	The only difference between these two functions is that pthread_cond_timedwait() allows the programmer to
	specify a timeout for the waiting, after which the function always returns, with a proper error value (ETIMEDOUT) to
	notify that condition variable was NOT signaled before the timeout passed. The pthread_cond_wait() would
	wait indefinitely if it was never signaled.
	
DESTROYING A CONDITION VARIABLE
	pthread_cond_destroy(&got_request);

THREAD CANCELLATION AND TERMINATION
	Canceling A Thread
		When we want to terminate a thread, we can use the pthread_cancel function. This function gets a thread ID as a
		parameter, and sends a cancellation request to this thread.
		
		pthread_cancel(thr_id);
		The pthread_cancel() function returns 0, so we cannot know if it succeeded or not.
	Setting Thread Cancellation State
		A thread's cancel state may be modified using several methods. The first is by using the
		pthread_setcancelstate() function. This function defines whether the thread will accept cancellation requests
		or not. The function takes two arguments. One that sets the new cancel state, and one into which the previous cancel
		state is stored by the function. Here is how it is used:
		
		int old_cancel_state;
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
		
		This will disable canceling this thread. We can also enable canceling the thread like this:
		
		int old_cancel_state;
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &old_cancel_state);
		
		A similar function, named pthread_setcanceltype() is used to define how a thread responds to a cancellation
		request, assuming it is in the 'ENABLED' cancel state. One option is to handle the request immediately
		(asynchronously). The other is to defer the request until a cancellation point. To set the first option (asynchronous
		cancellation), do something like:
		
		int old_cancel_type;
		pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, &old_cancel_type);
		
		And to set the second option (deferred cancellation):
		
		int old_cancel_type;
		pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &old_cancel_type);
		
		Note that you may supply a NULL pointer as the second parameter, and then you won't get the old cancel type.
		You might wonder - "What if i never set the cancellation state or type of a thread?". Well, in such a case, the
		pthread_create() function automatically sets the thread to enabled deferred cancellation, that is,
		PTHREAD_CANCEL_ENABLE for the cancel mode, and PTHREAD_CANCEL_DEFERRED for the cancel type.
		
	Cancellation Points
	● pthread_join()
	● pthread_cond_wait()
	● pthread_cond_timedwait()
	● pthread_testcancel()
	● sem_wait()
	● sigwait()
	
	This means that if a thread executes any of these functions, it'll check for deferred cancel requests. If there is one, it will
	execute the cancellation sequence, and terminate. Out of these functions, pthread_testcancel() is unique - it's
	only purpose is to test whether a cancellation request is pending for this thread. If there is, it executes the cancellationsequence. If not, it returns immediately. This function may be used in a thread that does a lot of processing without
	getting into a "natural" cancellation state.
	
*/