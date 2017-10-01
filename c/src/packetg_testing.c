#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "packetg.h"

int main(){
    int generator;
    struct mac_addr *l2_addr;
    struct ip_addr *l3_addr;
    char packet[1024];
    memset(packet, 0, 1024);
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

    l3_addr = (struct ip_addr*)malloc(sizeof(struct ip_addr));
    l3_addr->src_addr = "10.0.0.1";
    l3_addr->dst_addr = "10.0.0.2";
    
    generator = init_packet_generator();
    struct sockaddr_ll this_sockaddr;
    this_sockaddr = set_interface_and_get_bind_addr(generator, "eth0", l2_addr);
    push_l2_field(packet, l2_addr);
    push_l3_field(packet, l3_addr, 17);
    int header_size;
    header_size = L2_LENGTH + L3_LENGTH;
    // packet[header_size++] = 't';
    // packet[header_size++] = 'e';
    // packet[header_size++] = 's';
    // packet[header_size++] = 't';
    
    if (sendto(generator, packet, header_size, 0, (struct sockaddr*)&this_sockaddr, sizeof(struct sockaddr_ll)) < 0)
        printf("send: error\n");
    return 0;
}
