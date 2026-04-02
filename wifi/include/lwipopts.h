#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// 1. Fix the "redefinition of struct timeval" error
#include <sys/time.h>
#define LWIP_TIMEVAL_PRIVATE 0

// 2. Networking settings for Bare Metal (No OS)
#define NO_SYS                      1
#define LWIP_RAW                    1
#define LWIP_ARP                    1
#define LWIP_ETHERNET               1
#define LWIP_ICMP                   1
#define LWIP_UDP                    1
#define LWIP_TCP                    1
#define LWIP_DNS                    1
#define LWIP_DHCP                   1
#define LWIP_IPV4                   1

// 3. API Settings - Ensure we don't trigger "Sequential API" errors
#define LWIP_NETCONN                0
#define LWIP_SOCKET                 0

// 4. Memory and Performance
#define MEM_ALIGNMENT               4
#define MEM_SIZE                    4000
#define MEMP_NUM_TCP_PCB            1
#define TCP_MSS                     1460
#define TCP_WND                     (2 * TCP_MSS)
#define TCP_SND_BUF                 (2 * TCP_MSS)
#define PICO_LWIP_MAX_INTERRUPT_PRIORITY 0x20

#endif
