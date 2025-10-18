/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_ext.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 10:41:54 by cgross-s          #+#    #+#             */
/*   Updated: 2025/10/18 20:28:30 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/**
 * @brief Helpers to open files for redirections.
 *
 * open_output_file: opens/creates an output file (append or truncate).
 * open_input_file: opens an input file read-only.
 *
 * @param filename Path to the file.
 * @param append For output: non-zero appends, zero truncates.
 * @return File descriptor (>= 0) on success; -1 on error (perror printed).
 */

int	open_output_file(char *filename, int append)
{
	int	flags;
	int	fd;

	if (append)
		flags = O_WRONLY | O_CREAT | O_APPEND;
	else
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}

int	open_input_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (-1);
	}
	return (fd);
}
