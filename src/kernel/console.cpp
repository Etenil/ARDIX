#include "console.h"

Console::Console() {
	Serial.begin(115200);
}

size_t Console::write(const char *buffer, size_t size) {
	size_t n = 0;
	while (size--) {
		n += Serial.write(*buffer++);
	}

	Serial.flush();

	return n;
}

size_t Console::print(const char* string) {
	return this->write(string, strlen(string));
}

size_t Console::println(const char* string) {
	size_t string_size = strlen(string) + 3;
	char temp_string[string_size];
	memset(temp_string, '\0', string_size);
	strcpy(temp_string, string);
	temp_string[string_size - 2] = '\r';
	temp_string[string_size - 1] = '\n';
	temp_string[string_size] = '\0'; // Just to be safe...
	return this->write((const char*)temp_string, string_size);
}

