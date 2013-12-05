int cr_init(char* key,char *iv);
int cr_close();
int cr_encrypt(char* buffer);
int cr_decrypt(char* buffer);