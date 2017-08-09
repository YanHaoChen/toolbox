#include <unistd.h>
#include <stdio.h>
int main(){
	int value;
	
	value = sysconf(_SC_CLK_TCK);
	printf("CLOCK_TICKS_PER_SEC: %d \n", value);
	
	value = sysconf(_SC_NPROCESSORS_CONF);
	printf("PROCESSORS         : %d \n", value);
	
	value = sysconf(_SC_NPROCESSORS_ONLN);
	printf("PROCESSORS(ONLINE) : %d \n", value);
	
	long long int page_size = sysconf(_SC_PAGESIZE);
	long long int page_num = sysconf(_SC_PHYS_PAGES);
	long long int mb = 1024 * 1024;	
	printf("MEMORY_SIZE        : %lld MB \n", page_size * page_num / mb);	

}
