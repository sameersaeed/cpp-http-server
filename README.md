# HTTP Server

### A simple HTTP server, created to learn more about C socket programming as well as some C++ language features


## Building
1. First create a `build/` directory from the project root and build the server + client executables:
```bash
mkdir build

g++ -std=c++20 -O2 src/server.cpp -o build/server
g++ -std=c++20 -O2 src/client.cpp -o build/client
```
2. Then, while still on the project root, open two separate terminal windows
4. On the first window, run the server binary:
```bash
./build/server
```

3. Then run the client binary on the second window:
```bash
./build/client
```

Once both binaries are running, you can send messages between the client and server
