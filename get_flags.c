#include <stdio.h>
#include "main.h"
/**
 * get_flags - function that Calculates active flags.
 * @i: Pointer to the current position in the format string.
 * @format: Formatted string in which to print the arguments
 * Return: Flags:
 */
int get_flags(const char *format, int *i)
{
	int  a, cu_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	cu_i = *i + 1;
	while (format[cu_i] != '\0')
	{
		for (a = 0; FLAGS_CH[a] != '\0'; a++)
		{
			if (format[cu_i] == FLAGS_CH[a])
			{
				flags |= FLAGS_ARR[a];
				break;
			}
		}
		if (FLAGS_CH[a] == '\0')
			break;

		cu_i++;
	}

	*i = cu_i - 1;

	return (flags);
}
