/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:42:37 by cade-oli          #+#    #+#             */
/*   Updated: 2024/11/06 09:53:56 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	digit_len(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		n = -n;
		count++;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	const char	*digits = "0123456789";
	char		*a;
	int			len;
	long		nbr;

	nbr = n;
	len = digit_len(nbr);
	a = (char *)malloc((len + 1) * sizeof(char));
	if (!a)
		return (NULL);
	a[len--] = '\0';
	if (nbr < 0)
		nbr = -nbr;
	while (nbr > 0)
	{
		a[len--] = digits[nbr % 10];
		nbr /= 10;
	}
	if (n == 0)
		a[0] = '0';
	if (n < 0)
		a[0] = '-';
	return (a);
}
