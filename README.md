# toolbox

I made some tools useful to reduce the time of programing.

## What are tools in this box?

### C

* A library: `toolbox.h`、`toolbox.c`
	* void swap(char \*got\_array, int a, int b)
	* void char\_qsort(char \*got_array, int left, int right)
	* int yes\_or\_no(void)
	* struct key\_char\_head \*init\_key\_char(void)
	* int get\_hash(char \*key)
	* struct key\_char\_node \*get\_key\_char\_node(struct key\_char\_head \*this\_head, char \*key)
	* char \*get\_key\_char\_value(struct key\_char\_head \*this\_head, char \*key)
* Tools: `pcinfo`、`sysinfo`

#### Test
```shell
Start test.
----------------
swap: pass
----------------
char_qsort: pass
----------------
get_hash: pass
----------------
get_hash_with_zero_char: pass
----------------
pass: 4
pass rate: 100.00%
```