/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:02:36 by cade-oli          #+#    #+#             */
/*   Updated: 2024/10/28 15:13:07 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	cc;
	char	*result;

	i = -1;
	cc = (char) c;
	result = NULL;
	while (s[++i])
		if (s[i] == cc)
			result = ((char *) &s[i]);
	if (s[i] == cc)
		result = ((char *) &s[i]);
	return (result);
}
