#ifndef CONSTS_HPP
#define CONSTS_HPP

#include <string_view>

#include <netinet/in.h>
#include <sys/socket.h>

// default config vars
constexpr std::string_view HOST = "127.0.0.1";
constexpr int PORT = 8081;
constexpr int LISTEN_BACKLOG = 100;

constexpr in_addr_t BIND_ADDRESS = INADDR_ANY;
constexpr int DOMAIN = AF_INET;
constexpr int TYPE = SOCK_STREAM;
constexpr int PROTOCOL = IPPROTO_TCP;

#endif
