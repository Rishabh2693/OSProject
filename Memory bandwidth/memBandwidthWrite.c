#include <stdio.h>
#include <x86intrin.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include<math.h>

#pragma intrinsic(__rdtsc)
// Doing for a 8M memory and copying it to a different place
int main(){
uint64_t sum = 0;
int i;
uint64_t t1,t;
int *a = (int *)malloc(2097152 * sizeof(int));
memset(a,6,2097152);
for(i=0;i<2097152;i=i+1024){


	unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
	asm volatile ("CPUID\n\t"
 "RDTSC\n\t"
 "mov %%edx, %0\n\t"
 "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
"%rax", "%rbx", "%rcx", "%rdx");
int j;
for(j=i;j<i+1024;j=j+8)
{
a[j] = 10;
a[j+1] = 10;
a[j+2] = 10;
a[j+3] = 10;
a[j+4] = 10;
a[j+5] = 10;
a[j+6] = 10;
a[j+7] = 10;
}
asm volatile("RDTSCP\n\t"
 "mov %%edx, %0\n\t"
 "mov %%eax, %1\n\t"
 "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
"%rax", "%rbx", "%rcx", "%rdx");
	//cout<<cycles_high<<"\n"<<cycles_low<<"\n"<<cycles_high1<<"\n"<<cycles_low1<<"\n";
	
t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
sum=sum+(t1-t);
printf("%"PRIu64"\n",(t1-t));
}
//printf("%f\n",(8.0/((float)sum*(1.0/2500000000))));
FILE *fp = fopen("mem_write_bw.txt","a+");
     		fprintf(fp,"%f\n",8.0/((float)sum*(1.0/2500000000)));
      		fclose(fp);

}
