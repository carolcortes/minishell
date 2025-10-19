/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ext.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:32:55 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/19 10:27:24 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_child_process_single(t_command *cmd, t_shell *shell)
{
	if (!apply_redirections(cmd))
		return (1);
	if (is_builtin(cmd->args))
		return (exec_builtin(cmd->args, shell->envp));
	else
		return (execute_external(cmd->args, shell));
}

void	handle_parent_process(pid_t pid, t_shell *shell)
{
	int	status;

	setup_wait_signals();
	waitpid(pid, &status, 0);
	setup_signals();
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		if (WTERMSIG(status) == SIGQUIT)
			write(2, "Quit (core dumped)\n", 19);
		shell->last_status = 128 + WTERMSIG(status);
	}
}

char	*shell_read_line(void)
{
	char	*line;

	line = readline("minishell$> ");
	if (!line)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*line)
		add_history(line);
	return (line);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	printf("=== TOKENS PARSED ===\n");
	while (tokens[i].value)
	{
		printf("Token %d: '%s' (expand: %d, pipe: %d, redir: %d)\n",
			i, tokens[i].value, tokens[i].allow_expand,
			tokens[i].is_pipe, tokens[i].is_redirection);
		i++;
	}
	printf("=====================\n");
}

void	print_pipeline(t_command *pipeline)
{
	t_command	*cmd;
	int			cmd_index;
	int			i;

	cmd = pipeline;
	cmd_index = 0;
	printf("=== PIPELINE STRUCTURE ===\n");
	while (cmd)
	{
		printf("Command %d: ", cmd_index++);
		i = 0;
		while (i < cmd->argc)
		{
			printf("'%s' ", cmd->args[i]->value);
			i++;
		}
		printf("\n");
		cmd = cmd->next;
	}
	printf("==========================\n");
}
