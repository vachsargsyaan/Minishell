/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 17:50:05 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/31 17:21:12 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(int fd, const char *s, va_list args)
{
	int	i;

	i = 0;
	if (*s == 'c')
		i += ft_print_char(fd, va_arg(args, int));
	else if (*s == 's')
		i += ft_char(fd, va_arg(args, char *));
	else if (*s == 'p')
		i += ft_print_point(fd, va_arg(args, unsigned long long));
	else if (*s == 'i' || *s == 'd')
		i += ft_printnum(fd, va_arg(args, int));
	else if (*s == 'u')
		i += ft_it(fd, va_arg(args, unsigned int));
	else if (*s == 'x' || *s == 'X')
		i += ft_print_hex(fd, va_arg(args, unsigned int), *s);
	else if (*s == '%')
	{
		i += 1;
		write(fd, "%", 1);
	}
	return (i);
}

char	*printf_strchr(const char *str, int c)
{
	char	*buf;

	buf = (char *)str;
	while (*buf)
	{
		if (*buf == (unsigned char)(c & 0xFF))
			return (buf);
			buf++;
	}
	if (*buf == c)
		return (buf);
	else
		return (NULL);
}

char	*on_ft(int fd, char *s, va_list args, int *count)
{
	if (*s == '%')
	{
		s++;
		while (*s && !printf_strchr(FORMAT_FLAGS, *s)
			&& !printf_strchr(ESCAPE_SEQ, *s))
				s++;
		if (printf_strchr(FORMAT_FLAGS, *s))
			*count += check_flag(fd, s, args);
		else if (printf_strchr(ESCAPE_SEQ, *s))
		{
			write (fd, s, 1);
			(*count)++;
		}
		s++;
	}
	return (s);
}

int	ft_dprintf(int fd, const char *str, ...)
{
	va_list	args;
	int		count;
	char	*tmp;
	char	*s;

	va_start(args, str);
	if (!str)
		return (0);
	count = 0;
	s = (char *)str;
	while (*s)
	{
		tmp = on_ft(fd, s, args, &count);
		if (tmp == s)
		{
			write(fd, s, 1);
			s++;
			count++;
		}
		else
			s = tmp;
	}
	va_end(args);
	return (count);
}

t_init	init(int argc, char **argv, char **env)
{
	t_init	pars;

	(void)argv;
	(void)env;
	if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: non-interactive mode is not \
supported.\n");
		exit(EXIT_FAILURE);
	}
	pars.lex = NULL;
	pars.pars = NULL;
	pars.temp = NULL;
	pars.path = NULL;
	pars.flag = -42;
	return (pars);
}
