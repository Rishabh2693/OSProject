#include <stdio.h>
#include <x86intrin.h>
#include<pthread.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>

#pragma intrinsic(__rdtsc)

void testfun(){
}

int main(){
	uint64_t sum = 0;
	int i;
	pthread_t threads[1];
		unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
		asm volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
		pthread_create(&threads[0],NULL,testfun,NULL);
		asm volatile("RDTSCP\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t"
		 "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
		"%rax", "%rbx", "%rcx", "%rdx");
	
		uint64_t t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
		uint64_t t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
		sum=sum+(t1-t);
		printf("%"PRIu64"\n",(t1-t));
	printf("%"PRIu64"\n",sum/10);
}
