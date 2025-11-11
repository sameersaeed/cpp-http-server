#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <stdexcept>

#include <cstring>
#include <unistd.h>

#include "consts.hpp"

class Socket {
private:
    int fd;

    int m_domain;
    int m_type;
    int m_protocol;
public:
    Socket(int m_domain=DOMAIN, int m_type=TYPE, int m_protocol=PROTOCOL) { 
        fd = socket(m_domain, m_type, m_protocol);
        if (fd == -1) { throw std::runtime_error(std::string("Socket creation failed due to \"") + strerror(errno) + "\""); }
    }
    
    // create new socket at runtime for acceptClient() from server, just takes file descriptor (fd) for now
    static Socket acceptFd(int clientFd) {
        Socket s;

        s.fd = clientFd;
        s.m_domain = DOMAIN;
        s.m_type = TYPE;
        s.m_protocol = PROTOCOL;

        return s;
    }

    // close socket on delete
    ~Socket() { if (fd != -1) close(fd); }

    // prevent copy
    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    // allow move
    Socket(Socket&& other) noexcept : fd(other.fd) { other.fd = -1; }
    Socket& operator=(Socket&& other) noexcept {
        if (this != &other) {           // if diff connections, 
            if (fd != -1) close(fd);    // close current then transfer ownership to other 
            fd = other.fd;              
            other.fd = -1;              // close other connection as its no longer being used
        }
        return *this;
    }

    int get() const { return fd; }
    
    int setDomain(int newDomain) { return m_domain = newDomain; } 
    int setType(int newType) { return m_type = newType; }
    int setProtocol(int newProtocol) { return m_protocol = newProtocol; }
};

#endif
