#include <libms.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>

int main()
{
	ms_state_t st;
	ms_bin_seq_read_t mbr;
	ms_bin_ret_t retm;
	int ms[5 * 5];
	int i;
	char *uri, *str;
	int len;

	printf("Content-Type: text/plain\r\n");

	uri = getenv("REQUEST_URI");
	if (uri == NULL) {
		printf("\r\n");
		printf("error: invalid request URI\n");
		exit(EXIT_FAILURE);
	}

	str = basename(uri);
	len = strlen(str);
	if (len <= 4) {
		printf("\r\n");
		printf("error: request URI too short\n");
		exit(EXIT_FAILURE);
	}
	if (strncmp(str + len - 4, ".txt", 4)) {
		printf("\r\n");
		printf("error: request URI does not end with \".txt\"\n");
		exit(EXIT_FAILURE);
	}
	str[len - 3] = 'b';
	str[len - 2] = 'i';
	str[len - 1] = 'n';

	ms_init(5, MS_ORIGIN_ONE, &st);
	ms_bin_seq_read_open(str, MS_BIN_SEQ_READ_FLAG_NONE, &mbr, &st);
	printf("Content-Length: %llu\r\n", mbr.total * (1 * (9 - 1 + 1) + 2 * (25 - 10 + 1) + 1 * (25 - 1) + 1));
	printf("\r\n");
	ms_bin_seq_read_set_buffer(5224 * 8, &mbr, &st);
	do {
		retm = ms_bin_seq_read_next(ms, &mbr, &st);
		for (i = 0; i < 5 * 5 - 1; i ++)
			printf("%d ", ms[i]);
		printf("%d\n", ms[5 * 5 - 1]);
	} while (retm != MS_BIN_RET_EOF);
	ms_bin_seq_read_close(&mbr, &st);
	ms_finalize(&st);

	return 0;
}
