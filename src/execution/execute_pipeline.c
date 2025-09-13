/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 20:19:13 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Em src/execution/execute_pipeline.c
/*#include "../../inc/minishell.h"

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
*/

/*#include "../../inc/minishell.h"

extern int g_last_status;

void execute_pipeline(t_command *pipeline, char **envp)
{

	printf("=== DEBUG PIPELINE START ===\n");

    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd = pipeline;
    pid_t last_pid = 0;

    // Executar cada comando na pipeline
    while (cmd)
    {
        printf("DEBUG: Processing command: %s\n", cmd->args[0]->value);
        printf("DEBUG: Has next command: %d\n", cmd->next != NULL);

        // Criar pipe para todos os comandos exceto o último
        if (cmd->next && pipe(pipe_fd) == -1)
        {
            perror("minishell: pipe");
            g_last_status = 1;
            return;
        }

		if (cmd->next)
			printf("DEBUG: Created pipe: read=%d, write=%d\n", pipe_fd[0], pipe_fd[1]);

        pid = fork();
        if (pid == 0) // Processo filho
        {

			
            // Redirecionar entrada (do pipe anterior)
            if (input_fd != STDIN_FILENO)
            {
                dup2(input_fd, STDIN_FILENO);
                close(input_fd);
            }

            // Redirecionar saída (para o próximo pipe - se houver)
            if (cmd->next)
            {
                dup2(pipe_fd[1], STDOUT_FILENO); // ✅ SAÍDA vai para o pipe
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

			printf("DEBUG CHILD: Command %s - input_fd: %d\n", 
				cmd->args[0]->value, input_fd);
			printf("DEBUG CHILD: Has next: %d\n", cmd->next != NULL);

			if (cmd->next)
			{
				printf("DEBUG CHILD: STDOUT_FILENO = %d (should be pipe write end)\n", STDOUT_FILENO);
				printf("DEBUG CHILD: Writing test message to STDOUT...\n");
				write(STDOUT_FILENO, "CHILD_TEST_MESSAGE\n", 19);
			}
			else
			{
				printf("DEBUG CHILD: STDOUT_FILENO = %d (terminal)\n", STDOUT_FILENO);
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
        {
            last_pid = pid;
        }

        // Fechar file descriptors não mais necessários
        if (input_fd != STDIN_FILENO)
            close(input_fd);
        
        if (cmd->next)
        {
            close(pipe_fd[1]); // Fechar escrita do pipe atual
            input_fd = pipe_fd[0]; // Salvar leitura para próximo comando
        }
        else
        {
            input_fd = STDIN_FILENO;
        }

        cmd = cmd->next;
		printf("=== DEBUG PIPELINE END ===\n");
    }

    // Esperar todos os processos filhos e capturar status do ÚLTIMO
    int status;
    pid_t waited_pid;

    while ((waited_pid = wait(&status)) > 0)
    {
        if (waited_pid == last_pid) // Este é o último comando da pipeline
        {
            if (WIFEXITED(status))
            {
                g_last_status = WEXITSTATUS(status);
            }
            else if (WIFSIGNALED(status))
            {
                g_last_status = 128 + WTERMSIG(status);
            }
        }
    }
}*/

/*#include "../../inc/minishell.h"
#include <string.h> // Para strlen()

extern int g_last_status;

void execute_pipeline(t_command *pipeline, char **envp)
{
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd = pipeline;
    pid_t last_pid = 0;

    write(STDERR_FILENO, "=== PIPELINE START ===\n", 23);

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
            // Redirecionar entrada (do pipe anterior)
            if (input_fd != STDIN_FILENO)
            {
                if (dup2(input_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2 input failed");
                    exit(1);
                }
                close(input_fd);
            }

            // Redirecionar saída (para o próximo pipe - se houver)
            if (cmd->next)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 output failed");
                    exit(1);
                }
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // DEBUG SIMPLES E DIRETO (usando stderr)
            char debug_msg[100];
            int len = snprintf(debug_msg, 100, "CHILD: %s, STDIN=%d, STDOUT=%d\n", 
                              cmd->args[0]->value, STDIN_FILENO, STDOUT_FILENO);
            write(STDERR_FILENO, debug_msg, len);

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
        {
            last_pid = pid;
            char pid_msg[50];
            int len = snprintf(pid_msg, 50, "PARENT: Created child %d for %s\n", 
                              pid, cmd->args[0]->value);
            write(STDERR_FILENO, pid_msg, len);
        }

        // Fechar file descriptors não mais necessários
        if (input_fd != STDIN_FILENO)
            close(input_fd);
        
        if (cmd->next)
        {
            close(pipe_fd[1]); // Fechar escrita do pipe atual
            input_fd = pipe_fd[0]; // Salvar leitura para próximo comando
        }
        else
        {
            input_fd = STDIN_FILENO;
        }

        cmd = cmd->next;
    }

    write(STDERR_FILENO, "=== WAITING FOR CHILDREN ===\n", 30);

    // Esperar todos os processos filhos
    int status;
    pid_t waited_pid;

    while ((waited_pid = wait(&status)) > 0)
    {
        char wait_msg[50];
        int len = snprintf(wait_msg, 50, "PARENT: Child %d finished\n", waited_pid);
        write(STDERR_FILENO, wait_msg, len);
        
        if (waited_pid == last_pid) // Este é o último comando da pipeline
        {
            if (WIFEXITED(status))
            {
                g_last_status = WEXITSTATUS(status);
            }
            else if (WIFSIGNALED(status))
            {
                g_last_status = 128 + WTERMSIG(status);
            }
        }
    }

    write(STDERR_FILENO, "=== PIPELINE END ===\n", 22);
}*/

