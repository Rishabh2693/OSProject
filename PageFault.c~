#include <stdio.h>
#include <x86intrin.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#define O_LARGEFILE 0
#pragma intrinsic(__rdtsc)

int main(){
FILE * file;

   file = fopen ("abc.pdf", "r+");
if(file){
	printf("Open of file failed\n");
	return 0;
}
uint64_t offset = 8388608;
uint64_t SIZE = 1073741824;
char* map =(char*) mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);
uint64_t sum = 0;
int i;
uint64_t t1,t;
	unsigned cycles_high,cycles_low,cycles_high1,cycles_low1;
	asm volatile ("CPUID\n\t"
 "RDTSC\n\t"
 "mov %%edx, %0\n\t"
 "mov %%eax, %1\n\t": "=r" (cycles_high), "=r" (cycles_low)::
"%rax", "%rbx", "%rcx", "%rdx");
int j;
char c;
for(j=0;j<100;j++)
{
	c = map[(((i+1) * offset) % (SIZE - 1))]; 
}
asm volatile("RDTSCP\n\t"
 "mov %%edx, %0\n\t"
 "mov %%eax, %1\n\t"
 "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
"%rax", "%rbx", "%rcx", "%rdx");
	//cout<<cycles_high<<"\n"<<cycles_low<<"\n"<<cycles_high1<<"\n"<<cycles_low1<<"\n";
	
t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
sum=(t1-t);

printf("%"PRIu64"\n",sum/(100));
munmap(map,SIZE);
fclose(file);
}
