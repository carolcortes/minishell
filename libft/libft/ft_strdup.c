/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:06:53 by cade-oli          #+#    #+#             */
/*   Updated: 2024/10/30 08:14:45 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ss;
	size_t	len;

	len = ft_strlen(s) + 1;
	ss = (char *)malloc(len);
	if (!ss)
		return (NULL);
	len = -1;
	while (s[++len])
		ss[len] = s[len];
	ss[len] = '\0';
	return (ss);
}