/*#include "../../inc/minishell.h"
#include <string.h>

extern int g_last_status;

void execute_pipeline(t_command *pipeline, char **envp)
{
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd = pipeline;
    pid_t last_pid = 0;

    write(STDERR_FILENO, "=== PIPELINE START ===\n", 23);

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

        if (cmd->next)
        {
            char pipe_msg[50];
            int len = snprintf(pipe_msg, 50, "PIPE: read=%d, write=%d\n", 
                              pipe_fd[0], pipe_fd[1]);
            write(STDERR_FILENO, pipe_msg, len);
        }

        pid = fork();
        if (pid == 0) // Processo filho
        {
            // Debug ANTES dos redirecionamentos
            char pre_msg[100];
            snprintf(pre_msg, 100, "PRE: %s, stdin=%d, stdout=%d\n", 
                     cmd->args[0]->value, STDIN_FILENO, STDOUT_FILENO);
            write(STDERR_FILENO, pre_msg, strlen(pre_msg));

            // Redirecionar entrada (do pipe anterior)
            if (input_fd != STDIN_FILENO)
            {
                if (dup2(input_fd, STDIN_FILENO) == -1)
                {
                    perror("dup2 stdin failed");
                    exit(1);
                }
                close(input_fd);
            }

            // Redirecionar saída (para o próximo pipe - se houver)
            if (cmd->next)
            {
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                {
                    perror("dup2 stdout failed");
                    exit(1);
                }
                close(pipe_fd[0]);
                close(pipe_fd[1]);
            }

            // Debug DEPOIS dos redirecionamentos
            char post_msg[100];
            snprintf(post_msg, 100, "POST: %s, stdin=%d, stdout=%d\n", 
                     cmd->args[0]->value, STDIN_FILENO, STDOUT_FILENO);
            write(STDERR_FILENO, post_msg, strlen(post_msg));

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
        {
            last_pid = pid;
            char pid_msg[50];
            int len = snprintf(pid_msg, 50, "PARENT: Created child %d for %s\n", 
                              pid, cmd->args[0]->value);
            write(STDERR_FILENO, pid_msg, len);
        }

        // Fechar file descriptors não mais necessários
        if (input_fd != STDIN_FILENO)
            close(input_fd);
        
        if (cmd->next)
        {
            close(pipe_fd[1]); // Fechar escrita do pipe atual
            input_fd = pipe_fd[0]; // Salvar leitura para próximo comando
        }
        else
        {
            input_fd = STDIN_FILENO;
        }

        cmd = cmd->next;
    }

    write(STDERR_FILENO, "=== WAITING FOR CHILDREN ===\n", 30);

    // Esperar todos os processos filhos
    int status;
    pid_t waited_pid;

    while ((waited_pid = wait(&status)) > 0)
    {
        char wait_msg[50];
        int len = snprintf(wait_msg, 50, "PARENT: Child %d finished\n", waited_pid);
        write(STDERR_FILENO, wait_msg, len);
        
        if (waited_pid == last_pid)
        {
            if (WIFEXITED(status))
                g_last_status = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                g_last_status = 128 + WTERMSIG(status);
        }
    }

    write(STDERR_FILENO, "=== PIPELINE END ===\n", 22);
}*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:30:00 by cgross-s          #+#    #+#             */
/*   Updated: 2025/09/13 20:02:56 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <string.h>

extern int g_last_status;

void execute_pipeline(t_command *pipeline, char **envp)
{
    int pipe_fd[2];
    int input_fd = STDIN_FILENO;
    pid_t pid;
    t_command *cmd = pipeline;
    pid_t last_pid = 0;
    int prev_pipe_read = -1;

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
        {
            input_fd = STDIN_FILENO;
        }

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

