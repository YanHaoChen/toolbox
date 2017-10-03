# toolbox

I made some tools useful to reduce the time of programing.

## What are tools in this box?

### C

* `toolbox.h`、`toolbox.c`
	* void swap(char \*got\_array, int a, int b)
	* void char\_qsort(char \*got_array, int left, int right)
	* int yes\_or\_no(void)
	* struct key\_char\_head \*init\_key\_char(void)
	* int get\_hash(char \*key)
	* struct key\_char\_node \*get\_key\_char\_node(struct key\_char\_head \*this\_head, char \*key)
	* char \*get\_key\_char\_value(struct key\_char\_head \*this\_head, char \*key)
	* int delete\_key\_char(struct key\_char\_head \*this\_head, char \*key)
* `packetg.h`、`packetg.c`
	* unsigned short cal\_checksum(unsigned short \*buf, int header\_size)
	* int init\_packet\_generator(void);    
	* struct sockaddr\_ll set\_interface\_and\_get\_binding\_addr(int sockfd, char \*interface\_name , struct mac\_addr \*addr);
	* int push\_l2\_field(char \*packet, struct mac_addr \*addr);
	* int push\_l3\_field(char \*packet, struct ip_addr \*addr, int protocol);
 
* Tools：`pcinfo`、`sysinfo`

#### Packet Generator（packetg）

> For Linux

Follow those steps, and you will know how to use this tool!

##### step 1

Include this header(packetg.h).

```c
#include "packetg.h"
```
##### step 2
Prepare some variables for sending L3 packet.

```c
	// Store socket descriptor.
	int generator;
	struct mac_addr *l2_addr;
	struct ip_addr *l3_addr;
	// Initialize the packet which will be sent.
	char packet[1024];
	memset(packet, 0, 1024);
   
   // Full in fields of L2
   l2_addr = (struct mac_addr*)malloc(sizeof(struct mac_addr));
   (l2_addr->src_addr)[0] = 0x00;
   (l2_addr->src_addr)[1] = 0x00;
   (l2_addr->src_addr)[2] = 0x00;
   (l2_addr->src_addr)[3] = 0x00;
   (l2_addr->src_addr)[4] = 0x00;
   (l2_addr->src_addr)[5] = 0x01;
   (l2_addr->dst_addr)[0] = 0x00;
   (l2_addr->dst_addr)[1] = 0x00;
   (l2_addr->dst_addr)[2] = 0x00;
   (l2_addr->dst_addr)[3] = 0x00;
   (l2_addr->dst_addr)[4] = 0x00;
   (l2_addr->dst_addr)[5] = 0x02;
   
   // Full in fields of L3
   l3_addr = (struct ip_addr*)malloc(sizeof(struct ip_addr));
   l3_addr->src_addr = "10.0.0.1";
   l3_addr->dst_addr = "10.0.0.2";
```


##### step 3
Initialize the socket of generator.

```c
	generator = init_packet_generator();
```

##### step 4
Select the interface you want to use, and get this binding struct(`sockaddr_ll`) which will be used when you send a packet to internet on this interface.

```c
	struct sockaddr_ll this_sockaddr;
	this_sockaddr = set_interface_and_get_binding_addr(generator, "eth0", l2_addr);
```
##### step 5
Push L2 and L3 fields into this packet.

```c
	int header_size = 0;
	header_size += push_l2_field(packet, l2_addr);
	header_size += push_l3_field(packet, l3_addr, 17);
```

> "17" means UDP.

##### step 6
Send this packet!

```c
	if (sendto(generator, packet, header_size, 0, (struct sockaddr*)&this_sockaddr, sizeof(struct sockaddr_ll)) < 0)
		printf("send: error\n");
```

[Example code](https://github.com/YanHaoChen/toolbox/blob/master/c/src/packetg/packetg_testing.c)

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