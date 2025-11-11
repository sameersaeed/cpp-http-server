#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <string>

// default config vars
constexpr std::string HOST = "127.0.0.1";
constexpr int PORT = 8081;
constexpr int LISTEN_BACKLOG = 100;

constexpr in_addr_t BIND_ADDRESS = INADDR_ANY;
constexpr int DOMAIN = AF_INET;
constexpr int TYPE = SOCK_STREAM;
constexpr int PROTOCOL = IPPROTO_TCP;

#endif
