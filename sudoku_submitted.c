/* Program to assist in the challenge of solving sudoku puzzles.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2021, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: [Zixu Zhou 1272504]
   Dated:     [13/09/2021]

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* these #defines provided as part of the initial skeleton */

#define NDIM 3		/* sudoku dimension, size of each inner square */
#define NDIG (NDIM*NDIM)
			/* total number of values in each row */
#define NGRP 3		/* number of sets each cell is a member of */
#define NSET (NGRP*NDIG)
			/* total number of sets in the sudoku */
#define NCLL (NDIG*NDIG)
			/* total number of cells in the sudoku */

#define ERROR	(-1)	/* error return value from some functions */

/* these global constant arrays provided as part of the initial skeleton,
   you may use them in your code but must not alter them in any way,
   regard them as being completely fixed. They describe the relationships
   between the cells in the sudoku and provide a basis for all of the
   sudoku processing loops */

/* there are 27 different different sets of elements that need to be
   checked against each other, this array converts set numbers to cells,
   that's why its called s2c */
int s2c[NSET][NDIM*NDIM] = {
	/* the first group of nine sets describe the sudoku's rows */
	{  0,  1,  2,  3,  4,  5,  6,  7,  8 },
	{  9, 10, 11, 12, 13, 14, 15, 16, 17 },
	{ 18, 19, 20, 21, 22, 23, 24, 25, 26 },
	{ 27, 28, 29, 30, 31, 32, 33, 34, 35 },
	{ 36, 37, 38, 39, 40, 41, 42, 43, 44 },
	{ 45, 46, 47, 48, 49, 50, 51, 52, 53 },
	{ 54, 55, 56, 57, 58, 59, 60, 61, 62 },
	{ 63, 64, 65, 66, 67, 68, 69, 70, 71 },
	{ 72, 73, 74, 75, 76, 77, 78, 79, 80 },
	/* the second group of nine sets describes the sudoku's columns */
	{  0,  9, 18, 27, 36, 45, 54, 63, 72 },
	{  1, 10, 19, 28, 37, 46, 55, 64, 73 },
	{  2, 11, 20, 29, 38, 47, 56, 65, 74 },
	{  3, 12, 21, 30, 39, 48, 57, 66, 75 },
	{  4, 13, 22, 31, 40, 49, 58, 67, 76 },
	{  5, 14, 23, 32, 41, 50, 59, 68, 77 },
	{  6, 15, 24, 33, 42, 51, 60, 69, 78 },
	{  7, 16, 25, 34, 43, 52, 61, 70, 79 },
	{  8, 17, 26, 35, 44, 53, 62, 71, 80 },
	/* the last group of nine sets describes the inner squares */
	{  0,  1,  2,  9, 10, 11, 18, 19, 20 },
	{  3,  4,  5, 12, 13, 14, 21, 22, 23 },
	{  6,  7,  8, 15, 16, 17, 24, 25, 26 },
	{ 27, 28, 29, 36, 37, 38, 45, 46, 47 },
	{ 30, 31, 32, 39, 40, 41, 48, 49, 50 },
	{ 33, 34, 35, 42, 43, 44, 51, 52, 53 },
	{ 54, 55, 56, 63, 64, 65, 72, 73, 74 },
	{ 57, 58, 59, 66, 67, 68, 75, 76, 77 },
	{ 60, 61, 62, 69, 70, 71, 78, 79, 80 },
};


/* there are 81 cells in a dimension-3 sudoku, and each cell is a
   member of three sets, this array gets filled by the function 
   fill_c2s(), based on the defined contents of the array s2c[][] */
int c2s[NCLL][NGRP];

