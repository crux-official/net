#ifndef CRUX_DYNAMIC_NET_H
#define CRUX_DYNAMIC_NET_H

#include "kernel_types.h"
#include "net_api.h"
#include "engine.h"
#include "kernel_types.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// The dynamic rendering of the net contract: every call dispatches through
// the engine's registry channel - the net driver's served NetAPI, selected
// by the concern's stable dispatch id (DRIVER_NET, platform_types.h).
static inline void *Net_Listen(const char *host, uint16_t port, uint16_t *outPort) {
  return ((NetAPI *)crux_engine_api->GetExtensionAPI(DRIVER_NET))->Listen(host, port, outPort);
}
static inline bool Net_Connect(const char *host, uint16_t port, uint64_t timeoutNS, void **outConn) {
  return ((NetAPI *)crux_engine_api->GetExtensionAPI(DRIVER_NET))->Connect(host, port, timeoutNS, outConn);
}
static inline void *Net_Accept(void *listener, uint64_t timeoutNS) {
  return ((NetAPI *)crux_engine_api->GetExtensionAPI(DRIVER_NET))->Accept(listener, timeoutNS);
}
static inline int Net_Recv(void *conn, uint8_t *buf, size_t cap, uint64_t timeoutNS) {
  return ((NetAPI *)crux_engine_api->GetExtensionAPI(DRIVER_NET))->Recv(conn, buf, cap, timeoutNS);
}
static inline int Net_Send(void *conn, const uint8_t *buf, size_t len) {
  return ((NetAPI *)crux_engine_api->GetExtensionAPI(DRIVER_NET))->Send(conn, buf, len);
}
static inline void Net_Close(void *handle) {
  ((NetAPI *)crux_engine_api->GetExtensionAPI(DRIVER_NET))->Close(handle);
}

#ifdef __cplusplus
}
#endif

#endif
