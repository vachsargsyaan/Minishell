/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sghumash <sghumash@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 20:07:15 by sghumash          #+#    #+#             */
/*   Updated: 2024/02/01 16:48:57 by sghumash         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void					print_matrix(char *line);
char					*trim_zeroes(char *s);
unsigned long long int	ft_atll(char *str);
char					*ft_itul(long long n);
char					*zerocase(char *m);

char	*trim_zeroes(char *s)
{
	int		j;

	j = 0;
	if (s[j] == '-' || s[j] == '+')
		j++;
	if (s[j] == '0' || (s[j] == '0' && s[j + 1] == '0'))
	{
		while (s && s[j] != '\0')
		{
			while (s[j] != '\0' && s[j] == '0')
				j++;
			if (s[j] != '0')
				break ;
		}
		if (s[j] == '\0')
			return (ft_strdup("0"));
		return (ft_strdup(&s[j]));
	}
	return (ft_strdup(s));
}

unsigned long long int	ft_atll(char *str)
{
	long long	num;
	int			sign;
	int			i;

	sign = 1;
	num = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i] && ((str[i] == ' ') || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\f' || str[i] == '\v' || str[i] == '\n'))
		i++;
	if (str && str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

void	print_matrix(char *line)
{
	int		i;
	char	**matrix;

	i = 0;
	matrix = ft_split(line, ' ');
	if (!matrix)
		return ;
	while (matrix[i])
	{
		if (i)
			printf(" ");
		printf("%s", matrix[i]);
		i++;
	}
	free_matrix(matrix);
}

int	matrixlen(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return (0);
	while (matrix && matrix[i] != NULL)
		i++;
	return (i);
}
