#include <iostream>
#include <cctype>
#include <string>
#include <fstream>

void test_encode_char();

void test_decode_char();

void test_find_boundary();

void test_encode_string();

void test_decode_string();

std::string encode_char(std::string block, char payload);

char decode_char(std::string block);

int find_boundary(std::string message, int start);

std::string encode_string(std::string message, std::string payload);

std::string decode_string(std::string message);

std::string read_file(std::string filename);

void write_file(std::string filename, std::string message);

int main() {
    // function testing
    test_encode_char();
    test_decode_char();
    test_find_boundary();
    test_encode_string();
    test_decode_string();


    std::string message = read_file("input.txt");
    std::string payload = read_file("payload.txt");
    std::string encoded = encode_string(message, payload);
    write_file("encoded.txt", encoded);
    std::string read_encoded = read_file("encoded.txt");
    std::string recovered = decode_string(read_encoded);

    if (payload == recovered) {
        std::cout << "Success\n";
    } else {
        std::cout << "Failure\n";
    }


    return 0;
}

void test_encode_char() {
    // Simple cases
    if (encode_char("abcdefgh", 'A') != "aBcdefgH") {
        std::cout << "Error: In encode char, input 'abcdefgh', 'A' returned '" << encode_char("abcdefgh", 'A') << "'\n";
    }
    if (encode_char("abcdefgh", 'a') != "aBCdefgH") {
        std::cout << "Error: In encode char, input 'abcdefgh', 'a' returned '" << encode_char("abcdefgh", 'a') << "'\n";
    }

    // Expect failure if not enough characters provided
    try {
        std::string foo = encode_char("abcdefg", 'A');
        std::cout << "Error: In encode char, did not throw error when attempted to encode a char into"
                     " a string that was not long enough\n";
    } catch (...) {}

    // Cases with special characters in strings (whitespace etc)
    if (encode_char("a b c d e f g h", 'A') != "a B c d e f g H") {
        std::cout << "Error: In encode char, input 'a b c d e f g h', 'A' returned '"
                  << encode_char("a b c d e f g h", 'A') << "'\n";
    }
    if (encode_char("a\tbcdefgh", 'A') != "a\tBcdefgH") {
        std::cout << "Error: In encode char, input 'a\tbcdefgh', 'A' returned '"
                  << encode_char("a\tbcdefgh", 'A') << "'\n";
    }
    if (encode_char("a\nbcdefgh", 'A') != "a\nBcdefgH") {
        std::cout << "Error: In encode char, input 'a\nbcdefgh', 'A' returned '"
                  << encode_char("a\nbcdefgh", 'A') << "'\n";
    }

}

void test_decode_char() {
    if (decode_char("aBcdefgH") != 'A') {
        std::cout << "Error: In decode char, input \"aBcdefgH\", returned '" << decode_char("aBcdefgH") << "'\n";
    }
    if (decode_char("aBCdefgH") != 'a') {
        std::cout << "Error: In decode char, input 'aBCdefgH' returned '" << decode_char("aBCdefgH") << "'\n";
    }
    try {
        char foo = decode_char("abcdefg");
        std::cout << "Error: In decode char, did not throw error when attempted to encode a char into"
                     " a string that was not long enough\n";
    } catch (...) {}

    // Cases with special characters in strings (whitespace etc)
    if (decode_char("a B c d e f g H") != 'A') {
        std::cout << "Error: In decode char, input 'a B c d e f g H'"
                  << decode_char("a B c d e f g H") << "'\n";
    }
    if (decode_char("a\tBcdefgH") != 'A') {
        std::cout << "Error: In decode char, input 'a\tBcdefgH' returned "
                  << decode_char("a\tBcdefgH") << "'\n";
    }
    if (decode_char("a\nBcdefgH") != 'A') {
        std::cout << "Error: In decode char, input 'a\nBcdefgH' returned '"
                  << decode_char("a\nBcdefgH") << "'\n";
    }
}

void test_find_boundary() {
    if (find_boundary("abcdefgh", 0) != 8) {
        std::cout << "Error find_boundary of 'abcdefgh' starting at 0 doesn't return 8" << "\n";
    }
    if (find_boundary("abc   defgh", 0) != 11) {
        std::cout << "Error find_boundary of \"abc   defgh\" with a start of 0 doesn't return 11" << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 0) != 9) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 0 doesn't return 9"
                << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 9) != 9) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 9 doesn't return 9"
                << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 18) != 10) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 18 doesn't return 10"
                << "\n";
    }
    if (find_boundary("Few quips galvanized the mock jury box.", 28) != 10) {
        std::cout
                << "Error find_boundary of \"Few quips galvanized the mock jury box.\" with a start of 0 doesn't return 9"
                << "\n";
    }

}

