#include <iostream>
#include <stdexcept>

#include <netinet/in.h>
#include <arpa/inet.h>

#include "connection.hpp"
#include "consts.hpp"

class Client {
public:
    Client() : conn(Socket()) {}

    void connectToServer(const std::string_view ip, int port) {
        sockaddr_in addr{};
        addr.sin_family = DOMAIN;
        addr.sin_port = htons(PORT);

        if (inet_pton(DOMAIN, ip.data(), &addr.sin_addr) <= 0) {
            throw std::runtime_error("Invalid host was provided");
        }

        if (connect(conn.getSocket().get(), (sockaddr*)&addr, sizeof(addr)) == -1) {
            throw std::runtime_error("Client connection failed");
        }
    }

    void sendMessage(const std::string& msg) { conn.sendMessage(msg); }
    std::string receiveMessage() { return conn.receiveMessage(); }

private:
    Connection conn;
};

int main() {
    try {
        Client client;
        client.connectToServer(HOST, PORT);
        
        while (true) {
            std::string msg;
            std::cout << "Enter a message to send to the server (or 'quit' to exit): ";
            std::getline(std::cin, msg);
            
            if (msg == "quit") break;

            client.sendMessage(msg);
    
            std::string reply = client.receiveMessage();
            std::cout << reply << "\n"; // response from server
        }
    }
    catch (std::runtime_error& e) {
        std::cerr << "Error while running client: " << e.what() << "\n";
    }

    return 0;
}
