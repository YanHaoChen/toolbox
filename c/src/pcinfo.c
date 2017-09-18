#include <sys/utsname.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	struct utsname uts;

	if(uname(&uts) < 0)
		perror("Could not get host information.");
	printf("Hardware: %s \n", uts.machine);
	printf("Nodename: %s \n", uts.nodename);
	printf("System: %s \n", uts.sysname);
	printf("Release: %s \n", uts.release);
	printf("Version: %s \n", uts.version);
}
