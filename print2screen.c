#include "print2screen.h"

void print_end_delimiter(int x, int y){
	if(x == y-1){
		printw(">");
	};
}

void print2screen(
        threadData_t *ta,
        threadData_t *tb,
        threadData_t *tc,
        threadData_t *td,
        threadData_t *te,
	int active_thread_n
){
	int is_activeA = 0;
	int is_activeB = 0;
	int is_activeC = 0;
	int is_activeD = 0;
	int is_activeE = 0;

        int i;
	int row;
	int col;
	int MAXROW;
	int MAXCOL;
	int P_BAR_WIDTH;

        float progressA;
	float progressB;
	float progressC;
	float progressD;
	float progressE;

	if(active_thread_n == 0){
		is_activeA = 1;		
	}else if(active_thread_n == 0){
                is_activeA = 1;
	}else if(active_thread_n == 1){
                is_activeB = 1;
	}else if(active_thread_n == 2){
                is_activeC = 1;
	}else if(active_thread_n == 3){
                is_activeD = 1;
	}else if(active_thread_n == 4){
                is_activeE = 1;
        }else{
		is_activeA = 1;
	}

	////////////////////////////////////////
	// Print to screen
	////////////////////////////////////////

	//Clear stdscr
	clear();

	// Get terminal dimensions
	getmaxyx(stdscr,MAXROW,MAXCOL);

	printw("\rAthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
	ta->currPiValue, ta->currTerm, ta->totalTerms, is_activeA);
	printw("\rBthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
	tb->currPiValue, tb->currTerm, tb->totalTerms, is_activeB);
	printw("\rCthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
	tc->currPiValue, tc->currTerm, tc->totalTerms, is_activeC);
	printw("\rDthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
	td->currPiValue, td->currTerm, td->totalTerms, is_activeD);
	printw("\rEthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
	te->currPiValue, te->currTerm, te->totalTerms, is_activeE);

	//Percentage of completion
	progressA = (ta->currTerm/ta->totalTerms)*100;
	progressB = (tb->currTerm/tb->totalTerms)*100;
	progressC = (tc->currTerm/tc->totalTerms)*100;
	progressD = (td->currTerm/td->totalTerms)*100;
	progressE = (te->currTerm/te->totalTerms)*100;

	//Number of steps per percent
	P_BAR_WIDTH = 60;	// recommend 90 width
	int total_ticks = P_BAR_WIDTH-6;
	int progress_ticksA = (progressA*total_ticks)/100;
	int progress_ticksB = (progressB*total_ticks)/100;
	int progress_ticksC = (progressC*total_ticks)/100;
	int progress_ticksD = (progressD*total_ticks)/100;
	int progress_ticksE = (progressE*total_ticks)/100;

        printw("\rProgress A: %d %% [", (int) progressA);
        for(i = 0 ; i < (int) progress_ticksA; i++){
        	printw("=");
		print_end_delimiter(i,(int) progress_ticksA);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, total_ticks+20, "]");
        printw("\n");
        printw("\rProgress B: %d %% [", (int) progressB);
        for(i = 0 ; i < (int) progress_ticksB; i++){
        	printw("=");
		print_end_delimiter(i,(int) progress_ticksB);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, total_ticks+20, "]");
        printw("\n");
        printw("\rProgress C: %d %% [", (int) progressC);
        for(i = 0 ; i < (int) progress_ticksC; i++){
        	printw("=");
		print_end_delimiter(i,(int) progress_ticksC);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, total_ticks+20, "]");
        printw("\n");
        printw("\rProgress D: %d %% [", (int) progressD);
        for(i = 0 ; i < (int) progress_ticksD; i++){
        	printw("=");
		print_end_delimiter(i,(int) progress_ticksD);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, total_ticks+20, "]");
        printw("\n");
        printw("\rProgress E: %d %% [", (int) progressE);
        for(i = 0 ; i < (int) progress_ticksE; i++){
        	printw("=");
		print_end_delimiter(i,(int) progress_ticksE);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, total_ticks+20, "]");
        printw("\n");

	//refresh stdscr
        refresh();

}

