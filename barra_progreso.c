//Autor: YU
#include <stdio.h>
#include <curses.h>
#include <term.h>

int main(void) {
	printf("Hello world\n");

	int progress = 0;
	int i = 0;
	while(progress < 100)
	{
	    // Note the carriage return at the start of the string and the lack of a
	    // newline
	    printf("\rProgress: %d%% [", progress);
	for(i = 0 ; i < progress; i++)
	printf("=");
	    fflush(stdout);

	    // Do some work, and compute the new progress (0-100)
	    progress = progress+1;
	    sleep(1);
	}
	printf("\nDone\n");
return 0;
}
