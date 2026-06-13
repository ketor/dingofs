/* Standalone cache-node binary for the harness / pre-prod functional bring-up.
 * Usage: dfkv_server --dir <path> --port <p|0> --cap <bytes>
 * Prints "PORT <port>" on stdout once listening, then runs until SIGTERM/SIGINT. */
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "kv_node_server.h"

using dingofs::cache::kv::KvNodeServer;
using dingofs::cache::kv::Status;

static volatile sig_atomic_t g_stop = 0;
static void OnSig(int) { g_stop = 1; }

int main(int argc, char** argv) {
  std::string dir = "/tmp/dfkv_node";
  int port = 0;
  unsigned long long cap = 1ull << 30;
  for (int i = 1; i + 1 < argc; i += 2) {
    if (!std::strcmp(argv[i], "--dir")) dir = argv[i + 1];
    else if (!std::strcmp(argv[i], "--port")) port = std::atoi(argv[i + 1]);
    else if (!std::strcmp(argv[i], "--cap")) cap = std::strtoull(argv[i + 1], nullptr, 10);
  }
  std::signal(SIGINT, OnSig);
  std::signal(SIGTERM, OnSig);

  KvNodeServer srv(dir, cap);
  if (srv.Start(port) != Status::kOk) {
    std::fprintf(stderr, "failed to start on port %d\n", port);
    return 1;
  }
  std::printf("PORT %d\n", srv.port());
  std::fflush(stdout);
  while (!g_stop) { struct timespec ts{0, 50 * 1000 * 1000}; nanosleep(&ts, nullptr); }
  srv.Stop();
  return 0;
}
