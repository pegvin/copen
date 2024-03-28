#include "config.h"

#define CMD_SIZE (sizeof(commands)/sizeof(commands[0]))

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void _Usage(void) {
	printf("Usage: copen <path-to-file>\n");
}

int main(int argc, char** argv) {
	if (argc < 2) {
		_Usage();
		return 1;
	}

	const char* path = argv[1];
	size_t len = strlen(path);

	for (size_t i = 0; i < CMD_SIZE; i++) {
		const char* suffix = commands[i][0];
		size_t sLen = strlen(suffix);
		if (strncmp(suffix, path + len - sLen, sLen + 1 /* compare till NULL terminator */) == 0) {
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

