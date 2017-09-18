#include <stdio.h>
#include "toolbox.h"
//struct key_char_node{
//    struct key_char_node *next;
//    char *key;
//    char *value;
//};
//#define HASH_SIZE 20
//struct key_char_head{
//     struct key_char_node hash_list[HASH_SIZE];
//};
int main(){
	struct key_char_head *char_dict;
	char_dict = init_key_char();
	
	int append_state;
   	append_state = append_key_char(char_dict, "abc", "def");
	
	char *result;
	result = get_key_char_value(char_dict,"abc");

	printf("state:%d\nresult:%s\n",append_state, result);
	return 0;
}
