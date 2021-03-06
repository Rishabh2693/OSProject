#include <stdio.h>
#include <x86intrin.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#pragma intrinsic(__rdtsc)

int main()
{
	uint64_t sum = 0;
	int iteration,j;
	uint64_t t1,t;
	float timeoverhead = 101.0372002;
	for(iteration=0;iteration<1000;iteration++)
	{
		//////////////////////////////////////////////////////////
		unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
		asm volatile ("CPUID\n\t"
 		"RDTSC\n\t"
 		"mov %%edx, %0\n\t"
 		"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
		//////////////////////////////////////////////////////////
		
		for(j=0;j<100;j++)
		{
		}	
		///////////////////////////////////////////////////////////
		asm volatile("RDTSCP\n\t"
 		"mov %%edx, %0\n\t"
 		"mov %%eax, %1\n\t"
 		"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
		"%rax", "%rbx", "%rcx", "%rdx");
		// ////////////////////////////////////////////////////////
		
		t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
		t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
		sum=sum+(t1-t);
		// printf("%"PRIu64"\n",(t1-t));
	}
	FILE *f;
	f = fopen("loopoverhead.txt", "a+");	
	fprintf(f,"%f\n",((float)sum-(iteration*timeoverhead))/(j*iteration));
	fclose(f);
}
