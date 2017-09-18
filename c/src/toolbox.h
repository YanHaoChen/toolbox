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

struct key_char_head *init_key_char(void);
int get_hash(char *key);
struct key_char_node *get_key_char_node(struct key_char_head *this_head, char *key);
char *get_key_char_value(struct key_char_head *this_head, char *key);
int append_key_char(struct key_char_head *this_head, char *key, char *value);
