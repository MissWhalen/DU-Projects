#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <gmp.h> // For using large numbers...
/**
 * encrypt takes plainText, e (public exponent) and N (public modulus)
 *         and returns the encrypted ciphertext. Allocates a buffer for
 *         the ciphertext which must be free'd by caller.
 */
uint32_t *encrypt (unsigned char *plainText, size_t len, uint32_t e, uint32_t N) {
    unsigned int i;
    uint32_t *cipherText;
    // mpz_t types are used for large numbers.
    // needed for exponentiation because we end up with bigger results than can be
    //stored
    mpz_t base;
    mpz_t exp;
    mpz_t ret;
    mpz_t n;
    // mpz_t types must be initialized
    mpz_init(base);
    mpz_init(exp);
    mpz_init(ret);
    // here we set the mpz_t variable 'n' to the value of our modulus, 'N'
    mpz_init_set_ui(n, N);
    // here we set the mpz_variable 'exp' to the value of our exponent, 'e'
    mpz_set_ui(exp, e);
    // Allocate space for ciphertext.
    // Note that while plaintext is an array of unsigned characters (1 byte each),
    // the ciphertext array is of 4-byte unsigned integers. This is because we can
    // have ciphertext values from 0-N (our modulus) where N > 255. We can only
    // have 255 possible byte values in our 8-bit unsigned char, so that won't do!
    // How could this be optimized in practice?
    cipherText = malloc(sizeof(uint32_t) * len);
    for (i = 0; i < len; i++) {
        // Set the mpz_t variable 'base' to the value of our plainText byte.
        // We cast it to a uint32_t, because that's what mpz_set_ui expects.
        mpz_set_ui(base, (uint32_t)plainText[i]);
        // mpz_powm takes the mpz_t value 'base', raises it to exponent 'exp'
        // takes the modulo of 'n', and stores the result into 'ret'
        // thus 'ret' is now our cipherText byte, as encrypted with the public key,
        // encoded as a number
        mpz_powm(ret, base, exp, n);
        //fprintf(stderr, "Result of exponentiation is %u\n", mpz_get_ui(ret));
        // mpz_get_ui takes a mpz_t value and gives us back an unsigned int. That way
        //we can store
        // the value in a regular type. As long as N is not greater than 2^32-1 we can
        //do this.
                    cipherText[i] = mpz_get_ui(ret);
        fprintf(stderr, "Plaintext char is %u, ciphertext char is %u\n",
                (uint32_t)plainText[i], (uint32_t)cipherText[i]);
    }
    return cipherText;
}
/**
 * decrypt takes cipherText, d (public exponent) and N (public modulus)
 *         and returns the decrypted plaintext. Allocates a buffer for
 *         the ciphertext which must be free'd by caller.
 */
char *decrypt (uint32_t *cipherText, size_t len, uint32_t d, uint32_t N) {
    char *plainText;
    plainText = malloc(len);
    // Implement decrypt functionality here!
    return plainText;
}
int main (int argc, char *argv[]) {
    // p and q are two primes, you can choose any two primes
    uint32_t p = 107;
    uint32_t q = 181;
    // N (modulus, provided as part of public key)
    uint32_t N = p * q;
    uint32_t r = (p - 1) * (q - 1);
    // K is a number that satisfies
    // K % r == 1
    // and is not prime. K is not used
    // as part of the private key or public key
    // but is used to find e and d (e and d are factors of K)
    // uint32_t K = 190801
    // e is the public exponent
    // e * d == K
    // (e * d) % r == 1 (obvious, since K % r == 1)
    uint32_t e = 169;
    // d is the private exponent
    // (d * e) % r == 1 (obvious, since K % r == 1)
    uint32_t d = 1129;
    unsigned char *plainText = "This is a test message to test the test of messages.";
    unsigned char *decryptedPlaintext = NULL;
    uint32_t *cipherText = NULL;
    printf("Original plaintext is `%s'\n", plainText);
    // Encrypt the plaintext and store the result into an array of uint32_t's
    (cipherText)
    // Note that you only need e and N (the public key!)
    cipherText = encrypt(plainText, strlen(plainText) + 1, e, N);
    // Decrypt the ciphertext and store the result into an array of unsigned char's
    (decryptedPlaintext)
    // Note that you only need d and N (the private key!)
    decryptedPlaintext = decrypt(cipherText, strlen(plainText) + 1, d, N);
    printf("Deciphered plaintext is `%s'\n", decryptedPlaintext);
    return 0;
}