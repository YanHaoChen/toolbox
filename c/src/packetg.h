#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>


#define L2_LENGTH 14
#define L3_LENGTH 20

struct mac_addr{
    unsigned char src_addr[6];
    unsigned char dst_addr[6];
};
struct ip_addr{
    char *src_addr;
    char *dst_addr;
};
unsigned short calculate_csum(unsigned short *packet, int header_size);    
int init_packet_generator(void);    
struct sockaddr_ll set_interface_and_get_bind_addr(int sockfd, char *interface_name , struct mac_addr *addr);
int push_l2_field(char *packet, struct mac_addr *addr);
int push_l3_field(char *packet, struct ip_addr *addr, int protocol);    