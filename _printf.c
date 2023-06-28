#include "main.h"

/**
  *_printf - displays to the stdout according to a format
  *@format: format string containg the characters and specifiers
  *Description: This function calls get_print(). get_priint() function
  *determines what to print depending on the format
  *specifiers contained in @fmt
  *Return: length of the formatted output string.
  */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0) {
		int i;
		for (i = 0; i < *buff_ind; i++) {
			_putchar(buffer[i]);
		}
	}
	*buff_ind = 0;
}

int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++) {
		if (format[i] != '%') {
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE) {
				print_buffer(buffer, &buff_ind);
			}
			printed_chars++;
		} else {
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buffer(buffer, &buff_ind);

	va_end(list);

	return (printed_chars);
}
