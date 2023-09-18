/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dprintf_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 17:13:46 by vacsargs          #+#    #+#             */
/*   Updated: 2023/09/02 17:16:52 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
