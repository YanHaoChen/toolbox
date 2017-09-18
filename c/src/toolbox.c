#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>


struct key_char_node{
	struct key_char_node *next;
	char *key;
	char *value;
};

#define HASH_SIZE 20

struct key_char_head{
	struct key_char_node hash_list[HASH_SIZE];
};

struct key_char_head *init_key_char(){
	struct key_char_head *creating_head;
	creating_head = (struct key_char_head*)malloc(sizeof(struct key_char_head));
	for(int i=0;i < HASH_SIZE;i++){
		struct key_char_node *this_node;
		this_node = &(creating_head->hash_list[i]);
		this_node->next = NULL;
		this_node->key = NULL;
		this_node->value = NULL;
	}
	return creating_head;
}

int get_hash(char *key){
	int count = 0;
	
	for(;*key != '\0'; ++key){
		count += *key;
	}
	return count % HASH_SIZE;
}

struct key_char_node *get_key_char_node(struct key_char_head *this_head, char *key){
	int hash_num;
	hash_num = get_hash(key);
	struct key_char_node *this_node;
	this_node = &(this_head->hash_list[hash_num]);
	
	if(this_node->key == NULL){
		return this_node;
	}
	
	while(strcmp(this_node->key,key) != 0){
		if(this_node->next != NULL){
			this_node = this_node->next;
		}else{
			return this_node;
		}
	}
	return this_node;
}

char *get_key_char_value(struct key_char_head *this_head, char *key){
	struct key_char_node *this_node;
	this_node = get_key_char_node(this_head, key);
	if(this_node->key == NULL)
		return NULL;	
		
	if(strcmp(this_node->key, key) == 0){
		return this_node->value;
	}else{
		return NULL;
	}
}

int append_key_char(struct key_char_head *this_head, char *key, char *value){
	struct key_char_node *this_node;
	this_node = get_key_char_node(this_head, key);
	if (this_node->key == NULL){
		this_node->key = key;
		this_node->value = value;
		return 1;
	}
	if(strcmp(this_node->key, key) != 0){
		struct key_char_node *new_node;
		new_node = (struct key_char_node*)malloc(sizeof(struct key_char_node));
		new_node->next = NULL;
		new_node->key = key;
		new_node->value = value;
		this_node->next = new_node;
		return 2;
	}else{
		this_node->value = value;
		return 3;
	}
}

void swap(char got_array[], int a, int b){
	if(got_array[a] != got_array[b]){
		got_array[a] = got_array[a] ^ got_array[b];
		got_array[b] = got_array[a] ^ got_array[b];
		got_array[a] = got_array[a] ^ got_array[b];
	}
}

void char_qsort(char got_array[], int left,int right){
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
	int get_flags = fcntl(desc, F_GETFL, 0);
	if(get_flags == -1)
		return -1;

	if(value != 0)
		get_flags |= O_NONBLOCK;
	else
		get_flags &= O_NONBLOCK;

	return fcntl(desc, F_SETFL, get_flags);	
}
