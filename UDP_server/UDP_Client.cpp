//
// Created by Briana on 10/1/2021.
//

#include <iostream>
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

/**
 *
 * Dead simple UDP client example. Reads in IP PORT DATA
 * from the command line, and sends DATA via UDP to IP:PORT.
 *
 * e.g., ./udpclient 127.0.0.1 8888 this_is_some_data_to_send
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

    // Alias for argv[3] for convenience
    char *data_string;

    // Port to send UDP data to. Need to convert from command line string to a number
    unsigned int port;

    // The socket used to send UDP data on
    int udp_socket;

    // Variable used to check return codes from various functions
    int ret;

    // Memory location to hold incoming data sent from the client
    static char recv_buf[2048];

    // IPv4 structure representing and IP address and port of the destination
    struct sockaddr_in dest_addr;

    struct sockaddr_in recv_addr;
    socklen_t recv_addr_size;


    // Set dest_addr to all zeroes, just to make sure it's not filled with junk
    // Note we could also make it a static variable, which will be zeroed before execution
    memset(&dest_addr, 0, sizeof(struct sockaddr_in));

    // Note: this needs to be 4, because the program name counts as an argument!
    if (argc < 4) {
        std::cerr << "Please specify IP PORT DATA as first three arguments." << std::endl;
        return 1;
    }
    // Set up variables "aliases"
    ip_string = argv[1];
    port_string = argv[2];
    data_string = argv[3];

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
    ret = inet_pton(AF_INET, ip_string, (void *)&dest_addr.sin_addr);

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

    // Step 2: Send the data to the destination.
    // Note 1: we are sending strlen(data_string) + 1 to include the null terminator
    // Note 2: we are casting dest_addr to a struct sockaddr because sendto uses the size
    //         and family to determine what type of address it is.
    // Note 3: the return value of sendto is the number of bytes sent
    ret = sendto(udp_socket, data_string, strlen(data_string) + 1, 0,
                 (struct sockaddr *)&dest_addr, sizeof(struct sockaddr_in));

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

    if (ret == -1) {
        handle_error("recvfrom");
        close(udp_socket);
        return 1;
    }

    std::cout << "Received " << ret << " bytes from address size " << recv_addr_size << std::endl;
    recv_buf[ret] = '\0';
    std::cout << "Received '" << recv_buf << "'" << std::endl;
/*
 * while (bytes_processed < ret) {
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
 */


    close(udp_socket);
    return 0;
