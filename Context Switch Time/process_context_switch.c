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
    int iteration;
    ////////////////////////////////////////////////////
      asm volatile ("CPUID\n\t"
     "RDTSC\n\t"
     "mov %%edx, %0\n\t"
     "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
     "%rax", "%rbx", "%rcx", "%rdx");
     ///////////////////////////////////////////////////////
     // for(iteration =0 ; iteration < 20; iteration ++)
     { 
      sum=0;
      if ( fork ( ) == 0 )
      {
       /* Child Writer */
       close (fd[0]); /* Close unused end*/
       write (fd[1], phrase, strlen ( phrase) +1); /* include NULL*/
       close (fd[1]); /* Close used end*/
       // int wt = wait(NULL); 
        // printf("Child:  Wrote '%s' to pipe!\n", phrase);
      } 
      else
      {
        int wt = wait(NULL);
        close (fd[1]); /* Close unused end*/
        bytesRead = read ( fd[0], message, 100);
        /* Parent Reader */
        // printf ( "Parent: Read %d bytes from pipe: %s\n", bytesRead, message);
        close ( fd[0]); /* Close used end */

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
      FILE *fp = fopen("data.txt","a+");
      fprintf(fp,"%d\n",(int)(sum));
      fclose(fp);
      }     
     }
  }
  // printf("%"PRIu64"\n",sum);
}


 
