//
// Created by Briana on 11/3/2021.
//

#ifndef SIMPLE_UDP_2021_UTIL_H
#define SIMPLE_UDP_2021_UTIL_H

#define DEFAULT_BUF_SIZE 2048
#define MAX_CMD_BUFFER 1450
/***
 * Generic error handler. Just a shortcut. Prints out the strerror from errno,
 * along with whatever the context provided was.
 * @param context a printable char * string with any context of where the error occurred
 */
void handle_error(const char *context);

/***
 * Get a string representation (IP:PORT) of a sockaddr_in or sockaddr_in6 address.
 * This function is not re-entrant!
 *
 * @param address pointer to valid memory for a sockaddr_in or sockaddr_in6
 * @param addr_len length of address structure
 * @return pointer to string representation of address (safe to print, but not re-entrant)
 */
const char *get_network_address(struct sockaddr *address, socklen_t addr_len);

/***
 * Execute a command (using popen) and get the output.
 * Non-reentrant, as it uses a static buffer for the command output! If you change it to
 * callee allocated, caller freed that would make it "better", but slightly less performant.
 *
 * @param cmd the command to execute (may include arguments)
 * @param return_buffer modified by callee (this function!) to point to location of command result data
 * @return number of valid bytes in return_buffer
 */
int execute_command_get_response(const char *cmd, const char **return_buffer) {
    FILE *file_pointer;
    // max size for the command buffer
    static char cmd_buf[MAX_CMD_BUFFER];
    int bytes_read;

    // Execute a command in a shell, then get a file handle to the result data.
    // Be very careful with this, it's easy for someone to do something nasty!
    file_pointer = popen(cmd, "r");
    if (file_pointer == NULL) {
        handle_error("popen");
        std::cerr << "Failed to execute command: " << cmd << std::endl;
        (*return_buffer) = NULL;
        return 0;
    }

    // Read the output from the command into our buffer. If it's too big, truncate it.
    bytes_read = fread(cmd_buf, 1, MAX_CMD_BUFFER, file_pointer);

    if (bytes_read <= 0) {
        std::cerr << "Failed to read any bytes from command pipe? ret was " << bytes_read << std::endl;
        handle_error("fgets");
        (*return_buffer) = NULL;
        return 0;
    }

    std::cout << "Read " << bytes_read << " bytes of output from command " << cmd << std::endl;
    std::cout << "Read data was: " << cmd_buf << std::endl;
    cmd_buf[bytes_read] = '\0';
    (*return_buffer) = cmd_buf;
    // Close it, using pclose since we used popen!
    pclose(file_pointer);
    return bytes_read;
}


#endif //SIMPLE_UDP_2021_UTIL_H
