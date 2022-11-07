# Philoshophers : Usually Philosophers think for a living... These ones however... Not really.

## What is the goal of this project?
---
   
   > This project's sole perpose is to understand the meaning of Threads and how they function.

## How ?
----
> In order to understand the functionalities of threads, we will try to replicate the famous [dinning philosopher's problem]([This](https://www.geeksforgeeks.org/dining-philosopher-problem-using-semaphores/))


## In case you didn't want to open another tab and look for an already laid out information, I'll give you a watered down version.
###	But, before we do so, we need to clarify some **key concepts**
---
**POSIX :**
---
While working on this project, you will interact with alot of functions that start with the letter "P" (**p**thread_suffix), that little *p* is short for *POSIX*.  
Now you might be asking yourself, what is POSIX?  
Well in short, POSIX stands for "Portable Operating System interface" which is a set of standards made by IEEE (Institute of Electrical and Electronical Engeneers) to maintain compatibility between Operating Systems.   

**Thread :**
---
 it's simply the smallest sequence of programmed instructions that can be managed independently by a scheduler, which is a part of the OS.
 > Note1 : Threads are fast, like real fast (this will come handy later).  

**Deadlock :**  
---
Imagine you are two people trying to unscrew two bolts, in order to do that you both need to have two screw drivers (for some reason) with a small caviat, you two can't really communicate.  

Now, technically you can complete this task with ease, one of you will take the two screws, unscrew the first bolt and land them to the other.  

But imagine if both of you took one screw driver, now suddently we are in a bad position; since neither of you have enough ressources to complete a task, even though technically you have enough to complete said task.  

That's deadlock for you, in other technical (lame) words :  

 Is a situation where a set of processes are blocked because each process is holding a resource and waiting for another resource acquired by some other process, leading to no process having enough ressource access to perform a task, halting the whole program; thus *DEADLOCK* 

**Data race : (Race Conditions)**  
---
Let's say we have an integer that needs to be incremented to a certain number, we set two threads, each increment that said number by one, something like this :

```c
int number = 0;
	void *routine()
	{
		while(number < 1000000)
			i++;
	}
	int main(int ac, char **av)
	{
		pthread_t th1, th2;
		if (pthread_create(&th1, NULL, &routine, NULL) != 0)
			return(1);
		if (pthread_create(&th2, NULL, &routine, NULL) != 0)
			return(1);
		printf("%d", number);
	}
```

Now, technically once we print the number at the end we should end up with something like :  

>Expected result : 2,000,000 
>Actual result : a number != 2,000,000

You can go and try this yourself, in small numbers you might get the correct result since threads are fast and they can finish basic tasks almost instantaneously, but the high the number; the more off the result tend up to be since the interlacing between thread occurs, but why is that the case? 

To explain this, We need to explain how incrementing actually occurs.  
When you want to increment a number, your 1st thread reads the original value, then the value of said number gets incremented locally in the CPU, and then returns the new value.

Now in the 2nd reads the new value, increments it and then returns the newset value, something like this :  

| Threads / Actions       | thread 1      | thread 2  |
| ------------------------|:-------------:| ---------:|
| Reading the number      | 1 			  | 2   	  |
| Incrementing the number | 1 			  | 2   	  |
| Writing the number      | 2 			  | 3   	  |



However, if the threads happen to start their routine at the same moment in time, something strange happens..  
### Sidenote :
> ### Most of you have an idea about their CPU (what manifacturer/GEN/Core count, "Thread Count").  
> We will be taking the last info into considiration, Let's assume we have an 8 Threads CPU, If i launch an app that utilizes < 8 threads, my cpu will handle it by the book (create the threads and assigning them with the instruction provided by said program).  
> ### But what if the program wanted to create > 8 threads?  
> Then the cpu does something amazing, instead of just halting, it lauches all the 8 threads it has, then silencing some of them to cater the other threads the program needs.  
> So essentially; the cpu turns on and off the threads periodically so it can do the task it needs to do.
	
Taking everything I said into consideration, when we create those two threads, both threads read the value, but the CPU might silence one thread and let the second continue its work for numerous cycles (reading, incrementing, returning).  
But once the CPU starts the other thread one more time, the thread will increment the value it has read before being silenced; which is the outdated value, then overwrite the actual value with the old one, creating a conflict of values...  

| Threads / Actions       | thread 1      | thread 2  |
| ------------------------|:-------------:| ---------:|
| Reading the number      | 8 			  | 2   	  |
| Incrementing the number | 8 			  | 2   	  |
| Writing the number      | *9* 		  | *3*   	  |

> This conflict of values is what we call (race condition).

**Mutex :**
---
Now, how can we fix this race condition?
Well, we can create a flag that tells the thread either to start its functionality or in add a "lock" to the actual variable we are using, and in order to do so; we will be introducing a new "function" called *pthread_mutex*  not something similar to this :  

```c
pthread_mutex_t lock;
	void *routine()
	{
		for(int number = 0; number < 1000000) {
			pthread_mutex_lock(&lock);
			i++;
			pthread_mutex_unlock(&lock)
		}
	}
	int main(int ac, char **av)
	{
		pthread_t th1, th2;
		pthread_mutex_init(&lock, NULL);
		if (pthread_create(&th1, NULL, &routine, NULL) != 0)
			return(1);
		if (pthread_create(&th2, NULL, &routine, NULL) != 0)
			return(1);
		pthread_mutex_destroy(&lock, NULL)
		printf("%d", number);

	}

```
Now what **pthread_mutex_lock** does is tell the thread to not start reading until the other thread has finished it's job, thus getting away from any **race condition**.

> It's worth to mention that the mutexes will reduce the time of execution; therefore it is optimal to not use them all around...  
**Remember, your program should be perfect; and slow ain't perfect** 

### What are the functions am i going to use while tackling this project?

For this part, you can just go use your man to find what each function does, buuuut since I have this deal with myself to make this repo the all and be all for this project...  

1. pthread functions (POSIX thread)
    - [pthread_create](#pthread_create)
    - [pthread_detach](#pthread_detach)
	- [pthread_join](#pthread_join)
	- [pthread_mutex_init](#pthread_mutex_init)
	- [pthread_mutex_lock](#pthread_mutex_lock)
	- [pthread_mutex_unlock](#pthread_mutex_unlock)
	- [pthread_mutex_destroy](#pthread_mutex_destroy)  
---

pthread_create 
---
``` c
	int pthread_create(pthread_t *restrict thread, const pthread_attr_t *restrict attr, void *(*start_routine)(void *), void *restrict arg);
```

> *pthread create* function starts a new thread in the calling process. The new thread starts executing by invoking a **routine function** while passing **arg** as a parameter for the routine function. For the **attributes** argument I'd like to refer you to the [POSIX attributes man page](https://man7.org/linux/man-pages/man7/attributes.7.html), but in short; it's the safety of calling said function in a certain context.  
>> For the sake of this project, no attribute will be needed; but for better understanding the whole porspect; I **really encourage you to give that man page a good read.** 

>On success, pthread_create() returns 0, on error it returns an error number and the contents of *thread are undefined.
---
pthread_detach
---
```c
       int pthread_detach(pthread_t thread);
```

> *pthread_detach* function is basically self explanatory, it takes a thread and marks it as detached, meaning that all the ressources used by that thread has been released.  
>> attempting to detach an already detached thread results in an unspecified behavior.  

>On success, pthread_detach() returns 0, on error it returns an error number

---
pthread_join
---
```c
	int pthread_join(pthread_t thread, void **retval);
```

> *pthread_join* function waits for the thread specified to terminate. if that thread has already been terminated then **pthread_join** returns immediately, and the thread specified by thread must be joinable.
>> If *retval* is not *NULL*, the **pthread_join()** copies the exit status of the target thread into the location pointed to by *retval*

> On success, pthread_join() returns 0, on error it returns an error number.  
---

pthread_mutex_init
---
```c
int pthread_mutex_init(pthread_mutex_t *mutex, 
    const pthread_mutexattr_t *attr);
```
> *pthread_mutex_init* function initializes the mutex referenced by mutex with attributes specified by attr (see the remark earlier about the attributes)
>>Upon successful initialization, the state of the mutex becomes initialised and unlocked.
---
pthread_mutex_destroy
---
```c
int pthread_mutex_destroy(pthread_mutex_t *mutex);
```
> *pthread_mutex_destroy* function destroys the mutex referenced by mutex; rendering them "uninitialized", in other terms, it turns the object set to by mutex to an invalid value.
>> It is best to destroy an unlocked mutex, the destroying of an already locked mutex will cause undifined behaviors
---
pthread_mutex_lock
---
```c
int pthread_mutex_lock(pthread_mutex_t *mutex);
```

> *pthread_mutex_lock* function locks the object referenced by *mutex*, if the mutex is already locked, the calling thread blocks until the mutex becomes available. this operation returns with the mutex object referenced to by the mutex in a locked state (visit the race condition section for more information)
>> There is another similar function *pthread_mutex_trylock* which before locking the object; it checkes if said object was already locked; if true it immediatly returns; else it proceeds to lock the object.  

>On success, the *pthread_mutex_lock* returns zero, otherwise an error number.
---
pthread_mutex_unlock
---
```c
int pthread_mutex_unlock(pthread_mutex_t *mutex);
```
> *pthread_mutex_unlock* function unlock the object referenced by *mutex* based on the attributes passed to the thread.
>> if there are threads blocked on the mutex object referenced by mutex when pthread_mutex_unlock() is called, resulting in the mutex becoming available, the scheduling policy is used to determine which thread shall acquire the mute.  
> On success, *pthread_mutex_unlock* returns 0, otherwise it returns an error number. (check the error codes [here](https://pubs.opengroup.org/onlinepubs/007908799/xsh/pthread_mutex_unlock.html)).  

And just like that , we have finished with the introductory part.  
Now onto the actual logic behind the project...  
>Disclaimer : This next part is an explanation of the logic i went with while tackling this project; and by no means does it mean to take this logic and work with it  






> Note to self   
	Dude I know you are tired and can't be arsed to do anything but please *for the love of god, finish something in your damn life!!!!*



If you have any question about this sector or have found any misconception, please don't hesitate to contact [me](https://twitter.com/mehdicharouh1), I'll be more than happy to explain/fix upon my "article". 



<!-- routine :
	Eating :
		-> Lock the first fork and print
			Check if the 2nd fork is taken
		-> Lock the 2nd fork and print
		-> start eating and wait with the given args
		-> unlock the forks
	Sleeping :
		-> After the philo finishes eating, he would imediatly sleep for the arg the user has added in input (Print then sleep)
			-> You need to create your own sleep function (use gettimeofday and usleep)
	Thinking :
		-> Is the next step where the philos stand with no instruction
	

MY Struct :

	->The first one has all the info we need to start the program (number of philos/forks, the times)
	->The second has all the data we generate (Philos IDs)

Notes :
	The routine is an infinite loop of the three actions made by the philos (eating, sleeping and thinking)

How Do i create forks :
	-> How do i allocate to them :
			Forks are data types that are represented as pthread_mutex_t, you simply create an array of said data type with the amount of forks that are given which is the number of philos
	->


STEPS :

		---FIRST--- :
	-> Initialize your main list of Philos with their list of identifiers (timers, ID's ..)
	 -->