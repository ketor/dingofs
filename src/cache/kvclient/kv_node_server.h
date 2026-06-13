/* KvNodeServer — a cache-node daemon for the harness: wraps a KVStore and
 * serves Cache/Range/Exist over the TCP wire protocol. The real cache node is
 * dingo-cache (brpc + DiskCache); this proves the semantics end-to-end. */
#ifndef DINGOFS_SRC_CACHE_KVCLIENT_KV_NODE_SERVER_H_
#define DINGOFS_SRC_CACHE_KVCLIENT_KV_NODE_SERVER_H_

#include <atomic>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>

#include "kv_store.h"

namespace dingofs {
namespace cache {
namespace kv {

class KvNodeServer {
 public:
  KvNodeServer(const std::string& cache_dir, uint64_t capacity_bytes);
  ~KvNodeServer();

  Status Start(int port);  // port 0 => ephemeral; query with port()
  void Stop();
  int port() const { return port_; }
  size_t Count() const { return store_.Count(); }
  uint64_t UsedBytes() const { return store_.UsedBytes(); }

 private:
  void AcceptLoop();
  void Handle(int fd);

  KVStore store_;
  int listen_fd_ = -1;
  int port_ = 0;
  std::atomic<bool> running_{false};
  std::thread accept_thread_;
};

}  // namespace kv
}  // namespace cache
}  // namespace dingofs

#endif  // DINGOFS_SRC_CACHE_KVCLIENT_KV_NODE_SERVER_H_