void test_encode_string() {
    if (encode_string("abcdefgh", "") != "abcdefgh") {
        std::cout << R"(Error encoding "" into "abcdefgh" was not "abcdefg". It encoded )"
                  << encode_string("abcdefgh", "") << "\n";
    }

    if (encode_string("abcdefghstuvwxyz", "A") != "aBcdefgHstuvwxyz") {
        std::cout << R"(Error encoding "A" into "abcdefgHstuvwxyz" was not "aBcdefgHstuvwxyz". It encoded)"
                  << encode_string("abcdefghstuvwxyz", "A") << "\n";
    }
    if (encode_string("abcdefghstuvwxyz", "a") != "aBCdefgHstuvwxyz") {
        std::cout << R"(Error encoding "a" into "abcdefgHstuvwxyz" was not "aBCdefgHstuvwxyz". )" << "\n";
    }

    if (encode_string("Few quips galvanized the mock jury box.", "Hi!") != "fEw qUips gALvAniZed The moCk jury box.") {
        std::cout
                << R"(Error encoding "Hi!" into "Few quips galvanized the mock jury box." was not "fEw qUips gALvAniZed The moCk jury box.")"
                << "\n";
    }
    if (encode_string("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "A") != "aBcdefgHijklmnopQRSTUVWXYZ") {
        std::cout
                << R"(Error encoding "A" into "ABCDEFGHIJKLMNOPQRSTUVWXYZ" was not "aBcdefgHijklmnopQRSTUVWXYZ".)"
                << "\n";
    }
}

void test_decode_string() {

    if (decode_string("aBcdefgHstuvwxyz") != "A") {
        std::cout << R"(Error decoding "A" from "aBcdefgHstuvwxyz")" << "\n";
    }
    /*if (decode_string("aBCdefghstuvwxyz") != "a") {
        std::cout << R"(Error decoding "a" from "aBCdefgHstuvwxyz")" << "\n";
    }*/

    if (decode_string("fEw qUips gALvAniZed The moCk jury box.") != "Hi!") {
        std::cout
                << R"(Error decoding "Hi!" from "Few quips galvanized the mock jury box.")" << "\n";
    }
    if (decode_string("aBcdefgHijklmnopQRSTUVWXYZ") != "A") {
        std::cout
                << R"(Error decoding "A" from "aBcdefgHijklmnopQRSTUVWXYZ" )"
                << "\n";
    }

}

std::string encode_char(std::string block, char payload) {
    int current = 0;
    int length = block.length();

    for (int offset = 7; offset >= 0; --offset) {

        // Find the next alphabetic character
        while (!std::isalpha(block[current]) && current < length) {
            ++current;
        }

        // Ensure we haven't walked past the end of the block
        if (current >= length) {
            throw std::runtime_error("Current is bigger than Length");
        }
        // Fix the output case
        if ((payload >> offset) & 0x1) {
            block[current] = std::toupper(block[current]);
        } else {
            block[current] = std::tolower(block[current]);
        }
        ++current;
    }
    return block;

}

char decode_char(std::string block) {
    char ret = 0;
    int remaining = 8; // number of letters we are still looking for

    // Go through every character in the message
    //for every character c in the block
    for (char c : block) {
        // Verify it is a letter, otherwise ignore it
        //if c is an alphabetic letter
        if (std::isalpha(c)) {
            --remaining;

            // If it is upper case, that indicates a 1.
            //otherwise we can ignore it
            //if c is upper case
            //set the remaining bit of ret to 1

            if (std::isupper(c)) {
                ret |= 1 << remaining;
            }

            // If we found all the bits we are looking for, stop
            if (remaining == 0) {
                break;
            }
        }
    }
    //if we didn't find all the characters we needed
    //throw en error
    if (remaining != 0) {
        throw std::runtime_error("Not all characters discovered");
    }

    return ret;
}

int find_boundary(std::string message, int start) {
    int offset = 0;
    int remaining = 8;
    while (remaining > 0) {
        if (start + offset >= message.length()) {
            return -1;
        }
        if (std::isalpha(message[start + offset])) {
            --remaining;
        }
        ++offset;

    }
    return offset;
}

std::string encode_string(std::string message, std::string payload) {
    std::string ret;
    int start = 0;

// Encode the payload
    for (char c: payload) {
        int block_length = find_boundary(message, start);
        if (block_length == -1) {
            throw std::runtime_error("First error in encode_string");
        }
        std::string block = message.substr(start, block_length);
        ret += encode_char(block, c);
        start += block_length;
    }
    int block_length = find_boundary(message, start);
    if (block_length == -1) {
        throw std::runtime_error("Second error in encode_string");
    }
    std::string block = message.substr(start, block_length);
    ret += encode_char(block, '\0');
    start += block_length;
    ret += message.substr(start);
    return ret;
}

std::string decode_string(std::string message) {
    std::string ret;
    int start = 0;
    for (;;) {
        int block_length = find_boundary(message, start);
        if (block_length == -1) {
            throw std::runtime_error("First error in decode_string");
        }
        std::string block = message.substr(start, block_length);
        int c = decode_char(block);
        if (c == '\0') {
            break;
        }
        ret += c;
        start += block_length;
    }
    return ret;
}

std::string read_file(std::string filename) {
    std::ifstream in(filename);

    if (!in.is_open()) {
        throw std::runtime_error("Could not open file for reading");
    }

    std::string result;

    while (!in.eof()) {
        char c = in.get();

        if (in.gcount() != 1) {
            // Hit EOF
            break;
        }

        result += c;
    }
    in.close();

    return result;
}

void write_file(std::string filename, std::string message) {
    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    out << message;

    out.close();
}