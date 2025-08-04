/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 11:53:34 by cade-oli          #+#    #+#             */
/*   Updated: 2024/10/26 14:38:26 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = (unsigned char *) b;
	while (n > 0)
	{
		*(tmp++) = (unsigned char) c;
		n--;
	}
	return (b);
}
