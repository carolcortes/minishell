/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 22:35:42 by cade-oli          #+#    #+#             */
/*   Updated: 2025/12/03 11:37:10 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_strings(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_tokens(t_token *tokens)
{
	int	i;

	if (!tokens)
		return ;
	i = 0;
	while (tokens[i].value)
	{
		free(tokens[i].value);
		i++;
	}
	free(tokens);
}

char	*ft_strjoin_free(char *s1, char *s2, int mode)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (!result)
		return (NULL);
	if (mode == 1 || mode == 3)
		free(s1);
	if (mode == 2 || mode == 3)
		free(s2);
	return (result);
}

void	free_pipeline(t_command *pipeline)
{
	t_command	*current;
	t_command	*next;
	int			i;

	current = pipeline;
	while (current)
	{
		next = current->next;
		if (current->redirs && current->redir_count > 0)
		{
			i = 0;
			while (i < current->redir_count)
			{
				free(current->redirs[i].filename);
				i++;
			}
			free(current->redirs);
		}
		free(current->args);
		free(current);
		current = next;
	}
}
