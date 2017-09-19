#include <stdio.h>

#include "toolbox.h"

#include <string.h>

int test_count = 0;

int test_swap();
int test_char_qsort();
int test_get_hash();
int test_get_hash_with_zero_char();

int main(){
	int pass_count = 0;	
	printf("Start test.\n");
	printf("----------------\n");
	pass_count += test_swap();	
	printf("----------------\n");
	pass_count += test_char_qsort();	
	printf("----------------\n");
	pass_count += test_get_hash();
	printf("----------------\n");
	pass_count += test_get_hash_with_zero_char();
	printf("----------------\n");
	printf("pass: %d\n", pass_count);
	printf("pass rate: %.2f", ((float)pass_count / (float)test_count) * 100);
	return 0;
}

int test_swap(){
	test_count++;
	char test_array[5] = "abcd\0";
	char result_array[5] = "\0bcda";
	swap(test_array, 0, 4);
	if(strcmp(test_array, result_array) == 0){
		printf("swap: pass\n");
		return 1;
	} else {
		printf("swap: failed\n");
		return 0;
	}
}

int test_char_qsort(){
	test_count++;
	char test_array[5] = "dcba\0";
	char result_array[5] = "\0abcd";
	char_qsort(test_array, 0, 4);
	if(strcmp(test_array, result_array) == 0){
		printf("char_qsort: pass\n");
		return 1;
	} else {
		printf("char_qsort: failed\n");
		return 0;
	}
}

int test_get_hash(){
	test_count++;
	int test_hash = 0;
	int result_hash = 0;
	
	test_hash = get_hash("0123");
	result_hash = (48 + 49 + 50 + 51) % HASH_SIZE;
	if(test_hash == result_hash){
		printf("get_hash: pass\n");
		return 1;
	}else{
		printf("get_hash: failed\n");
		return 0;
	}
}

int test_get_hash_with_zero_char(){
	test_count++;
	int test_hash = 0;
	int result_hash = -1;
	
	test_hash = get_hash("");
	if(test_hash == result_hash){
		printf("get_hash_with_zero_char: pass\n");
		return 1;
	}else{
		printf("get_hash_witch_zero_char: failed\n");
		return 0;
	}
}