void
fill_c2s() {
	int s=0, d=0, c;
	for ( ; s<NSET; s++) {
		/* record the first set number each cell is part of */
		for (c=0; c<NDIM*NDIM; c++) {
			c2s[s2c[s][c]][d] = s;
		}
		if ((s+1)%(NGRP*NDIM) == 0) {
			d++;
		}
	}
#if 0
	/* this code available here if you want to see the array
	   cs2[][] that gets created, just change that 0 two lines back
	   to a 1 and recompile */
	for (c=0; c<NCLL; c++) {
		printf("cell %2d: sets ", c);
		for (s=0; s<NGRP; s++) {
			printf("%3d", c2s[c][s]);
		}
		printf("\n");
	}
	printf("\n");
#endif
	return;
}

/* find the row number a cell is in, counting from 1
*/
int
rownum(int c) {
	return 1 + (c/(NDIM*NDIM));
}

/* find the column number a cell is in, counting from 1
*/
int
colnum(int c) {
	return 1 + (c%(NDIM*NDIM));
}

/* find the minor square number a cell is in, counting from 1
*/
int
sqrnum(int c) {
	return 1 + 3*(c/NSET) + (c/NDIM)%NDIM;
}

/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration 
*/


/****************************************************************/


/****************************************************************/

/* debugging statements from programming tips by Alistair Moffat
*/
#define DEBUG 0
#if DEBUG
#define DUMP_INT(x) printf("line %d: %s = %2d\n", __LINE__, #x, x)
#else
#define DUMP_int(x)
#endif
    
int print_sudoku(int array[]);
int find_GCD(int, int);
int find_duplicate(int array[], int);
int find_missing_num(int array[]);
void strat_one(int array[]);\
void blank_line(void);


/* main program controls all the action
*/

int
main(int argc, char *argv[]) {
	
	int val, sudoku[NCLL], temp_array[NDIG],i, j;
	int set_violations = 0, tot_violations = 0, check;
	
	fill_c2s();
	
	blank_line();
    
	for(i = 0; i < NCLL; i++){
		scanf("%d", &val);
		sudoku[i] = val;
	}
    print_sudoku(sudoku);
    /* creates and checks for duplicate violations in each set
    */
    
    for (i = 0; i < NSET; i++){
        for (j = 0; j < NDIG; j++){
            temp_array[j] = sudoku[s2c[i][j]];
        }
        check = find_duplicate(temp_array, i);
        if ( check ){
        	set_violations++;
        	tot_violations += check;
        }
    }
    /* are there any violations? if yes PROGRAM TERMINATED*/
    if ( set_violations && tot_violations ){
		printf("\n%d different sets have violations\n", set_violations);
		printf("%d violations in total\n", tot_violations);
		exit(EXIT_FAILURE);
    }
    
    strat_one(sudoku);
	
	return 0;
}

/****************************************************************/

/* prints the array that is entered with sudoku formatting
*/
int
print_sudoku(int array[]){
	
    int zero_count = 0, i;
    
    for (i = 1; i <= NCLL; i++){
        if ( array[i - 1] == 0 && (i % NDIG) ){
            zero_count += 1;
            printf(". ");
        }    
        else if ( array[i - 1]==0 ){
        	zero_count += 1;
        	printf(".");
        }
        else if( !(i % NDIG) ){
        	printf("%d", array[i - 1]);
        }
        else{
            printf("%d ", array[i - 1]);
        }
        if ( !((i % NDIG)) ){
            printf("\n");
        }
        if ( !(i % NDIM) && (i % NDIG) ){
            printf("| ");
        }
        if ( !(i % NSET) && (i % NCLL) ){
            printf("------+-------+------\n" );
        }
    }
    blank_line();
    printf("%2d cells are unknown\n\n", zero_count);
    
    return zero_count;
}

/***********************************************************/

/*helper function meant to determine the greatest common divisor
*/

int find_GCD(int num1, int num2){
	
	if ( num1 % num2 ){
		return find_GCD(num2, num1 % num2);
	}
	return num2;
}

/************************************************************/

/* finds duplicates of given array by assigning corresponding prime numbers to
each non-zero number and finding greatest common divisor
*/

