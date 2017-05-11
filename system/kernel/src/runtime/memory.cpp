


extern "C"
{
	#include <string.h>
	
	void *memcpy(void *dst, const void *src, size_t len)
	{
		char *dst8 = (char *) dst;
		const char *src8 = (char *) src;

		while (len--)
		*dst8++ = *src8++;

		return dst;
	}

	/*
*/
	void *memset(void *ptr, int value, size_t len)
	{
		// TODO: volatile is a hacky workaround, gcc 4.8.0 at -O3 seems to optimize
		// away most of the code here...
		volatile char *ptr8 = (volatile char *) ptr;

		while (len--)
		*ptr8++ = value;

		return ptr;
	}

	void *memmove(void *dst, const void *src, size_t len)
	{
		if (src == dst)
		return dst;

		const void *src_end = (const void *) ((uintptr_t) src + len);
		if (src < dst && dst < src_end)
		{
			char *dst8 = (char *) dst;
			const char *src8 = (const char *) src;

			for (ptrdiff_t i = len - 1; i >= 0; i--)
			dst8[i] = src8[i];

			return dst;
		}

		return memcpy(dst, src, len);
	}

	int memcmp(const void *ptr1, const void *ptr2, size_t len)
	{
		const unsigned char *p1 = (const unsigned char *) ptr1;
		const unsigned char *p2 = (const unsigned char *) ptr2;

		while (len--)
		{
			if (*p1 != *p2)
			return *p1 - *p2;

			p1++;
			p2++;
		}

		return 0;

	}

	void *memclr(void *ptr, size_t len)
	{
		return memset(ptr, 0, len);
	}
}