#ifndef CRUX_STATIC_NET_H
#define CRUX_STATIC_NET_H

#include "kernel_types.h"
#include "net_api.h"

#ifdef __cplusplus
extern "C" {
#endif

// The static rendering of the net contract: plain externs, defined by the
// net driver and linked into the binary. A static consumer pays zero
// indirection and cannot accidentally dispatch.
extern void *Net_Listen(const char *host, uint16_t port, uint16_t *outPort);
extern bool Net_Connect(const char *host, uint16_t port, uint64_t timeoutNS, void **outConn);
extern void *Net_Accept(void *listener, uint64_t timeoutNS);
extern int Net_Recv(void *conn, uint8_t *buf, size_t cap, uint64_t timeoutNS);
extern int Net_Send(void *conn, const uint8_t *buf, size_t len);
extern void Net_Close(void *handle);

#ifdef __cplusplus
}
#endif

#endif
