/**
 * In-class demonstrated UDP client example.
 */

#include <iostream>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <random>
#include "RAT.h"
#include "util.h"

/***
 * Send a list files request to a UDP RAT server.
 *
 * @param socket the socket to send data on (UDP)
 * @param server_address the server destination address
 * @return the number of bytes sent, or -1 on error.
 */


std::random_device rd;
std::mt19937 prng{rd()};
std::uniform_int_distribution<int> dist(1, 1000);
int random_number;


int send_list_files(int socket, const struct sockaddr *server_address) {
    int bytes_sent;

    struct RATRequest ls_request;
    ls_request.hdr.type = htons(RAT_REQUEST);
    ls_request.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    ls_request.req_type = htons(REQUEST_LIST_FILES);
    ls_request.request_id = htonl(random_number);
    ls_request.argument_length = htons(0);

    bytes_sent = sendto(socket, &ls_request, sizeof(struct RATRequest), 0, server_address, sizeof(struct sockaddr_in));
    return bytes_sent;
}


void handle_error(const char *context) {
    std::cerr << context << " failed with error:" << std::endl;
    std::cerr << strerror(errno) << std::endl;
    return;
}

/**
 *
 * UDP RAT client. Parses a request from the command line, then sends to the server.
 * Awaits response from server after request is sent.
 *
 * e.g., ./rat_udpclient 127.0.0.1 8888 ls
 *       ./rat_udpclient 127.0.0.1 8888 cd /root/
 *
 * @param argc count of arguments on the command line
 * @param argv array of command line arguments
 * @return 0 on success, non-zero if an error occurred
 */
int send_PWD_request(int socket, const struct sockaddr *server_address) {
    int bytes_sent;

    struct RATRequest PWD_request;
    PWD_request.hdr.type = htons(RAT_REQUEST);
    PWD_request.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    PWD_request.req_type = htons(REQUEST_PWD);
    PWD_request.request_id = htonl(random_number);
    PWD_request.argument_length = htons(0);

    bytes_sent = sendto(socket, &PWD_request, sizeof(struct RATRequest), 0, server_address, sizeof(struct sockaddr_in));
    return bytes_sent;
}

int send_change_directory(int socket, const struct sockaddr *server_address) { //add arg string
    int bytes_sent;

    int offset = 0;
    struct RATRequest change_directory;
    change_directory.hdr.type = htons(RAT_REQUEST);
    change_directory.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    change_directory.req_type = htons(REQUEST_PWD);
    change_directory.request_id = htonl(random_number);
    change_directory.argument_length = htons(0);


    memcpy(&send_buf[offset], &change_directory, sizeof(struct RATRequest));
    offset += sizeof(struct RATRequest);
    memcpy(&send_buf[offset], data_string, strlen(data_string));
    offset += strlen(data_string);
//send_buff decl. data_string?
    bytes_sent = sendto(socket, send_buf, offset, 0, server_address,
                        sizeof(struct sockaddr_in));
    return bytes_sent;
}

int send_execute_command(int socket, const struct sockaddr *server_address) {
    int bytes_sent;

    struct RATRequest execute_command;
    execute_command.hdr.type = htons(RAT_REQUEST);
    execute_command.hdr.total_msg_size = htons(sizeof(struct RATRequest));
    execute_command.req_type = htons(REQUEST_PWD);
    execute_command.request_id = htonl(random_number);
    execute_command.argument_length = htons(0);
//send TCP sendto UDP
    bytes_sent = sendto(socket, &execute_command, sizeof(struct RATRequest), 0, server_address,
                        sizeof(struct sockaddr_in));
    return bytes_sent;
}

