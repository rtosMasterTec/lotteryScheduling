#include "mathAlgo.h"

/*PI calculation                                                           *
* the Following formula calculate 2 arcsin (1) given by the Taylor series  *
* where  arcsin(x) =                                                       *
*                    x                           // n = 1                  *
*                    + 1/2 (x^3/3)               // n = 2                  *
*                    + (1/2)(3/4)(x^5/5)         // n = 3 .... etc         *
*                    + [1/2)(3/4)(5/6)(x^7/7) + ... "                      *
* and x = 1 for this case                                                  *
* N.B: THIS SERIES CONVERGERS VERRRRYYY SLOWLY! for 10,000 terms,          *
* pi = 3.130309. I checked this with an online reference.                  */
void calculatePI(threadData_t *t ,double percentage)
{
   double tempResultA = 0;
   double tempResultB = 1;
   double n = 2;  //initial m value
   double m = 2;  //initial m value
   int numTermsExecute = 0;
   int totalIterations = 0;
   int currentIteration = 1;
   
//printf("In Calculate PI\n");
   // set percentage
   if(percentage == 100)
   {
      numTermsExecute = t->totalTerms;
   }
   else
   {
      numTermsExecute = t->totalTerms*(percentage/100);
//printf("NTE: %d\n", numTermsExecute);
	totalIterations = (t->totalTerms/numTermsExecute) + 1;
//printf("TI: %d\n", totalIterations);
   }

   if(t->totalTerms == 1)
   {
      t->currPiValue = 2*1;

      return;
   }
   else
   {
     t->currPiValue = 2*1;
   }

   while (n <= t->totalTerms)
   {
      
      // Calculate last fraction of a single nth term (i.e (x^5/5)) for x = 1
      tempResultA = 2*(1/((2*n)-1));

      // calculates the remaining first n-1 fractions of nth term (i.e (1/2)(3/4))
      while(m <= n)
      {
          tempResultB = tempResultB*(((2*m)-3)/((2*m)-2));
        //printf("This fract is %f : Nth term = %d \n", tempResultB, (int) n);
          m++;
      }

      // multiplies previous calculations (i.e (x^5/5)*(1/2)(3/4))
      // this is the calculation of an nth term
      t->currPiValue = t->currPiValue + (tempResultA*tempResultB);
      t->currTerm = n;
      
      n++;
      // Reset Variables
      m = 2;
      tempResultB = 1;
      
      
	// not preemptive code to give control to CPU
      if (totalIterations != 0 && (n == (numTermsExecute*currentIteration))) // if not preemptive we go in here
      {
            currentIteration++;
	 printf("---Giving Control to Scheduler---\n");
            //give control to scheduler; Should eventually return control here
	    syscall(SIGVTALRM); 
      }
      
   } //end while totalTerms
   
}



