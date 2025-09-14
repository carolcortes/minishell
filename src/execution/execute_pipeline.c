/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/14 20:14:39 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "../../inc/minishell.h"

extern int g_last_status;

void	execute_pipeline(t_command *pipeline, char **envp)
{
	int			pipe_fd[2];
	int			input_fd = STDIN_FILENO;
	pid_t		pid;
	t_command	*cmd = pipeline;
	pid_t		last_pid = 0;
	int			prev_pipe_read = -1;

	// Executar cada comando na pipeline
	while (cmd)
	{
		// Criar pipe para todos os comandos exceto o último
		if (cmd->next && pipe(pipe_fd) == -1)
		{
			perror("minishell: pipe");
			g_last_status = 1;
			return;
		}

		pid = fork();
		if (pid == 0) // Processo filho
		{
			// Fechar o lado de leitura do pipe anterior (se houver)
			if (prev_pipe_read != -1)
				close(prev_pipe_read);
			
			// Redirecionar entrada (do pipe anterior ou stdin)
			if (input_fd != STDIN_FILENO)
			{
				if (dup2(input_fd, STDIN_FILENO) == -1)
				{
					perror("minishell: dup2 stdin");
					exit(1);
				}
				close(input_fd);
			}

			// Redirecionar saída (para o próximo pipe ou stdout)
			if (cmd->next)
			{
				if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
				{
					perror("minishell: dup2 stdout");
					exit(1);
				}
				close(pipe_fd[0]);
				close(pipe_fd[1]);
			}

			// Executar o comando
			if (is_builtin(cmd->args))
			{
				int exit_status = exec_builtin(cmd->args, envp);
				exit(exit_status);
			}
			else
			{
				int exit_status = execute_external(cmd->args, envp);
				exit(exit_status);
			}
		}
		else if (pid < 0) // Erro no fork
		{
			perror("minishell: fork");
			g_last_status = 1;
			return;
		}

		// Processo pai: guardar PID do último processo
		if (pid > 0)
			last_pid = pid;

		// Fechar file descriptors não mais necessários
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		
		if (cmd->next)
		{
			close(pipe_fd[1]); // Fechar escrita do pipe atual
			input_fd = pipe_fd[0]; // Salvar leitura para próximo comando
		}
		else
			input_fd = STDIN_FILENO;

		cmd = cmd->next;
	}

	// Esperar todos os processos filhos e capturar status do ÚLTIMO
	int status;
	pid_t waited_pid;

	while ((waited_pid = wait(&status)) > 0)
	{
		if (waited_pid == last_pid) // Este é o último comando da pipeline
		{
			if (WIFEXITED(status))
				g_last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_last_status = 128 + WTERMSIG(status);
		}
	}
}
*/

#include "../../inc/minishell.h"

extern int	g_last_status;

static void	redirect_input(int input_fd)
{
	if (input_fd != STDIN_FILENO)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
		{
			perror("minishell: dup2 stdin");
			exit(1);
		}
		close(input_fd);
	}
}

static void	redirect_output(int pipe_fd[2])
{
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 stdout");
		exit(1);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	execute_command(t_command *cmd, char **envp)
{
	int	exit_status;

	if (is_builtin(cmd->args))
	{
		exit_status = exec_builtin(cmd->args, envp);
		exit(exit_status);
	}
	else
	{
		exit_status = execute_external(cmd->args, envp);
		exit(exit_status);
	}
}

static void	handle_child_process(t_command *cmd, int input_fd, 
	int pipe_fd[2], char **envp)
{
	redirect_input(input_fd);
	if (cmd->next)
		redirect_output(pipe_fd);
	execute_command(cmd, envp);
}

static void	process_command(t_command *cmd, int *input_fd, 
	int pipe_fd[2], pid_t *last_pid, char **envp)
{
	pid_t	pid;

	if (cmd->next && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		g_last_status = 1;
		return ;
	}
	pid = fork();
	if (pid == 0)
		handle_child_process(cmd, *input_fd, pipe_fd, envp);
	else if (pid < 0)
	{
		perror("minishell: fork");
		g_last_status = 1;
		return ;
	}
	if (pid > 0)
		*last_pid = pid;
	if (*input_fd != STDIN_FILENO)
		close(*input_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*input_fd = pipe_fd[0];
	}
	else
		*input_fd = STDIN_FILENO;
}

static void	wait_for_children(pid_t last_pid)
{
	int		status;
	pid_t	waited_pid;

	waited_pid = 1;
	while (waited_pid > 0)
	{
		waited_pid = wait(&status);
		if (waited_pid == last_pid)
		{
			if (WIFEXITED(status))
				g_last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				g_last_status = 128 + WTERMSIG(status);
		}
	}
}

void	execute_pipeline(t_command *pipeline, char **envp)
{
	int			pipe_fd[2];
	int			input_fd;
	t_command	*cmd;
	pid_t		last_pid;

	input_fd = STDIN_FILENO;
	cmd = pipeline;
	last_pid = 0;
	while (cmd)
	{
		process_command(cmd, &input_fd, pipe_fd, &last_pid, envp);
		if (g_last_status == 1)
			return ;
		cmd = cmd->next;
	}
	wait_for_children(last_pid);
}
