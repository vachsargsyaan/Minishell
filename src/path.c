/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:52:02 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/12 16:56:10 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	find_path(t_init *init, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (temp)
	{
		if (ft_strcmp(temp->key, "PATH") == 0)
		{
			if (temp->flag)
				init->flag = 1;
			else
				init->flag = 0;
			break ;
		}
		temp = temp->next;
	}
	if (!init->path)
		init->path = ft_split(temp->data, ':');
}

char static	*find_cmdpath(char *cmd, char **path)
{
	char	*cmdpath;
	int		i;

	i = -1;
	cmdpath = NULL;
	if (cmd[0] == '\0')
		return (NULL);
	while (path && path[++i])
	{
		cmdpath = ft_strjoin(path[i], "/", 0);
		cmdpath = ft_strjoin(cmdpath, cmd, 1);
		if (access(cmdpath, X_OK | F_OK) == -1)
			free (cmdpath);
		else
			return (cmdpath);
	}
	return (NULL);
}

char	*check_cmd(t_init *init, t_parser *stack, char *cmd, char **path)
{
	char	*cmd_path;

	if (access(cmd, X_OK | F_OK) == -1 && ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
		{
			ft_dprintf(2, "minishell1: %s: No such file or directory\n", cmd);
			return (NULL);
		}
		ft_dprintf(2, "minishell: %s: Permission denied\n", cmd);
		stack->err_code = -1;
		return (NULL);
	}
	else if (access(cmd, X_OK) != -1 && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	cmd_path = find_cmdpath(cmd, path);
	if (!cmd_path)
	{
		ft_dprintf(2, "minishell: %s: command not found\n", cmd);
		return (NULL);
	}
	init->flag++;
	return (cmd_path);
}