#include <string.h>
#include <Arduino.h>

class Console
{
public:
	const char EOL = '\n';

	Console();
	size_t write(const char* buffer, size_t size);
	size_t print(const char* string);
	size_t println(const char* string);
};

