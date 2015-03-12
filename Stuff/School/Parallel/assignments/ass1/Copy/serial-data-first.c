/*******************************************************************************
*
*  Filter a large array based on the values in a second array.
*
********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <omp.h>
#include <math.h>
#include <assert.h>

/* Example filter sizes */
#define DATA_LEN  512*512*128
#define FILTER_LEN  4
#define NUM_THREADS 16


/* Subtract the `struct timeval' values X and Y,
    storing the result in RESULT.
    Return 1 if the difference is negative, otherwise 0. */
int timeval_subtract (struct timeval * result, struct timeval * x, struct timeval * y)
{
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
    
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}


/* Function to apply the filter with the filter list in the outside loop */
void serialDataFirst ( int data_len, unsigned int* input_array, unsigned int* output_array, int filter_len, unsigned int* filter_list, FILE *f )
{
  /* Variables for timing */
  struct timeval ta, tb, tresult;

  /* get initial time */
  gettimeofday ( &ta, NULL );

  /* for all elements in the data */
  for (int x=0; x<data_len; x++) {
    /* for all elements in the filter */ 
    for (int y=0; y<filter_len; y++) { 
      /* it the data element matches the filter */ 
      if (input_array[x] == filter_list[y]) {
        /* include it in the output */
        output_array[x] = input_array[x];
      }
    }
  }

  /* get initial time */
  gettimeofday ( &tb, NULL );

  timeval_subtract ( &tresult, &tb, &ta );

  // printf ("Serial data first took %lu seconds and %lu microseconds.\n", tresult.tv_sec, tresult.tv_usec );
  fprintf(f, "%d,%lu\t,%lu\n", filter_len, tresult.tv_sec, tresult.tv_usec );
}

void checkData ( unsigned int * serialarray, unsigned int * parallelarray )
{
  for (int i=0; i<DATA_LEN; i++)
  {
    if (serialarray[i] != parallelarray[i])
    {
      printf("Data check failed offset %d\n", i );
      return;
    }
  }
}


int main( int argc, char** argv )
{
  /* loop variables */
  int x,y;

  /* Create matrixes */
  unsigned int * input_array;
  unsigned int * serial_array;
  unsigned int * output_array;
  unsigned int * filter_list;

  /* Initialize the data. Values don't matter much. */
  posix_memalign ( (void**)&input_array, 4096,  DATA_LEN * sizeof(unsigned int));
//  input_array = (unsigned int*) posix_memalign ( DATA_LEN * sizeof(unsigned int), 4096);
  for (x=0; x<DATA_LEN; x++)
  {
    input_array[x] = x % 2048;
  }

  /* start with an empty *all zeros* output array */
  posix_memalign ( (void**)&output_array, 4096, DATA_LEN * sizeof(unsigned int));
  memset ( output_array, 0, DATA_LEN );
  posix_memalign ( (void**)&serial_array, 4096, DATA_LEN * sizeof(unsigned int));
  memset ( serial_array, 0, DATA_LEN );

  /* Initialize the filter. Values don't matter much. */
  filter_list = (unsigned int*) malloc ( FILTER_LEN * sizeof(unsigned int));
  for (y=0; y<FILTER_LEN; y++)
  {
    filter_list[y] = y;
  }

  // FILE *f = fopen("output.txt", "a");
  FILE *f = fopen("serialoutput.csv", "a");


  fprintf(f, "-----------------------------------------------------------\n");
  /* Execute at a variety of filter lengths */
  for ( int filter_len =1; filter_len<=FILTER_LEN; filter_len*=2) 
  {
    // fprintf(f, "\nDATA_LEN = %d, FILTER_LEN = %d \n------------------------------------\n", DATA_LEN, filter_len);
    // printf("\nDATA_LEN = %d, FILTER_LEN = %d \n------------------------------------\n", DATA_LEN, filter_len);
    // fprintf(f, "\n");

    serialDataFirst ( DATA_LEN, input_array, serial_array, filter_len, filter_list, f );
    memset ( output_array, 0, DATA_LEN );

    // serialFilterFirst ( DATA_LEN, input_array, output_array, filter_len, filter_list, f );
    // checkData ( serial_array, output_array );
    // memset ( output_array, 0, DATA_LEN );

    // parallelDataFirst ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    // checkData ( serial_array, output_array );
    // memset ( output_array, 0, DATA_LEN );

    // parallelFilterFirst ( DATA_LEN, input_array, output_array, filter_len, filter_list );
    // checkData ( serial_array, output_array );
    // memset ( output_array, 0, DATA_LEN );
  }
}

