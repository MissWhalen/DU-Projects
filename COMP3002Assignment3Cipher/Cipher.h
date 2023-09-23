//
// Created by Briana on 2/15/2021.
//

#ifndef COMP3002ASSIGNMENT3CIPHER_CIPHER_H
#define COMP3002ASSIGNMENT3CIPHER_CIPHER_H
#include <string>
#include <fstream>



    std::string read_file(std::string filename);
    void write_file(std::string filename, std::string cipher_text);

std::string encrypt(std::string plaintext, std::string key);
void test_encrypt();
std::string decrypt(std::string ciphertext, std::string key);
void test_decrypt();

#endif //COMP3002ASSIGNMENT3CIPHER_CIPHER_H
