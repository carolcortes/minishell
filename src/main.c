/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgross-s <cgross-s@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 17:05:01 by cade-oli          #+#    #+#             */
/*   Updated: 2025/08/07 22:48:32 by cgross-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*cell_read_line(void)
{
	char	*buf;
	size_t	bufsize;
	char	cwd[BUFSIZ];

	buf = NULL;
	ft_getcwd(cwd, sizeof(cwd));
	printf(C"🏴‍☠️ %s 🐗"RST"$>", cwd);
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

int	main(void)
{
	char	*line;

	line = NULL;
	printbanner();
	while ((line = cell_read_line()) != NULL)
	{
		printf("%s\n", line);
	}
	return (EXIT_SUCCESS);
}

/*int	main(int ac, char **av)
{
	int	status;

	(void)ac;
	if (fork() == 0)
		execvp(av[1], av + 1);
	wait(&status);
	return (EXIT_SUCCESS);
}*/
