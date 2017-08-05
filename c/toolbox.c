#include <stdio.h>
#include <string.h>

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
