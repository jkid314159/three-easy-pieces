#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

/* File Comments
Date:	January 30, 2016
Author: Alex Cholakis
E-Mail: coder314159@gmail.com
Book:	Operating Systems: Three Easy Pieces
URL:	http://pages.cs.wisc.edu/~remzi/OSTEP/cpu-api.pdf
Chap:	5 Interlude: Process API
HW Q:	6
Oh!	:	waitpid() useful when program needs to wait for specified child.
		waitpid() returns no child.  Returning threads crash into each
		other, no waiting.  Program output below:
		
			$ ./P56
			hello world (pid:1644)

			hello, I am child (pid:5880) (returnchild:0) (waitcall:-1)
			waitpidhello, I am parent of 5880 (pid:1644)
			: No child processes

		Part of child returns, then parent interrupts and returns, 
		and finally, child thread returns and completes.  Pretty Ugly! 
*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*/

main( int argc, char *argv[] )
{	
	int status;
	printf( "hello world (pid:%d)\n\n", (int) getpid() );
	
	int returnchild = fork();
	
	// fork failed; exit
	if ( returnchild < 0 ) {
		fprintf( stderr, "fork failed\n\n" );
		exit( 1 );	
	} //  end if
	// child (new process)
	else if ( returnchild == 0 ) { 
		int childpid = ( int ) getpid();
		int waitcall = waitpid( returnchild, &status, WUNTRACED | WCONTINUED );
		printf( "hello, I am child (pid:%d) (returnchild:%d) (waitcall:%d)\n", 
				childpid, returnchild, waitcall );
		if ( waitcall == -1 ) {
			perror("waitpid");
			exit( EXIT_FAILURE );
		} // end if
	} // end else inner if
	// parent goes down this path (main)
	else {
		int parentpid = (int) getpid();
		printf( "hello, I am parent of %d (pid:%d)\n", 
				returnchild, parentpid );
				
	} // end else
	return 0;
} // end main