#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/select.h>
#include <vector>
#include <string>
#include <fcntl.h>
#include <random>
#include "util.h"
#include "RAT.h"
// response from server, quit, history,
/**
 * Entrypoint to the program.
 *
 * @param argc count of arguments on command line
 * @param argv character array of command line arguments
 *
 * @return exit code of the program
 */



int send_list_files(int tcp_socket) {
    int bytes_sent;
    int random_number = rand();
    struct RATRequest ls_request;
    ls_request.hdr.type = htons(RAT_REQUEST);
    ls_request.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    ls_request.req_type = htons(REQUEST_LIST_FILES);
    ls_request.request_id = htonl(random_number);
    ls_request.argument_length = htons(0);

    bytes_sent = send(tcp_socket, &ls_request, sizeof(struct RATRequest), 0);
    return bytes_sent;
}
int send_PWD_request(int tcp_socket) {
    int bytes_sent;
    int random_number = rand();
    struct RATRequest PWD_request;
    PWD_request.hdr.type = htons(RAT_REQUEST);
    PWD_request.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    PWD_request.req_type = htons(REQUEST_PWD);
    PWD_request.request_id = htonl(random_number);
    PWD_request.argument_length = htons(0);

    bytes_sent = send(tcp_socket, &PWD_request, sizeof(struct RATRequest), 0);
    return bytes_sent;
}
int send_show_history_request(int tcp_socket) {
    int bytes_sent;
    int random_number = rand();
    struct RATRequest show_history_request;
    show_history_request.hdr.type = htons(RAT_REQUEST);
    show_history_request.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    show_history_request.req_type = htons(REQUEST_SHOW_HISTORY);
    show_history_request.request_id = htonl(random_number);
    show_history_request.argument_length = htons(0);

    bytes_sent = send(tcp_socket, &show_history_request, sizeof(struct RATRequest), 0);
    return bytes_sent;
}
int send_change_directory(int tcp_socket, char *data_string) {
    int bytes_sent;
    int random_number = rand();
    static char send_buf[2048];
    int offset = 0;
    struct RATRequest change_directory;
    change_directory.hdr.type = htons(RAT_REQUEST);
    change_directory.hdr.total_msg_size = htons(sizeof(struct RATRequest) + strlen(data_string));
    change_directory.req_type = htons(REQUEST_CHANGE_DIR);
    change_directory.request_id = htonl(random_number);
    change_directory.argument_length = htons(strlen(data_string));


    memcpy(&send_buf[offset], &change_directory, sizeof(struct RATRequest));
    offset += sizeof(struct RATRequest);
    memcpy(&send_buf[offset], data_string, strlen(data_string));
    offset += strlen(data_string);

    bytes_sent = send(tcp_socket, send_buf, offset, 0);
    offset = 0;
    return bytes_sent;
}
int send_execute_command(int tcp_socket, char *data_string) {
    int bytes_sent;
    int random_number = rand();
    static char send_buf[2048];
    int offset = 0;
    struct RATRequest change_directory;
    change_directory.hdr.type = htons(RAT_REQUEST);
    change_directory.hdr.total_msg_size = htons(sizeof(struct RATRequest) + strlen(data_string));
    change_directory.req_type = htons(REQUEST_EXECUTE_COMMAND);
    change_directory.request_id = htonl(random_number);
    change_directory.argument_length = htons(strlen(data_string));


    memcpy(&send_buf[offset], &change_directory, sizeof(struct RATRequest));
    offset += sizeof(struct RATRequest);
    memcpy(&send_buf[offset], data_string, strlen(data_string));
    offset += strlen(data_string);

    bytes_sent = send(tcp_socket, send_buf, offset, 0);
    offset = 0;
    return bytes_sent;
}
int main(int argc, char *argv[]) {
    /* alias for command line argument for ip address */
    char *ip_str;
    /* alias for command line argument for port */
    char *port_str;
    // alias for command line argument string to send to server
    char *data_str;
    /* tcp_socket will be the socket used for sending/receiving */
    int tcp_socket;
    // Port to send TCP data to. Need to convert from command line string to a number
    unsigned int port;
    // Variable for the ipv4 server address
    struct sockaddr_in server_address;
    // Variable for the ipv4 server address length
    socklen_t server_address_len;
    // The type of request specified on the client command line.
    uint16_t request_type;
    /* variable to hold return values from network functions */
    int ret;
    /* buffer to use for receiving data */
    static char recv_buf[DEFAULT_BUF_SIZE];
    //pointer to server response
    struct RATResponse *server_response;
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

    // Note: this needs to be 3, because the program name counts as an argument!
    if (argc < 3) {
        std::cerr << "Please specify HOSTNAME PORT as first two arguments." << std::endl;
        return 1;
    }

    /* assign ip_str to the first command line argument */
    ip_str = argv[1];
    /* assign port_str to the second command line argument */
    port_str = argv[2];
    //data_str = argv[3];

    // 1. Create the socket
    tcp_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Make sure socket was created successfully, or exit.
    if (tcp_socket == -1) {
        std::cerr << "Failed to create tcp socket!" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        return 1;
    }

    /*/ Set the socket to be non blocking
    ret = fcntl(tcp_socket, F_SETFL, O_NONBLOCK);
    if (ret == -1) {
        perror("can’t set O_NONBLOCK using fcntl()");
        exit(EXIT_FAILURE);
    }*/

    // 2. Connect the socket to the server.
    // First need to look up a suitable address for the server
    // (may need to do a DNS lookup first!)

    // hints are things we want the returned address to match
    struct addrinfo hints;
    // results is where our list of addresses will be stored
    struct addrinfo *results;
    // results_it is just a pointer to iterate over the list in results
    struct addrinfo *results_it;
    // set hints to all zeroes, these are the "defaults" for the values
    memset(&hints, 0, sizeof(struct addrinfo));
    // Specify we want only ipv4 addresses
    hints.ai_family = AF_INET;
    // Specify that we want a TCP capable address
    hints.ai_socktype = SOCK_STREAM;
    // There are other members of hints that we don't need right now. man getaddrvinfo for details!

    // getaddrinfo will take our hostname, port number and hints, and return a list of compatible addresses
    // these addresses (in results) will be of the correct type for bind or connect.
    ret = getaddrinfo(ip_str, port_str, &hints, &results);

    if (ret != 0) {
        handle_error("getaddrinfo");
        return -1;
    }

    // results_it is an "interator" element for our results
    // results is a list of addresses that match our specifications
    results_it = results;
    ret = -1;
    int std_in_fd = 0;

    while (results_it != NULL) {
        std::cout << "Attempting to CONNECT to " <<
                  get_network_address(results_it->ai_addr, results_it->ai_addrlen) << std::endl;

        // Actually connect to the server!
        ret = connect(tcp_socket, results_it->ai_addr, results_it->ai_addrlen);
        if (ret == 0) // Success
        {
            break;
        }
        ret = -1;
        handle_error("connect");
        // ai_next points to the next element in the linked list of results.
        // if NULL, it means we have reached the end
        results_it = results_it->ai_next;

    }
    bool quit = false;
    while (quit == false){
        // Empty out the read set (for incoming data on socket)
        FD_ZERO(&read_set);
        // Empty out the write set (for outgoing data on socket)
        FD_ZERO(&write_set);
        // Empty out the except set (for errors/exceptions on socket)
        FD_ZERO(&except_set);

        // Set fd 0 (stdin) for checking if data has been entered
        FD_SET(std_in_fd, &read_set);
        max_fds = std_in_fd + 1;

        FD_SET(1, &write_set);
        max_fds = 1 + 1;

        if ((ret = select(max_fds + 1, &read_set, &write_set, &except_set, &tv)) == -1) {
            perror("select");
            break;
        }

        // Nothing ready to receive on select!
        if (ret == 0) {
            std::cout << "No file descriptors ready in select!" << std::endl;
            continue;
        }

        //std::cout << ret << " file descriptors ready to do something!" << std::endl;
        if (FD_ISSET(std_in_fd, &read_set)) {
            std::cout << "Ready to read on standard in!" << std::endl;
            //save command entered from terminal into recv buffer
            ret = read(std_in_fd, recv_buf, DEFAULT_BUF_SIZE - 1);

            std::cout << "Read " << ret << " bytes on standard in!" << std::endl;
            recv_buf[ret] = '\0';
            std::cout << "Read " << recv_buf << " from standard in" << std::endl;
            //save message returned from server into recv buffer

            if(strncmp("quit", recv_buf, 4) == 0){
               std::cerr << "Client is quitting" << "\n";
               return 0;
            }else if (strncmp("ls", recv_buf, 2) == 0) {
                request_type = REQUEST_LIST_FILES;
                ret = send_list_files(tcp_socket);
            }else if (strncmp("cd", recv_buf, 2) == 0) {
                request_type = REQUEST_CHANGE_DIR;
                data_str = &recv_buf[3];
                ret = send_change_directory(tcp_socket, data_str);
                if (data_str == NULL) {
                    std::cerr << "This command requires an argument." << std::endl;
                    return 1;
                }
            }else if (strncmp("pwd", recv_buf, 3) == 0) {
                request_type = REQUEST_PWD;
                ret = send_PWD_request(tcp_socket);
            }else if (strncmp("run", recv_buf, 3) == 0) {
                request_type = REQUEST_EXECUTE_COMMAND;
                data_str = &recv_buf[4];
                ret = send_execute_command(tcp_socket, data_str);
                if (data_str == NULL) {
                    std::cerr << "This command requires an argument." << std::endl;
                    return 1;
                }
            }else if (strncmp("history", recv_buf, 7) == 0) {
                request_type = REQUEST_SHOW_HISTORY;
                ret = send_show_history_request(tcp_socket);
            }else {
                std::cerr << "Unknown command " << recv_buf << std::endl;
                std::cerr << "Please enter a valid command, one of ls, cd, pwd, run, history, quit. " << std::endl;
                return 1;
            }
            ret = recv(tcp_socket, recv_buf, DEFAULT_BUF_SIZE, 0);
            std::cout << "Received " << ret << " bytes of data." << std::endl;
            recv_buf[ret] = '\0';
            int bytes_processed = 0;
            //while (bytes_processed < ret) {
            // Convenience variable for making code easier to read
            int bytes_left = ret - bytes_processed;
            if (bytes_left >= sizeof(struct RATResponse)) {
                // If so, point server_response to the location in the recv_buf
                server_response = (struct RATResponse *)&recv_buf[bytes_processed];
                // Convert numerical data from network to host byte order
                server_response->response_type = ntohs(server_response->response_type);
                server_response->hdr.total_msg_size = ntohs(server_response->hdr.total_msg_size);
                server_response->data_length = ntohs(server_response->data_length);
                server_response->request_id = ntohs(server_response->request_id);
                //check request id
                std::cout << "Received Response " << server_response->response_type << " Length "
                          << server_response->hdr.total_msg_size << std::endl;
                // data_length should be the size of  + whatever data follows. Make sure bytes_left
                // is at *least* that large. Otherwise we'll overflow our buffer (probably a malformed message!)
                std::cout << "Bytes left before" << bytes_left << std::endl;//2048
                std::cout << "total length" << server_response->hdr.total_msg_size << std::endl;//2945
                if (bytes_left >= server_response->hdr.total_msg_size) {
                    int string_len = server_response->hdr.total_msg_size - sizeof(struct RATResponse);
                    char *temp_client_string = (char *)malloc(string_len + 1);
                    std::cout << "Bytes left after" << bytes_left << std::endl;
                    memcpy(temp_client_string, &server_response[1], string_len);
                    temp_client_string[string_len] = '\0';
                    std::cout << "Message string from server was: " << temp_client_string << std::endl;
                    bytes_processed += server_response->hdr.total_msg_size;
                } else
                    bytes_processed += sizeof(struct RATResponse);
            } else {
                std::cout << "Have " << bytes_left << " bytes, but too small to be a correctly formatted message. Ignoring!" << std::endl;
                // This ensures we don't have an infinite loop when receiving (potentially) too small messages.
                bytes_processed += bytes_left;
            }
            //}
        }

        // This check is to see if this FD is in the write-ready set
        if (FD_ISSET(1, &write_set)) {
            //std::cout << "Ready to write to socket fd " << tcp_clients[i]->sock_fd << std::endl;
        }

        // This check is to see if this FD is in the exception set
        if (FD_ISSET(std_in_fd, &except_set)) {
            std::cout << "Got an exception on socket fd " << std_in_fd << std::endl;
        }

    }

    // Whatever happened, we need to free the address list.
    freeaddrinfo(results);

    if (ret == -1) {
        handle_error("connect failed");
        return -1;
    }

    // If we get here, it means that we are successfully connected to a server somewhere! Yay!!!
    // That means we can send just by using the socket, as it's already connected.

    ret = send(tcp_socket, recv_buf, strlen(recv_buf), 0);
    std::cout << "sent " << ret << " bytes to server" << std::endl;


    // If we expect a result from the server, this is where we would get it.
    //create function to put in while loop for receiving back from server
    ret = recv(tcp_socket, recv_buf, DEFAULT_BUF_SIZE, 0);


    if (ret <= 0) {
        handle_error("recv");
        close(tcp_socket);
        return 1;
    }

    // Original server code, just print out the raw bytes received.
    std::cout << "Received " << ret << " bytes of data." << std::endl;
    recv_buf[ret] = '\0';
    std::cout << "Data received was `" << recv_buf << "'" << std::endl;

    close(tcp_socket);
    return 0;
}
