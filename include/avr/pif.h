#ifndef PIF_H
#define PIF_H
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

void pif_host_transmit(uint8_t pin,
                       void *send_buf, uint8_t send_length,
                       void *recv_buf, uint8_t recv_length);
void pif_client_recv(uint8_t pin, void *recv_buf, uint8_t *recv_length);
void pif_client_send(uint8_t pin, void *send_buf, uint8_t send_length);

#ifdef __cplusplus
}
#endif

#endif
