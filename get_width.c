#include "main.h"
/**
 * get_width - a function that calculates the width
 * @format: way in which to print arguments.
 * @i: input
 * @list: list of arguments in program
 * Return: width for printing
 */
int get_width(const char *format, int *i, va_list list)
{
	int r;
	int w = 0;

	r = *i + 1;
	while (format[r] != '\0')
	{
		if (is_digit(format[r]))
		{
			w *= 10;
			w += format[r] - '0';
			r++;
		}
		else if (format[r] == '*')
		{
			r++;
			w = va_arg(list, int);
			break;
		}
	}
	*i = r - 1;

	return (w);
}
