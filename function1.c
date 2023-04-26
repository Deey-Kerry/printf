#include <stdio.h>
#include "main.h"

/** PRINT UNSIGNED NUMBER */
/**
 * print_unsigned - function that Prints an unsigned number
 * @flags:  Calculates active flags
 * @size: Used to specify the size
 * @precision: specifies the Precision
 * @width: gets the width
 * @buffer: Buffer array that handles print
 * @types: List a of arguments
 * Return: Number of characters to be printed.
 */
int print_unsigned(va_list types, char buffer[],
		int size, int flags, int width, int precision)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	do {
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	} while (num > 0);

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**PRINT UNSIGNED NUMBER IN OCTAL*/
/**
 * print_octal - Prints an unsigned number in octal starting  with zero
 * @types: A va_list containing the arguments to be printed
 * @buffer: A character array to store the output
 * @flags: An integer that contains various flag options
 * @width: An integer specifying the minimum field width
 * @precision: An integer specifying the precision of the output
 * @size: An integer specifying the size of the argument
 *
 * Return: The number of characters printed
 */
int print_octal(va_list types, char buffer[],
		int precision, int flags, int width, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	do {
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	} while (num > 0);

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	I++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/** PRINT UNSIGNED NUMBER IN HEXADECIMAL*/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @precision: The precision specifier
 * @flags: The active flags
 * @buffer: The buffer array to handle the print
 * @types: The list of arguments
 * @size: The size specifier
 * @width: The width specifier
 *
 * This function prints an unsigned number in hexadecimal notation, using the
 * characters "0123456789abcdef". It takes in a precision specifier, an active
 * flags variable, a buffer array, a list of arguments, a size specifier, and
 * a width specifier.
 * Return: number of characters printed.
 */
int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}
/**PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL*/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: List of arguments
 * @buffer: Buffer array used for printing
 * @width: Minimum width of the printed field
 * @precision: Minimum number of digits to be printed
 * @flags: Flags to modify the behavior of the function
 * @size: Length modifier specifying the size of the argument
 *
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list types, char buffer[],
		int width, int precision, int flags, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}
/** PRINT HEXADECIMAL NUMBERS IN LOWER OR UPPER CASE */
/**
 * print_hexa - Prints a hexadecimal number in lower or upper case
 * @types: List of arguments to be passed
 * @map_to: Array of characters used to map the number to hexadecimal notation
 * @buffer: Buffer array used for printing
 * @flags: Flags to modify the behavior of the function
 * @flag_ch: Character used for the '#' flag
 * @width: Minimum width of the printed field
 * @precision: Minimum number of digits to be printed
 * @size: Length modifier specifying the size of the argument
 *
 * Return: number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
		int flags, char flag_ch, int width, int precision, int size)
{
	int I = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[I--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	/* LOOP that Count the number of hexadecimal digits */
	int num_digits = 0;
	unsigned long int temp = num;

	while (temp > 0)
	{
		num_digits++;
		temp /= 16;
	}

	/* loop that Iterate over the digits in reverse order */
	for (int I = num_digits - 1; I >= 0; I--)
	{
		buffer[j--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[I--] = flag_ch;
		buffer[I--] = '0';
	}

	I++;

	return (write_unsgnd(0, I, buffer, flags, width, precision, size));
}
