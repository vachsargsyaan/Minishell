/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:16:49 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/02 17:16:45 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_char(int fd, int c)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_char(int fd, const char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!str)
	{
		return (write(fd, "(null)", 6));
	}
	while (str[i])
	{
		write(fd, &str[i], 1);
		i++;
		len++;
	}
	return (len);
}

int	ft_printnum(int fd, int num)
{
	long	nb;
	int		i;

	nb = num;
	i = 0;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
		i++;
	}
	if (nb > 9)
	{
		i += ft_printnum(fd, (nb / 10));
		i += ft_printnum(fd, (nb % 10));
	}
	else
	{
		nb += 48;
		write(fd, &nb, 1);
		i++;
	}
	return (i);
}

int	ft_it(int fd, unsigned int num)
{
	long				nb;
	unsigned int		i;

	nb = num;
	i = 0;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
		i++;
	}
	if (nb > 9)
	{
		i += ft_it(fd, (nb / 10));
		i += ft_it(fd, (nb % 10));
	}
	else
	{
		nb += 48;
		write(fd, &nb, 1);
		i++;
	}
	return (i);
}
