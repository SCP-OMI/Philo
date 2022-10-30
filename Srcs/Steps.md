
routine :
	Eating :
		--> Lock the first fork and print
			Check if the 2nd fork is taken
		--> Lock the 2nd fork and print
		--> start eating and wait with the given args
		--> unlock the forks
	Sleeping :
		--> After the philo finishes eating, he would imediatly sleep for the arg the user has added in input (Print then sleep)
			--> You need to create your own sleep function (use gettimeofday and usleep)
	Thinking :
		--> Is the next step where the philos stand with no instruction
	

MY Struct :

	-->The first one has all the info we need to start the program (number of philos/forks, the times)
	-->The second has all the data we generate (Philos IDs)

Notes :
	The routine is an infinite loop of the three actions made by the philos (eating, sleeping and thinking)

How Do i create forks :
	--> How do i allocate to them :
			Forks are data types that are represented as pthread_mutex_t, you simply create an array of said data type with the amount of forks that are given which is the number of philos
	-->


STEPS :

		---FIRST--- :
