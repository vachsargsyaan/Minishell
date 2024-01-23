/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 15:10:18 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/18 19:17:13 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mshell_unset(t_parser *stack, char **matrix, t_env *my_env);
int		check_unset(char *str);
void	builtins_error(char	*str, char *err);

int	mshell_unset(t_parser *stack, char **matrix, t_env *my_env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (matrix && matrix[++i])
	{
		if (check_unset(matrix[i]))
			stack->err_code = -1;
		tmp = my_env;
		while (tmp != NULL)
		{
			if (ft_strcmp(matrix[i], tmp->key) == 0)
			{
				tmp->flag = 1;
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (0);
}

int	check_unset(char *str)
{
	if (!ft_isalpha(str[0]) && str[0] != '_')
	{
		builtins_error("unset", str);
		return (1);
	}
	return (0);
}

void	builtins_error(char	*str, char *err)
{
	if (!ft_strcmp(str, "cd") && err == NULL)
		ft_dprintf(2, "cd: error retrieving current directory: %s%s\n", \
					"getcwd: cannot access parent directories: ", \
					"No such file or directory");
	else if (!ft_strcmp(str, "export") && err)
		ft_dprintf(2, "minishell: export: `%s': not a %s\n", \
					err, "valid identifier");
	else if (!ft_strcmp(str, "unset") && err)
		ft_dprintf(2, "minishell: unset: `%s': not a %s\n", \
					err, "valid identifier");
	g_exit_status_ = -42;
}
