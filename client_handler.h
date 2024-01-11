
class ClientHandler{

    public:
        ClientHandler(int client_socket);
        void start();
    private:
        // client socket
        int socket_fd;
};
