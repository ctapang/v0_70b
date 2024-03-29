#ifndef _IPERF_CONFIG_H_
#define _IPERF_CONFIG_H_


#define IPERF_SERVER_PORT (5001)
#define IPERF_TCP_LOCAL_PORT_START_NUMBER     (1024u)

#define IPERF_TX_BUFFER_SIZE            4096    // default size of the iperf TX buffer
#define IPERF_RX_BUFFER_SIZE            4096    // default size of the iperf RX buffer
                                                // bigger buffers will help obtain higher performance numbers
                                                // adjust as needed

#define IPERF_TX_WAIT_TMO               200     // timeout to wait for TX channel to be ready to transmit a new packet; ms
                                                // depends on the channel bandwidth


#define IPERF_TX_QUEUE_LIMIT              2     // for iperf UDP client, the limit to set to avoit memory allocation
                                                // overflow on slow conenctions
#endif /* __IPERFAPP_H__ */

