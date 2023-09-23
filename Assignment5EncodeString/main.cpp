#include <iostream>
#include <string>


std::string encode_string(std::string message, std::string payload);

void test_encode_string();

int main() {
    test_encode_string();
    return 0;
}

std::string encode_string(std::string message, std::string payload) {
//encode_string(message, payload)
    std::string ret;
    int start = 0;

// Encode the payload
//for every character c in the payload
    for (char c: payload) {
        int block_length = find_boundary(message, start);
//if block_length == -1
        if (block_length == -1) {
            throw std::runtime_error("");
        }
//throw an error
        // block = substring of message starting at start, block_length chars in length
        std::string block = message.substr(start, block_length);

        //append encode_char(block, c) to ret
        ret += encode_char(block, c);
        //increase start by block_length
        start += block_length;
    }
// Encode a null terminator
    int block_length = find_boundary(message, start);
    //if (block_length == -1)
    //throw an error
    if (block_length == -1) {
        throw std::runtime_error("");
    }
    std::string block = message.substr(start, block_length);
    ret += encode_char(block, '\0');
    start += block_length;
    //append encode_char(block, '\0') to ret
    //increase start by block_length

// Add remainder of message
//remainder = substring of message starting at start, going to the end of the string append remainder to ret
    ret += message.substr(start);
    return ret;
}

void test_encode_string() {
    //Encoding "" into "abcdefgh" should be "abcdefgh"
    if (encode_string("", "abcdefgh") != "abcdefgh") {
        std::cout << R"(Error encoding "" into "abcdefgh" was not "abcdefg". It encoded )"
                  << encode_string("", "abcdefgh") << "\n";
    }

    if (encode_string("A", "abcdefghstuvwxyz") != "aBcdefgHstuvwxyz") {
        std::cout << R"(Error encoding "A" into "abcdefgHstuvwxyz" was not "aBcdefgHstuvwxyz". It encoded )"
                  << encode_string("A", "abcdefgHstuvwxyz") << "\n";
    }
    if (encode_string("a", "abcdefghstuvwxyz") != "aBCdefgHstuvwxyz") {
        std::cout << R"(Error encoding "a" into "abcdefgHstuvwxyz" was not "aBCdefgHstuvwxyz". It encoded )"
                  << encode_string("a", "abcdefgHstuvwxyz") << "\n";
    }

    if (encode_string("Hi!", "Few quips galvanized the mock jury box.") != "fEw qUips gALvAniZed The moCk jury box.") {
        std::cout
                << R"(Error encoding "Hi!" into "Few quips galvanized the mock jury box." was not "fEw qUips gALvAniZed The moCk jury box.". It encoded )"
                << encode_string("Hi!", "Few quips galvanized the mock jury box.") << "\n";
    }
    if (encode_string("A", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != "aBcdefgHijklmnopQRSTUVWXYZ") {
        std::cout
                << R"(Error encoding "A" into "ABCDEFGHIJKLMNOPQRSTUVWXYZ" was not "aBcdefgHijklmnopQRSTUVWXYZ". It encoded )"
                << encode_string("A", "ABCDEFGHIJKLMNOPQRSTUVWXYZ") << "\n";
    }
}