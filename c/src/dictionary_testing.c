#include <stdio.h>
#include "toolbox.h"
int main(){
	struct key_char_head *char_dict;
	char_dict = init_key_char();
	
	int append_state;
	char *result;
   	printf("Append: key:abc value:def\n");
	append_state = append_key_char(char_dict, "abc", "def");
	printf("state:%d\n",append_state);
	printf("Find the value with this key: adc.\n");
	result = get_key_char_value(char_dict,"abc");
	printf("result:%s\n",result);

   	printf("Append: key:bac value:aaa\n");
   	append_state = append_key_char(char_dict, "bac", "aaa");
	printf("state:%d\n",append_state);
	printf("Find the value with this key: bac.\n");
	result = get_key_char_value(char_dict,"bac");
	printf("result:%s\n", result);
	int delete_state;
	printf("Delete the value with this key: abc.\n");
	delete_state = delete_key_char(char_dict, "abc");
	printf("state:%d\n",delete_state);
	printf("Find the value with this key: bac.\n");
	result = get_key_char_value(char_dict,"bac");
	printf("result:%s\n",result);
	return 0;
}
