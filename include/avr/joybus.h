#ifndef JOYBUS_H
#define JOYBUS_H

#ifdef __cplusplus
extern "C"
{
#endif

void joybus_host_transceive(unsigned char pin,
		void *send_buf, unsigned char send_length,
		void *recv_buf, unsigned char recv_length);
void joybus_client_recv(unsigned char pin,
		void *recv_buf, unsigned char *recv_length);
void joybus_client_send(unsigned char pin,
		void *send_buf, unsigned char send_length);

#ifdef __cplusplus
}
#endif

#endif
