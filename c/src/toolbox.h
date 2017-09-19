enum boolean{
	NO = 0,
	FALSE = 0,
	YES = 1,
	TRUE = 1
};

struct key_char_node{
	struct key_char_node *next;
	char *key;
	char *value;
};
#define HASH_SIZE 20
struct key_char_head{
	struct key_char_node hash_list[HASH_SIZE];
};

void swap(char got_array[], int a, int b);
void char_qsort(char got_array[], int left, int right);
int yes_or_no(void);
int set_nonblock_flag(int desc, int value);

// dict
struct key_char_head *init_key_char(void);

// get_hash
// return -1: length of string < 1
int get_hash(char *key);
struct key_char_node *get_key_char_node(struct key_char_head *this_head, char *key);
char *get_key_char_value(struct key_char_head *this_head, char *key);

// append_key_char
// return 1: This key_char is frist node in this hash_number.
// return 2: This key_char was appended behind someone key_char_node.
// retunn 3: This key's value was Override by the new value.
int append_key_char(struct key_char_head *this_head, char *key, char *value);
// delete_key_char
// return 0: This key was not found in this dictionary.
// return 1: This key was deleted.
int delete_key_char(struct key_char_head *this_head, char *key);
