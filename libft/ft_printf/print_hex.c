/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 18:11:26 by cade-oli          #+#    #+#             */
/*   Updated: 2025/01/11 18:11:46 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned long n)
{
	const char	*bc = "0123456789abcdef";
	int			len;

	len = 0;
	if (n >= 16)
		len += print_hex(n / 16);
	len += print_char(bc[n % 16]);
	return (len);
}

int	print_uphex(unsigned long n)
{
	const char	*bc = "0123456789ABCDEF";
	int			len;

	len = 0;
	if (n >= 16)
		len += print_uphex(n / 16);
	len += print_char(bc[n % 16]);
	return (len);
}
