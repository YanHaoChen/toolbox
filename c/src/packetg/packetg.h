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

struct packet_seed{
    int generator;
    char *packet;
    int len;
    struct sockaddr_ll binding;
};

unsigned short cal_checksum(unsigned short *buf, int header_size);
int init_packet_generator(void);    
struct sockaddr_ll set_interface_and_get_binding_addr(int sockfd, char *interface_name , struct mac_addr *addr);
int push_l2_field(char *packet, struct mac_addr *addr);
int push_l3_field(char *packet, struct ip_addr *addr, int protocol);
int push_udp_field(char *packet, unsigned short int src_port, unsigned short int dst_port);

int send_l2_packet(struct packet_seed *seed);
    