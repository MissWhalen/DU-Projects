#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
    int ReceiveAndEnvelopeDecryptMessage(int src, EVP_PKEY *pri_key, byte *buffer, int buffer_size) {
        bytes_t iv, encrypted_key, ciphertext;
        int ret = FAILURE;

        byte *plaintext = NULL;
        int plaintext_len;

        // receive encrypted key, IV, and message
        if (ReceiveBytes(src, &encrypted_key) == FAILURE) {
            cout << "Failure receiving encrypt key" << endl;
        }
        if (ReceiveBytes(src, &iv) == FAILURE) {
            cout << "Failure receiving iv" << endl;
        }
        PrintBytes("Received IV: ", iv.value, iv.len);
        if (ReceiveBytes(src, &ciphertext) == FAILURE) goto done;

        // TODO: decrypt message
        plaintext = new byte[ciphertext.len + CIPHER_BLOCK_SIZE];
        if (EnvelopeDecryptMessage(pri_key, ciphertext.value, ciphertext.len, encrypted_key.value, encrypted_key.len,
                                   &iv.value, plaintext) == FAILURE) {
            cout << "decrypt message failure" << endl;
            goto done;
        }

        // TODO: copy plaintext to buffer
        //       you should copy as many bytes as the length of the plaintext
        //         but never more than buffer_size bytes
        memcpy(&plaintext, buffer, buffer_size);

        // TODO: set return value
        ret = SUCCESS;
        done:

        // cleanup
        if (plaintext) delete (plaintext);
        if (encrypted_key.value) delete (encrypted_key.value);
        if (ciphertext.value) delete (ciphertext.value);
        if (iv.value) delete (iv.value);

        return ret;
    }


}
