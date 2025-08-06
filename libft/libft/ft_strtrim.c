/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 12:32:06 by cade-oli          #+#    #+#             */
/*   Updated: 2024/11/13 10:28:21 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	size_t	last_i;
	char	*result;

	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	last_i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[last_i]))
		last_i--;
	result = ft_substr(s1, i, (last_i - i + 1));
	return (result);
}
