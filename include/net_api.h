#ifndef CRUX_NET_API_H
#define CRUX_NET_API_H

#include "kernel_types.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// The net concern's contract: the one struct of function pointers the net
// driver fills and serves - the byte transport, loopback-first. Every
// operation is TIMED (the deadline argument bounds the driver's blocking
// waits; the contract carries no threads and no poll set). Handles are
// opaque records and NULL is not a handle.
//
// The concern is dispatched through the engine's registry channel: the
// driver's served NetAPI, selected by the concern's stable dispatch id.
// The concern is OPTIONAL:
// net_none serves the empty contract (every verb a graceful failure) and
// registers no concern bit - the consumer's gate is
// Engine_Supports(CRUX_CONCERN_NET).
typedef struct NetAPI {
  PackageVersion version;
  void *(*Listen)(const char *host, uint16_t port, uint16_t *outPort);
  bool (*Connect)(const char *host, uint16_t port, uint64_t timeoutNS, void **outConn);
  void *(*Accept)(void *listener, uint64_t timeoutNS);
  int (*Recv)(void *conn, uint8_t *buf, size_t cap, uint64_t timeoutNS);
  int (*Send)(void *conn, const uint8_t *buf, size_t len);
  void (*Close)(void *handle);
} NetAPI;

#ifdef __cplusplus
}
#endif

#endif
