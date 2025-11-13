#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <sys/socket.h>

#include "socket.hpp"

class Connection {
private:
    Socket socket;
public:
    Connection(Socket s) : socket(std::move(s)) {}

    Socket& getSocket() { return socket; }

    void sendMessage(const std::string_view message) {
        ssize_t n = send(socket.get(), message.data(), message.length(), 0); 
        if (n == -1) throw std::runtime_error("Failed to send message");
    }
    
    std::string receiveMessage(size_t maxLength=1024) {
        char buffer[1024] = {};
        ssize_t n = recv(socket.get(), buffer, maxLength - 1, 0);
        
        if (n < 0) throw std::runtime_error("Failed to receive message");
        if (n == 0) return ""; // close connection

        return std::string(buffer, n);
    }
};

#endif
