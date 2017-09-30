#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>


#define L2_LENGTH 14
#define L3_LENGTH 20

struct mac_addr{
    unsigned char src_addr[6];
    unsigned char dst_addr[6];
};
unsigned short calculate_csum(unsigned short *packet, int header_size);    
int init_packet_generator(char *interface_name);    
struct sockaddr_ll set_interface_and_push_l2_field(int sockfd, char *packet, char *interface_name , struct mac_addr *addr);
