#include <stdio.h>
#include <string.h>
#include <time.h>

#include "DynamicArray.h"

#define MIN     1000000
#define MAX     10000000
#define STEP    1000000
#define RATE    2.0

#define COL1    "# expand  "
#define COL2    "growth rate  "
#define COL3    "max op time 1 (msec)  "
#define COL4    "max op time 2 (msec)  "
#define COL5    "max op time 3 (msec)  "

int main(){

    int n;

    /* print header */
    printf("%-*s %-*s %-*s %-*s %-*s\n", 
        strlen(COL1), COL1, 
        strlen(COL2), COL2, 
        strlen(COL3), COL3, 
        strlen(COL4), COL4,
        strlen(COL5), COL5
    );

    for (n = MIN; n <= MAX; n += STEP) {

        int i;
        unsigned long theStart;
        double theMaxDuration1 = 0.0,  theMaxDuration2 = 0.0,  theMaxDuration3 = 0.0;

        DynamicArray* theArray;
        
        /* ------------------- run 1 ------------------- */
        theArray = DynamicArray_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        for (i = 0; i < n; ++i) {
            double theOpDuration;
            unsigned long theOpStart = clock();
            DynamicArray_Expand(theArray);
            theOpDuration = (double)(clock() - theOpStart) / CLOCKS_PER_SEC * 1000;
            if (theOpDuration > theMaxDuration1) theMaxDuration1 = theOpDuration;
        }

        DynamicArray_Delete(theArray);
        
        /* ------------------- run 2 ------------------- */
        theArray = DynamicArray_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        for (i = 0; i < n; ++i) {
            double theOpDuration;
            unsigned long theOpStart = clock();
            DynamicArray_Expand(theArray);
            theOpDuration = (double)(clock() - theOpStart) / CLOCKS_PER_SEC * 1000;
            if (theOpDuration > theMaxDuration2) theMaxDuration2 = theOpDuration;
        }

        DynamicArray_Delete(theArray);
        
        /* ------------------- run 3 ------------------- */
        theArray = DynamicArray_New(sizeof(int), RATE);
        if (!theArray) goto Err;

        for (i = 0; i < n; ++i) {
            double theOpDuration;
            unsigned long theOpStart = clock();
            DynamicArray_Expand(theArray);
            theOpDuration = (double)(clock() - theOpStart) / CLOCKS_PER_SEC * 1000;
            if (theOpDuration > theMaxDuration3) theMaxDuration3 = theOpDuration;
        }

        DynamicArray_Delete(theArray);

        /* print row */
        printf("%-*lu %-*f %-*f %-*f %-*f\n", 
            strlen(COL1), n, 
            strlen(COL2), RATE, 
            strlen(COL3), theMaxDuration1, 
            strlen(COL4), theMaxDuration2, 
            strlen(COL5), theMaxDuration3 
        );
    }

    return 0;
        
Err:
    fprintf(stderr, "Error in main\n");
    return 1;
}
