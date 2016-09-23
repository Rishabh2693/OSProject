#include <stdio.h>
#include <x86intrin.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>

#pragma intrinsic(__rdtsc)


void testFunct(int a,int b,int c,int d,int e,int f){
	 __asm__ __volatile(""); 
} 

int main(){
	uint64_t sum = 0;
	int i;
	for(i=0;i<10;i++){
		unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
		asm volatile ("CPUID\n\t"
		 "RDTSC\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
		"%rax", "%rbx", "%rcx", "%rdx");
		testFunct(1,2,3,4,5,6);
		asm volatile("RDTSCP\n\t"
		 "mov %%edx, %0\n\t"
		 "mov %%eax, %1\n\t"
		 "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
		"%rax", "%rbx", "%rcx", "%rdx");
	
		uint64_t t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
		uint64_t t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
		sum=sum+(t1-t);
		printf("%"PRIu64"\n",(t1-t));
	}
	printf("%"PRIu64"\n",sum/10);
}
