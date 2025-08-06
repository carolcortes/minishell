/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:31:48 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/12 17:01:04 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ss;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ss = (char *)malloc((len + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	ft_strlcpy(ss, s1, ft_strlen(s1) + 1);
	ft_strlcat(ss, s2, len + 1);
	return (ss);
}
