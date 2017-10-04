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
#include <netinet/udp.h>

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


unsigned short cal_checksum(unsigned short *buf, int header_size){
        unsigned long sum;
        // This unit includes 2 bytes.  
        header_size /= 2;
        for(sum=0; header_size>0; header_size--){
            sum += *buf++;
        }
        while((sum >> 16) > 0){
            sum = (sum >> 16) + (sum & 0x0000ffff);
        }
        return (unsigned short)(~sum);
}

unsigned short cal_udp_checksum(unsigned short *presudo_header , unsigned short *buf, int header_size){
    unsigned long sum = 0;
    
    int i = 0;
    for(i = 6; i > 0; i--){
        sum += *presudo_header++;
    }
    // This unit includes 2 bytes.
    header_size /= 2;
    for(; header_size>0; header_size--){
        sum += *buf++;
    }
    while((sum >> 16) > 0){
        sum = (sum >> 16) + (sum & 0x0000ffff);
    }
    
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

struct sockaddr_ll set_interface_and_get_binding_addr(int sockfd, char *interface_name , struct mac_addr *addr){
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
    return sizeof(struct ether_header);
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
    l3_header->ip_len = 0;
    inet_aton(addr->src_addr, &l3_header->ip_src);
	inet_aton(addr->dst_addr, &l3_header->ip_dst);
    return sizeof(struct ip);  
}

int push_udp_field(char *packet, unsigned short int src_port, unsigned short int dst_port){
    struct udphdr *udp_header = (struct udphdr*)(packet+L2_LENGTH+L3_LENGTH);
    udp_header->uh_sport = htons(src_port);
    udp_header->uh_dport = htons(dst_port);
    udp_header->uh_ulen = 0;
    udp_header->uh_sum = 0;
    return sizeof(struct udphdr);
}


int send_packet(struct packet_seed *seed){
    if (sendto(seed->generator, seed->packet, seed->len, 0, (struct sockaddr*)&seed->binding, sizeof(struct sockaddr_ll)) < 0){
        return 0;
    } else {
        return 1;
    }
}

int package_l3_packet(struct packet_seed *seed){
    struct ip *l3_header = (struct ip *)(seed->packet + L2_LENGTH);
    l3_header->ip_len = seed->len - L2_LENGTH;
    l3_header->ip_sum = cal_checksum((unsigned short *)l3_header, L3_LENGTH);
}

int package_udp_packet_without_checksum(struct packet_seed *seed){
    struct ip *l3_header = (struct ip *)(seed->packet + L2_LENGTH);
    l3_header->ip_len = seed->len - L2_LENGTH;
    l3_header->ip_sum = cal_checksum((unsigned short *)l3_header, L3_LENGTH);
    
    struct udphdr *udp_header = (struct udphdr *)(seed->packet + L2_LENGTH + L3_LENGTH);
    int udp_len = seed->len - L2_LENGTH - L3_LENGTH;
    udp_header->uh_ulen = (unsigned short)udp_len;
}

int package_udp_packet_with_checksum(struct packet_seed *seed){
    struct ip *l3_header = (struct ip *)(seed->packet + L2_LENGTH);
    l3_header->ip_len = seed->len - L2_LENGTH;
    l3_header->ip_sum = cal_checksum((unsigned short *)l3_header, L3_LENGTH);
    
    struct udphdr *udp_header = (struct udphdr *)(seed->packet + L2_LENGTH + L3_LENGTH);
    int udp_len = seed->len - L2_LENGTH - L3_LENGTH;
    udp_header->uh_ulen = (unsigned short)udp_len;
    unsigned long presudo_header[3];
    memset(presudo_header, 0, 12);
    unsigned long tmp = 0;
    //presudo header
    presudo_header[0]= (unsigned long)(l3_header->ip_src.s_addr);
    presudo_header[1]= (unsigned long)(l3_header->ip_dst.s_addr);
    tmp |= udp_len;
    tmp |= 0x00110000;
    presudo_header[2] = tmp;
    udp_header->uh_sum=cal_udp_checksum((unsigned short *)presudo_header, (unsigned short *)udp_header, udp_len);
}