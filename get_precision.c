#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
/**
 * get_precision - a program that calculates the precision
 * @format:format of a string
 * @i: input arguments
 * @list: list of arguments of tthe function
 * Return: precision
 */
int get_precision(const char *format, int *i, va_list list)
{
	int precision = -1;
	int r = *i + 1;

	if (format[r] == '.')
	{
		return (precision);
	}

	precision = 0;
	r += 1;
	while (format[r] != '\0')
	{
		if (is_digit(format[r]))
		{
			precision *= 10;
			precision += format[r] - '0';
			r++;
		}
		else if (format[r] == '*')
		{
			r++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
		r++;
	}
	*i = r - 1;

	return (precision);
}
