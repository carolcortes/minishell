/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:00:09 by cade-oli          #+#    #+#             */
/*   Updated: 2024/11/06 10:16:05 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*result;

	s_len = ft_strlen(s);
	result = (char *)malloc((s_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < s_len)
		result[i] = (*f)(i, s[i]);
	result[i] = '\0';
	return (result);
}
