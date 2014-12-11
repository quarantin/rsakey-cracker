#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/bio.h>

#define SIZE 8192

int main (int argc, char *argv[])
{
	BIO *mem;
	BIO *file;
	EVP_PKEY *pkey;

	FILE *fp;
	char *ptr;
	char pwd[SIZE];
	char key[SIZE];

	if (argc < 2) {
		fprintf(stderr, "Usage:\n\t%s <rsa key .pem>\n\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	fp = fopen(argv[1], "r");

	memset(key, 0x00, SIZE);

	SSL_library_init();

	file = BIO_new(BIO_s_file());
	BIO_set_fp(file, fp, BIO_CLOSE);
	BIO_read(file, key, SIZE);
	BIO_free(file);

	mem = BIO_new_mem_buf(key, -1);

	while (fgets(pwd, sizeof(pwd), stdin)) {

		ptr = strchr(pwd, '\n');
		if (ptr)
			*ptr = '\0';

		BIO_reset(mem);
		pkey = PEM_read_bio_PrivateKey(mem, NULL, NULL, (char *)pwd);

		if (pkey) {
			printf("\nPassphrase is: %s\n", pwd);
			goto end;
		}
	}

	printf("Passphrase not found.\n");
end:
	if (mem)
		BIO_free(mem);

	return EXIT_SUCCESS;
}

