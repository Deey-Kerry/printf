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
	int width = 0;

	r = *i + 1;
	while (format[r] != '\0')
	{
		if (is_digit(format[r]))
		{
			width *= 10;
			width += format[r] - '0';
			r++;
		}
		else if (format[r] == '*')
		{
			r++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = r - 1;

	return (width);
}
