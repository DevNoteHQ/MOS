

extern "C" {
	#include <c_string.hpp>
	
	uint32_t strlen(const char *s) {
		int i = 0;
		while (*s++)
		i++;
		return i;
	}

	char *strncpy(char *destString, const char *sourceString,uint32_t maxLength) {
		unsigned count;

		if ((destString == (char *) NULL) || (sourceString == (char *) NULL)) {
			return (destString = NULL);
		}

		if (maxLength > 255)
		maxLength = 255;

		for (count = 0; (int)count < (int)maxLength; count ++) {
			destString[count] = sourceString[count];
			
			if (sourceString[count] == '\0')
			break;
		}

		if (count >= 255) {
			return (destString = NULL);
		}

		return (destString);
	}

	int strcmp(const char *dst, const char *src) {
		int i = 0;

		while ((dst[i] == src[i])) {
			if (src[i++] == 0)
			return 0;
		}

		return 1;
	}


	char *strcpy(char *dst,const char *src) {
		int i = 0;
		do {
			dst[i] = src[i];
			i++;
		} while (src[i] != '\0');
		
		return (char*) i;
	}

	char *strcat(char *dest, const char *src) {
		memcpy((char*)((int)dest+(int)strlen((char*)dest)),(char*)src,strlen((char*)src));
	}

	int strncmp( const char* s1, const char* s2, uint32_t c ) {
		int result = 0;

		while ( c ) {
			result = *s1 - *s2++;

			if ( ( result != 0 ) || ( *s1++ == 0 ) ) {
				break;
			}

			c--;
		}

		return result;
	}
}