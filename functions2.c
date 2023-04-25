#include "main.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
/**
 * print_pointer - a program that prints a pointer value
 * @types: types of arguments
 * @buffer: storage for arrays
 * @flags:  active flags
 * @width: width of the function
 * @precision: precision for function
 * @size: size of function
 * Return: pointer value
 */
int print_pointer(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
	unsigned long base_len;
	void *len = va_arg(types, void *);
	int result = BUFF_SIZE - 2, length = 2, padd_start = 1;
	char ext_x = 0, padd = ' ';
	char map_to[] = "0123456789abcdef";

	UNUSED(size);
	UNUSED(width);

	if (len == NULL)
	{
		fputs("(nil)", stdout);
		return (5);
	}
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	base_len = (unsigned long)len;

	for (; base_len > 0; base_len /= 16, result--, length++)
	{
		buffer[result] = map_to[base_len % 16];
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		ext_x = '+', length++;
	else if (flags & F_SPACE)
		ext_x = ' ', length++;

	result++;
	return (write_pointer(buffer, result, length, width, flags,
				padd, ext_x, padd_start));
}
/**
 * print_non_printable - a program that prints a non-printable
 * character
 * @types: types of arguments
 * @buffer: storage for arrays
 * @flags:  active flags
 * @width: width of the function
 * @precision: precision for function
 * @size: size of function
 * Return: non-printable character
 */
int print_non_printable(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
	char *str = va_arg(types, char *);
	int i = 0, offset = 0;

	UNUSED(precision);
	UNUSED(size);
	UNUSED(flags);
	UNUSED(width);

	if (str == NULL)
		return (write(1, "(null)", 6));

	for (i = 0; str[i] != '\0'; i++)
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}
/**
 * print_reverse - a program that prints a reverse string
 * @types: types of arguments
 * @buffer: storage for arrays
 * @flags:  active flags
 * @width: width of the function
 * @precision: precision for function
 * @size: size of function
 * Return: reverse
 */
int print_reverse(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
	char *chr;
	int i, count = 0;

	UNUSED(size);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);

	chr = va_arg(types, char *);

	if (chr == NULL)
	{
		UNUSED(precision);

		chr = ")Null(";
	}
	for (i = 0; chr[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = chr[i];

		write(1, &z, 1);
		count++;
	}

	return (count);
}
/**
 * print_rot13string - a program that prints a rot13 string
 * @types: types of arguments
 * @buffer: storage for arrays
 * @flags:  active flags
 * @width: width of the function
 * @precision: precision for function
 * @size: size of function
 * Return: rot13 string
 */
int print_rot13string(va_list types, char buffer[], int flags,
int width, int precision, int size)
{
	int count = 0;
	char a;
	char *chr;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";
	unsigned int i, j;

	chr = va_arg(types, char *);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(buffer);
	UNUSED(size);

	if (chr == NULL)
		chr = "(AHYY)";

	i = 0;
	j = 0;

	while (chr[i] != '\0')
	{
		for (j = 0; in[j] != '\0'; j++)
		{
			if (chr[j] == in[j])
			{
				a = out[j];
				write(1, &a, 1);
				count++;
				break;
			}
		}
		i++;
	}
	if (!in[j])
	{
		a = chr[j];
		write(1, &a, 1);
		count++;
	}

	return (count);
}