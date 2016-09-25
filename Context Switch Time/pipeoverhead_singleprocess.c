#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <string.h>

#pragma intrinsic(__rdtsc)

char *phrase = "That";


int main()
{
  int fd[2], n;
  char buf[100]; /* Parent process message buffer */
  uint64_t sum = 0;
  int i;
  pipe ( fd );
  // for(i=0;i<1;i++)
  
    unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
    int iteration;
    float timeoverhead = 101.03;
    sum=0;
    ////////////////////////////////////////////////////
      asm volatile ("CPUID\n\t"
     "RDTSC\n\t"
     "mov %%edx, %0\n\t"
     "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
     "%rax", "%rbx", "%rcx", "%rdx");
     ///////////////////////////////////////////////////////
    for(iteration = 0 ; iteration < 2000; iteration ++)
     { 
       write (fd[1], phrase, strlen ( phrase) +1); /* include NULL*/
       n = read(fd[0], buf, 1024);
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
      FILE *fp = fopen("pipeoverhead.txt","a+");
      fprintf(fp,"%f\n",(float)(sum)/iteration - timeoverhead);
      fclose(fp);
  }



 
