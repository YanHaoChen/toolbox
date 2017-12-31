# toolbox

I made some tools useful to reduce the time of programing.

## What are tools in this box?

### C

* `toolbox.h`,`toolbox.c`
  * void swap(char \*got\_array, int a, int b)
  * void char\_qsort(char \*got_array, int left, int right)
  * int yes\_or\_no(void)
  * struct key\_char\_head \*init\_key\_char(void)
  * int get\_hash(char \*key)
  * struct key\_char\_node \*get\_key\_char\_node(struct key\_char\_head \*this\_head, char \*key)
  * char \*get\_key\_char\_value(struct key\_char\_head \*this\_head, char \*key)
  * int delete\_key\_char(struct key\_char\_head \*this\_head, char \*key)
* [`packetg.h`,`packetg.c`](https://github.com/YanHaoChen/packetg)

* Tools：`pcinfo`,`sysinfo`、`swap`

#### Testing

[toolbox_testing.c](https://github.com/YanHaoChen/toolbox/blob/master/c/src/toolbox/toolbox_testing.c)

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

Dictionary testing：[dictionary_testing.c](https://github.com/YanHaoChen/toolbox/blob/master/c/src/toolbox/dictionary_testing.c)

```shell
Append: key:abc value:def
state:1
Find the value with this key: adc.
result:def
Append: key:bac value:aaa
state:2
Find the value with this key: bac.
result:aaa
Delete the value with this key: abc.
state:1
Find the value with this key: bac.
result:aaa
```
