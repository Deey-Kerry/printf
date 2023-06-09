#include "main.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
/**
 * is_printable - this function checks if char is printable
 * @c: input
 * Return: character
 */
int is_printable(char c)
{
	if (c >= 32 && c <= 126)
		return (1);
	return (0);
}
/**
 * append_hexa_code - two decimal numbers
 * @ascii_code: American Standard Code
 * @buffer: storage device
 * @i: input
 * Return: hexa code
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii_code / 16];
	buffer[i] = map_to[ascii_code % 16];

	return (3);
}
/**
 * is_digit - this program checks for digits
 * @c: input character
 * Return: digit
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}
/**
 * convert_size_number - this function is use for conersion
 * @num: number to input
 * @size: size to be checked
 * Return: size
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}
/**
 * convert_size_unsgnd - this function converts size of unsigned
 * number
 * @num: number to be checked
 * @size: size to be checked
 * Return: unsigned number
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