int find_duplicate(int array[], int set_num){
	int primes[] = { 2,3,5,7,11,13,17,19,23 };
	int product_of_primes = 1, value = 1, violations = 0, i;
	
	/*creates product of all corresponding primes*/
	for (i = 0; i < NDIG; i++){
		product_of_primes *= primes[i];
		if ( array[i] != 0 ){
			value *= primes[array[i] - 1];
		}
	}
	/* find GCD of product*/
	int duplicates_product = value / find_GCD(product_of_primes, value);
	
	/* if there is a duplicate, find out how many*/
	for (i = 0; i < NDIG; i++){
		int count = 1;
		/* seeing how many of the duplicate there are*/
		while ( !(duplicates_product % primes[i]) ){
			count++;
			duplicates_product /= primes[i];
		}
		/* counting violations */
		if ( count > 1 ){
			violations += 1;
		}
		/* checking if set is row, col or sqr*/
		if( count > 1 && (set_num - (2 * NDIG)) >= 0 ){
			printf("set %2d (sqr %d): %d instances of %d\n",
				set_num, (set_num + 1) - (2 * NDIG), count, i + 1);
		}
		else if( count > 1 && (((set_num) - NDIG >= 0)) ){
			printf("set %2d (col %d): %d instances of %d\n",
				set_num, (set_num + 1) - NDIG, count, i + 1);
		}
		else if( count > 1 ){
			printf("set %2d (row %d): %d instances of %d\n",
				set_num, set_num + 1, count, i + 1);
		}
	}
	
	return violations;
}

/***************************************************************/

/*finds missing single digit number among an array, required for strategy one
*/
int 
find_missing_num(int array[]){
	int sudokuNums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}, i, j, counter = 0;
	
	/*loops gets rid of non_zero numbers in sudokuNums that are also in the 
	argument array*/
	for (i = 0;i < NDIG;i++){
		for (j = 0; j < NSET; j++){
			if ( sudokuNums[i] == array[j] && array[j] != 0 ){
				sudokuNums[i] = 0;
				counter++;
			}
		}
	}
	/*did we remove 8 of the 9 numbers? If so, return remaining number*/
	if ( counter == (NDIG - 1) ){
		for (i = 0; i < NDIG; i++){
			if ( sudokuNums[i] != 0 ){
				return sudokuNums[i];
			}
		}
	}
	return 0;
}

/********************************************************************/

/* fills in sudoku based on strategy one - finding the only possible number in 
a cell
*/
void
strat_one(int array[]){
	int temp_array[NSET], num_array[NCLL], pos_array[NCLL];
	int i, j, k, l = 0, m, n = 0;
	int flag = 1, check;
	
	/* try strategy one until sudoku cannot be solved or is completely filled */
    while( flag ){
    	flag = 0;
    	/* making array of length NSET to test the column, row and square the 
    	cell belongs to*/
		for (i = 0; i < NCLL; i++){
			if ( !(array[i]) ){
				for (j = 0; j < NGRP; j++){
					for (k = 0; k < NDIG; k++){
						temp_array[l] = array[s2c[c2s[i][j]][k]];
						l++;
					}
				}
				/* creates arrays to hold the number to be filled in and the
				position to be filled at*/
				if ( find_missing_num(temp_array) ){
					num_array[n] = find_missing_num(temp_array);
					pos_array[n] = i;
					n++;
					flag = 1;
				}
				l = 0;
				
			}
		}
		/* if the sudoku can be changed, make the changes*/
		if ( flag ){
			printf("strategy one\n");
			m = n;
			for (n = 0; n < m; n++){
				printf("row %d col %d must be %d\n", rownum(pos_array[n]),
					   colnum(pos_array[n]), num_array[n]);
				array[pos_array[n]] = num_array[n];
			}
			blank_line();
		}
		n = 0;
		
	}
	
	check = print_sudoku(array);
	
	if ( !check ){
		/* we solved it!! */
		printf("ta daa!!!\n");
	}
}

/****************************************************************/

/* helper functions (from example given on canvas)
*/

void
blank_line(void) {
	printf("\n");
}

/* algorithms are fun! */

/****************************************************************/