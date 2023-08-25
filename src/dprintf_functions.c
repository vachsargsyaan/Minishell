/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 12:16:49 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/25 12:32:47 by vacsargs         ###   ########.fr       */
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
		i += ft_printnum(fd,(nb / 10));
		i += ft_printnum(fd,(nb % 10));
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

static void	ft_hex(int fd, unsigned long long nb, const char format)
{
	unsigned long long	i;
	char				b;
	char				a;

	if (nb < 16)
	{
		i = nb;
		nb = 0;
	}
	else
	{
		i = nb % 16;
		nb /= 16;
	}
	if (nb > 0)
		ft_hex(fd, nb, format);
	b = "0123456789ABCDEF"[i];
	a = "0123456789abcdef"[i];
	if (format == 'X')
		write(fd, &b, 1);
	if (format == 'x')
		write(fd, &a, 1);
}
static int	ft_hex_len(unsigned long long nb)
{
	int	i;

	i = 0;
	while (nb != 0)
	{
		nb /= 16;
		i++;
	}
	return (i);
}

int	ft_print_hex(int fd, unsigned long long nb, const char format)
{
	if (nb == 0)
		return (write(fd, "0", 1));
	ft_hex(fd, nb, format);
	return (ft_hex_len(nb));
}

int	ft_print_point(int fd, unsigned long long lu)
{
	int					count;

	count = 0;
	if (!lu)
		return (ft_char(fd, "0x0"));
	count += ft_char(fd, "0x");
	count += ft_print_hex(fd, lu, 'x');
	return (count);
}