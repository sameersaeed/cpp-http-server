#include <iostream>
#include <stdexcept>

#include <sys/socket.h>
#include <netinet/in.h>   
#include <unistd.h>

#include "consts.hpp"
#include "socket.hpp"
#include "connection.hpp"

class Server {
public:
    // bind and listen on server socket
    Server(int port, int bindAddress=BIND_ADDRESS, int domain=DOMAIN, int type=TYPE, int protocol=PROTOCOL) 
        : bindAddress(bindAddress), domain(domain), type(type), protocol(protocol),
        socket(domain, type, protocol) 
    {
        sockaddr_in addr{};

        addr.sin_family = domain;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = bindAddress;
    
        if (bind(socket.get(), (sockaddr*)&addr, sizeof(addr)) == -1) {
            throw std::runtime_error("Bind failed on server");
        }

        if (listen(socket.get(), LISTEN_BACKLOG) == -1) {
            throw std::runtime_error("Listen failed on server");
        }

        std::cout << "Started server on port: " << port << "\n";
    }
    
    // accept clients on server socket
    Connection acceptClient() {
        sockaddr_in clientAddr{};
        socklen_t clientAddrSize = sizeof(clientAddr);
        
        int clientFd = accept(socket.get(), (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientFd == -1) throw std::runtime_error("Accept client connection failed on server");

        return Connection(Socket::acceptFd(clientFd));
    }

private:
    Socket socket;

    int domain;
    int type;
    int protocol;
    int port;

    in_addr_t bindAddress;
};

int main() {
    try {
        Server server(PORT);
        Connection client = server.acceptClient();

        while (true) {
            std::string msg = client.receiveMessage();
            if (msg.empty()) break;

            std::cout << "Server received message: \"" << msg << "\"\n";
            client.sendMessage("[SERVER]: Received message from client: " + msg);
        }
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error while running server: " << e.what() << "\n"; 
    }

    return 0;
}
