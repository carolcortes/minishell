/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_ext2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:45:00 by cade-oli          #+#    #+#             */
/*   Updated: 2025/10/19 13:43:22 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*create_new_var(char *key, char *old_value, char *value)
{
	char	*new_value;
	char	*key_eq;
	char	*result;

	new_value = ft_strjoin(old_value, value);
	key_eq = ft_strjoin(key, "=");
	result = ft_strjoin(key_eq, new_value);
	free(new_value);
	free(key_eq);
	return (result);
}

int	append_to_existing(char **envp, int i, char *key, char *value)
{
	char	*old_value;
	char	*result;

	old_value = ft_strchr(envp[i], '=') + 1;
	result = create_new_var(key, old_value, value);
	free(envp[i]);
	envp[i] = result;
	return (0);
}
