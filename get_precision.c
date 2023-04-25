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
	int p = -1;
	int cx_m = *i + 1;

	if (format[cx_m] == '.')
	{
		return (p);
	}
	else
	{
		return (p);
	}

	p = 0;
	while (format[cx_m] != '\0')
	{
		if (is_digit(format[cx_m]))
		{
			p *= 10;
			p += format[cx_m] - '0';
			cx_m++;
		} else if (format[cx_m] == '*')
		{
			cx_m++;
			p = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*i = cx_m - 1;

	return (p);
}
