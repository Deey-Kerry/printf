#include "main.h"
#include <stdlib.h>
#include <stdio.h>
/**
 * print_char - a function that prints a char
 * @types: types of arguments
 * @buffer: storage for the function print
 * @flags: active flags
 * @width: Width of function
 * @precision: precision for funtion
 * @size: size of function
 * Return: chars
 */
int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char x = va_arg(types, int);

	return (handle_write_char(x, buffer, flags, width, precision, size));
}
/**
 * print_string - a function that prints a string
 * @types: types of arguments
 * @buffer: storage for the function print
 * @flags: active flags
 * @width: Width of function
 * @precision: precision for funtion
 * @size: size of function
 * Return: string
 */
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char *str = va_arg(types, char *);
	int k = 0;
	int i;

	UNUSED(width);
	UNUSED(precision);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(flags);

	if (!str)
	{
		str = precision >= 6 ? "      " : "(null)";
	}
	while (str[k] != '\0')
		k++;
	if (precision >= 0)
	{
		k = (precision < k) ? precision : k;
	}
	i = 0;

	if (width > k)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], k);
			for (i = width - k; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			i = width - k;
			for (i = width - k; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], k);
			return (width);
		}
	} return (write(1, str, k));
}
/**
 * print_percent - a function that prints a percent
 * @types: types of arguments
 * @buffer: storage for the function print
 * @flags: active flags
 * @width: Width of function
 * @precision: precision for funtion
 * @size: size of function
 * Return: percent
 */
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(width);
	UNUSED(precision);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(flags);
	UNUSED(types);

	return (write(1, "%%", 1));
}
/**
 * print_int - a function that prints an int
 * @types: types of arguments
 * @buffer: storage for the function print
 * @flags: active flags
 * @width: Width of function
 * @precision: precision for funtion
 * @size: size of function
 * Return: integer
 */
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	long int h = va_arg(types, long int);
	unsigned long int len;
	int is_negative = 0;
	int i = BUFF_SIZE - 2;

	h = convert_size_number(h, size);

	if (h == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	len = (unsigned long int)h;

	while (h < 0)
	{
		len = (unsigned long int)((-1) * h);
		is_negative = 1;
		break;
	}
	while (len > 0)
	{
		buffer[i--] = (len % 10) + '0';
		len /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
/**
 * print_binary - a function that prints a binary number
 * @types: types of arguments
 * @buffer: storage for the function print
 * @flags: active flags
 * @width: Width of function
 * @precision: precision for funtion
 * @size: size of function
 * Return: binary
 */
int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int count;
	unsigned int g, h, i, add;
	unsigned int y[32];

	UNUSED(width);
	UNUSED(precision);
	UNUSED(buffer);
	UNUSED(size);
	UNUSED(flags);

	h = va_arg(types, unsigned int);
	g = 2147483648; /* (2 ^ 31) */
	y[0] = h / g;

	i = 1;

	while (i < 32)
	{
		g /= 2;
		y[i] = (h / g) % 2;
		i++;
	}
	i = 0, add = 0, count = 0;
	while (i < 32)
	{
		add += y[i];
		if (add || i == 31)
		{
			char z = '0' + y[i];

			write(1, &z, 1);
			count++;
		}
		i++;
	}
	return (count);
}
