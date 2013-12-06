int aes_init(char* key,char *iv);
int aes_close();
int aes_encrypt(char* buffer, int bufsize);
int aes_decrypt(char* buffer, int bufsize);
void aes_random_key(char* key);