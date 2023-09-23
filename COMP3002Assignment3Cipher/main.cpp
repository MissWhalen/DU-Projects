#include <iostream>
#include "Letter.h"
#include "Cipher.h"

int main() {
    std::cout << "Enter a one word cipher key: " << "\n";
    std::string key;
    std::cin >> key;
    std::string plaintext = read_file("Plaintext.txt");


    //Run key through encryption with plain text
    std::string cipher_text = encrypt(plaintext, key);

    //Output Encrypted text
    write_file("cipher_text", cipher_text);
    //Decrypt text and check against original plain text
    std::string ciphertext_out = read_file("cipher_text");

    std::string decrypted_text = decrypt(ciphertext_out, key);
    if (plaintext == decrypted_text){
        std::cout << "YAY!\n";
    } else{
        std::cout << "Bummer\n";
    }

    test_addition();
    test_subtraction();
    test_encrypt();
    test_decrypt();

    return 0;
}
