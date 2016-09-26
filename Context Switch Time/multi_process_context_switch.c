#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#pragma intrinsic(__rdtsc)

char *phrase = "Stuff";


int main()
{
  int fd[2], bytesRead;
  char message [100]; /* Parent process message buffer */
  pipe ( fd ); /*Create an unnamed pipe*/
  uint64_t sum = 0;
  int i;

  // for(i=0;i<1;i++)
  {
    unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
    int iteration, process_no = 2;

    float timeoverhead = 101.03;
    float pipeoverhead = 2515.3961084;
    float process_creation_overhead = 491661.715;
    // for(process_no=2;process_no <21; process_no++)
    {
    ////////////////////////////////////////////////////
      asm volatile ("CPUID\n\t"
     "RDTSC\n\t"
     "mov %%edx, %0\n\t"
     "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
     "%rax", "%rbx", "%rcx", "%rdx");
     ///////////////////////////////////////////////////////
     sum=0;
     // int process_no = 1
     int f = fork();

     for(iteration =1 ; iteration < process_no; iteration ++)
     { 
      
      if ( f == 0 )
      {
       /* Child Writer */
       close (fd[0]); /* Close unused end*/
       write (fd[1], phrase, strlen ( phrase) +1); /* include NULL*/
       close (fd[1]); /* Close used end*/
       exit(0);
      } 
      else if(iteration < process_no -1)
      {
        int wt = wait(NULL);
        close (fd[1]); /* Close unused end*/
        bytesRead = read ( fd[0], message, 100);
        /* Parent Reader */
        // printf ( "Parent: Read %d bytes from pipe: %s\n", bytesRead, message);
        close ( fd[0]); /* Close used end */
        f = fork();
      }
     }
     ///////////////////////////////////////////////////////
     asm volatile("RDTSCP\n\t"
     "mov %%edx, %0\n\t"
     "mov %%eax, %1\n\t"
     "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
     "%rax", "%rbx", "%rcx", "%rdx");
     /////////////////////////////////////////////////////////

      uint64_t t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
      uint64_t t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
      sum=(t1-t);
      printf("%"PRIu64"\n",sum);
      FILE *fp = fopen("multi_data_2_process.txt","a+");
      fprintf(fp,"%f\n",(float)(sum/iteration) - pipeoverhead*process_no - timeoverhead-process_creation_overhead);
      fclose(fp);
  }
}
  // printf("%"PRIu64"\n",sum);
}


 
