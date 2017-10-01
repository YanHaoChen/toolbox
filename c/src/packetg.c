#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/ip.h>

struct mac_addr{
    unsigned char src_addr[6];
    unsigned char dst_addr[6];
};
struct ip_addr{
    char *src_addr;
    char *dst_addr;
};
unsigned short calculate_csum(unsigned short *buf, int header_size)
        unsigned long sum;
        // This unit is 2 bytes.  
        header_size /= 2;
        for(sum=0; header_size>0; header_size--)
                sum += *buf++;
        sum = (sum >> 16) + (sum & 0x0000ffff);
        return (unsigned short)(~sum);
}

int init_packet_generator(void){
    int sockfd;
    
    if((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1){
        perror("Establish socket: error\n");
        return -1;
    }
    
    return sockfd;
}

struct sockaddr_ll set_interface_and_get_bind_addr(int sockfd, char *interface_name , struct mac_addr *addr){
    struct ifreq if_id;
    struct sockaddr_ll bind_addr;   
    memset(&if_id, 0, sizeof(struct ifreq));
	strncpy(if_id.ifr_name, interface_name, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_id) < 0){
        perror("Setting interface: error\n");
    }
    int i; 
    for(i=0 ;i<6 ;i++ ){
        (bind_addr.sll_addr)[i] = (addr->dst_addr)[i];
    }
    bind_addr.sll_ifindex = if_id.ifr_ifindex;
    bind_addr.sll_halen = ETH_ALEN;
    return bind_addr;
}

int push_l2_field(char *packet, struct mac_addr *addr){
    struct ether_header *l2_header = (struct ether_header *)packet;
    l2_header->ether_type = htons(ETH_P_IP);
    int i; 
    for(i=0 ;i<6 ;i++){
        (l2_header->ether_shost)[i] = (addr->src_addr)[i];
        (l2_header->ether_dhost)[i] = (addr->dst_addr)[i];
    }
    return 1;
}

int push_l3_field(char *packet, struct ip_addr *addr, int protocol){
    struct ip *l3_header = (struct ip *)(packet + sizeof(struct ether_header));
    int header_size = 0;
    header_size = sizeof(l3_header);
    l3_header->ip_hl = 5;
    l3_header->ip_v = 4;
    l3_header->ip_tos = 0;
    l3_header->ip_id = htons(rand());
    l3_header->ip_ttl = 255;
    l3_header->ip_p = protocol;
    l3_header->ip_len = header_size;
    inet_aton(addr->src_addr, &l3_header->ip_src);
	inet_aton(addr->dst_addr, &l3_header->ip_dst);
    
    l3_header->ip_sum = csum((unsigned short *)l3_header, header_size);
    return 1;   
}