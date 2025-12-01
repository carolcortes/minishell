/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_ext2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:36:21 by cgross-s          #+#    #+#             */
/*   Updated: 2025/11/25 22:15:56 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	handle_child_process_single(t_command *cmd, t_shell *shell, t_token *tokens)
{
	if (!apply_redirections(cmd, shell, tokens))
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

void	execute_with_redirections(t_command *cmd, t_shell *shell,
	t_token *tokens)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		setup_child_signals();
		exit(handle_child_process_single(cmd, shell, tokens));
	}
	else if (pid > 0)
		handle_parent_process(pid, shell);
	else
	{
		perror("minishell: fork");
		shell->last_status = 1;
	}
}
