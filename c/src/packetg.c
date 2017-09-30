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

unsigned short calculate_csum(unsigned short *packet, int header_size){
	unsigned long sum;
	for(sum=0;header_size>0;header_size--)
		sum += *packet++;

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return (unsigned short)(~sum);
};

int init_packet_generator(char *interface_name){
    int sockfd;
    
    if((sockfd = socket(AF_PACKET, SOCK_RAW, IPPROTO_RAW)) == -1){
        perror("Establish socket: error\n");
        return -1;
    }
    
    return sockfd;
}

struct sockaddr_ll set_interface_and_push_l2_field(int sockfd, char *packet, char *interface_name , struct mac_addr *addr){
    struct ifreq if_id;
    struct sockaddr_ll bind_addr;   
    memset(&if_id, 0, sizeof(struct ifreq));
	strncpy(if_id.ifr_name, interface_name, IFNAMSIZ-1);
	if (ioctl(sockfd, SIOCGIFINDEX, &if_id) < 0){
        perror("Setting interface: error\n");
    }
    struct ether_header *l2_header = (struct ether_header *)packet;
    l2_header->ether_type = htons(ETH_P_IP);
    int i; 
    for(i=0 ;i<6 ;i++ ){
        (l2_header->ether_shost)[i] = (addr->src_addr)[i];
        (l2_header->ether_dhost)[i] = (addr->dst_addr)[i];
        (bind_addr.sll_addr)[i] = (addr->dst_addr)[i];
    }
    bind_addr.sll_ifindex = if_id.ifr_ifindex;
    bind_addr.sll_halen = ETH_ALEN;
    return bind_addr;
}
