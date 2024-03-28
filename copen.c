#include "config.h"

#define CMD_SIZE (sizeof(commands)/sizeof(commands[0]))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

static void _Usage(void) {
	printf("Usage: copen <path-to-file>\n");
}

static int _cmp(const char* s1, const char* s2, size_t len, int isCaseSensitive) {
	return isCaseSensitive ?
		(strncmp(s1, s2, len) == 0) :
		(strncasecmp(s1, s2, len) == 0);
}
static char* _dupstr(const char *src) {
    char* dst = malloc(strlen (src) + 1);
    if (dst == NULL) {
		return NULL;
	}
    strcpy(dst, src);

	return dst;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		_Usage();
		return 1;
	}

	const char* path = argv[1];
	size_t pathLen = strlen(path);

	for (size_t i = 0; i < CMD_SIZE; i++) {
		int isAMatch = 0;

		char* suffixList = _dupstr(commands[i][0]);
		size_t suffixListLen = strlen(suffixList);

		char* tok = strtok(suffixList, ",");
		size_t tokLen = 0;
		if (tok == NULL) {
			isAMatch = _cmp(suffixList, path + pathLen - suffixListLen, suffixListLen, case_sensitive);
			goto skipTokenIter;
		} else {
			tokLen = strlen(tok);
		}

		while (tok != NULL) {
			isAMatch = _cmp(tok, path + pathLen - tokLen, tokLen, case_sensitive);
			if (isAMatch) {
				break;
			}
			tok = strtok(NULL, ",");
		}

skipTokenIter:
		free(suffixList);
		suffixList = NULL;

		if (isAMatch) {
			#define cap 4096
			char cmd[cap] = {0};
			size_t cmdLen = 0;

			cmdLen += snprintf(cmd, cap, "%s ", commands[i][1]);
			cmdLen += snprintf(cmd + cmdLen, cap - cmdLen, "%s", path);

			system(cmd);
			return 0;
		}
	}
	printf("No command found to run for '%s'\n", path);

	return 0;
}

