#include <stdio.h>
#include <x86intrin.h>
#include<stdint.h>
#include<inttypes.h>
#include<time.h>
#include<sys/time.h>
#include<unistd.h>
#include</usr/src/linux-headers-3.19.0-33/include/linux/preempt.h>
#include</usr/src/linux-headers-3.19.0-33/include/linux/linkage.h>
//#pragma intrinsic(__rdtsc)
//using namespace std;

static __inline__ uint64_t clockCount (void) {
    unsigned a, d;
    __asm__ __volatile__("rdtsc": "=a" (a), "=d" (d) );
    return (((uint64_t)a) | (((uint64_t)d) << 32));
}

int testFunct(int arg1){
	 __asm__ __volatile(""); 
} 
int main(){
	uint64_t  t2,t3;
	preempt_disable();
	t2= clockCount();
	//sleep(10);
	t3= clockCount();
	printf("%" PRIu64 "clocks",t3-t2);
	//cout<<t3-t2<<"\n";	

}
