#include <stdio.h>
#include "main.h"
/**WRITE HANDLE */
/**
 * handle_write_char - function that Prints a string
 * @flags:  used to Calculates active flags.
 * @c: character types to be printed.
 * @buffer: the character buffer to print to
 * @size: the total size of the character buffer
 * @precision: the precision of the printed character
 * @width: the minimum width of the printed character
 *
 * Return: Number of characters printed.
 */
int handle_write_char(char c, char buffer[],
		int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}
/**WRITE NUMBER*/
/**
 * write_number - function that Prints a string
 * @size: total size of the character buffer
 * @ind: the current index of the character buffer
 * @precision: the precision of the printed number
 * @flags: Calculates active flags
 * @width: the minimum width of the printed number, padded
 * @buffer: the character buffer to print to
 * @is_negative: indicates if the number is negative
 *
 * Return: Number of characters printed.
 */
int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
				length, padd, extra_ch));
}
/**
 * write_num - Writes a no using a buffer & specified width, precision,padding.
 * @ind: Index at which the number starts on the buffer.
 * @buffer: Buffer to store the number.
 * @flags: Flags that modify the behavior of the function.
 * @width: Minimum width of the output.
 * @prec: Precision specifier for numeric conversions.
 * @length: Length of the number.
 * @padd: Padding character to use for the output.
 * @extra_c: Extra character to include in the output
 *
 * Return: Number of printed characters.
 */
int write_num(int ind, char buffer[],
		int flags, int width, int prec,
		int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}
/**
 * write_unsgnd -  Writes an unsigned number to the output buffer
 * @is_negative: unused parameter (indicates if number is negative)
 * @buffer: character array to store the formatted output
 * @ind: starting index in the buffer to write the number
 * @width: minimum width of the formatted output
 * @flags: flags specifier for formatting options
 * @size: unused parameter (specifies the size of the number)
 * @precision: minimum number of digits to display (padded with zeros)
 *
 * Return: Number of characters written to the output stream
 */
int write_unsgnd(int is_negative, int ind,
		char buffer[],
		int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}
/**
 * write_pointer - Writes memory address to buffer & prints to stdout
 * @buffer: Array of characters to store the formatted output
 * @ind: Index in the buffer at which the number starts
 * @length: Length of the memory address
 * @width: Minimum width of the output
 * @flags: Flags specifying output format
 * @padd: Character representing the padding
 * @extra_c: Character representing any extra flags
 * @padd_start: Index at which padding should start
 *
 * Return: Number of characters written to stdout
 */
int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
