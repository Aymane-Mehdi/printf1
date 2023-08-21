#include "main.h"

/**
 * print - This is the function in charge of parsing and printing out all arg
 * int the standar input output.
 * @format: A string containing all specifiers.
 * @conv_list: A list of converter functions ( specifiers ).
 * @arg_list: A list containing all the argumentents passed to the program.
 *
 * Return: A total count of the characters printed.
 */
int print(const char *format, conv_type conv_list[], va_list arg_list)
{
	int i, j, char_count, chars;

	chars = 0;
	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			for (j = 0; conv_list[j].spec != NULL; j++)
			{
				if (format[i + 1] == conv_list[j].spec[0])
				{
					char_count = conv_list[j].func(arg_list);
					if (char_count == -1)
						return (-1);
					chars += char_count;
					break;
				}
			}
			if (conv_list[j].spec == NULL && format[i + 1] != ' ')
			{
				if (format[i + 1] != '\0')
				{
				put_character(format[i]);
				put_character(format[i + 1]);
				chars += 2;
				}
				else
				return (-1);
			}
			i++;
		}
		else
		{
			put_character(format[i]);
			chars++;
		}
	}
	return (chars);
}

/**
 * _printf - The function to print to the console
 * @format: A string containing all the desired characters to print
 * and conversion specifiers
 *
 * Return: The length of the string to print
 */
int _printf(const char *format, ...)
{
	int char_count;
	conv_type conv_list[] = {
		{"c", print_character},
		{"s", print_string},
		{"d", print_integer},
		{"i", print_integer},
		{"b", print_bin},
		{"r", print_reverse_string},
		{"R", rotter},
		{"u", print_unsigned},
		{"o", print_octal_number},
		{"x", print_hexadecimal_lower},
		{"X", print_hexadecimal_upper},
		{"%", print_percentage},
		{"S", print_string_non_printable},
		{NULL, NULL}
	};

	va_list arg_list;

	if (format == NULL)
		return (-1);

	va_start(arg_list, format);

	char_count  = print(format, conv_list, arg_list);

	va_end(arg_list);

	return (char_count);
}
