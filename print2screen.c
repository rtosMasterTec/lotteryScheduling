#include "print2screen.h"
#include <ncurses.h>

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
        }

	clear();	//Clear stdscr
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

        int i,row,col,MAXROW,MAXCOL;
	getmaxyx(stdscr,MAXROW,MAXCOL);
	float progressA,progressB,progressC,progressD,progressE;
	progressA = (ta->currTerm/ta->totalTerms)*100;
	progressB = (tb->currTerm/tb->totalTerms)*100;
	progressC = (tc->currTerm/tc->totalTerms)*100;
	progressD = (td->currTerm/td->totalTerms)*100;
	progressE = (te->currTerm/te->totalTerms)*100;

        printw("\rProgress A: %d %% [", (int) progressA);
        for(i = 0 ; i < (int) progressA; i++){
        	printw("=");
		print_end_delimiter(i,(int) progressA);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, MAXCOL-5, "]");
        printw("\n");
        printw("\rProgress B: %d %% [", (int) progressB);
        for(i = 0 ; i < (int) progressB; i++){
        	printw("=");
		print_end_delimiter(i,(int) progressB);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, MAXCOL-5, "]");
        printw("\n");
        printw("\rProgress C: %d %% [", (int) progressC);
        for(i = 0 ; i < (int) progressC; i++){
        	printw("=");
		print_end_delimiter(i,(int) progressC);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, MAXCOL-5, "]");
        printw("\n");
        printw("\rProgress D: %d %% [", (int) progressD);
        for(i = 0 ; i < (int) progressD; i++){
        	printw("=");
		print_end_delimiter(i,(int) progressD);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, MAXCOL-5, "]");
        printw("\n");
        printw("\rProgress E: %d %% [", (int) progressE);
        for(i = 0 ; i < (int) progressE; i++){
        	printw("=");
		print_end_delimiter(i,(int) progressE);
	};
	getyx(stdscr, row, col);
	mvaddstr(row, MAXCOL-5, "]");
        printw("\n");
        refresh();	//refresh stdscr

}

