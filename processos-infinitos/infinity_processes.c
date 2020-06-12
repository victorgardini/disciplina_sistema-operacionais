#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	// DO NOT EXECUTE THIS PROGRAM ON A SHARED SYSTEM WITHOUT
	// PERMISSION. THIS WILL HALT THE OPERATIONAL SYSTEM.
	// ALSO, EXECUTE sync ON TERMINAL BEFORE EXECUTE THIS 
	// PROGRAM

	pid_t child;
	
	int i = 0;
	while(1){
		child = fork(); // Creates a child process
		printf("Child process %d created\n", i);
		i++;
	}
}
