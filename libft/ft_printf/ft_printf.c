/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:37:02 by cade-oli          #+#    #+#             */
/*   Updated: 2025/01/11 18:09:07 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(++format))
			count += format_specifier(args, *format);
		else
		{
			ft_putchar_fd(*format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}

int	format_specifier(va_list arg, char type)
{
	if (type == 'c')
		return (print_char(va_arg(arg, int)));
	if (type == 's')
		return (print_str(va_arg(arg, char *)));
	if (type == 'p')
		return (print_pointer(va_arg(arg, unsigned long)));
	if (type == 'd' || type == 'i')
		return (print_num(va_arg(arg, int)));
	if (type == 'u')
		return (print_num(va_arg(arg, unsigned)));
	if (type == 'x')
		return (print_hex(va_arg(arg, unsigned int)));
	if (type == 'X')
		return (print_uphex(va_arg(arg, unsigned int)));
	ft_putchar_fd(type, 1);
	return (1);
}
