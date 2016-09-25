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
int fileDes = open("abc.pdf", O_RDWR);
    if (fileDes < 0) {
        printf("Open failed\n");
        return -1;
    }
    unsigned int offset = 16777216; 
    unsigned int FILESIZE = 209715200; 
    char* map =(char*) mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fileDes, 0);
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
	c = map[(((i+1) * offset) % (FILESIZE - 1))]; 
}
asm volatile("RDTSCP\n\t"
 "mov %%edx, %0\n\t"
 "mov %%eax, %1\n\t"
 "CPUID\n\t": "=r" (cycles_high1), "=r" (cycles_low1)::
"%rax", "%rbx", "%rcx", "%rdx");
t1 =  ((uint64_t)cycles_low1) | (((uint64_t)cycles_high1)<<32);
t =  ((uint64_t)cycles_low) | (((uint64_t)cycles_high)<<32);
sum=(t1-t);

printf("%f\n",(float)(sum/(100)));
munmap(map,FILESIZE);
 close(fileDes);
}
