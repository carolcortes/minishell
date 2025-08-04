/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:08:49 by cade-oli          #+#    #+#             */
/*   Updated: 2025/01/11 18:11:09 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_str(char *s)
{
	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

int	print_pointer(unsigned long ptr)
{
	int	len;

	len = 0;
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	len = 2 + print_hex(ptr);
	return (len);
}

int	print_num(long n)
{
	const char	*bc = "0123456789";
	int			len;

	len = 0;
	if (n < 0)
	{
		len += print_char('-');
		n = -n;
	}
	if (n >= 10)
		len += print_num(n / 10);
	len += print_char(bc[n % 10]);
	return (len);
}
