#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	const char *message = "Hello, World!\n\r";
	size_t message_length = strlen(message);
	ssize_t bytes_written = write(STDOUT_FILENO, message, message_length);
	if (bytes_written == -1) {
		perror("Error writing file\n");
		return 1;
	}
	return 0;
}

