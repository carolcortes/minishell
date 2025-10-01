/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 20:50:56 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/01 10:05:24 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*static int	count_args_until_pipe(t_token *tokens, int start_index)
{
	int	count;
	int	i;

	count = 0;
	i = start_index;
	while (tokens[i].value && !tokens[i].is_pipe)
	{
		count++;
		i++;
	}
	return (count);
}*/

static t_token	**copy_command_args(t_token *tokens, int start, int count)
{
	t_token	**args;
	int		i;

	args = malloc(sizeof(t_token *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i < count)
	{
		args[i] = &tokens[start + i];
		i++;
	}
	args[count] = NULL;
	return (args);
}

static t_command	*create_new_command(t_token *tokens, int i, int arg_count)
{
	t_command	*new_cmd;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->args = copy_command_args(tokens, i, arg_count);
	if (!new_cmd->args)
	{
		free(new_cmd);
		return (NULL);
	}
	new_cmd->argc = arg_count;
	new_cmd->redirs = NULL;
	new_cmd->redir_count = 0;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	return (new_cmd);
}

/*static int	add_command_to_pipeline(t_token *tokens, int *i,
	t_command **first, t_command **current)
{
	int			arg_count;
	t_command	*new_cmd;

	arg_count = count_args_until_pipe(tokens, *i);
	if (arg_count == 0)
		return (0);
	new_cmd = create_new_command(tokens, *i, arg_count);
	if (!new_cmd)
		return (0);
	if (!*first)
		*first = new_cmd;
	if (*current)
	{
		(*current)->next = new_cmd;
		new_cmd->prev = *current;
	}
	*current = new_cmd;
	*i += arg_count;
	return (1);
}*/

static int	add_command_to_pipeline(t_token *tokens, int *i,
	t_command **first, t_command **current)
{
	int			arg_count;
	t_command	*new_cmd;

	arg_count = count_args_until_pipe(tokens, *i);
	if (arg_count == 0 || (tokens[*i].is_redirection && !tokens[*i + 1].value))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (0);
	}
	new_cmd = create_new_command(tokens, *i, arg_count);
	if (!new_cmd)
		return (0);
	if (!*first)
		*first = new_cmd;
	if (*current)
	{
		(*current)->next = new_cmd;
		new_cmd->prev = *current;
	}
	*current = new_cmd;
	*i += arg_count;
	return (1);
}

static void	extract_redirections_from_pipeline(t_command *pipeline)
{
	t_command	*current;

	current = pipeline;
	while (current)
	{
		extract_redirections(current);
		current = current->next;
	}
}

/*t_command	*parse_pipeline(t_token *tokens)
{
	t_command	*first;
	t_command	*current;
	int			i;

	if (!tokens || !tokens[0].value)
		return (NULL);
	first = NULL;
	current = NULL;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].is_pipe)
		{
			i++;
			continue ;
		}
		if (!add_command_to_pipeline(tokens, &i, &first, &current))
			break ;
	}
	extract_redirections_from_pipeline(first);
	return (first);
}*/

static t_command	*remove_empty_commands(t_command *pipeline)
{
	t_command	*cur;
	t_command	*next;
	t_command	*head;
	//t_command	*head = pipeline;

	head = pipeline;
	cur = pipeline;
	while (cur)
	{
		next = cur->next;
		if (cur->argc == 0)
		{
			if (cur->prev)
				cur->prev->next = cur->next;
			if (cur->next)
				cur->next->prev = cur->prev;
			if (cur == head)
				head = cur->next;
			free(cur->args);
			free(cur);
		}
		cur = next;
	}
	return (head);
}

t_command	*parse_pipeline(t_token *tokens)
{
	t_command	*first;
	t_command	*current;
	int			i;

	if (!tokens || !tokens[0].value)
		return (NULL);
	first = NULL;
	current = NULL;
	i = 0;
	while (tokens[i].value)
	{
		if (tokens[i].is_pipe)
		{
			i++;
			continue ;
		}
		if (!add_command_to_pipeline(tokens, &i, &first, &current))
			break ;
	}
	extract_redirections_from_pipeline(first);
	return (remove_empty_commands(first));
}
