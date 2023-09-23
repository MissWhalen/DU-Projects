//
// Created by Briana on 2/15/2021.
//

#include "Cipher.h"
#include "Letter.h"
#include <iostream>

std::string read_file(std::string filename) {

    std::ifstream in(filename);

    if (!in.is_open()) {
        throw std::runtime_error(std::string{"Failed to open "} + filename);
    }

    std::string ret;
    while (!in.eof()) {
        // Use get to read a single char
        char c = static_cast<char> (in.get());

        // Verify read a single char
        if (in.gcount() == 1) {
            ret.push_back(c);
        }
    }
    in.close();


    return ret;
}

void write_file(std::string filename, std::string cipher_text) {

    std::ofstream out(filename);

    if (!out.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    out << cipher_text;

    out.close();
}


std::string encrypt(std::string plaintext, std::string key) {
    std::string ciphertext;
    unsigned counter = 0;

    for (auto c: plaintext) {
        if (isalpha(c)) {
            ciphertext += Letter(c) + Letter(key[counter]);
            ++counter;
            counter %= key.size();
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

void test_encrypt() {
    {
        std::string plaintext = "How vexingly quick daft zebras jump!";
        std::string key = "KEY";
        std::string expected = "Rsu fivsrevc oemau hypx xofpkw heqn!";
        std::string actual = encrypt(plaintext, key);
        if (actual != expected) {
            std::cout << "Error Actual does not match Expected";
        }
    }
    {
        std::string plaintext = "The quick brown fox jumps over 13 lazy dogs.";
        std::string key = "cryptii";
        std::string expected = "Vyc fnqkm spdpv nqo hjfxa qmcg 13 eiha umvl.";
        std::string actual = encrypt(plaintext, key);
        if (actual != expected) {
            std::cout << "Error Actual does not match Expected for encrypting";
        }
    }
    {
        std::string plaintext = "Jaded zombies acted quaintly but kept driving their oxen forward.";
        std::string key = "yellow";
        std::string expected = "Heopr vmqmtso ygepr msetyhhw ffe yanx ocwrgrr evagv zisj dschonb.";
        std::string actual = encrypt(plaintext, key);
        if (actual != expected) {
            std::cout << "Error Actual does not match Expected for encrypting";
        }
    }
}

std::string decrypt(std::string ciphertext, std::string key) {
    std::string plaintext;
    unsigned counter = 0;

    for (auto c: ciphertext) {
        if (isalpha(c)) {
            plaintext += Letter(c) - Letter(key[counter]);
            ++counter;
            counter %= key.size();
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

void test_decrypt() {
    {
        std::string ciphertext = "Rsu fivsrevc oemau hypx xofpkw heqn!";
        std::string key = "KEY";
        std::string expected = "How vexingly quick daft zebras jump!";
        std::string actual = decrypt(ciphertext, key);
        if (actual != expected) {
            std::cout << "Error Actual does not match Expected";
        }
    }
    {
        std::string ciphertext = "Vyc fnqkm spdpv nqo hjfxa qmcg 13 eiha umvl.";
        std::string key = "cryptii";
        std::string expected = "The quick brown fox jumps over 13 lazy dogs.";
        std::string actual = decrypt(ciphertext, key);
        if (actual != expected) {
            std::cout << "Error Actual does not match Expected";
        }
    }
    {
        std::string ciphertext = "Heopr vmqmtso ygepr msetyhhw ffe yanx ocwrgrr evagv zisj dschonb.";
        std::string key = "yellow";
        std::string expected = "Jaded zombies acted quaintly but kept driving their oxen forward.";
        std::string actual = decrypt(ciphertext, key);
        if (actual != expected) {
            std::cout << "Error Actual does not match Expected";
        }
    }
}
