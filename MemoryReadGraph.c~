#include <stdio.h>
#include <x86intrin.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>

#pragma intrinsic(__rdtsc)

int main(){
	int j=0;
	int timeOverhead = 108;
	int loopOverhead = 20;
	for(j=1; j <256000000; j=j*2)
	{
		uint64_t sum = 0;
		int *a = (int *) malloc(j*sizeof(int)); 
		memset(a, 0, sizeof(a));
		int i;
		uint64_t t1,t;
		int k;
		for(k = 0;k<30; k++){
			unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
			asm volatile ("CPUID\n\t"
 			"RDTSC\n\t"
 			"mov %%edx, %0\n\t"
 			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
			"%rax", "%rbx", "%rcx", "%rdx");
				for(i=0;i<j;i=i+1024){
				int tmp = a[i];	
				}
			asm volatile("RDTSCP\n\t"
 			"mov %%edx, %0\n\t"
 			"mov %%eax, %1\n\t"
 			"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
			"%rax", "%rbx", "%rcx", "%rdx");

			t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
			t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
			if(k!=0)
				sum=sum+((t1-t)-(123+(((j/1024)+1))));
		}


		printf("%"PRIu64"  %d %d\n",sum/((k-1)*((j/1024)+1)),sum,j);

	}
}
