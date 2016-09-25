#include <stdio.h>
#include <x86intrin.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include<math.h>

#pragma intrinsic(__rdtsc)

int main(){
	int j=0;
	int times = 1000;
	int timeOverhead = 108;
	int loopOverhead = 20;
	int stride = 1024;
	// 1024 Corresponds to 4K in memory as size of int is 4
	int str[10]={512,1024,2048,4096,8192,16384,32768,65536,131072,262144};
	int l;	
	for( l = 0; l<10 ; l++)
	for(j=1; j <256000000; j=j*2)
	{
		uint64_t sum = 0;
		int *a = (int *) malloc(j*sizeof(int)); 
		int i,index;
		a[0] = 0;
   		 for (i = 0; i < j; i++) {
       			 index = i + str[l];
       			 if (index >= j) {
       			     index %= j;
       			 }
       			 a[i] = index;
    		}	
		
		uint64_t t1,t;
		int k;
		for(k = 0;k<30; k++){
			int temp = 0;
			unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
			asm volatile ("CPUID\n\t"
 			"RDTSC\n\t"
 			"mov %%edx, %0\n\t"
 			"mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
			"%rax", "%rbx", "%rcx", "%rdx");
				for(i=0;i<1000;i++){
				  temp = a[temp];	
				}
			asm volatile("RDTSCP\n\t"
 			"mov %%edx, %0\n\t"
 			"mov %%eax, %1\n\t"
 			"CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
			"%rax", "%rbx", "%rcx", "%rdx");

			t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
			t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
			if(k!=0)
				sum=sum+((t1-t)-(108));
		}


		printf("%"PRIu64"  %d %d\n",sum/((k-1)*(1000)),sum,j);

	}
		printf("Next Stride\n");
}
