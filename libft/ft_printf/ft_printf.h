/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cade-oli <cade-oli@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 11:36:54 by cade-oli          #+#    #+#             */
/*   Updated: 2025/04/12 16:58:07 by cade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

int	format_specifier(va_list arg, char type);
int	print_char(char c);
int	print_str(char *s);
int	print_pointer(unsigned long ptr);
int	print_num(long n);
int	print_hex(unsigned long n);
int	print_uphex(unsigned long n);

#endif
