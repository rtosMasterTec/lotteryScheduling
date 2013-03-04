#include "print2screen.h"
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
printf("\rAthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
ta->currPiValue, ta->currTerm, ta->totalTerms, is_activeA);
printf("\rBthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
tb->currPiValue, tb->currTerm, tb->totalTerms, is_activeB);
printf("\rCthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
tc->currPiValue, tc->currTerm, tc->totalTerms, is_activeC);
printf("\rDthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
td->currPiValue, td->currTerm, td->totalTerms, is_activeD);
printf("\rEthread: Pi Value: %f  CurrentTerm: %d  TotalTerms: %d Active: %d\n", 
te->currPiValue, te->currTerm, te->totalTerms, is_activeE);
//	printf("\rProgress: %d%% [", progress);
//	for(i = 0 ; i < progress; i++)
//	printf("=");
	fflush(stdout);
}
