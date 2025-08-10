/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/08 19:32:15 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//#define SPACE	"\t\n\v\f\r "

char	*shell_read_line(void)
{
	char	*buf;
	size_t	bufsize;
	char	cwd[BUFSIZ];

	buf = NULL;
	ft_getcwd(cwd, sizeof(cwd));
	printf(C"🏴‍☠️:: %s 🐗"RST"$>", cwd);
	if (getline(&buf, &bufsize, stdin) == -1)
	{
		buf = NULL;
		if (feof(stdin))
		{
			printf(RED"[EOF]"RST);
			printf("TESTE");
		}
		else
			printf(RED"Getline failed"RST);
	}
	return (buf);
}

static bool	is_delim(char c)
{
	int	i;

	i = 0;
	while (SPACE[i])
	{
		if (c == SPACE[i])
			return (true);
		i++;
	}
	return (false);
}

char	**shell_split_line(char *line)
{
	int		i;
	char	*copy;
	char	**tokens;

	// Criar cópia editável da string
	copy = ft_strdup(line);
	if (!copy)
		return (NULL);

	// Substituir todos delimitadores por espaço
	i = 0;
	while (copy[i])
	{
		if (is_delim(copy[i]))
			copy[i] = ' ';
		i++;
	}

	// Agora podemos usar ft_split da libft
	tokens = ft_split(copy, ' ');

	free(copy);
	return (tokens);
}


int	main(void)
{
	char	*line;
	char	**args;
	int		i;

	line = NULL;
	printbanner();
	while ((line = shell_read_line()) != NULL)
	{
		args = shell_split_line(line);
		if (!args)
			continue;

		// Percorre e imprime cada argumento
		i = 0;
		while (args[i])
		{
			printf("arg[%d]: %s\n", i, args[i]);
			i++;
		}

		// Libera memória
		i = 0;
		while (args[i])
			free(args[i++]);
		free(args);
		free(line);
	}
	return (EXIT_SUCCESS);
}

/*int	main(void)
{
	char	*line;
	char	**args;
	int		i;

	i = 0;
	line = NULL;
	printbanner();
	while ((line = shell_read_line()) != NULL)
	{
		args = shell_split_line(line);
		//while (*args)
		//{

		//}
		//printf("%s\n", line);
	}
	return (EXIT_SUCCESS);
}*/

/*int	main(int ac, char **av)
{
	int	status;

	(void)ac;
	if (fork() == 0)
		execvp(av[1], av + 1);
	wait(&status);
	return (EXIT_SUCCESS);
}*/
