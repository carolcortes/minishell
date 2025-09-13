/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 16:58:26 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Em src/execution/execute_pipeline.c
#include "../../inc/minishell.h"

// Variável global para o último status (declarada no main.c)
extern int g_last_status;  // ✅ Declara que usa a variável global

void	execute_pipeline(t_command *pipeline, char **envp)
{
	int pipe_fd[2];
	int input_fd = STDIN_FILENO;
	pid_t pid;
	t_command *cmd = pipeline;
	pid_t last_pid = 0;

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
			// Redirecionar entrada (do pipe anterior ou stdin)
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}

			// Redirecionar saída (para o próximo pipe ou stdout)
			if (cmd->next)
			{
				dup2(pipe_fd[1], STDOUT_FILENO);
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
				// execute_external agora retorna int
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
				g_last_status = WEXITSTATUS(status); // Status normal de saída
			else if (WIFSIGNALED(status))
				g_last_status = 128 + WTERMSIG(status); // Terminado por sinal
		}
	}
}