int main(int argc, char *argv[]) {

    // Alias for argv[1] for convenience
    char *ip_string;

    // Alias for argv[2] for convenience
    char *port_string;

    // Alias for argv[3] for convenience
    char *command_string;

    // Alias for argv[4] for convenience
    char *arg_string;

    // Port to send UDP data to. Need to convert from command line string to a number
    unsigned int port;

    // The socket used to send UDP data on
    int udp_socket;

    // Variable used to check return codes from various functions
    int ret;

    // Buffer for sending data
    char send_buf[2048];

    // Current offset into send_buf
    int offset = 0;

    //Memory location to hold incoming data sent from the server
    static char recv_buf[2048];

    // IPv4 structure representing and IP address and port of the destination
    struct sockaddr_in dest_addr;

    // Binary address structure of the server
    struct sockaddr_in recv_addr;

    // Size of the address we received data from (it could be ipv4 or ipv6, which have different sizes)
    socklen_t recv_addr_size;

    // The type of request specified on the client command line.
    uint16_t request_type;

    // 2. A game message
    struct RATRequest something_differnt;

    //struct GameMessage *game_message;
    //int msg_size = sizeof(struct GameMessage) + strlen(arg_string);
    //game_message = (struct GameMessage *) (malloc(msg_size));

    // Set dest_addr to all zeroes, just to make sure it's not filled with junk
    // Note we could also make it a static variable, which will be zeroed before execution
    memset(&dest_addr, 0, sizeof(struct sockaddr_in));

    // Note: this needs to be at least 4, program name counts as an argument!
    if (argc < 4) {
        std::cerr << "Please specify IP PORT COMMAND [ARGUMENT] as arguments." << std::endl;
        return 1;
    }
    // Set up variables "aliases"
    ip_string = argv[1];
    port_string = argv[2];
    command_string = argv[3];
    if (argc == 5) {
        arg_string = argv[4];
    } else {
        arg_string = NULL;
    }

    // Parse out the command given to the client.
    if (strncmp("ls", command_string, 2) == 0) {
        request_type = REQUEST_LIST_FILES;
    } else if (strncmp("cd", command_string, 2) == 0) {
        request_type = REQUEST_CHANGE_DIR;
        if (arg_string == NULL) {
            std::cerr << "This command requires an argument." << std::endl;
            return 1;
        }
    } else if (strncmp("pwd", command_string, 3) == 0) {
        request_type = REQUEST_PWD;
    } else if (strncmp("run", command_string, 3) == 0) {
        request_type = REQUEST_EXECUTE_COMMAND;
        if (arg_string == NULL) {
            std::cerr << "This command requires an argument." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown command " << command_string << std::endl;
        std::cerr << "Please enter a valid command, one of ls, cd, pwd, run. " << std::endl;
        return 1;
    }

    // Step 1: Create the UDP socket.
    // AF_INET is the address family used for IPv4 addresses
    // SOCK_DGRAM indicates creation of a UDP socket
    udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    // Make sure socket was created successfully, or exit.
    if (udp_socket == -1) {
        std::cerr << "Failed to create udp socket!" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        return 1;
    }

    // inet_pton converts an ip address string (e.g., 1.2.3.4) into the 4 byte
    // equivalent required for using the address in code.
    // Note that because dest_addr is a sockaddr_in (IPv4) the 'sin_addr'
    // member of the struct is used for the IP
    ret = inet_pton(AF_INET, ip_string, (void *) &dest_addr.sin_addr);

    // Check whether the specified IP was parsed properly. If not, exit.
    if (ret == -1) {
        std::cerr << "Failed to parse IPv4 address!" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        close(udp_socket);
        return 1;
    }

    // Convert the port string into an unsigned integer.
    ret = sscanf(port_string, "%u", &port);
    // sscanf is called with one argument to convert, so the result should be 1
    // If not, exit.
    if (ret != 1) {
        std::cerr << "Failed to parse port!" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        close(udp_socket);
        return 1;
    }

    // Set the address family to AF_INET (IPv4)
    dest_addr.sin_family = AF_INET;
    // Set the destination port. Use htons (host to network short)
    // to ensure that the port is in big endian format
    dest_addr.sin_port = htons(port);

    std::cout << "Will send to server at address "
              << get_network_address((sockaddr * ) & dest_addr, sizeof(struct sockaddr_in)) << std::endl;

    // Send the correct message based on the request type.
    switch (request_type) {
        case REQUEST_LIST_FILES:
            ret = send_list_files(udp_socket, (struct sockaddr *) &dest_addr);
            break;
        case REQUEST_EXECUTE_COMMAND:
            ret = send_execute_command(udp_socket, (struct sockaddr *) &dest_addr);
            break;
        case REQUEST_CHANGE_DIR:
            ret = send_change_directory(udp_socket, (struct sockaddr *) &dest_addr);
            break;
        case REQUEST_PWD:
            ret = send_PWD_request(udp_socket, (struct sockaddr *) &dest_addr);
            break;
        default:
            std::cerr << "Unknown request type?" << std::endl;
            return 1;
            break;
    }

    // Check if send worked, clean up and exit if not.
    if (ret == -1) {
        std::cerr << "Failed to send data!" << std::endl;
        std::cerr << strerror(errno) << std::endl;
        close(udp_socket);
        return 1;
    }

    std::cout << "Sent " << ret << " bytes out." << std::endl;

    /**
     * Code to receive response from the server goes here!
     * recv or recvfrom...
     */
    // Before receiving, set the allowed size of an incoming address. Since our recv_addr is a
    // sockaddr_in, we need to set it to the sizeof(struct sockaddr_in)
    recv_addr_size = sizeof(struct sockaddr_in);
    // Receive data from Server
    ret = recvfrom(udp_socket, recv_buf, 2047, 0, (struct sockaddr *) &recv_addr, &recv_addr_size);

    if (ret == -1) {
        handle_error("recvfrom");
        close(udp_socket);
        return 1;
    }

    std::cout << "Received " << ret << " bytes from address size " << recv_addr_size << std::endl;
    recv_buf[ret] = '\0';
    std::cout << "Received '" << recv_buf << "'" << std::endl;

    //I didn't see this until 10:00 the night it was due because I was looking at a file with the same name
    //I had downloaded earlier. I couldn't figure out why it wasn't helping until I finally got this one

  while (bytes_processed < ret) {
    // Convenience variable for making code easier to read
    int bytes_left = ret - bytes_processed;
    // Check whether the remaining bytes we have to process are big enough to be a GameMessage
    if (bytes_left >= sizeof(struct GameMessage)) {
      // If so, point client_game_message to the location in the recv_buf
      client_game_message = (struct GameMessage *)&recv_buf[bytes_processed];
      // Convert numerical data from network to host byte order
      client_game_message->type = ntohs(client_game_message->type);
      client_game_message->msg_len = ntohs(client_game_message->msg_len);
      std::cout << "Received game message type " << client_game_message->type << " Length "
                << client_game_message->msg_len << std::endl;
      // msg_len should be the size of GameMessage + whatever data follows. Make sure bytes_left
      // is at *least* that large. Otherwise we'll overflow our buffer (probably a malformed message!)
      if (bytes_left >= client_game_message->msg_len) {
        int string_len = client_game_message->msg_len - sizeof(struct GameMessage);
        char *temp_client_string = (char *)malloc(string_len + 1);
        memcpy(temp_client_string, &client_game_message[1], string_len);
        //memcpy(temp_client_string, &recv_buf[sizeof(struct GameMessage)], client_game_message->msg_len - sizeof(struct GameMessage));
        temp_client_string[string_len] = '\0';
        std::cout << "Message string from client was: " << temp_client_string << std::endl;
        bytes_processed += client_game_message->msg_len;
      } else
        bytes_processed += sizeof(struct GameMessage);
    } else {
      std::cout << "Have " << bytes_left << " bytes, but too small to be a correctly formatted message. Ignoring!" << std::endl;
      // This ensures we don't have an infinite loop when receiving (potentially) too small messages.
      bytes_processed += bytes_left;
    }
  }


    close(udp_socket);
    return 0;
}