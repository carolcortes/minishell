/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:39:32 by cade-oli          #+#    #+#             */
/*   Updated: 2024/10/28 15:50:47 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	cc;
	unsigned char	*ss;

	cc = (unsigned char) c;
	ss = (unsigned char *) s;
	i = -1;
	while (++i < n)
		if (ss[i] == cc)
			return ((void *) &ss[i]);
	return (NULL);
}
