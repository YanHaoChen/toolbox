#include <stdio.h>
#include <string.h>
#include <ctype.h>

void swap(char *got_array, int a, int b){
	if(got_array[a] != got_array[b]){
		got_array[a] = got_array[a] ^ got_array[b];
		got_array[b] = got_array[a] ^ got_array[b];
		got_array[a] = got_array[a] ^ got_array[b];
	}
}

void char_qsort(char *got_array, int left,int right){
	if(left < right){
		int pivot = left;
		for(int i = left+1;i <= right; i++){
			if(strcmp(&got_array[left], &got_array[i]) > 0){
				swap(got_array, ++pivot, i);
			}
		}
		swap(got_array, left, pivot);
		char_qsort(got_array, left, pivot-1);
		char_qsort(got_array, pivot+1, right);
	}
}

#define YES_OR_NO_MAX_LEN 4

int yes_or_no(void){
	char ans[YES_OR_NO_MAX_LEN];
	
	while(1){
		printf("Type Y(YES) or N(NO):");
		fgets(ans, YES_OR_NO_MAX_LEN, stdin);
		for(int i= 0;i < YES_OR_NO_MAX_LEN;++i) ans[i] = tolower(ans[i]);
		if(strcmp(ans,"y\n") == 0 || strcmp(ans, "yes") == 0)
			return 1;
		if(strcmp(ans,"n\n") == 0 || strcmp(ans, "no") == 0)
			return 0;
	}
}

int set_nonblock_flag(int desc, int value){
	int get_flags = fcntl(desc, F_FETFL, 0);
	if(get_flags == -1)
		return -1;

	if(value != 0)
		get_flags |= O_NONBLOCK;
	else
		get_flags &= O_NONBLOCK;

	return fcntl(desc, F_SETFL, get_flags);	
}
