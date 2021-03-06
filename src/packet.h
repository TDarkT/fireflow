#ifndef PACKET_HEADER
#define PACKET_HEADER
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

// simplified packet struct for lightweight save into memory
class packet {

public:
    static int internalPacketCounter;
    packet():
        sample_ratio(1),
        src_ip(0), dst_ip(0),
        src_port(0), dst_port(0),
        protocol(0), ip_protocol_version(4),
        ttl(0), length(0), flags(0),
        ip_fragmented(false),
        packet_payload_pointer(NULL), packet_payload_length(0){ internalPacketCounter++; }

    uint32_t        sample_ratio;

    /* Contains IP (using IPv4 for now) */
    uint32_t        src_ip;                 /* Host IP */
    uint32_t        dst_ip;                 /* Destination IP */

    uint32_t        input_interface  = 0;   /* Input interface */
    uint32_t        output_interface = 0;   /* Output interface */

    uint16_t        src_port;               /* Source port */
    uint16_t        dst_port;               /* Destination port */

    unsigned int    protocol;               /* TCP or UDP */
    uint8_t         ip_protocol_version;    /* IPv4 or IPv6 */

    uint8_t         ttl;                    /* Time to live */
    uint64_t        length;                 /* Packet length */
    uint8_t         flags;                  /* TCP flags */

    bool            ip_fragmented;          /* If IP packet fragmented */

    struct timeval  ts;                     /* ... */

    void*           packet_payload_pointer;
    uint32_t        packet_payload_length;
    uint32_t        packet_payload_full_length = 0; // In case of cropped packets we use this

    int64_t         flow_start = 0;         /* Device uptime when flow started */
    int64_t         flow_end   = 0;         /* Device uptime when flow fnishes */

};

typedef void (*packet_process_ptr)(packet&);
#endif
