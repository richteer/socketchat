#ifndef _aes_h_
#define _aes_h_

#define AES_KEY_SIZE 16


int aes_init(char* key,char *iv);
void aes_close(void);
int aes_encrypt(char* buffer, size_t bufsize);
int aes_decrypt(char* buffer, size_t bufsize);
void aes_random_key(char* key);

#endif